# 🤖 Autonomous Maze Solver Bot (Right-Wall Follower)

Welcome to the repository for my **Autonomous Maze Solver Robot** project, developed using **Arduino Uno + Adafruit Motor Shield v1**, **IR sensors**, and a basic **right-hand wall-following algorithm**. This project represents my journey into the world of embedded systems, sensor integration, and autonomous robot navigation.

---

## 🚀 Features

- ✅ Right-Wall Following Algorithm for maze navigation  
- ✅ Obstacle detection using analog IR sensor  
- ✅ Adafruit Motor Shield control with four DC motors  
- ✅ Dead-end detection and multi-level turning strategy  
- ✅ Fully autonomous decision-making based on real-time sensor data  
- ✅ Serial monitor logging for debugging and optimization

---

## 🔧 Hardware Used

| Component              | Description                                      |
|------------------------|--------------------------------------------------|
| Arduino Uno            | Main controller for the robot                    |
| Adafruit Motor Shield v1 | Motor control (4 DC motors)                     |
| 4 x DC Motors (6V, N20 series) | Individual wheel control               |
| Sharp IR Sensor (A2 pin) | For wall/obstacle detection in front           |
| PLA Chassis    | Light-weight body platform                      |
| 12V Battery Pack       | Power source for motors and logic               |

---

## 🧠 Logic Overview

### ✅ Wall-Following Strategy:
- The robot follows the **right wall** using data from the front IR sensor.
- If a **wall is detected** (sensor value in calibrated range), it makes a **right turn**.
- If the robot turns right and again finds a wall ahead, it takes **two consecutive left turns** to backtrack.
- In case of a **dead-end**, the robot performs a **3-left-turn maneuver** to reverse.

### 🧪 Sensor Calibration:
- **IR Sensor Range:** Obstacle detected when `analogRead(IR) ∈ [400, 510]`
- Value may vary depending on lighting, surface, and sensor quality. Tuned via trial and error.

---

## 🧾 Code Structure

- `setup()`: Initializes motors and IR sensor
- `loop()`: Continuously reads sensor and decides movement
- `check()`: Reads IR value and returns 1 if wall is detected
- `moveForward()`, `moveRight()`, `moveLeft()`, `stopMotors()`: Motor control functions

---

## 🛠️ Future Work

- ✅ Multi-sensor setup (IR on front, left, and right)
- ⏳ PID-based wall following for smoother control
- ⏳ Maze mapping with memory and backtracking
- ⏳ ROS and SLAM integration for advanced navigation
 
- 💬 Feel free to open issues or reach out with suggestions!
