# ⚡ EMBEDDED SYSTEMS ENGINEERING - FORMULAS CHEATSHEET ⚡

## ELECTRICAL CIRCUITS (電気回路)

### Ohm's Law
```
V = I × R
I = V / R
R = V / I
```

### Power
```
P = V × I
P = I² × R
P = V² / R
```

### Kirchhoff's Laws
```
KCL: ∑I_in = ∑I_out (at node)
KVL: ∑V = 0 (around loop)
```

### Resistors
```
Series:   R_total = R1 + R2 + R3 + ...
Parallel: 1/R_total = 1/R1 + 1/R2 + 1/R3 + ...
2 Parallel: R_total = (R1 × R2) / (R1 + R2)
```

### Capacitors
```
Q = C × V
E = ½ CV²
Series:   1/C_total = 1/C1 + 1/C2 + ...
Parallel: C_total = C1 + C2 + ...
```

### Inductors
```
V = L × (dI/dt)
E = ½ LI²
Series:   L_total = L1 + L2 + ...
Parallel: 1/L_total = 1/L1 + 1/L2 + ...
```

### Time Constants
```
RC Circuit: τ = R × C
RL Circuit: τ = L / R
63.2% charge at t = τ
99% settled at t = 5τ
```

### Voltage Divider
```
Vout = Vin × (R2 / (R1 + R2))
```

### Current Divider
```
I1 = Iin × (R2 / (R1 + R2))
```

### AC Circuits
```
V_rms = V_peak / √2 ≈ 0.707 × V_peak
Impedance: Z_C = 1 / (2πfC)
           Z_L = 2πfL
Resonance: f_r = 1 / (2π√(LC))
```

### LED Current Limiting
```
R = (V_supply - V_led) / I_led
```

---

## CONTROL SYSTEMS

### PID Controller
```
u(t) = Kp×e(t) + Ki×∫e(t)dt + Kd×de(t)/dt

Discrete:
P[k] = Kp × e[k]
I[k] = I[k-1] + Ki × T × e[k]
D[k] = Kd × (e[k] - e[k-1]) / T
```

### Transfer Function
```
G(s) = Y(s) / U(s)

First-Order:  G(s) = K / (τs + 1)
Second-Order: G(s) = ωn² / (s² + 2ζωn×s + ωn²)
```

### Time Response
```
Rise Time (tr): 10% to 90%
Settling Time (ts): Within 2% of final
Overshoot: (Peak - Final) / Final × 100%
```

### Stability
```
Closed-Loop: G_cl = G / (1 + GH)
All poles Re < 0 for stability
```

### Ziegler-Nichols Tuning
```
Kp = 0.6 × Ku
Ki = 2 × Kp / Tu
Kd = Kp × Tu / 8
```

### Sampling
```
Nyquist: f_sample > 2 × f_max
Practical: f_sample ≥ 10 × f_bandwidth
```

---

## EMBEDDED SYSTEMS

### Bit Manipulation
```
Set bit n:    x |= (1 << n)
Clear bit n:  x &= ~(1 << n)
Toggle bit n: x ^= (1 << n)
Read bit n:   (x & (1 << n))
```

### ADC Conversion
```
Digital = (V_in / V_ref) × (2^bits - 1)
V_in = (Digital / (2^bits - 1)) × V_ref

Example (12-bit, 3.3V ref):
V_in = (ADC_value / 4095) × 3.3
```

### PWM
```
Duty Cycle (%) = (ON_time / Period) × 100
Average Voltage = Duty_Cycle × V_supply

PWM Frequency = Clock / ((Prescaler + 1) × (ARR + 1))
Duty = (CCR / ARR) × 100%
```

### Timer Configuration
```
Prescaler = (Clock_Freq / Desired_Freq) - 1
Period (ARR) = Desired_Counts - 1
```

### UART Baud Rate
```
Baud_Rate = Clock_Freq / (16 × USARTDIV)
USARTDIV = Clock_Freq / (16 × Baud_Rate)
```

### Memory Sizes
```
1 KB = 1024 bytes
1 MB = 1024 KB = 1,048,576 bytes
1 GB = 1024 MB
```

