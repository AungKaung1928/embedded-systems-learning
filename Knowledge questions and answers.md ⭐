## Common Questions & Answers

### Embedded Systems Basics

**Q: Microcontroller vs Microprocessor?**
**A:** MCU = CPU + Memory + Peripherals on one chip (Arduino, STM32). MPU = Only CPU, needs external components (Intel, ARM Cortex-A).

**Q: Harvard vs Von Neumann architecture?**
**A:** Von Neumann: Single bus for code+data (simpler, bottleneck). Harvard: Separate buses (faster, can fetch instruction while accessing data).

**Q: Explain volatile keyword**
**A:** Tells compiler variable can change unexpectedly (hardware registers, interrupt variables). Prevents optimization that could break hardware access.

**Q: What is ISR?**
**A:** Interrupt Service Routine. Function that handles interrupt. Must be SHORT, no blocking, use volatile for shared variables.

**Q: Pull-up vs Pull-down resistor?**
**A:** Pull-up: Connects to Vcc, default HIGH. Pull-down: Connects to GND, default LOW. Prevents floating (undefined) input.

---

### Memory & Pointers

**Q: Stack vs Heap?**
**A:** Stack: Fast, automatic, LIFO, fixed size, local variables. Heap: Slow, manual (malloc/free), dynamic, fragmentation risk. Avoid heap in embedded.

**Q: What is stack overflow?**
**A:** Stack grows beyond allocated space, corrupts memory. Causes: deep recursion, large local arrays, insufficient stack size.

**Q: Memory segments?**
**A:** 
- Text: Program code (Flash)
- Data: Initialized globals (RAM, copied from Flash)
- BSS: Uninitialized globals (RAM, zeroed at startup)
- Stack: Local variables, grows down
- Heap: Dynamic allocation, grows up

**Q: What is memory-mapped I/O?**
**A:** Hardware registers accessed like memory addresses. Writing to 0x40021000 controls GPIO, not RAM.

```c
#define GPIOA_ODR (*(volatile uint32_t*)0x40021000)
GPIOA_ODR |= (1 << 5);  // Set PA5
```

---

### Communication Protocols

**Q: UART vs SPI vs I2C?**
**A:**
- UART: 2 wires, simple, point-to-point, async, 9600-115200 baud
- SPI: 4 wires, fast (MHz), full-duplex, master-slave, short distance
- I2C: 2 wires, multi-device, 100-400kHz, half-duplex, addressing

**Q: What is CAN bus?**
**A:** Automotive protocol, differential (CAN_H/L), multi-master, message-based, very robust, up to 1Mbps. Used in vehicles, industrial.

**Q: Explain I2C addressing**
**A:** 7-bit address (0x00-0x7F), 8th bit R/W (0=write, 1=read). Transaction: START + Address+R/W + ACK + Data + ACK + STOP.

---

### Timers & PWM

**Q: What is PWM?**
**A:** Pulse Width Modulation. Digital signal with variable duty cycle. Simulates analog output. Used for: LED dimming, motor speed, servo control.

**Q: How to control LED brightness with PWM?**
**A:** Vary duty cycle: 0%=OFF, 50%=half brightness, 100%=full. Human eye averages pulses due to persistence of vision.

**Q: What is timer overflow?**
**A:** Counter reaches maximum (ARR register), resets to 0, can trigger interrupt. Used for periodic tasks.

---

### Control Systems

**Q: Open-loop vs Closed-loop?**
**A:** Open: No feedback (toaster). Closed: Uses feedback to correct error (thermostat). Closed more accurate but complex.

**Q: Explain P, I, D terms**
**A:**
- P: Proportional to current error (fast response, steady-state error remains)
- I: Accumulates error over time (eliminates steady-state error, can overshoot)
- D: Based on error rate (predicts future, reduces overshoot, amplifies noise)

**Q: What is integral windup?**
**A:** Integral term grows huge during saturation, causes overshoot. Fix: clamp integral, conditional integration, back-calculation.

**Q: How to tune PID?**
**A:** Start with P only, increase until oscillation. Set Ki = Kp/10, Kd = Kp/100. Fine-tune based on response. Or use Ziegler-Nichols method.

---

### Firmware Development

**Q: Bare-metal vs RTOS?**
**A:** Bare-metal: Simple superloop, no overhead, good for simple apps. RTOS: Multi-tasking, priorities, better for complex systems with concurrent tasks.

**Q: What is a task in RTOS?**
**A:** Independent execution thread with own stack. Scheduled by RTOS based on priority. Can be blocked (waiting) or running.

**Q: Semaphore vs Mutex?**
**A:** Semaphore: Signaling (can be given by any task, count 0-N). Mutex: Resource lock (must be released by same task that took it, ownership).

**Q: What is deadlock?**
**A:** Two tasks waiting for resources held by each other. Prevention: consistent lock order, timeouts, avoid nested locks.

**Q: What is bootloader?**
**A:** Small program that runs first. Can update main firmware without debugger. Checks for update, verifies, programs flash, jumps to app.

---

### Electrical Circuits

**Q: Ohm's Law?**
**A:** V = I × R. Voltage = Current × Resistance.

**Q: Kirchhoff's Laws?**
**A:** KCL: Current in = Current out (at node). KVL: Sum of voltages around loop = 0.

**Q: Series vs Parallel resistors?**
**A:** Series: R_total = R1 + R2 (same current). Parallel: 1/R_total = 1/R1 + 1/R2 (same voltage).

