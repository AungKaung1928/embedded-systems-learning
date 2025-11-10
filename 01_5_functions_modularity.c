// Program 5: Functions and Modularity
// Demonstrates how to write clean, reusable embedded code

#include <stdio.h>
#include <stdint.h>
#include <math.h>

// ===== SENSOR DRIVER FUNCTIONS =====

// Initialize a sensor (common embedded pattern)
void sensor_init(uint8_t sensor_id) {
    printf("[INIT] Sensor %u initialized\n", sensor_id);
    // In real embedded code, this would configure GPIO, I2C, SPI, etc.
}

// Read raw value from ADC
uint16_t sensor_read_raw(uint8_t channel) {
    // Simulate ADC read from a channel
    // In real code, this reads from actual hardware register
    static uint16_t sim_values[] = {512, 1024, 2048, 4095};
    return sim_values[channel % 4];
}

// Convert raw ADC to physical units
float adc_to_voltage(uint16_t raw_value) {
    // 12-bit ADC (0-4095) maps to 0-3.3V
    return (raw_value / 4095.0) * 3.3;
}

// Convert voltage to temperature
int16_t voltage_to_temperature(float voltage) {
    // TMP36 sensor: 0.5V = -40°C, 1.5V = 25°C, 2.5V = 85°C
    return (int16_t)((voltage - 0.5) * 100);
}

// ===== MOTOR CONTROL FUNCTIONS =====

// Set motor speed (0-255)
void motor_set_speed(uint8_t motor_id, uint8_t speed) {
    if (speed > 100) {
        printf("[MOTOR] Motor %u: Speed clamped to 100%% (input was %u)\n", 
               motor_id, speed);
        speed = 100;
    }
    printf("[MOTOR] Motor %u set to %u%%\n", motor_id, speed);
}

// Smooth motor speed ramp (for drone acceleration)
void motor_ramp_speed(uint8_t motor_id, uint8_t target_speed, uint8_t ramp_steps) {
    printf("[MOTOR] Ramping motor %u to %u%% in %u steps: ",
           motor_id, target_speed, ramp_steps);
    
    for (uint8_t i = 0; i <= ramp_steps; i++) {
        uint8_t current_speed = (target_speed * i) / ramp_steps;
        printf("%u%% ", current_speed);
    }
    printf("\n");
}

// ===== FILTER FUNCTIONS =====

// Simple low-pass filter for sensor noise reduction
typedef struct {
    float alpha;         // Filter coefficient (0-1)
    float last_output;   // Previous filtered value
} LowPassFilter;

void filter_init(LowPassFilter *filter, float alpha) {
    filter->alpha = alpha;
    filter->last_output = 0.0;
}

float filter_apply(LowPassFilter *filter, float input) {
    filter->last_output = (filter->alpha * input) + 
                         ((1.0 - filter->alpha) * filter->last_output);
    return filter->last_output;
}

// ===== SAFETY CHECK FUNCTIONS =====

// Check if value is within acceptable range
int8_t check_range(int16_t value, int16_t min, int16_t max, const char *name) {
    if (value < min || value > max) {
        printf("[ERROR] %s out of range: %d (min: %d, max: %d)\n",
               name, value, min, max);
        return -1;  // Error
    }
    return 0;  // OK
}

// Validate all drone parameters
int8_t validate_drone_state(int16_t altitude, uint8_t battery, float temp) {
    int errors = 0;
    
    printf("[VALIDATION] Checking drone state...\n");
    
    if (check_range(altitude, 0, 500, "Altitude (m)") != 0) errors++;
    if (check_range(battery, 0, 100, "Battery (%)") != 0) errors++;
    if (check_range((int16_t)temp, -20, 60, "Temperature (°C)") != 0) errors++;
    
    if (errors == 0) {
        printf("[VALIDATION] ✓ All parameters OK\n");
        return 0;
    } else {
        printf("[VALIDATION] ✗ %d errors found\n", errors);
        return -1;
    }
}

// ===== MAIN PROGRAM =====

int main() {
    printf("=== Functions and Modularity for Embedded Systems ===\n\n");
    
    // ===== TASK 1: Sensor Reading Pipeline =====
    printf("1. SENSOR READING PIPELINE:\n");
    sensor_init(0);
    
    printf("Reading from channel 1...\n");
    uint16_t raw = sensor_read_raw(1);
    float voltage = adc_to_voltage(raw);
    int16_t temperature = voltage_to_temperature(voltage);
    
    printf("Raw ADC: %u -> Voltage: %.2fV -> Temperature: %d°C\n\n",
           raw, voltage, temperature);
    
    // ===== TASK 2: Motor Control with Safety =====
    printf("2. MOTOR CONTROL:\n");
    motor_set_speed(0, 50);
    motor_set_speed(1, 75);
    motor_set_speed(2, 150);  // Will be clamped
    printf("\n");
    
    // ===== TASK 3: Smooth Motor Ramp =====
    printf("3. MOTOR ACCELERATION RAMP:\n");
    motor_ramp_speed(0, 100, 5);
    printf("\n");
    
    // ===== TASK 4: Sensor Filtering =====
    printf("4. SENSOR FILTERING (Noise Reduction):\n");
    LowPassFilter temp_filter;
    filter_init(&temp_filter, 0.3);  // Alpha = 0.3
    
    int16_t noisy_readings[] = {25, 28, 26, 24, 27, 25, 26};
    printf("Raw readings:     ");
    for (int i = 0; i < 7; i++) printf("%d ", noisy_readings[i]);
    printf("\n");
    
    printf("Filtered values:  ");
    for (int i = 0; i < 7; i++) {
        float filtered = filter_apply(&temp_filter, noisy_readings[i]);
        printf("%.1f ", filtered);
    }
    printf("\n\n");
    
    // ===== TASK 5: State Validation =====
    printf("5. DRONE STATE VALIDATION:\n");
    printf("\nTest A: Valid parameters\n");
    validate_drone_state(100, 75, 25.5);
    
    printf("\nTest B: Invalid parameters\n");
    validate_drone_state(600, 120, -25);  // All out of range
    printf("\n");
    
    // ===== TASK 6: Processing Loop (Embedded Real-Time Loop) =====
    printf("6. MAIN EMBEDDED LOOP (Real-time simulation):\n");
    printf("Cycle | Raw   | Voltage | Temp | Filter | Status\n");
    printf("------+-------+---------+------+--------+--------\n");
    
    LowPassFilter rt_filter;
    filter_init(&rt_filter, 0.2);
    
    for (int cycle = 0; cycle < 5; cycle++) {
        uint16_t raw = sensor_read_raw(cycle);
        float voltage = adc_to_voltage(raw);
        int16_t temp = voltage_to_temperature(voltage);
        float filtered = filter_apply(&rt_filter, temp);
        
        const char *status = "OK";
        if (temp > 50) status = "HOT";
        if (temp < 0) status = "COLD";
        
        printf("%d    | %4u  | %.2f    | %d   | %.1f  | %s\n",
               cycle, raw, voltage, temp, filtered, status);
    }
    printf("\n");
    
    // ===== TASK 7: Memory Efficient Code =====
    printf("7. MEMORY USAGE ANALYSIS:\n");
    printf("Function size estimation:\n");
    printf("  sensor_init: ~10 bytes (code)\n");
    printf("  motor_set_speed: ~20 bytes (code)\n");
    printf("  LowPassFilter struct: %lu bytes (data)\n", sizeof(LowPassFilter));
    printf("Total program code: typically 2-10 KB for simple embedded app\n");
    printf("Total RAM used: ~100 bytes (varies by platform)\n");
    
    return 0;
}
