// Program 4: Practical Embedded Tasks Simulation
// Simulates real embedded work: sensor reading, state management, simple logic

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ===== SENSOR SIMULATION =====
typedef struct {
    uint16_t raw_adc;      // Raw ADC value (0-4095 for 12-bit ADC)
    float voltage;         // Converted to voltage
    int8_t temperature;    // Converted to temperature
} ADCReading;

// ===== LED/MOTOR CONTROL STATE =====
typedef enum {
    STATE_OFF = 0,
    STATE_ON = 1,
    STATE_BLINKING = 2,
    STATE_ERROR = 3
} DeviceState;

// ===== SIMPLE DRONE TELEMETRY =====
typedef struct {
    uint8_t battery_percent;
    int16_t altitude;      // meters
    uint8_t signal_strength; // 0-100%
    DeviceState motor_state;
} DroneTelemetry;

// Function to read ADC (simulated)
ADCReading read_ADC_channel(uint16_t raw_value) {
    ADCReading reading;
    reading.raw_adc = raw_value;
    
    // Convert 12-bit ADC (0-4095) to 0-3.3V
    reading.voltage = (raw_value / 4095.0) * 3.3;
    
    // Convert voltage to temperature (simplified: 0V = -40°C, 3.3V = 85°C)
    reading.temperature = (int8_t)((-40) + (reading.voltage / 3.3) * 125);
    
    return reading;
}

// Function to control device based on conditions (embedded logic)
void update_device_state(DroneTelemetry *telem) {
    if (telem->battery_percent < 10) {
        telem->motor_state = STATE_ERROR;
    } else if (telem->battery_percent < 30) {
        telem->motor_state = STATE_BLINKING;  // Low power mode
    } else if (telem->signal_strength > 50) {
        telem->motor_state = STATE_ON;
    } else {
        telem->motor_state = STATE_OFF;
    }
}

// Function to get state name
const char* get_state_name(DeviceState state) {
    switch(state) {
        case STATE_OFF: return "OFF";
        case STATE_ON: return "ON";
        case STATE_BLINKING: return "BLINKING";
        case STATE_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

int main() {
    printf("=== Practical Embedded Systems Tasks ===\n\n");
    
    // ===== TASK 1: Read and Convert ADC Values =====
    printf("1. ADC SENSOR READING AND CONVERSION:\n");
    
    uint16_t adc_samples[] = {0, 1024, 2048, 4095};
    const char* labels[] = {"Minimum", "1/4 Scale", "1/2 Scale", "Maximum"};
    
    for (int i = 0; i < 4; i++) {
        ADCReading reading = read_ADC_channel(adc_samples[i]);
        printf("%s (0x%X): %.2fV -> %d°C\n", 
               labels[i], 
               reading.raw_adc,
               reading.voltage,
               reading.temperature);
    }
    printf("\n");
    
    // ===== TASK 2: Drone Telemetry and State Management =====
    printf("2. DRONE TELEMETRY AND STATE CONTROL:\n");
    
    // Scenario 1: Normal flight
    printf("\nScenario A: Normal flight conditions\n");
    DroneTelemetry drone1 = {
        .battery_percent = 75,
        .altitude = 50,
        .signal_strength = 85,
        .motor_state = STATE_OFF
    };
    
    update_device_state(&drone1);
    printf("Battery: %u%%, Altitude: %dm, Signal: %u%%\n",
           drone1.battery_percent, drone1.altitude, drone1.signal_strength);
    printf("Motor State: %s\n\n", get_state_name(drone1.motor_state));
    
    // Scenario 2: Low battery warning
    printf("Scenario B: Low battery warning\n");
    DroneTelemetry drone2 = {
        .battery_percent = 25,
        .altitude = 30,
        .signal_strength = 70,
        .motor_state = STATE_OFF
    };
    
    update_device_state(&drone2);
    printf("Battery: %u%%, Altitude: %dm, Signal: %u%%\n",
           drone2.battery_percent, drone2.altitude, drone2.signal_strength);
    printf("Motor State: %s\n\n", get_state_name(drone2.motor_state));
    
    // Scenario 3: Critical error
    printf("Scenario C: Critical battery level\n");
    DroneTelemetry drone3 = {
        .battery_percent = 5,
        .altitude = 10,
        .signal_strength = 40,
        .motor_state = STATE_OFF
    };
    
    update_device_state(&drone3);
    printf("Battery: %u%%, Altitude: %dm, Signal: %u%%\n",
           drone3.battery_percent, drone3.altitude, drone3.signal_strength);
    printf("Motor State: %s (CRITICAL!)\n\n", get_state_name(drone3.motor_state));
    
    // ===== TASK 3: Data Logging Loop =====
    printf("3. SIMULATED DATA LOGGING (5 timesteps):\n");
    printf("Time\tBattery\tAltitude\tMotor State\n");
    printf("----\t-------\t--------\t-----------\n");
    
    for (int t = 0; t < 5; t++) {
        drone1.battery_percent -= 5;  // Battery drains
        drone1.altitude += 10;        // Ascending
        
        update_device_state(&drone1);
        
        printf("%d\t%u%%\t%dm\t%s\n", 
               t, drone1.battery_percent, drone1.altitude, 
               get_state_name(drone1.motor_state));
    }
    printf("\n");
    
    // ===== TASK 4: Bit Manipulation (Embedded Flags) =====
    printf("4. BIT MANIPULATION (Status Flags):\n");
    
    uint8_t status_flags = 0;  // All flags off
    
    // Set individual flags
    status_flags |= (1 << 0);  // Set bit 0: Motor enabled
    status_flags |= (1 << 2);  // Set bit 2: Sensor ready
    
    printf("Status flags (binary): ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (status_flags >> i) & 1);
    }
    printf(" (0x%02X)\n", status_flags);
    
    // Check specific flags
    printf("Bit 0 (Motor): %s\n", (status_flags & (1 << 0)) ? "ON" : "OFF");
    printf("Bit 1 (Sensor): %s\n", (status_flags & (1 << 1)) ? "ON" : "OFF");
    printf("Bit 2 (Ready): %s\n", (status_flags & (1 << 2)) ? "ON" : "OFF");
    printf("\n");
    
    // ===== TASK 5: Simple Filter Simulation =====
    printf("5. SENSOR FILTERING (Moving Average):\n");
    
    uint16_t sensor_buffer[5] = {100, 102, 98, 101, 99};
    uint32_t sum = 0;
    
    for (int i = 0; i < 5; i++) {
        sum += sensor_buffer[i];
    }
    uint16_t average = sum / 5;
    
    printf("Raw readings: ");
    for (int i = 0; i < 5; i++) {
        printf("%u ", sensor_buffer[i]);
    }
    printf("\nFiltered (average): %u\n", average);
    
    return 0;
}
