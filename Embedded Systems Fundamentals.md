# Embedded Systems Fundamentals

## Table of Contents
1. [Microcontroller Architecture](#microcontroller-architecture)
2. [Memory Organization](#memory-organization)
3. [GPIO and Digital I/O](#gpio-and-digital-io)
4. [Communication Protocols](#communication-protocols)
5. [Timers and PWM](#timers-and-pwm)
6. [Interrupts](#interrupts)
7. [ADC/DAC](#adc-dac)
8. [Power Management](#power-management)

---

## Microcontroller Architecture

### Microcontroller vs Microprocessor

**Microcontroller (MCU):**
- Complete computer on single chip
- CPU + Memory + Peripherals integrated
- Examples: ATmega328 (Arduino), STM32, PIC, ESP32
- Use: Dedicated embedded tasks

**Microprocessor (MPU):**
- Only CPU, requires external components
- Examples: Intel Core, ARM Cortex-A series
- Use: General-purpose computing (PCs, smartphones)

---

### Harvard vs Von Neumann Architecture

**Von Neumann:**
```
CPU ←→ [Single Memory] (Code + Data)
```
- Single bus for instructions and data
- Simpler, but bottleneck (von Neumann bottleneck)
- Example: Intel x86

**Harvard:**
```
CPU ←→ [Instruction Memory]
    ←→ [Data Memory]
```
- Separate buses for code and data
- Faster, can fetch instruction while accessing data
- Example: AVR, ARM Cortex-M

---

### ARM Cortex-M Series (Most Popular)

**Cortex-M0/M0+:**
- Ultra-low power
- Simple applications (sensors, IoT)
- 24-48 MHz

**Cortex-M3:**
- Balanced performance/power
- Industrial control
- Up to 100 MHz

**Cortex-M4:**
- DSP instructions + optional FPU
- Audio processing, motor control
- Up to 200 MHz

**Cortex-M7:**
- High performance
- Advanced control, graphics
- Up to 600 MHz

---

### Key MCU Components

1. **CPU**: Executes instructions
2. **Flash Memory**: Stores program code
3. **SRAM**: Stores variables during execution
4. **Peripherals**: GPIO, Timers, UART, SPI, I2C, ADC, DMA
5. **Clock System**: Generates timing signals
6. **Bus System**: Connects components

---

## Memory Organization

### Memory Types

**1. Flash Memory (Non-Volatile)**
- Stores program code
- Retains data when powered off
- Slower write, faster read
- Limited write cycles (~10,000-100,000)
- Size: 32KB - 2MB typical

**2. SRAM (Static RAM - Volatile)**
- Stores variables, stack, heap
- Fast read/write
- Loses data when powered off
- Size: 4KB - 512KB typical

**3. EEPROM (Non-Volatile)**
- Small storage for configuration
- Byte-level write
- Size: 512B - 4KB typical

**4. ROM (Read-Only Memory)**
- Factory-programmed
- Bootloader, hardware info

---

### Memory Map (STM32 Example)

```
0xFFFF FFFF ┌─────────────────┐
            │   Reserved      │
            ├─────────────────┤
0x6000 0000 │   External RAM  │
            ├─────────────────┤
0x4000 0000 │   Peripherals   │ ← GPIO, UART, Timers, etc.
            ├─────────────────┤
0x2000 0000 │   SRAM          │ ← Variables, Stack, Heap
            ├─────────────────┤
0x0800 0000 │   Flash Memory  │ ← Program Code
            ├─────────────────┤
0x0000 0000 │   Aliases       │
            └─────────────────┘
```

---

### Memory Segments

**1. Text (Code) Segment:**
- Program instructions
- Read-only
- Stored in Flash

**2. Data Segment:**
- Initialized global/static variables
- Copied from Flash to RAM at startup

**3. BSS Segment:**
- Uninitialized global/static variables
- Initialized to zero at startup

**4. Heap:**
- Dynamic memory allocation (`malloc()`)
- Grows upward
- Avoid in embedded systems (fragmentation risk)

**5. Stack:**
- Local variables, function calls, return addresses
- Grows downward
- Collision with heap = stack overflow!

```
High Address
    ┌────────────┐
    │   Stack    │ ← Grows down
    │     ↓      │
    ├────────────┤
    │            │
    │    Free    │
    │            │
    ├────────────┤
    │     ↑      │
    │   Heap     │ ← Grows up
    ├────────────┤
    │    BSS     │
    ├────────────┤
    │   Data     │
    ├────────────┤
    │   Text     │
Low Address
    └────────────┘
```

---

## GPIO and Digital I/O

### GPIO Modes

**1. Input Mode:**
- Read external signals (buttons, sensors)
- High impedance
- Can be floating, pull-up, or pull-down

**2. Output Mode:**
- Drive external devices (LEDs, relays)
- Push-pull or open-drain
- Drive high (3.3V/5V) or low (0V)

**3. Analog Mode:**
- Connect to ADC for analog readings

**4. Alternate Function:**
- UART_TX, SPI_SCK, PWM, etc.

---

### Pull-Up / Pull-Down Resistors

**Why needed?**
Prevent floating inputs (undefined logic level)

**Pull-Up:**
```
Vcc (3.3V)
    │
   ┌┴┐
   │R│ 10kΩ
   └┬┘
    ├─── GPIO Pin
    │
  [Button]
    │
   GND
```
- Default HIGH (1)
- Pressing button → LOW (0)

**Pull-Down:**
```
    ├─── GPIO Pin
    │
   ┌┴┐
   │R│ 10kΩ
   └┬┘
    │
   GND
```
- Default LOW (0)
- Pressing button → HIGH (1)

---

### Bit Manipulation for GPIO

**Set bit (turn ON):**
```c
GPIOA->ODR |= (1 << 5);  // Set bit 5 (PA5)
```

**Clear bit (turn OFF):**
```c
GPIOA->ODR &= ~(1 << 5); // Clear bit 5
```

**Toggle bit:**
```c
GPIOA->ODR ^= (1 << 5);  // Toggle bit 5
```

**Read bit:**
```c
if (GPIOA->IDR & (1 << 5)) {
    // Pin is HIGH
}
```

---

## Communication Protocols

### UART (Universal Asynchronous Receiver-Transmitter)

**Characteristics:**
- Asynchronous (no clock line)
- Point-to-point (one-to-one)
- Two wires: TX, RX (plus GND)
- Speed: 9600, 115200 baud common

**Frame Format:**
```
[Start bit][8 Data bits][Parity?][Stop bit(s)]
    0      D0-D7         ?         1 or 2
```

**Connection:**
```
MCU1 TX ──────→ RX MCU2
MCU1 RX ←────── TX MCU2
     GND ←────→ GND
```

**Use Cases:**
- Serial debugging
- GPS modules
- Bluetooth modules (HC-05)
- PC communication

**Code Example:**
```c
// Send character
void UART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Wait until TX empty
    USART1->DR = c;
}

// Receive character
char UART_ReceiveChar(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until data ready
    return USART1->DR;
}
```

---

### SPI (Serial Peripheral Interface)

**Characteristics:**
- Synchronous (clock signal)
- Master-Slave
- Four wires: MOSI, MISO, SCK, CS/SS
- Speed: Up to 10s of MHz
- Full-duplex (send/receive simultaneously)

**Pins:**
- **SCK**: Clock (Master generates)
- **MOSI**: Master Out, Slave In
- **MISO**: Master In, Slave Out
- **CS/SS**: Chip Select (active LOW)

**Connection:**
```
Master          Slave
  SCK  ────────→ SCK
  MOSI ────────→ MOSI (DI)
  MISO ←──────── MISO (DO)
  CS   ────────→ CS
```

**Clock Modes (CPOL/CPHA):**
- Mode 0: CPOL=0, CPHA=0 (most common)
- Mode 1: CPOL=0, CPHA=1
- Mode 2: CPOL=1, CPHA=0
- Mode 3: CPOL=1, CPHA=1

**Use Cases:**
- SD cards
- Flash memory
- Displays (TFT LCD)
- Sensors (accelerometers)

**Code Example:**
```c
uint8_t SPI_Transfer(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));  // Wait TX empty
    SPI1->DR = data;                    // Send data
    while (!(SPI1->SR & SPI_SR_RXNE)); // Wait RX ready
    return SPI1->DR;                    // Return received data
}
```

---

### I2C (Inter-Integrated Circuit)

**Characteristics:**
- Synchronous (clock signal)
- Multi-master, multi-slave
- Two wires: SDA, SCL
- Speed: 100 kHz (Standard), 400 kHz (Fast), 3.4 MHz (High-speed)
- Half-duplex
- Addressing: 7-bit or 10-bit

**Pins:**
- **SDA**: Serial Data (bidirectional)
- **SCL**: Serial Clock
- Both need pull-up resistors (typically 4.7kΩ)

**Connection:**
```
       Vcc
        │
   4.7kΩ│  4.7kΩ
        │     │
  Master│     │Slave1   Slave2   Slave3
    SDA ├─────┼────────┼────────┼──
    SCL ├─────┼────────┼────────┼──
```

**Transaction Format:**
```
[Start][Address+R/W][ACK][Data][ACK]...[Stop]
```

**7-bit Addressing:**
- 0x00-0x7F (128 devices possible)
- R/W bit: 0=Write, 1=Read

**Use Cases:**
- Sensors (IMU, temperature, pressure)
- EEPROMs
- RTCs (Real-Time Clocks)
- I/O expanders

**Code Example:**
```c
// Start condition
void I2C_Start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for start bit
}

// Send address
void I2C_SendAddress(uint8_t address, uint8_t rw) {
    I2C1->DR = (address << 1) | rw;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; // Clear ADDR flag
}

// Write data
void I2C_WriteData(uint8_t data) {
    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_TXE));
}

// Stop condition
void I2C_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}
```

---

### CAN (Controller Area Network)

**Characteristics:**
- Designed for automotive/industrial
- Multi-master
- Two wires: CAN_H, CAN_L (differential)
- Speed: Up to 1 Mbps
- Very robust (noise immunity)
- Message-based (not address-based)

**Frame Structure:**
- Identifier (11-bit or 29-bit)
- Data (0-8 bytes)
- CRC, ACK

**Use Cases:**
- Vehicle ECUs
- Industrial automation
- Robotics

---

### Protocol Comparison

| Feature      | UART    | SPI        | I2C        | CAN        |
|--------------|---------|------------|------------|------------|
| Wires        | 2       | 4+         | 2          | 2          |
| Speed        | Slow    | Fast       | Medium     | Medium     |
| Distance     | Short   | Very Short | Short      | Long       |
| Devices      | 2       | Many       | Many       | Many       |
| Complexity   | Simple  | Medium     | Medium     | Complex    |
| Use          | Debug   | High-speed | Sensors    | Automotive |

---

## Timers and PWM

### Hardware Timers

**Purpose:**
- Generate precise delays
- Count events
- Generate PWM signals
- Measure input signals (capture)

**Basic Operation:**
```
Counter: 0 → 1 → 2 → ... → ARR (Auto-Reload) → 0 (overflow)
```

**Timer Modes:**
1. **Upcounting**: 0 → ARR
2. **Downcounting**: ARR → 0
3. **Center-aligned**: 0 → ARR → 0

---

### PWM (Pulse Width Modulation)

**What is PWM?**
Digital signal with variable duty cycle to simulate analog output

**Duty Cycle:**
```
Duty Cycle (%) = (ON time / Period) × 100
```

**Example:**
- Period = 10ms
- ON time = 7ms
- Duty cycle = 70%

```
      ┌──┐    ┌──┐    ┌──┐
      │  │    │  │    │  │
──────┘  └────┘  └────┘  └────
  3ms  7ms  3ms  7ms  3ms  7ms
```

---

### PWM Applications

**1. LED Brightness Control:**
- 0% duty = OFF
- 50% duty = Half brightness
- 100% duty = Full brightness

**2. Motor Speed Control:**
- 0% duty = Stop
- 50% duty = Half speed
- 100% duty = Full speed

**3. Servo Motor Position:**
- 1ms pulse = 0° position
- 1.5ms pulse = 90° position
- 2ms pulse = 180° position
- Period: 20ms (50Hz)

**4. Audio Generation:**
- Variable frequency PWM
- Low-pass filter to smooth

---

### PWM Code Example (STM32)

```c
// Configure Timer for PWM
void PWM_Init(void) {
    // Enable clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    
    // Set prescaler (reduce frequency)
    TIM3->PSC = 72 - 1;  // 72MHz / 72 = 1MHz
    
    // Set auto-reload (period)
    TIM3->ARR = 1000 - 1; // 1MHz / 1000 = 1kHz PWM
    
    // Set compare value (duty cycle)
    TIM3->CCR1 = 500; // 50% duty cycle
    
    // Configure as PWM mode
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE; // Preload enable
    
    // Enable output
    TIM3->CCER |= TIM_CCER_CC1E;
    
    // Start timer
    TIM3->CR1 |= TIM_CR1_CEN;
}

// Set duty cycle (0-100%)
void PWM_SetDuty(uint8_t duty) {
    if (duty > 100) duty = 100;
    TIM3->CCR1 = (TIM3->ARR * duty) / 100;
}
```

---

## Interrupts

### What are Interrupts?

**Definition:**
Hardware or software signals that pause main program execution to handle urgent events.

**Analogy:**
You're reading a book (main program). Phone rings (interrupt). You answer (ISR), then return to reading.

---

### Interrupt Types

**1. External Interrupts (EXTI):**
- GPIO pin changes (button press)
- Rising/falling edge

**2. Timer Interrupts:**
- Timer overflow
- Compare match

**3. Peripheral Interrupts:**
- UART data received
- ADC conversion complete
- DMA transfer complete

**4. System Interrupts:**
- SysTick (periodic)
- Hard Fault, NMI

---

### Interrupt Priority

**NVIC (Nested Vectored Interrupt Controller):**
- Manages interrupt priorities
- Higher priority interrupts can preempt lower
- Priority 0 = Highest

**Example (ARM Cortex-M):**
```c
NVIC_SetPriority(USART1_IRQn, 0); // Highest priority
NVIC_SetPriority(TIM3_IRQn, 1);   // Lower priority
NVIC_EnableIRQ(USART1_IRQn);
```

---

### ISR (Interrupt Service Routine)

**Rules for ISR:**
1. **Keep it SHORT** - execute quickly
2. **No blocking** - no delays, no while loops
3. **Minimal processing** - set flags, copy data
4. **Volatile variables** for shared data
5. **No printf()** - too slow

**Good ISR Pattern:**
```c
volatile uint8_t flag = 0;
volatile uint8_t data = 0;

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        // Clear interrupt flag
        EXTI->PR |= EXTI_PR_PR0;
        
        // Quick action
        data = GPIOA->IDR;
        flag = 1;
    }
}

// Main loop handles processing
int main(void) {
    while (1) {
        if (flag) {
            flag = 0;
            process_data(data); // Do heavy work here
        }
    }
}
```

---

## ADC/DAC

### ADC (Analog-to-Digital Converter)

**Purpose:**
Convert analog voltage to digital value

**Resolution:**
- 10-bit: 0-1023 (Arduino)
- 12-bit: 0-4095 (STM32)
- 16-bit: 0-65535 (high precision)

**Formula:**
```
Digital Value = (V_in / V_ref) × (2^bits - 1)

Example: 10-bit ADC, V_ref = 5V, V_in = 2.5V
Digital = (2.5 / 5) × 1023 = 511
```

**Conversion Time:**
- Depends on sampling rate
- Faster sampling = less precision

**Code Example:**
```c
uint16_t ADC_Read(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;          // Start conversion
    while (!(ADC1->SR & ADC_SR_EOC));       // Wait complete
    return ADC1->DR;                        // Read result
}

// Convert to voltage
float voltage = (adc_value * 3.3) / 4095.0; // For 3.3V reference
```

---

### DAC (Digital-to-Analog Converter)

**Purpose:**
Convert digital value to analog voltage

**Resolution:**
- 8-bit: 0-255 levels
- 12-bit: 0-4095 levels

**Formula:**
```
V_out = (Digital Value / (2^bits - 1)) × V_ref
```

**Applications:**
- Audio output
- Signal generation
- Analog control signals

**Code Example:**
```c
void DAC_Write(uint16_t value) {
    if (value > 4095) value = 4095; // 12-bit limit
    DAC->DHR12R1 = value;
}

// Generate 1.65V on 3.3V reference
DAC_Write(2048); // 2048/4095 × 3.3V = 1.65V
```

---

## Power Management

### Sleep Modes

**1. Sleep Mode:**
- CPU stopped
- Peripherals running
- Wake: Any interrupt
- Power: ~10-20% reduction

**2. Stop Mode:**
- CPU and most peripherals stopped
- RTC running
- Wake: External interrupt, RTC
- Power: ~90% reduction

**3. Standby Mode:**
- Everything off except backup domain
- Only RTC running
- Wake: Reset, RTC alarm, external pin
- Power: ~99% reduction

---

### Power-Saving Techniques

**1. Clock Gating:**
Disable clocks for unused peripherals
```c
RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN; // Disable TIM3 clock
```

**2. Dynamic Frequency Scaling:**
Reduce CPU frequency when possible

**3. Peripheral Power Control:**
Turn off unused peripherals

**4. Efficient Polling:**
Use interrupts instead of busy-waiting

---

## Quick Reference

**GPIO:**
```c
Set pin:   GPIOA->BSRR = (1 << pin);
Clear pin: GPIOA->BSRR = (1 << (pin + 16));
Read pin:  (GPIOA->IDR & (1 << pin))
```

**Bit Operations:**
```c
Set bit:    var |= (1 << n)
Clear bit:  var &= ~(1 << n)
Toggle bit: var ^= (1 << n)
Read bit:   (var & (1 << n))
```

**Delay (inefficient, avoid in production):**
```c
void delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms * 1000; i++) {
        __NOP();
    }
}
```

---
