// Program 3: Structs and Bit Fields
// Structs organize sensor data; bit fields manipulate hardware registers

#include <stdio.h>
#include <stdint.h>

// ===== STRUCT FOR SENSOR DATA =====
// In a real drone, you'd have structs for IMU data, GPS data, etc.
typedef struct {
    uint16_t temperature;      // Temperature reading (in 0.1°C units)
    uint16_t humidity;         // Humidity percentage
    int16_t pressure;          // Pressure in hPa
    uint8_t sensor_status;     // 0=OK, 1=ERROR
} EnvironmentalSensor;

// ===== BIT FIELD FOR HARDWARE REGISTER =====
// Simulates a real hardware status register
typedef struct {
    uint8_t power_on : 1;      // Bit 0 - Power status
    uint8_t enabled : 1;       // Bit 1 - Enable flag
    uint8_t interrupt : 1;     // Bit 2 - Interrupt flag
    uint8_t reserved : 5;      // Bits 3-7 - Reserved
} MotorStatusRegister;

// ===== STRUCT FOR DRONE SENSOR FUSION =====
typedef struct {
    float accel_x, accel_y, accel_z;    // Accelerometer (from IMU)
    float gyro_x, gyro_y, gyro_z;       // Gyroscope (from IMU)
    uint32_t timestamp;                 // When this data was captured
    uint8_t data_ready;                 // 1 if new data available
} IMUSensorData;

int main() {
    printf("=== Structs and Bit Fields for Embedded Systems ===\n\n");
    
    // ===== EXAMPLE 1: Environmental Sensor Data =====
    printf("1. ENVIRONMENTAL SENSOR STRUCT:\n");
    
    EnvironmentalSensor env_sensor = {
        .temperature = 250,      // 25.0°C
        .humidity = 65,
        .pressure = 1013,
        .sensor_status = 0       // OK
    };
    
    printf("Temperature: %.1f°C\n", env_sensor.temperature / 10.0);
    printf("Humidity: %u%%\n", env_sensor.humidity);
    printf("Pressure: %d hPa\n", env_sensor.pressure);
    printf("Status: %s\n", env_sensor.sensor_status == 0 ? "OK" : "ERROR");
    printf("Struct size: %lu bytes\n", sizeof(EnvironmentalSensor));
    printf("\n");
    
    // ===== EXAMPLE 2: Bit Fields (Hardware Register) =====
    printf("2. BIT FIELD (Hardware Register):\n");
    
    MotorStatusRegister motor_status = {
        .power_on = 1,
        .enabled = 1,
        .interrupt = 0
    };
    
    printf("Power On: %u\n", motor_status.power_on);
    printf("Enabled: %u\n", motor_status.enabled);
    printf("Interrupt: %u\n", motor_status.interrupt);
    printf("Register size: %lu bytes\n", sizeof(MotorStatusRegister));
    printf("\n");
    
    // Modify individual bits
    printf("Setting interrupt flag...\n");
    motor_status.interrupt = 1;
    printf("Interrupt now: %u\n", motor_status.interrupt);
    printf("\n");
    
    // ===== EXAMPLE 3: IMU Sensor Data (Drone Application) =====
    printf("3. IMU SENSOR DATA (for autonomous drone):\n");
    
    IMUSensorData imu = {
        .accel_x = 0.05f,
        .accel_y = -0.02f,
        .accel_z = 9.81f,       // 1G gravity
        .gyro_x = 0.001f,
        .gyro_y = 0.002f,
        .gyro_z = -0.001f,
        .timestamp = 1000000,
        .data_ready = 1
    };
    
    printf("Accelerometer (m/s²): [%.2f, %.2f, %.2f]\n", 
           imu.accel_x, imu.accel_y, imu.accel_z);
    printf("Gyroscope (rad/s): [%.3f, %.3f, %.3f]\n", 
           imu.gyro_x, imu.gyro_y, imu.gyro_z);
    printf("Timestamp: %u\n", imu.timestamp);
    printf("Data Ready: %s\n", imu.data_ready ? "YES" : "NO");
    printf("Struct size: %lu bytes\n", sizeof(IMUSensorData));
    printf("\n");
    
    // ===== EXAMPLE 4: Array of Structs (Multiple Sensors) =====
    printf("4. ARRAY OF STRUCTS (4 environmental sensors on drone):\n");
    
    EnvironmentalSensor sensors[4];
    // Initialize with different readings
    uint16_t base_temps[] = {240, 250, 255, 248};
    
    for (int i = 0; i < 4; i++) {
        sensors[i].temperature = base_temps[i];
        sensors[i].humidity = 60 + i*2;
        sensors[i].pressure = 1013 - i;
        sensors[i].sensor_status = 0;
    }
    
    printf("Sensor Array:\n");
    for (int i = 0; i < 4; i++) {
        printf("  Sensor %d: %.1f°C, %u%%\n", i, 
               sensors[i].temperature / 10.0, 
               sensors[i].humidity);
    }
    printf("\n");
    
    // ===== EXAMPLE 5: Pointer to Struct (Common in Embedded) =====
    printf("5. POINTER TO STRUCT (function parameter):\n");
    
    EnvironmentalSensor *sensor_ptr = &env_sensor;
    printf("Via pointer - Temperature: %.1f°C\n", 
           sensor_ptr->temperature / 10.0);
    printf("Struct address: %p\n", (void*)sensor_ptr);
    
    return 0;
}