---

## COMMUNICATION PROTOCOLS

### UART Frame
```
[Start(1)] [Data(8)] [Parity(0/1)] [Stop(1/2)]
Time per bit = 1 / Baud_Rate
```

### SPI Speed
```
Clock Freq = Master_Clock / Prescaler
Max Speed: Depends on slave device spec
```

### I2C Address
```
7-bit: 0x00 to 0x7F (128 addresses)
With R/W bit: [7-bit Address][R/W]
```

---

## POWER & ENERGY

### Power Consumption
```
P = V × I
Energy (Wh) = P × t
Battery Life (hours) = Battery_Capacity (mAh) / Current_Draw (mA)
```

### Sleep Mode Savings
```
Active: 100% power
Sleep: 10-20% power
Stop: ~10% power
Standby: ~1% power
```

---

## DIGITAL FILTERS

### Moving Average
```
y[n] = (1/N) × Σ(x[n-i]) for i=0 to N-1
```

### Exponential Moving Average
```
y[n] = α × x[n] + (1-α) × y[n-1]
α = 0.1 (heavy filter)
α = 0.9 (light filter)
```

### Low-Pass RC Filter
```
f_cutoff = 1 / (2πRC)
```

---

## MATLAB/SIMULINK

### Transfer Function
```matlab
G = tf(num, den)
% Example: G(s) = 5/(s+3)
G = tf(5, [1 3])
```

### PID Controller
```matlab
C = pid(Kp, Ki, Kd)
% Or auto-tune:
C = pidtune(G, 'PID')
```

### Closed-Loop
```matlab
T = feedback(C*G, 1)
```

### Step Response
```matlab
step(T)
info = stepinfo(T)
```

### Digital Filter
```matlab
[b,a] = butter(order, f_cutoff/(f_sample/2))
y = filter(b, a, x)
```

---

## COMMON VALUES & CONVERSIONS

### Standard Resistor Values (E12 Series)
```
10, 12, 15, 18, 22, 27, 33, 39, 47, 56, 68, 82
× 10^n (n = -1, 0, 1, 2, 3, ...)
```

### LED Forward Voltages
```
Red:    1.8-2.2V
Yellow: 2.0-2.2V
Green:  2.0-3.0V
Blue:   3.0-3.5V
White:  3.0-3.5V
```

### Common Currents
```
LED: 10-20 mA
GPIO: 4-25 mA typical, check datasheet
High-power LED: 350-1000 mA
```

### Voltage Levels
```
TTL: 0V = LOW, 5V = HIGH
CMOS: 0V = LOW, 3.3V or 5V = HIGH
Logic Threshold: ~1.5V (TTL), ~1.65V (CMOS 3.3V)
```

### Temperature Conversion
```
°C = (°F - 32) / 1.8
°F = °C × 1.8 + 32
K = °C + 273.15
```

---

## QUICK UNITS

### SI Prefixes
```
T (Tera)  = 10^12
G (Giga)  = 10^9
M (Mega)  = 10^6
k (kilo)  = 10^3
m (milli) = 10^-3
μ (micro) = 10^-6
n (nano)  = 10^-9
p (pico)  = 10^-12
```

### Data Sizes
```
1 bit
1 byte = 8 bits
1 word = 16 bits (usually)
1 dword = 32 bits
```

---

## SAFETY LIMITS

### ARM Cortex-M GPIO
```
Typical Max Current: 25 mA per pin
Total: 120 mA all pins
Always check datasheet!
```

### Component Ratings
```
Always: P_actual < P_rating
Safety Factor: Use 50-70% of max rating
Temperature: Derate at high temp
```

---

## DEBUGGING VALUES

### Common Clock Speeds
```
Arduino: 16 MHz
STM32F1: 72 MHz
STM32F4: 168 MHz
ESP32: 240 MHz
```

### Typical Sample Rates
```
Slow sensor: 1-10 Hz
Control loop: 100-1000 Hz
Audio: 44.1 kHz
Fast DAQ: 100+ kHz
```

---