**Q: What is voltage divider?**
**A:** Vout = Vin × (R2/(R1+R2)). Used to scale voltages, read sensors.

**Q: Capacitor in AC vs DC?**
**A:** DC: Charges then blocks (open circuit). AC: Passes (lower impedance at higher frequency).

**Q: NPN transistor as switch?**
**A:** I_C = β × I_B. Apply base current to turn ON (V_CE ≈ 0.2V). No base current = OFF (open).

---

### C/C++ Programming

**Q: Pointer vs Array?**
**A:** Array is contiguous memory. Pointer stores address. `arr[i]` = `*(arr+i)`. Pointer arithmetic: `ptr+1` advances by sizeof(type).

**Q: What is NULL pointer?**
**A:** Pointer with value 0, points nowhere. Dereferencing causes crash. Always check: `if(ptr != NULL)`.

**Q: Static variable?**
**A:** File scope: Limits visibility to file. Function scope: Retains value between calls. Initialized once.

**Q: Bit manipulation operators?**
**A:** 
- Set: `var |= (1 << n)`
- Clear: `var &= ~(1 << n)`
- Toggle: `var ^= (1 << n)`
- Check: `if(var & (1 << n))`

**Q: Why use typedef?**
**A:** Create alias for better readability. `typedef uint8_t byte;` `byte data = 0x55;`

**Q: Struct vs Union?**
**A:** Struct: Members at different memory. Union: Members share same memory (size = largest member).

**Q: C++ class vs struct?**
**A:** Class: Default private. Struct: Default public. Otherwise identical.

**Q: What is virtual function?**
**A:** Allows polymorphism (runtime binding). Derived class overrides base method. Uses vtable (small overhead).

---

### Debugging & Tools

**Q: How to debug without debugger?**
**A:** 
1. LED blink patterns (error codes)
2. UART printf debugging
3. Toggle GPIO and measure with scope
4. Log to flash memory
5. Watchdog monitoring

**Q: What is watchdog timer?**
**A:** Hardware timer that resets system if not refreshed periodically. Prevents system hang. Must "pet the dog" in main loop.

**Q: Common causes of hard fault?**
**A:** NULL pointer dereference, stack overflow, misaligned access, division by zero, accessing invalid memory.

**Q: How to prevent stack overflow?**
**A:** Proper sizing, avoid deep recursion, limit local arrays, use static/heap for large buffers, enable stack overflow detection.

---

## Coding Problems

### Problem 1: Toggle LED every 500ms (bare-metal)
```c
volatile uint32_t tick = 0;

void SysTick_Handler(void) {
    tick++;
}

int main(void) {
    SysTick_Config(SystemCoreClock / 1000);  // 1ms
    
    while(1) {
        if(tick >= 500) {
            GPIOA->ODR ^= (1 << 5);  // Toggle PA5
            tick = 0;
        }
    }
}
```

### Problem 2: Simple PID controller
```c
typedef struct {
    float Kp, Ki, Kd;
    float prev_error, integral;
} PID;

float PID_Update(PID* pid, float setpoint, float measured, float dt) {
    float error = setpoint - measured;
    pid->integral += error * dt;
    float derivative = (error - pid->prev_error) / dt;
    
    float output = pid->Kp * error + 
                   pid->Ki * pid->integral + 
                   pid->Kd * derivative;
    
    pid->prev_error = error;
    return output;
}
```

### Problem 3: Circular buffer
```c
#define BUFFER_SIZE 8
typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head, tail, count;
} CircularBuffer;

bool buffer_push(CircularBuffer* cb, uint8_t data) {
    if(cb->count >= BUFFER_SIZE) return false;
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;
    return true;
}

bool buffer_pop(CircularBuffer* cb, uint8_t* data) {
    if(cb->count == 0) return false;
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;
    return true;
}
```

### Problem 4: State machine
```c
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} State;

State current_state = STATE_IDLE;

void state_machine_update(void) {
    switch(current_state) {
        case STATE_IDLE:
            if(start_button_pressed()) {
                current_state = STATE_RUNNING;
            }
            break;
            
        case STATE_RUNNING:
            do_work();
            if(error_detected()) {
                current_state = STATE_ERROR;
            }
            if(stop_button_pressed()) {
                current_state = STATE_IDLE;
            }
            break;
            
        case STATE_ERROR:
            handle_error();
            if(reset_button_pressed()) {
                current_state = STATE_IDLE;
            }
            break;
    }
}
```

---

## Essential Formulas

### Electrical
```
Ohm's Law:        V = I × R
Power:            P = V × I = I²R = V²/R
Voltage Divider:  Vout = Vin × R2/(R1+R2)
RC Time Constant: τ = R × C
LED Resistor:     R = (Vsupply - Vled) / Iled
Capacitor Energy: E = ½CV²
```

### Control Systems
```
PID:              u = Kp×e + Ki×∫e + Kd×de/dt
Natural Freq:     ωn = √(k/m)
Damping Ratio:    ζ = c/(2√(km))
Settling Time:    Ts ≈ 4/ζωn
```

### Digital Systems
```
Resolution:       Levels = 2^bits
ADC Conversion:   Digital = (Vin/Vref) × (2^bits - 1)
PWM Duty:         Duty% = (ON_time/Period) × 100
Sample Rate:      fs > 2 × fmax (Nyquist)
```

---
