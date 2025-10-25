// Program 2: Pointers and Arrays
// Pointers are CRITICAL for embedded systems (hardware register access!)

#include <stdio.h>
#include <stdint.h>

int main() {
    printf("=== Pointers and Arrays for Embedded Systems ===\n\n");
    
    // ===== ARRAYS (simulating sensor buffer) =====
    printf("1. ARRAYS - Storing multiple sensor readings:\n");
    uint16_t sensor_readings[5] = {100, 105, 98, 102, 101};  // ADC readings
    
    printf("Sensor readings: ");
    for (int i = 0; i < 5; i++) {
        printf("%u ", sensor_readings[i]);
    }
    printf("\n\n");
    
    // ===== POINTERS (simulating hardware register access) =====
    printf("2. POINTERS - Direct memory access:\n");
    
    int temperature = 25;
    int *ptr_temp = &temperature;  // Pointer to temperature variable
    
    printf("Temperature value: %d\n", temperature);
    printf("Temperature address: %p\n", (void*)&temperature);
    printf("Pointer value (address): %p\n", (void*)ptr_temp);
    printf("Dereference pointer: %d\n", *ptr_temp);
    printf("\n");
    
    // ===== POINTER ARITHMETIC (common in embedded) =====
    printf("3. POINTER ARITHMETIC - Iterating through array:\n");
    uint16_t *sensor_ptr = sensor_readings;  // Point to first element
    
    printf("Using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("Address: %p, Value: %u\n", (void*)sensor_ptr, *sensor_ptr);
        sensor_ptr++;  // Move pointer to next element
    }
    printf("\n");
    
    // ===== SIMULATING HARDWARE REGISTER ACCESS =====
    printf("4. HARDWARE REGISTER ACCESS (simulated):\n");
    
    // In real embedded systems, hardware registers are at fixed memory addresses
    // Example: PORT A register might be at address 0x40020000
    
    uint32_t hw_register_value = 0xDEADBEEF;
    uint32_t *hw_register = &hw_register_value;  // Simulate register pointer
    
    printf("Hardware Register Address: %p\n", (void*)hw_register);
    printf("Hardware Register Value: 0x%X\n", *hw_register);
    
    // Reading from "register"
    uint32_t read_value = *hw_register;
    printf("Read value from register: 0x%X\n", read_value);
    
    // Writing to "register"
    *hw_register = 0xCAFEBABE;
    printf("After write, register value: 0x%X\n", *hw_register);
    printf("\n");
    
    // ===== ARRAY OF POINTERS =====
    printf("5. ARRAY OF POINTERS - Multiple sensor references:\n");
    int sensor1 = 30, sensor2 = 40, sensor3 = 50;
    int *sensor_ptrs[3] = {&sensor1, &sensor2, &sensor3};
    
    for (int i = 0; i < 3; i++) {
        printf("Sensor %d value: %d\n", i+1, *sensor_ptrs[i]);
    }
    
    return 0;
}
