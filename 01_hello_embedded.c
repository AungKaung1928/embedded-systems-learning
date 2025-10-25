// Program 1: Basic Data Types and Output
// Demonstrates fundamental C concepts for embedded systems

#include <stdio.h>
#include <stdint.h>  // For fixed-width integer types (important for embedded!)

int main() {
    printf("=== Embedded Systems C Basics ===\n\n");
    
    // Basic data types
    char sensor_id = 'A';           // Single character
    int temperature = 25;            // Integer (could be sensor reading)
    unsigned int count = 0;          // Unsigned (for counters, no negative values)
    float voltage = 3.3;             // Floating point (ADC readings often use this)
    
    printf("Sensor Information:\n");
    printf("Sensor ID: %c\n", sensor_id);
    printf("Temperature: %d°C\n", temperature);
    printf("Count: %u\n", count);
    printf("Voltage: %.2f V\n", voltage);
    printf("\n");
    
    // Memory sizes - important for embedded systems with limited RAM
    printf("Data Type Sizes (in bytes):\n");
    printf("char: %lu bytes\n", sizeof(char));
    printf("int: %lu bytes\n", sizeof(int));
    printf("float: %lu bytes\n", sizeof(float));
    printf("double: %lu bytes\n", sizeof(double));
    printf("\n");
    
    // Fixed-width types (used in embedded for predictable behavior across platforms)
    uint8_t status_byte = 255;       // 8-bit unsigned (like a register)
    uint16_t sensor_value = 65535;   // 16-bit unsigned (common ADC resolution)
    int32_t large_number = 2147483647; // 32-bit signed
    
    printf("Fixed-Width Integer Types:\n");
    printf("uint8_t max value: %u\n", status_byte);
    printf("uint16_t max value: %u\n", sensor_value);
    printf("int32_t max value: %d\n", large_number);
    
    return 0;
}
