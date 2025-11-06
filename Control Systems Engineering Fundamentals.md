# Control Systems Engineering Fundamentals

## Table of Contents
1. [Control System Basics](#control-system-basics)
2. [PID Controller](#pid-controller)
3. [System Modeling](#system-modeling)
4. [Stability Analysis](#stability-analysis)
5. [Digital Control](#digital-control)
6. [State Machines](#state-machines)

---

## Control System Basics

### What is a Control System?

**Definition:**
A system that manages, commands, directs, or regulates the behavior of other systems to achieve desired outcomes.

**Goal:**
Maintain desired output (setpoint) despite disturbances and changes

---

### Open-Loop vs Closed-Loop

**Open-Loop Control:**
```
Input → [Controller] → [System] → Output
```
- No feedback
- Executes commands without checking results
- **Example:** Toaster timer, washing machine cycle
- **Pros:** Simple, cheap
- **Cons:** No correction for errors, sensitive to disturbances

**Closed-Loop Control (Feedback):**
```
Setpoint → [+] → [Controller] → [System] → Output
           ↑                              ↓
           └───── [Sensor] ←──────────────┘
           (Feedback)
```
- Uses feedback to correct errors
- **Example:** Thermostat, cruise control
- **Pros:** Accurate, robust to disturbances
- **Cons:** More complex, can be unstable

---

### Control System Components

1. **Setpoint (SP):** Desired value
2. **Process Variable (PV):** Actual measured value
3. **Error:** e = SP - PV
4. **Controller:** Calculates control action
5. **Actuator:** Applies control action (motor, heater, valve)
6. **Sensor:** Measures output

---

### Control System Examples

**Temperature Control:**
```
Setpoint: 25°C
Sensor: Thermistor
Controller: PID
Actuator: Heater/Cooler
Error: 25°C - 24°C = 1°C → Increase heating
```

**Motor Speed Control:**
```
Setpoint: 1000 RPM
Sensor: Encoder
Controller: PID
Actuator: Motor driver (PWM)
Error: 1000 - 980 = 20 → Increase PWM duty
```

---

## PID Controller

### What is PID?

**PID = Proportional + Integral + Derivative**

Most widely used industrial controller. Adjusts control output based on error to minimize it.

---

### The Three Terms

**1. Proportional (P):**
```
P = Kp × error
```
- Output proportional to **current error**
- **Effect:** Immediate response to error
- **Problem:** Steady-state error remains
- **Analogy:** Push harder when further from goal

**Example:**
- Error = 10°C, Kp = 2 → P = 20
- Error = 5°C, Kp = 2 → P = 10

---

**2. Integral (I):**
```
I = Ki × ∫error dt
```
- Output proportional to **accumulated error**
- **Effect:** Eliminates steady-state error
- **Problem:** Can cause overshoot (windup)
- **Analogy:** Remember past mistakes and compensate

**Example:**
- Persistent error of 1°C for 10 seconds
- Integral accumulates → increases output gradually

---

**3. Derivative (D):**
```
D = Kd × d(error)/dt
```
- Output proportional to **rate of error change**
- **Effect:** Predicts future error, provides damping
- **Problem:** Amplifies noise
- **Analogy:** Anticipate where you're going

**Example:**
- Error decreasing rapidly → D reduces output
- Prevents overshoot

---

### Complete PID Formula

```
u(t) = Kp × e(t) + Ki × ∫e(t)dt + Kd × de(t)/dt

Where:
u(t) = Control output
e(t) = Error (setpoint - measurement)
Kp, Ki, Kd = Tuning gains
```

---

### PID Behavior Visualization

**Response to Step Change (Setpoint = 100):**

```
Output
  110 ┤     ╱╲           ← Overshoot
      │    ╱  ╲
  100 ┤───╱────╲─────   ← Setpoint
      │  ╱      ╲___
   90 ┤ ╱
      │╱
    0 └────────────────→ Time
       ↑    ↑      ↑
      Rise  Peak  Settling
      Time  Time   Time
```

**P-only:** Fast response, steady-state error
**PI:** No steady-state error, some overshoot
**PID:** Fast, no overshoot, no steady-state error (ideal)

---

### Tuning PID Controllers

**Manual Tuning (Start from Zero):**

**Step 1: Start with P-only (Ki=0, Kd=0)**
1. Set Kp = 0.1, test
2. Gradually increase Kp until oscillation occurs
3. Reduce Kp to 60% of oscillation point

**Step 2: Add Integral (Ki)**
1. Start Ki = 0.01
2. Increase until steady-state error eliminated
3. If overshoot excessive, reduce Ki

**Step 3: Add Derivative (Kd)**
1. Start Kd = 0.001
2. Increase to reduce overshoot
3. Stop if system becomes jittery (noise amplification)

---

**Ziegler-Nichols Method:**

1. Set Ki = 0, Kd = 0
2. Increase Kp until sustained oscillation (Ku)
3. Measure oscillation period (Tu)
4. Calculate PID gains:

```
Kp = 0.6 × Ku
Ki = 2 × Kp / Tu
Kd = Kp × Tu / 8
```

---

### PID Implementation (C)

**Simple PID:**
```c
typedef struct {
    float Kp, Ki, Kd;
    float prev_error;
    float integral;
    float dt;  // Sample time
} PID;

float PID_Update(PID *pid, float setpoint, float measurement) {
    float error = setpoint - measurement;
    
    // Proportional
    float P = pid->Kp * error;
    
    // Integral
    pid->integral += error * pid->dt;
    float I = pid->Ki * pid->integral;
    
    // Derivative
    float derivative = (error - pid->prev_error) / pid->dt;
    float D = pid->Kd * derivative;
    
    // Save for next iteration
    pid->prev_error = error;
    
    return P + I + D;
}
```

---

**Anti-Windup PID:**
```c
float PID_Update_AntiWindup(PID *pid, float setpoint, float measurement) {
    float error = setpoint - measurement;
    
    float P = pid->Kp * error;
    
    // Integral with clamping
    pid->integral += error * pid->dt;
    if (pid->integral > MAX_INTEGRAL) pid->integral = MAX_INTEGRAL;
    if (pid->integral < MIN_INTEGRAL) pid->integral = MIN_INTEGRAL;
    float I = pid->Ki * pid->integral;
    
    float derivative = (error - pid->prev_error) / pid->dt;
    float D = pid->Kd * derivative;
    
    pid->prev_error = error;
    
    float output = P + I + D;
    
    // Clamp output
    if (output > MAX_OUTPUT) output = MAX_OUTPUT;
    if (output < MIN_OUTPUT) output = MIN_OUTPUT;
    
    return output;
}
```

---

### Common PID Problems & Solutions

**1. Integral Windup:**
- **Problem:** Integral term grows too large during saturation
- **Solution:** Clamp integral term, conditional integration

**2. Derivative Kick:**
- **Problem:** Sudden setpoint change causes derivative spike
- **Solution:** Calculate derivative on measurement, not error

**3. Noise Sensitivity:**
- **Problem:** Derivative amplifies measurement noise
- **Solution:** Low-pass filter on derivative term

**4. Steady-State Error:**
- **Problem:** Output doesn't reach setpoint
- **Solution:** Increase Ki (or add integral term)

---

## System Modeling

### Transfer Functions

**Definition:**
Mathematical representation of system input-output relationship in Laplace domain.

```
G(s) = Y(s) / U(s)

Where:
Y(s) = Output (Laplace)
U(s) = Input (Laplace)
s = Complex frequency
```

---

### First-Order Systems

**Transfer Function:**
```
G(s) = K / (τs + 1)

K = Steady-state gain
τ = Time constant
```

**Time Constant (τ):**
- Time to reach 63.2% of final value
- After 5τ, system ~99% settled

**Example: RC Circuit**
```
τ = R × C
K = 1 (unity gain)
```

**Step Response:**
```
y(t) = K × (1 - e^(-t/τ))
```

---

### Second-Order Systems

**Transfer Function:**
```
G(s) = ωn² / (s² + 2ζωn×s + ωn²)

ωn = Natural frequency
ζ = Damping ratio
```

**Damping Ratio (ζ):**
- **ζ < 0:** Unstable
- **ζ = 0:** Undamped (continuous oscillation)
- **0 < ζ < 1:** Underdamped (oscillates before settling)
- **ζ = 1:** Critically damped (fastest settling, no overshoot)
- **ζ > 1:** Overdamped (slow, no overshoot)

**Example: Mass-Spring-Damper**
```
m×ÿ + c×ẏ + k×y = F(t)

ωn = √(k/m)
ζ = c / (2√(km))
```

---

### Block Diagram Algebra

**Series (Cascade):**
```
[G1] → [G2] → [G3]
G_total = G1 × G2 × G3
```

**Parallel:**
```
    ┌─[G1]─┐
→ ──┤      ├─ → +
    └─[G2]─┘
G_total = G1 + G2
```

**Feedback Loop:**
```
    ┌─────────┐
→ [+]→ [G] ──┬→ Output
  ↑         │
  └←[H]←────┘
  
Closed-loop: G / (1 + G×H)
```

---

## Stability Analysis

### What is Stability?

**Stable System:**
- Bounded input → Bounded output
- Returns to equilibrium after disturbance
- Example: Ball in valley

**Unstable System:**
- Small disturbance → Runaway response
- Example: Ball on hill

---

### Routh-Hurwitz Criterion

**For characteristic equation:**
```
a_n×s^n + a_{n-1}×s^{n-1} + ... + a_1×s + a_0 = 0
```

**System is stable if:**
All coefficients positive AND all elements in first column of Routh array are positive.

**Example: Third-Order System**
```
s³ + 3s² + 3s + 1 = 0

Routh Array:
s³ │ 1   3
s² │ 3   1
s¹ │ 8/3 0
s⁰ │ 1

All first column positive → Stable
```

---

### Root Locus

**Shows how closed-loop poles move as gain K increases**

**Rules:**
- System stable if all poles in left half-plane (Re < 0)
- Poles on imaginary axis → marginally stable (oscillation)
- Poles in right half-plane → unstable

---

### Bode Plot

**Frequency response analysis**

**Two plots:**
1. Magnitude (dB) vs Frequency
2. Phase (degrees) vs Frequency

**Stability Margins:**
- **Gain Margin:** How much gain can increase before instability
- **Phase Margin:** Safety margin in phase (>45° good)

---

## Digital Control

### Sampling and Discretization

**Nyquist-Shannon Theorem:**
```
f_sample > 2 × f_max
```
Sample at more than twice the highest frequency to avoid aliasing.

**Practical:** Use 10× highest frequency

**Example:**
- Control loop bandwidth: 10 Hz
- Sample at: 100 Hz (10 ms period)

---

### Z-Transform

**Discrete-time equivalent of Laplace transform**

**Tustin (Bilinear) Approximation:**
```
s = (2/T) × (z - 1) / (z + 1)

T = Sample period
```

**Convert Continuous PID to Discrete:**
```
P[k] = Kp × e[k]

I[k] = I[k-1] + Ki × T × e[k]

D[k] = Kd × (e[k] - e[k-1]) / T
```

---

### Digital Filter Implementation

**Moving Average Filter (Low-Pass):**
```c
#define FILTER_SIZE 5

float moving_average(float new_value) {
    static float buffer[FILTER_SIZE] = {0};
    static uint8_t index = 0;
    
    buffer[index] = new_value;
    index = (index + 1) % FILTER_SIZE;
    
    float sum = 0;
    for (int i = 0; i < FILTER_SIZE; i++) {
        sum += buffer[i];
    }
    return sum / FILTER_SIZE;
}
```

**Exponential Moving Average (IIR):**
```c
float ema_filter(float new_value, float alpha) {
    static float filtered = 0;
    filtered = alpha * new_value + (1 - alpha) * filtered;
    return filtered;
}
// alpha = 0.1 → heavy filtering
// alpha = 0.9 → light filtering
```

---

## State Machines

### What is a State Machine?

**Definition:**
System that can be in one of finite number of states, transitions between states based on events/conditions.

**Components:**
1. **States:** Distinct modes of operation
2. **Transitions:** Rules for moving between states
3. **Events:** Triggers for transitions
4. **Actions:** What to do in each state

---

### State Machine Example: Traffic Light

**States:**
- RED
- YELLOW
- GREEN

**Transitions:**
- RED → GREEN (after 30s)
- GREEN → YELLOW (after 25s)
- YELLOW → RED (after 5s)

**Code:**
```c
typedef enum {
    STATE_RED,
    STATE_YELLOW,
    STATE_GREEN
} TrafficState;

TrafficState current_state = STATE_RED;
uint32_t state_timer = 0;

void traffic_light_update(void) {
    uint32_t current_time = HAL_GetTick();
    
    switch (current_state) {
        case STATE_RED:
            set_red_light(ON);
            set_yellow_light(OFF);
            set_green_light(OFF);
            
            if (current_time - state_timer > 30000) {
                current_state = STATE_GREEN;
                state_timer = current_time;
            }
            break;
            
        case STATE_GREEN:
            set_red_light(OFF);
            set_yellow_light(OFF);
            set_green_light(ON);
            
            if (current_time - state_timer > 25000) {
                current_state = STATE_YELLOW;
                state_timer = current_time;
            }
            break;
            
        case STATE_YELLOW:
            set_red_light(OFF);
            set_yellow_light(ON);
            set_green_light(OFF);
            
            if (current_time - state_timer > 5000) {
                current_state = STATE_RED;
                state_timer = current_time;
            }
            break;
    }
}
```

---

### State Machine Best Practices

1. **One state at a time:** System in exactly one state
2. **Clear transitions:** Well-defined conditions
3. **Entry/Exit actions:** Initialize/cleanup when entering/leaving
4. **Default case:** Handle unexpected states
5. **State timeout:** Prevent stuck states

---

### State Machine Pattern

**Table-Driven:**
```c
typedef struct {
    TrafficState current;
    Event event;
    TrafficState next;
    void (*action)(void);
} Transition;

Transition transitions[] = {
    {STATE_RED,    EVENT_TIMEOUT, STATE_GREEN,  NULL},
    {STATE_GREEN,  EVENT_TIMEOUT, STATE_YELLOW, NULL},
    {STATE_YELLOW, EVENT_TIMEOUT, STATE_RED,    NULL},
};
```

---

## Practical Control Examples

### Temperature Controller

```c
typedef struct {
    float Kp, Ki, Kd;
    float setpoint;
    float measurement;
    float integral;
    float prev_error;
    uint8_t heater_pwm;
} TempController;

void temp_control_update(TempController *tc) {
    // Read temperature from ADC
    uint16_t adc = ADC_Read();
    tc->measurement = adc_to_celsius(adc);
    
    // PID calculation
    float error = tc->setpoint - tc->measurement;
    
    tc->integral += error * SAMPLE_TIME;
    float derivative = (error - tc->prev_error) / SAMPLE_TIME;
    
    float output = tc->Kp * error + 
                   tc->Ki * tc->integral + 
                   tc->Kd * derivative;
    
    tc->prev_error = error;
    
    // Convert to PWM (0-100%)
    if (output > 100) output = 100;
    if (output < 0) output = 0;
    
    tc->heater_pwm = (uint8_t)output;
    TIM3->CCR1 = (tc->heater_pwm * TIM3->ARR) / 100;
}
```

---

### Motor Speed Controller

```c
typedef struct {
    PID pid;
    uint32_t encoder_count;
    uint32_t prev_count;
    float rpm_setpoint;
    float rpm_measured;
} MotorController;

void motor_control_update(MotorController *mc) {
    // Calculate speed from encoder
    uint32_t delta = mc->encoder_count - mc->prev_count;
    mc->rpm_measured = (delta * 60.0) / (SAMPLE_TIME * ENCODER_PPR);
    
    // PID update
    float pwm = PID_Update(&mc->pid, mc->rpm_setpoint, mc->rpm_measured);
    
    // Apply to motor
    if (pwm > 100) pwm = 100;
    if (pwm < -100) pwm = -100;
    
    if (pwm >= 0) {
        motor_set_direction(FORWARD);
        motor_set_pwm((uint8_t)pwm);
    } else {
        motor_set_direction(REVERSE);
        motor_set_pwm((uint8_t)(-pwm));
    }
    
    mc->prev_count = mc->encoder_count;
}
```

---

## Useful knowledges for Control System Engineering

**Q1: "Explain P, I, and D terms in your own words."**
**A:** P reacts to current error (immediate response), I eliminates persistent error (accumulates over time), D predicts future error based on trend (damping/smoothing).

**Q2: "When would you use only PI instead of full PID?"**
**A:** Most temperature control, pressure control. When derivative is too sensitive to noise or when response doesn't need aggressive damping.

**Q3: "What is integral windup and how to prevent it?"**
**A:** Integral term grows too large when output saturated, causing overshoot. Prevent by: clamping integral, conditional integration (stop when saturated), or back-calculation.

**Q4: "How do you choose sampling rate?"**
**A:** At least 10× the control loop bandwidth. For 1 Hz control, sample at 10 Hz minimum. Too slow misses dynamics, too fast wastes resources.

**Q5: "Difference between open-loop and closed-loop?"**
**A:** Open-loop: no feedback, simple but inaccurate. Closed-loop: uses feedback to correct errors, more complex but accurate and robust.

---

## Quick Reference

**PID Equation:**
```
u = Kp×e + Ki×∫e + Kd×(de/dt)
```

**Tuning Starting Points:**
```
Kp: Start 1, increase until oscillation
Ki: Kp / 10
Kd: Kp / 100
```

**Stability:**
```
All poles must have negative real part
Sample rate > 10 × bandwidth
```

**Digital PID:**
```
P[k] = Kp × e[k]
I[k] = I[k-1] + Ki × T × e[k]
D[k] = Kd × (e[k] - e[k-1]) / T
```

---

**Next: See MATLAB/Simulink examples for control system simulation and analysis!**
