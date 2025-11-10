# C++ Essentials for Embedded Systems

## Why C++ for Embedded?

**Advantages over C:**
- Object-Oriented (encapsulation, inheritance)
- Type safety (templates, strong typing)
- RAII (automatic resource management)
- Zero-cost abstractions (when done right)

**Used in:** Arduino, ROS2, Modern embedded frameworks

---

## Classes & Objects

### Basic Class
```cpp
class LED {
private:
    uint8_t pin;
    bool state;
    
public:
    LED(uint8_t p) : pin(p), state(false) {  // Constructor
        pinMode(pin, OUTPUT);
    }
    
    void on() {
        digitalWrite(pin, HIGH);
        state = true;
    }
    
    void off() {
        digitalWrite(pin, LOW);
        state = false;
    }
    
    void toggle() {
        state = !state;
        digitalWrite(pin, state);
    }
};

// Usage
LED statusLED(13);
statusLED.on();
```

---

### Hardware Abstraction with Classes

```cpp
class UARTDriver {
private:
    USART_TypeDef* uart;
    uint32_t baudrate;
    
public:
    UARTDriver(USART_TypeDef* u, uint32_t baud) 
        : uart(u), baudrate(baud) {
        init();
    }
    
    void send(uint8_t data) {
        while (!(uart->SR & USART_SR_TXE));
        uart->DR = data;
    }
    
    uint8_t receive() {
        while (!(uart->SR & USART_SR_RXNE));
        return uart->DR;
    }
    
private:
    void init() {
        // Configure UART registers
    }
};

// Usage
UARTDriver serial(USART1, 115200);
serial.send('A');
```

---

## Constructors & Destructors

### RAII Pattern (Resource Acquisition Is Initialization)

```cpp
class Timer {
private:
    TIM_TypeDef* timer;
    
public:
    Timer(TIM_TypeDef* t) : timer(t) {
        // Enable clock
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
        timer->CR1 |= TIM_CR1_CEN;  // Start
    }
    
    ~Timer() {  // Destructor - called automatically
        timer->CR1 &= ~TIM_CR1_CEN;  // Stop
        // Disable clock to save power
    }
};

// Automatic cleanup when object goes out of scope
void runTemporaryTimer() {
    Timer t(TIM3);  // Timer starts
    // Use timer
}  // Timer stops automatically (destructor called)
```

---

## Inheritance & Polymorphism

### Base Class for Sensors
```cpp
class Sensor {
public:
    virtual float read() = 0;  // Pure virtual (must implement)
    virtual ~Sensor() {}       // Virtual destructor
};

class TemperatureSensor : public Sensor {
private:
    uint8_t adc_channel;
    
public:
    TemperatureSensor(uint8_t ch) : adc_channel(ch) {}
    
    float read() override {
        uint16_t adc = ADC_Read(adc_channel);
        return (adc * 3.3 / 4095.0) * 100.0;  // Convert to °C
    }
};

class PressureSensor : public Sensor {
private:
    uint8_t i2c_address;
    
public:
    PressureSensor(uint8_t addr) : i2c_address(addr) {}
    
    float read() override {
        return I2C_ReadPressure(i2c_address);
    }
};

// Usage: Polymorphism
void printSensorData(Sensor* sensor) {
    Serial.println(sensor->read());  // Calls correct read()
}

TemperatureSensor temp(0);
PressureSensor pressure(0x76);
printSensorData(&temp);      // Prints temperature
printSensorData(&pressure);  // Prints pressure
```

---

## Templates

### Generic Function
```cpp
template<typename T>
T constrain(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Usage
int x = constrain(150, 0, 100);      // Returns 100
float y = constrain(1.5f, 0.0f, 2.0f);  // Returns 1.5
```

### Template Class (Ring Buffer)
```cpp
template<typename T, size_t SIZE>
class RingBuffer {
private:
    T buffer[SIZE];
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    
public:
    bool push(T item) {
        if (count >= SIZE) return false;
        buffer[head] = item;
        head = (head + 1) % SIZE;
        count++;
        return true;
    }
    
    bool pop(T& item) {
        if (count == 0) return false;
        item = buffer[tail];
        tail = (tail + 1) % SIZE;
        count--;
        return true;
    }
    
    bool isEmpty() { return count == 0; }
    bool isFull() { return count >= SIZE; }
};

// Usage
RingBuffer<uint8_t, 64> rxBuffer;  // 64-byte buffer
rxBuffer.push(0xAA);
uint8_t data;
rxBuffer.pop(data);
```

---

## Modern C++ Features (C++11 and beyond)

### Auto Keyword
```cpp
auto x = 5;           // int
auto y = 3.14f;       // float
auto sensor = new TemperatureSensor(0);  // TemperatureSensor*
```

---

### Range-Based For Loop
```cpp
uint8_t data[] = {1, 2, 3, 4, 5};

// Instead of
for (int i = 0; i < 5; i++) {
    process(data[i]);
}

// Use
for (auto value : data) {
    process(value);
}
```

---

### Lambda Functions
```cpp
// Sort array with custom comparison
std::sort(arr, arr+n, [](int a, int b) {
    return a > b;  // Descending order
});

// Capture variables
int threshold = 100;
auto isHigh = [threshold](int value) {
    return value > threshold;
};
```

---

### Smart Pointers (Avoid in embedded - understand concept)

