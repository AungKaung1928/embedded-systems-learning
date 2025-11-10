# Electrical Circuit Fundamentals (電気回路基礎)

## Table of Contents
1. [Basic Laws](#basic-laws)
2. [Passive Components](#passive-components)
3. [Circuit Analysis](#circuit-analysis)
4. [AC Circuits](#ac-circuits)
5. [Active Components](#active-components)

---

## Basic Laws

### 1. Ohm's Law
**The most fundamental relationship in electronics**

```
V = I × R
I = V / R
R = V / I
```

Where:
- V = Voltage (Volts, V)
- I = Current (Amperes, A)
- R = Resistance (Ohms, Ω)

**Example:**
- If R = 100Ω and I = 0.05A, then V = 100 × 0.05 = 5V
- If V = 12V and R = 1kΩ, then I = 12/1000 = 0.012A = 12mA

**Interview Tip:** Always check units! mA → A, kΩ → Ω

---

### 2. Kirchhoff's Current Law (KCL)
**"Current in = Current out" at any node**

```
∑ I_in = ∑ I_out
or
∑ I = 0 (at any node)
```

**Explanation:** 
Current cannot accumulate at a point. Whatever flows in must flow out.

**Example:**
```
    I1 = 5A →  ● (Node)  → I2 = 3A
                ↓
              I3 = ?
```
Answer: I3 = I1 - I2 = 5 - 3 = 2A (flowing down)

---

### 3. Kirchhoff's Voltage Law (KVL)
**"Sum of voltages around any closed loop = 0"**

```
∑ V = 0 (around closed loop)
```

**Explanation:** 
Energy is conserved. Voltage rises equal voltage drops around a loop.

**Example:**
```
Battery (+12V) → R1 (voltage drop V1) → R2 (voltage drop V2) → Back to Battery (-)

V_battery - V1 - V2 = 0
12V = V1 + V2
```

---

### 4. Power Formulas
**Power = Rate of energy use**

```
P = V × I
P = I² × R
P = V² / R
```

Where P = Power (Watts, W)

**Example:**
- LED with V = 2V, I = 20mA → P = 2 × 0.02 = 0.04W = 40mW
- Resistor with R = 100Ω, I = 0.1A → P = (0.1)² × 100 = 1W

**Important:** Component power rating must exceed calculated power!

---

## Passive Components

### 1. Resistors (抵抗)
**Oppose current flow, dissipate energy as heat**

**Series Connection:**
```
R_total = R1 + R2 + R3 + ...
```
- Same current through all resistors
- Voltages add up

**Parallel Connection:**
```
1/R_total = 1/R1 + 1/R2 + 1/R3 + ...
```
- Same voltage across all resistors
- Currents add up

**Special Case (2 resistors in parallel):**
```
R_total = (R1 × R2) / (R1 + R2)
```

**Example:**
- R1 = 100Ω, R2 = 100Ω in series → R_total = 200Ω
- R1 = 100Ω, R2 = 100Ω in parallel → R_total = 50Ω

**Color Code:**
```
Black  = 0    Green = 5
Brown  = 1    Blue  = 6
Red    = 2    Violet= 7
Orange = 3    Gray  = 8
Yellow = 4    White = 9

4th band: Multiplier (10^n)
5th band: Tolerance (Gold=5%, Silver=10%)
```

---

### 2. Capacitors (コンデンサ)
**Store energy in electric field**

**Key Properties:**
- **Blocks DC** (after charging)
- **Passes AC** (higher frequency = lower impedance)
- **Stores charge:** Q = C × V

**Energy Stored:**
```
E = ½ CV²
```

**Series Connection:**
```
1/C_total = 1/C1 + 1/C2 + ...
```
(Opposite of resistors!)

**Parallel Connection:**
```
C_total = C1 + C2 + C3 + ...
```

**Time Constant (RC Circuit):**
```
τ = R × C (seconds)
```
- Time to charge to 63.2% of final voltage
- Time to discharge to 36.8% of initial voltage

**Example:**
- R = 10kΩ, C = 100μF → τ = 10,000 × 0.0001 = 1 second

**Applications:**
- Filtering (smooth DC power supplies)
- Timing circuits
- Coupling/decoupling AC signals
- Energy storage

---

### 3. Inductors (インダクタ)
**Store energy in magnetic field**

**Key Properties:**
- **Opposes changes in current**
- **Passes DC** (after steady state)
- **Blocks AC** (higher frequency = higher impedance)

**Voltage-Current Relationship:**
```
V = L × (dI/dt)
```
Voltage proportional to rate of current change

**Energy Stored:**
```
E = ½ LI²
```

**Series Connection:**
```
L_total = L1 + L2 + L3 + ...
```

**Parallel Connection:**
```
1/L_total = 1/L1 + 1/L2 + ...
```

**Time Constant (RL Circuit):**
```
τ = L / R (seconds)
```

**Applications:**
- Filters (block high-frequency noise)
- Transformers
- DC-DC converters (switching power supplies)
- Motor windings

---

## Circuit Analysis

### 1. Voltage Divider
**Most common circuit in electronics**

```
       ┌──R1──┐
Vin ───┤      ├─── Vout
       └──R2──┘
       
Vout = Vin × (R2 / (R1 + R2))
```

**Example:**
- Vin = 5V, R1 = 1kΩ, R2 = 1kΩ
- Vout = 5 × (1/(1+1)) = 2.5V

**Use Case:** Read analog sensors, reduce voltage levels

---

### 2. Current Divider
**Split current between parallel branches**

```
       ┌──R1──┐
Iin ───┤      ├───
       └──R2──┘

I1 = Iin × (R2 / (R1 + R2))
I2 = Iin × (R1 / (R1 + R2))
```

Note: Current prefers the path of **least resistance**

---

### 3. Thevenin's Theorem
**Any complex circuit can be simplified to:**
- Single voltage source (V_th)
- Single series resistor (R_th)

**Steps:**
1. Find open-circuit voltage → V_th
2. Find equivalent resistance (short voltage sources, open current sources) → R_th

**Use:** Simplify complex circuits for analysis

---

### 4. Norton's Theorem
**Dual of Thevenin: Current source + parallel resistor**

```
I_n = V_th / R_th
R_n = R_th
```

---

## AC Circuits

### 1. AC Voltage Basics
**Alternating Current: voltage/current changes direction periodically**

```
v(t) = V_peak × sin(2πft + φ)
```

Where:
- V_peak = Maximum voltage
- f = Frequency (Hz)
- φ = Phase shift (degrees or radians)

**RMS (Root Mean Square):**
```
V_rms = V_peak / √2 ≈ V_peak × 0.707
```
- AC voltmeters show RMS values
- Example: 120V AC (USA) = 170V peak

---

### 2. Impedance (交流インピーダンス)
**AC equivalent of resistance**

**Resistor:** Z_R = R (no phase shift)

**Capacitor:** 
```
Z_C = 1 / (2πfC) = 1 / (jωC)
```
- Lower impedance at high frequency
- Current leads voltage by 90°

**Inductor:**
```
Z_L = 2πfL = jωL
```
- Higher impedance at high frequency
- Current lags voltage by 90°

---

### 3. RC Filter Circuits

**Low-Pass Filter (LPF):**
```
     R
Vin ─┤├─┬─ Vout
        ─┴─ C
         ─
         
Cutoff frequency: f_c = 1/(2πRC)
```
- Passes low frequencies, blocks high
- Use: Smooth PWM signals, anti-aliasing

**High-Pass Filter (HPF):**
```
        C
Vin ─┤├──┬─ Vout
         ├─ R
         
f_c = 1/(2πRC)
```
- Passes high frequencies, blocks low
- Use: Remove DC offset, AC coupling

---

### 4. Resonance (LC Circuit)
**Inductor + Capacitor: frequency-selective**

```
Resonant frequency: f_r = 1 / (2π√(LC))
```

At resonance:
- Z_L = Z_C (impedances cancel)
- Circuit impedance minimum (series) or maximum (parallel)

**Applications:**
- Radio tuning
- Filters
- Oscillators

---

## Active Components

### 1. Diodes (ダイオード)
**One-way valve for current**

**Symbol:**
```
    Anode  │ Cathode
    ───▶│├───
```

**Properties:**
- Forward voltage drop: ~0.7V (silicon), ~0.3V (Schottky)
- Blocks reverse current (until breakdown)

**Applications:**
- Rectification (AC to DC)
- Voltage clamping
- Protection circuits

**LED (Light Emitting Diode):**
- Forward voltage: 1.8-3.3V (depends on color)
- Typical current: 10-20mA
- **Always use current-limiting resistor!**

**Calculate LED resistor:**
```
R = (V_supply - V_led) / I_led

Example: 5V supply, 2V red LED, 20mA
R = (5 - 2) / 0.02 = 150Ω
```

---

### 2. Transistors (トランジスタ)

#### **BJT (Bipolar Junction Transistor)**

**NPN Configuration (most common):**
```
    C (Collector)
    │
  ──┤
    │╲
B ──│ ╲ ← Base
    │  │
    ╲ │
     ╲│
    ──│
      │
      E (Emitter)
```

**Key Formulas:**
```
I_C = β × I_B
where β (gain) typically 100-200

V_BE ≈ 0.7V (when ON)
```

**Saturation (fully ON):**
```
V_CE ≈ 0.2V
```

**Use as Switch:**
- I_B = 0 → Transistor OFF (open circuit)
- I_B > I_C/β → Transistor ON (closed circuit)

**Example:**
```
Control 100mA LED with 5V supply, β=100
I_B needed = 100mA / 100 = 1mA
R_base = (5V - 0.7V) / 1mA = 4.3kΩ
```

---

#### **MOSFET (Metal-Oxide-Semiconductor FET)**

**N-Channel MOSFET (most common):**
```
    D (Drain)
    │
  ──│──
    │ │
G ──│ │ ← Gate
    │ │
  ──│──
    │
    S (Source)
```

**Key Properties:**
- **Voltage-controlled** (not current like BJT)
- Very high input impedance (essentially no gate current)
- **V_GS(th)**: Threshold voltage (typically 2-4V)
- **R_DS(on)**: On-resistance when fully conducting

**Use as Switch:**
- V_GS < V_th → OFF (open)
- V_GS > V_th + 2V → ON (closed)

**Advantages over BJT:**
- No base current required
- Faster switching
- Better for high-power applications

**Applications:**
- Motor drivers
- Power switching
- PWM control
- Logic-level switching

---

### 3. Operational Amplifiers (Op-Amp)

**Ideal Op-Amp Rules:**
1. Infinite input impedance (no current into inputs)
2. Zero output impedance
3. Infinite gain
4. No voltage difference between inputs (in feedback)

**Inverting Amplifier:**
```
      R_f
      ┌─┐
      │ │
Vin ─┤ ├─┬──┐
  R_in  │  │  │
      │ │  │ ├── Vout
      └─┘  │  │
       ┌───┴──┘
    ───│─ (Op-Amp)
       └─── ┬
            │
           GND

Vout = -(R_f / R_in) × Vin
```

**Non-Inverting Amplifier:**
```
Vout = (1 + R_f / R_in) × Vin
```

**Voltage Follower (Buffer):**
```
Vout = Vin (unity gain, high input impedance)
```

---

## Essential Formulas Quick Reference

```
Ohm's Law:        V = IR
Power:            P = VI = I²R = V²/R
KCL:              ∑I = 0 (at node)
KVL:              ∑V = 0 (around loop)

Resistors Series:   R_total = R1 + R2 + ...
Resistors Parallel: 1/R_total = 1/R1 + 1/R2 + ...

Capacitor Energy:   E = ½CV²
Inductor Energy:    E = ½LI²

RC Time Constant:   τ = RC
RL Time Constant:   τ = L/R

AC Impedance:       Z_C = 1/(2πfC)
                    Z_L = 2πfL

Voltage Divider:    Vout = Vin × (R2/(R1+R2))

LED Resistor:       R = (Vsupply - Vled) / Iled

BJT:                I_C = β × I_B
```

---

## Practice Problems

**Problem 1:**
Given: Vin = 12V, R1 = 4.7kΩ, R2 = 4.7kΩ
Find: Vout, Power in R1

**Problem 2:**
Design LED circuit: 5V supply, 2V red LED, 20mA current
Find: Resistor value and power rating

**Problem 3:**
RC circuit: R = 10kΩ, C = 100μF
Find: Time constant, voltage after 1 second

**Answers:**
1. Vout = 6V, P_R1 = 7.66mW
2. R = 150Ω, P = 60mW (use 1/4W resistor)
3. τ = 1s, V = 63.2% of final value

---
