================================================================================
             C PROGRAMMING FOR EMBEDDED SYSTEMS - COMPLETE PACKAGE
                    For Mechanical Engineer Transitioning to Embedded
================================================================================
This package contains everything you need to start learning C for embedded
systems development, with a focus on practical applications relevant to
embedded control systems and real-time applications
================================================================================
FILES INCLUDED
================================================================================
LEARNING MATERIALS:
  ✓ C_EMBEDDED_GUIDE.txt    - Comprehensive 8-section guide with concepts,
                              patterns, best practices, and learning path
  ✓ CHEAT_SHEET.txt         - Quick reference guide (print this!)
  ✓ README.txt              - This file
C PROGRAM FILES:
  ✓ 01_hello_embedded.c     - Data types, printf, memory sizes
  ✓ 02_pointers_arrays.c    - Pointers, arrays, hardware register access
  ✓ 03_structs_bitfields.c  - Structs, bit fields, data organization
  ✓ 04_practical_tasks.c    - ADC reading, telemetry, filtering, validation
  ✓ 05_functions_modularity.c - Functions, modularity, real-time loops
================================================================================
HOW TO USE THIS PACKAGE
================================================================================
STEP 1: Read the Materials
  1. Start with C_EMBEDDED_GUIDE.txt sections 1-3 (understand concepts)
  2. Keep CHEAT_SHEET.txt next to you for quick reference
  3. Print CHEAT_SHEET.txt if possible
STEP 2: Compile and Run Each Program
  $ gcc -o 01_hello_embedded 01_hello_embedded.c && ./01_hello_embedded
  $ gcc -o 02_pointers_arrays 02_pointers_arrays.c && ./02_pointers_arrays
  $ gcc -o 03_structs_bitfields 03_structs_bitfields.c && ./03_structs_bitfields
  $ gcc -o 04_practical_tasks 04_practical_tasks.c && ./04_practical_tasks
  $ gcc -o 05_functions_modularity 05_functions_modularity.c -lm && ./05_functions_modularity
STEP 3: Study and Modify
  - Read each program's comments carefully
  - Modify the values and see how output changes
  - Experiment: add printf() statements, change logic
  - Compile with warnings: gcc -Wall -Wextra
STEP 4: Build Your Own
  - Combine concepts from multiple programs
  - Create simple projects: calculator, temperature logger
  - Gradually increase complexity
STEP 5: Progress Through Learning Path
  - Follow the 12-week path in C_EMBEDDED_GUIDE.txt section 6
  - Do hands-on projects with real hardware (Arduino, STM32)
  - Practice C++ after mastering C
================================================================================
QUICK START (30 SECONDS)
================================================================================
Linux/Mac:
  $ gcc -o 01_hello_embedded 01_hello_embedded.c
  $ ./01_hello_embedded
Windows (with GCC installed):
  > gcc -o 01_hello_embedded.exe 01_hello_embedded.c
  > 01_hello_embedded.exe
Expected output:
  === Embedded Systems C Basics ===
  
  Sensor Information:
  Sensor ID: A
  Temperature: 25°C
  Count: 0
  Voltage: 3.30 V
  ... (more output)
================================================================================
PROGRAM DESCRIPTIONS
================================================================================
PROGRAM 1: 01_hello_embedded.c (5 min read)
  Teaches: Basic data types, printf formatting, memory sizes
  Key concepts: Variables, unsigned vs signed, fixed-width types
  Relevance: Understanding what types to use for different sensor readings
  
  Example output: Shows how much RAM each data type uses
  Time to complete: 30 minutes of study + practice
PROGRAM 2: 02_pointers_arrays.c (15 min read)
  Teaches: Pointers, dereferencing, pointer arithmetic, array access
  Key concepts: Memory addresses, hardware register simulation
  Relevance: Critical for reading/writing hardware registers in control systems
  
  Example: Simulates reading sensor data via pointer arithmetic
  Time to complete: 1-2 hours (pointers take time to understand)
PROGRAM 3: 03_structs_bitfields.c (15 min read)
  Teaches: Struct organization, bit fields, pointer to struct
  Key concepts: Data grouping, hardware register layout, arrays of structs
  Relevance: Organizing sensor data (IMU, environmental, motion control, etc.)
  
  Example: IMU sensor data structure, hardware register bit fields
  Time to complete: 1-2 hours
PROGRAM 4: 04_practical_tasks.c (20 min read)
  Teaches: Practical embedded patterns, state management, filtering
  Key concepts: ADC conversion, conditional logic, data filtering
  Relevance: Real-time telemetry, battery management, sensor fusion
  
  Example: Simulate system state changes based on battery level
  Time to complete: 2-3 hours
PROGRAM 5: 05_functions_modularity.c (20 min read)
  Teaches: Function design, modularity, sensor drivers, real-time loops
  Key concepts: Clean code organization, abstraction, filter implementation
  Relevance: How to structure production embedded code
