# Embedded Systems Engineering - Complete Learning Repository

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2FC%2B%2B-green.svg)
![Status](https://img.shields.io/badge/status-Active-success.svg)

## 📚 Overview

A comprehensive, structured repository covering fundamental concepts in **Embedded Systems Engineering**, **Control Systems**, **Electrical Circuits**, **C/C++ Programming**, and **MATLAB/Simulink** - designed for engineers transitioning into embedded systems or preparing for technical interviews in Japan.

## 🎯 Who This Is For

- Mechanical/Electrical engineers transitioning to embedded systems
- Software engineers learning hardware programming
- Self-taught developers entering embedded/firmware roles

---

## 📁 Repository Structure

### **01_C_Programming/**
Foundation C programming for embedded systems with hands-on examples.
- **Files:** `01_hello_embedded.c` through `05_functions_modularity.c`
- Data types, pointers, memory management
- Bit manipulation and hardware register access
- Structures, unions, and efficient data organization
- Practical embedded patterns and real-time code
- **CHEAT_SHEET.txt** - Quick reference guide

### **02_Electrical_Circuits/**
Essential electrical circuit theory for embedded engineers.
- **File:** `01_basics.md`
- Ohm's Law, Kirchhoff's Laws, Power calculations
- Passive components (R, L, C, Diodes)
- Active components (Transistors, Op-Amps)
- Circuit analysis techniques (Voltage divider, Thevenin's theorem)
- AC/DC circuits and impedance

### **03_Embedded_Systems/**
Core embedded systems concepts with detailed explanations.
- **File:** `01_fundamentals.md`
- Microcontroller architecture (ARM Cortex-M, Harvard vs Von Neumann)
- Memory organization (Flash, SRAM, Stack, Heap)
- GPIO and digital I/O
- Communication protocols (UART, SPI, I2C, CAN)
- Timers, PWM, and hardware interrupts
- ADC/DAC converters
- Power management techniques

### **04_Control_Systems/**
Control theory fundamentals with practical implementations.
- **File:** `01_fundamentals.md`
- Open-loop vs Closed-loop control
- Complete PID controller theory and implementation
- PID tuning methods (Manual, Ziegler-Nichols)
- System modeling (Transfer functions, State-space)
- Stability analysis (Routh-Hurwitz)
- Digital control and Z-transform
- State machines and practical examples

### **05_MATLAB_Simulink/**
MATLAB/Simulink for control system design and simulation.
- **File:** `01_basics.md`
- Essential MATLAB commands and syntax
- Control System Toolbox
- PID design and auto-tuning
- Transfer function analysis
- Bode plots, root locus, step response
- Simulink modeling basics
- Discrete-time systems

### **06_CPP_Programming/**
C++ essentials for modern embedded systems development.
- **File:** `01_essentials.md`
- Classes and objects for hardware abstraction
- RAII pattern and resource management
- Templates and modern C++ features (C++11/14/17)
- Inheritance and polymorphism
- Best practices for embedded C++
- Real-world examples (motor controllers, sensors)

---

## 🚀 Quick Start

### Prerequisites
```bash
# C Compiler (GCC)
sudo apt-get install build-essential  # Linux
brew install gcc                       # macOS
# Windows: Install MinGW or use WSL

# Optional: ARM Cross-Compiler
sudo apt-get install gcc-arm-none-eabi

# MATLAB (for MATLAB/Simulink section)
# Download from MathWorks website
```

### Run Your First Program
```bash
# Clone repository
git clone https://github.com/AungKaung1928/embedded-systems-learning.git
cd embedded-systems-learning

# Compile and run first C program
cd 01_C_Programming
gcc -o hello 01_hello_embedded.c
./hello
```

---