```cpp
#include <memory>

// Unique pointer (single owner)
std::unique_ptr<Sensor> sensor(new TemperatureSensor(0));
sensor->read();  // Auto-deleted when out of scope

// Shared pointer (multiple owners)
std::shared_ptr<Sensor> s1 = std::make_shared<TemperatureSensor>(0);
std::shared_ptr<Sensor> s2 = s1;  // Both point to same object
```

**Note:** Smart pointers use heap - avoid in resource-constrained embedded systems

---

### Constexpr (Compile-Time Constants)

```cpp
constexpr int MAX_BUFFER = 128;
constexpr float PI = 3.14159f;

constexpr int square(int x) {
    return x * x;
}

uint8_t buffer[square(8)];  // Computed at compile time
```

---

### Namespaces

```cpp
namespace HAL {
    void GPIO_Write(uint8_t pin, bool value);
    uint8_t GPIO_Read(uint8_t pin);
}

namespace Sensors {
    float readTemperature();
    float readPressure();
}

// Usage
HAL::GPIO_Write(13, true);
float temp = Sensors::readTemperature();
```

---

### Enum Class (Type-Safe Enums)

```cpp
// Old C-style enum (not type-safe)
enum Color { RED, GREEN, BLUE };

// C++11 enum class (type-safe)
enum class State : uint8_t {
    IDLE = 0,
    RUNNING = 1,
    ERROR = 2
};

State current = State::IDLE;

// Cannot accidentally compare with int
// if (current == 0)  // Error!
if (current == State::IDLE)  // Correct
```

---

## Operator Overloading

### Custom Vector Class
```cpp
class Vector3 {
public:
    float x, y, z;
    
    Vector3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}
    
    // Addition
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    
    // Multiplication by scalar
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    // Dot product
    float dot(const Vector3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }
};

// Usage
Vector3 v1(1, 2, 3);
Vector3 v2(4, 5, 6);
Vector3 v3 = v1 + v2;       // (5, 7, 9)
Vector3 v4 = v1 * 2;        // (2, 4, 6)
float dot = v1.dot(v2);     // 32
```

---

## Embedded C++ Best Practices

### 1. Avoid Dynamic Memory
```cpp
// Bad (uses heap)
Sensor* sensor = new Sensor();

// Good (static allocation)
Sensor sensor;
// Or
static Sensor sensor;
```

---

### 2. Use Constexpr for Constants
```cpp
constexpr uint32_t CLOCK_FREQ = 72000000;
constexpr uint16_t PWM_PERIOD = 1000;
```

---

### 3. Inline Small Functions
```cpp
class GPIO {
public:
    inline void set() { PORT |= (1 << pin); }
    inline void clear() { PORT &= ~(1 << pin); }
};
```

---

### 4. Use References to Avoid Copies
```cpp
// Bad (copies large struct)
void process(SensorData data);

// Good (reference, no copy)
void process(const SensorData& data);
```

---

### 5. Mark Non-Changing Methods as const
```cpp
class Sensor {
private:
    float value;
    
public:
    float getValue() const {  // Promises not to modify object
        return value;
    }
};
```

---

## Real-World Example: Motor Controller

```cpp
class MotorController {
private:
    uint8_t pwm_pin;
    uint8_t dir_pin;
    int16_t current_speed;  // -100 to +100
    
public:
    MotorController(uint8_t pwm, uint8_t dir) 
        : pwm_pin(pwm), dir_pin(dir), current_speed(0) {
        pinMode(pwm_pin, OUTPUT);
        pinMode(dir_pin, OUTPUT);
    }
    
    void setSpeed(int16_t speed) {
        // Constrain
        if (speed > 100) speed = 100;
        if (speed < -100) speed = -100;
        
        current_speed = speed;
        
        // Set direction
        digitalWrite(dir_pin, speed >= 0);
        
        // Set PWM
        uint8_t duty = abs(speed) * 255 / 100;
        analogWrite(pwm_pin, duty);
    }
    
    void stop() {
        setSpeed(0);
    }
    
    int16_t getSpeed() const {
        return current_speed;
    }
};

// Usage
MotorController leftMotor(9, 8);
MotorController rightMotor(10, 11);

leftMotor.setSpeed(75);   // 75% forward
rightMotor.setSpeed(-50); // 50% reverse
```

---

## C vs C++ Comparison

| Feature | C | C++ |
|---------|---|-----|
| Functions | ✓ | ✓ |
| Structs | ✓ | ✓ (+ methods) |
| Classes | ✗ | ✓ |
| Encapsulation | Manual | Built-in |
| Templates | Macros | Type-safe templates |
| Namespaces | Prefixes | Built-in |
| Memory Safety | Manual | RAII, smart pointers |
| Overhead | Minimal | Zero (when done right) |

---

## Quick Reference

**Class:** `class Name { public: methods; private: data; };`  
**Constructor:** `Name(params) : member(value) {}`  
**Inheritance:** `class Derived : public Base`  
**Virtual:** `virtual returnType func() = 0;` (pure virtual)  
**Template:** `template<typename T> T func(T a)`  
**Namespace:** `namespace Name { content }`  
**Enum Class:** `enum class Name : uint8_t { A, B };`  
**Auto:** `auto var = value;`  
**Lambda:** `[capture](params) { body }`  
**Constexpr:** `constexpr int VAL = 10;`

---
