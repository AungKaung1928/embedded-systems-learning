# MATLAB & Simulink Basics for Embedded/Control Engineers

## Essential MATLAB Commands

### Basic Operations
```matlab
% Variables
x = 5;              % Assignment
y = 2*x + 3;        % Math operations
clear;              % Clear workspace
clc;                % Clear command window

% Arrays/Vectors
v = [1 2 3 4 5];    % Row vector
v = [1; 2; 3];      % Column vector
v = 0:0.1:10;       % 0 to 10, step 0.1
v = linspace(0,10,100); % 100 points from 0 to 10

% Matrix
A = [1 2 3; 4 5 6; 7 8 9];
B = A';             % Transpose
C = A * B;          % Matrix multiply
D = A .* B;         % Element-wise multiply
```

---

### Plotting
```matlab
% Basic plot
x = 0:0.1:2*pi;
y = sin(x);
plot(x, y);
xlabel('Time (s)');
ylabel('Amplitude');
title('Sine Wave');
grid on;

% Multiple plots
figure;
subplot(2,1,1);
plot(x, sin(x));
title('Sine');
subplot(2,1,2);
plot(x, cos(x));
title('Cosine');
```

---

### Control System Toolbox

#### Transfer Functions
```matlab
% Create transfer function
s = tf('s');
G = 1 / (s^2 + 2*s + 1);  % Second-order system

% Or using numerator/denominator
num = [1];
den = [1 2 1];
G = tf(num, den);

% Display
display(G);
```

#### System Analysis
```matlab
% Step response
step(G);
grid on;

% Bode plot
bode(G);
grid on;

% Root locus
rlocus(G);
grid on;

% Pole-zero map
pzmap(G);

% System info
[poles, zeros, gain] = zpkdata(G);
damp(G);  % Natural frequency and damping
```

---

### PID Controller Design

```matlab
% Plant transfer function
s = tf('s');
G = 1 / (s^2 + 10*s + 20);

% Create PID controller
Kp = 350;
Ki = 300;
Kd = 50;
C = pid(Kp, Ki, Kd);

% Closed-loop system
T = feedback(C*G, 1);

% Analyze
step(T);
title('Closed-Loop Step Response');
stepinfo(T)  % Rise time, overshoot, etc.
```

---

### PID Tuning
```matlab
% Auto-tune PID
C = pidtune(G, 'PID');

% Or use PID Tuner GUI
pidTuner(G, 'PID');
```

---

### Frequency Response
```matlab
% Bode diagram
bode(G);
[Gm, Pm, Wcg, Wcp] = margin(G);
fprintf('Gain Margin: %.2f dB\n', 20*log10(Gm));
fprintf('Phase Margin: %.2f deg\n', Pm);
```

---

### State-Space Representation
```matlab
% State-space: dx/dt = Ax + Bu, y = Cx + Du
A = [0 1; -2 -3];
B = [0; 1];
C = [1 0];
D = 0;
sys = ss(A, B, C, D);

% Convert to transfer function
G = tf(sys);

% Simulate
t = 0:0.01:10;
u = ones(size(t));  % Step input
lsim(sys, u, t);
```

---

### Discrete-Time Systems
```matlab
% Convert continuous to discrete (Ts = 0.1s)
Ts = 0.1;
Gz = c2d(G, Ts, 'tustin');  % Tustin/bilinear

% Z-transform
z = tf('z', Ts);
Hz = (z - 0.5) / (z^2 - 1.5*z + 0.5);

% Digital PID implementation
Kp = 2; Ki = 0.5; Kd = 0.1;
C_digital = pid(Kp, Ki, Kd, Ts);
```

---

## Simulink Basics

### Creating Simple Model

**Step 1: Open Simulink**
```matlab
simulink  % Opens Simulink start page
```

**Step 2: New Model**
- File → New → Model

**Step 3: Add Blocks**
Common blocks:
- **Sources:** Step, Sine Wave, Constant
- **Math:** Gain, Sum, Product
- **Continuous:** Transfer Fcn, PID Controller, Integrator
- **Sinks:** Scope, To Workspace

**Step 4: Connect & Configure**
- Drag blocks to canvas
- Click and drag to connect
- Double-click to configure parameters

---

### Example: PID Temperature Controller

**Blocks needed:**
1. Step (setpoint) → 100°C at t=0
2. Sum (error = setpoint - measurement)
3. PID Controller
4. Transfer Function (plant: 1/(10s+1))
5. Scope (plot output)

