# C Programming for Embedded Systems Engineers
## Beginner-Level Guide

## Table of Contents
1. [Key Concepts You Must Know](#key-concepts-you-must-know)
2. [Common Embedded Patterns](#common-embedded-patterns)
3. [Best Practices for Embedded C](#best-practices-for-embedded-c)
4. [Programs Included](#programs-included---what-they-teach)
5. [How to Compile & Run](#how-to-compile--run-linux-ubuntu-2204)
6. [Learning Path](#learning-path)
7. [Next Steps After Basics](#next-steps-after-basics)
8. [Useful Resources](#useful-resources)
9. [Quick Reference](#quick-reference-essential-c-syntax-for-embedded)

---

## Key Concepts You Must Know

### A. Data Types & Memory
- Understand fixed-width types: `uint8_t`, `uint16_t`, `int32_t` (essential for hardware)
- Know the size of each type using `sizeof()`
- **Signed vs Unsigned:** use unsigned for values that can't be negative

**Example for drone:**
- Battery level: `uint8_t` (0-100%)
- Temperature: `int16_t` (-40 to +85°C)
- Timestamp: `uint32_t` (large counter)

---

### B. Pointers (MOST IMPORTANT FOR EMBEDDED!)
- Pointers let you directly access memory → essential for hardware registers
- `&` gets address, `*` dereferences
- Pointer arithmetic: `ptr++` moves to next memory location

**Real example:** To control a motor, you write to a hardware register:
```c
uint32_t *motor_register = (uint32_t *)0x40020000;  // Fixed address
*motor_register = 0xFF;  // Write value to register
```

---

### C. Structs & Bit Fields
- **Struct:** groups related data (sensor readings, configuration)
- **Bit fields:** manipulate individual bits in hardware registers

**Example:**
```c
typedef struct {
    float accel_x, accel_y, accel_z;
    uint32_t timestamp;
} IMUSensorData;
```

---

### D. Functions
- Organize code into modular pieces
- Pass parameters by value or by pointer
- Return types for error checking

---

### E. Arrays
- Store multiple values efficiently
- Use for sensor buffers, logging data
- Pointer arithmetic simplifies iteration

---

### F. Control Flow
- `if/else` for decisions
- `for/while` for loops
- `switch` for multiple conditions

---

### G. Bit Manipulation (Common in Embedded!)
```c
// Set bit
value |= (1 << bit_position);

// Clear bit
value &= ~(1 << bit_position);

// Check bit
if (value & (1 << bit_position))

// Toggle bit
value ^= (1 << bit_position);
```

---

## Common Embedded Patterns

### Pattern 1: Hardware Register Access
```c
#define MOTOR_CONTROL_REG ((uint32_t *)0x40001000)
*MOTOR_CONTROL_REG = speed_value;
```

---

### Pattern 2: Sensor Reading Pipeline
```c
uint16_t raw = read_adc();
float voltage = raw_to_voltage(raw);
int temp = voltage_to_temperature(voltage);
```

---

### Pattern 3: State Machine
```c
typedef enum {
    STATE_IDLE, 
    STATE_ARMED, 
    STATE_FLYING, 
    STATE_ERROR
} DroneState;

void update_state(DroneState current_state) { 
    // State transition logic
}
```

---

### Pattern 4: Interrupt Handler
```c
void timer_interrupt() {
    // Time-critical code runs here
    update_motor_speed();
}
```

---

### Pattern 5: Filtering (Noise Reduction)
```c
float filtered = alpha * raw + (1 - alpha) * previous;
```

---

## Best Practices for Embedded C

### ✓ DO:
- Use fixed-width integer types (`uint8_t`, not `unsigned char`)
- Keep ISR (interrupt service routines) short and fast
- Initialize all variables
- Check return values from functions
- Use meaningful variable names
- Add comments explaining hardware operations
- Use `const` for configuration values
- Validate input ranges

### ✗ DON'T:
- Use `malloc`/`free` in real-time code (causes unpredictable delays)
- Have infinite loops without timeout protection
- Use global variables excessively (prefer structs)
- Forget to configure GPIO, I2C, SPI correctly
- Ignore watchdog timers
- Use floating point in time-critical code (use fixed-point instead)
- Forget to handle error states

---

## Programs Included - What They Teach

### 01_hello_embedded.c
- Data types, sizes, fixed-width integers
- Output with printf for debugging
- Understanding memory layout

### 02_pointers_arrays.c
- Pointers and dereferencing
- Array storage and access
- Pointer arithmetic
- Hardware register simulation

### 03_structs_bitfields.c
- Organizing data with structs
- Bit fields for hardware registers
- Array of structs (multiple sensors)
- Pointers to structs

### 04_practical_tasks.c
- ADC reading and conversion
- Drone telemetry simulation
- State management
- Bit manipulation
- Sensor filtering

### 05_functions_modularity.c
- Function design for embedded systems
- Sensor driver patterns
- Motor control abstraction
- Filter implementation
- Real-time loop simulation

---

## How to Compile & Run (Linux Ubuntu 22.04)

### Basic Compilation
```bash
gcc -o program_name program_name.c
```

### With warnings (recommended)
```bash
gcc -Wall -Wextra -o program_name program_name.c
```

### With optimization (for embedded)
```bash
gcc -O2 -o program_name program_name.c
```

### With math library
```bash
gcc -o program_name program_name.c -lm
```

### Run the program
```bash
./program_name
```

### Debug with gdb
```bash
gcc -g -o program_name program_name.c
gdb ./program_name
```

---

## Learning Path

### Week 1-2: Fundamentals
- Understand data types and memory
- Learn pointers thoroughly
- Master arrays

### Week 3-4: Structures
- Work with structs
- Learn bit fields
- Practice pointer-to-struct

### Week 5-6: Functions & Modularity
- Write clean functions
- Create sensor drivers
- Implement filters

### Week 7-8: Real-time Concepts
- Study RTOS basics
- Learn about interrupts
- Understand timing constraints

### Week 9-12: Projects
- Build a sensor driver
- Create a simple state machine
- Implement a motor controller

---

## Next Steps After Basics

After mastering this material:

1. Learn microcontroller architecture (ARM Cortex-M)
2. Study hardware: GPIO, PWM, ADC, I2C, SPI, UART
3. Learn RTOS: FreeRTOS or Linux kernel
4. Practice on real hardware: Arduino, STM32, Raspberry Pi
5. Study communication protocols: CAN, RS485, wireless
6. Build a real project: drone controller, robot, sensor system

**For the Liberaware job specifically:**
- Deep dive into C++ (they use it alongside C)
- Learn ROS (Robot Operating System)
- Study autonomous systems and SLAM
- Practice with Jetson boards

---

## Useful Resources

### Books
- "The C Programming Language" by Kernighan & Ritchie
- "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M" by Dean
- "Making Embedded Systems" by Elecia White

### Online
- Coursera: Embedded Systems Specialization
- Udemy: C Programming for Embedded Systems
- GitHub: Open-source embedded projects
- STMicroelectronics: HAL documentation

### Practice
- LeetCode (for C fundamentals)
- Build projects on Arduino
- Contribute to FreeRTOS or other embedded projects

---

## Quick Reference: Essential C Syntax for Embedded

### Basic Types
```c
uint8_t byte_value;      // 0-255
uint16_t word_value;     // 0-65535
int32_t signed_value;    // -2B to +2B
float floating_value;    // 3.14
```

### Pointers
```c
int *ptr = &variable;    // Address of
int value = *ptr;        // Dereference
```

### Struct
```c
typedef struct {
    uint16_t x;
    uint16_t y;
} Coordinate;
```

### Bit Operations
```c
value |= (1 << 3);       // Set bit 3
value &= ~(1 << 3);      // Clear bit 3
if (value & (1 << 3)) {} // Check bit 3
```

### Array
```c
uint16_t buffer[10];     // 10-element array
buffer[0] = 100;         // Access element
```

### Function
```c
int add(int a, int b) { 
    return a + b; 
}
```

### Loop
```c
for (int i = 0; i < 10; i++) { 
    // Loop body
}

while (condition) { 
    // Loop body
}
```

---