**Configuration:**
```
PID Block:
- Proportional: Kp = 10
- Integral: Ki = 1
- Derivative: Kd = 2

Plant Block:
- Numerator: [1]
- Denominator: [10 1]

Simulation:
- Stop time: 100
- Solver: ode45 (auto)
```

---

### Running Simulation
```matlab
% From command window
sim('model_name');

% Or in Simulink: Click Run button
```

---

### Export Data to Workspace
```matlab
% Add "To Workspace" block
% Variable name: output_data
% Save format: Array

% After simulation
plot(output_data);
```

---

## Control System Analysis Examples

### Example 1: Second-Order System Analysis
```matlab
% System parameters
wn = 2;      % Natural frequency (rad/s)
zeta = 0.5;  % Damping ratio

% Transfer function
s = tf('s');
G = wn^2 / (s^2 + 2*zeta*wn*s + wn^2);

% Step response
figure;
step(G);
grid on;

% Get info
info = stepinfo(G);
fprintf('Overshoot: %.2f%%\n', info.Overshoot);
fprintf('Rise Time: %.2f s\n', info.RiseTime);
fprintf('Settling Time: %.2f s\n', info.SettlingTime);
```

---

### Example 2: Root Locus Design
```matlab
% Open-loop plant
s = tf('s');
G = 1 / (s*(s+1)*(s+5));

% Root locus
figure;
rlocus(G);
sgrid;  % Add grid lines for damping ratio

% Find gain for specific damping
zeta_desired = 0.7;
[K, poles] = rlocfind(G);  % Click on plot
fprintf('Gain K = %.2f\n', K);
```

---

### Example 3: Frequency Response
```matlab
% System
s = tf('s');
G = 100 / ((s+1)*(s+10));

% Bode plot
figure;
bode(G);
grid on;

% Margins
[Gm, Pm, Wcg, Wcp] = margin(G);
fprintf('Gain Margin: %.2f dB at %.2f rad/s\n', 20*log10(Gm), Wcg);
fprintf('Phase Margin: %.2f deg at %.2f rad/s\n', Pm, Wcp);
```

---

## Practical Motor Control Example

```matlab
% DC Motor Model
% Electrical: V = R*i + L*di/dt + Ke*w
% Mechanical: J*dw/dt = Kt*i - B*w - Tload

% Parameters
R = 1;      % Resistance (Ohm)
L = 0.5;    % Inductance (H)
J = 0.01;   % Inertia (kg.m^2)
B = 0.1;    % Friction (N.m.s)
Kt = 0.01;  % Torque constant
Ke = 0.01;  % Back-EMF constant

% State-space model
A = [-R/L, -Ke/L; Kt/J, -B/J];
B = [1/L; 0];
C = [0, 1];  % Output: speed
D = 0;
motor = ss(A, B, C, D);

% Design PID for speed control
G = tf(motor);
C = pidtune(G, 'PID');

% Closed-loop
T = feedback(C*G, 1);

% Test
figure;
step(T);
title('Motor Speed Response');
xlabel('Time (s)');
ylabel('Speed (rad/s)');
grid on;
```

---

## Common Tasks Cheat Sheet

```matlab
% Load data
data = load('filename.mat');
data = readmatrix('file.csv');

% Save data
save('output.mat', 'variable');
writematrix(data, 'output.csv');

% Find system poles/zeros
poles = pole(G);
zeros = zero(G);

% Stability check
if all(real(poles) < 0)
    disp('System is stable');
end

% Bandwidth
bw = bandwidth(G);

% DC gain
dcgain(G);

% Final value theorem
finalvalue = dcgain(G);  % For step input
```

---

## Interview Questions

**Q: "How to check system stability in MATLAB?"**
```matlab
poles = pole(G);
if all(real(poles) < 0)
    disp('Stable');
end
% Or use: isstable(G)
```

**Q: "How to design PID in MATLAB?"**
```matlab
% Auto-tune
C = pidtune(G, 'PID');
% Or manual
C = pid(Kp, Ki, Kd);
```

**Q: "Convert continuous to discrete?"**
```matlab
Ts = 0.01;  % Sample time
Gz = c2d(G, Ts, 'tustin');
```

---

## Quick Reference

**Transfer Function:** `G = tf(num, den)`  
**Step Response:** `step(G)`  
**Bode Plot:** `bode(G)`  
**Root Locus:** `rlocus(G)`  
**PID Controller:** `C = pid(Kp, Ki, Kd)`  
**Closed-Loop:** `T = feedback(C*G, 1)`  
**Discrete System:** `Gz = c2d(G, Ts)`  
**Stability:** `isstable(G)` or check `pole(G)`

---
