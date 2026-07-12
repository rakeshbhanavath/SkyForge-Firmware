# SkyForge

> A modular, scalable embedded firmware framework for STM32-based drones and robotics.

SkyForge is a long-term firmware project focused on building a professional-grade software stack for autonomous drones and robotic systems. The framework is designed with clean architecture, reusable drivers, and hardware abstraction to support future flight controllers and robotics platforms.

---

## Vision

The goal of SkyForge is to develop a complete embedded firmware framework capable of powering:

- Autonomous drones
- Custom flight controllers
- Robotics platforms
- Sensor fusion systems
- Navigation and telemetry
- Motor control systems

Rather than writing firmware for a single project, SkyForge is being developed as a reusable engineering framework.

---

## Design Philosophy

SkyForge follows a layered architecture to separate hardware-specific code from application logic.

```
Application
     │
     ▼
Services
     │
     ▼
Drivers
     │
     ▼
Board Support Package (BSP)
     │
     ▼
STM32 HAL
     │
     ▼
Hardware
```

### Design Principles

- Hardware abstraction through BSP
- Modular driver architecture
- Reusable components
- Clean separation of responsibilities
- Scalable project structure
- Git-driven development
- Every commit must compile successfully

---

## Project Structure

```
SkyForge
│
├── Core/                     # STM32CubeMX generated source
├── Drivers/                  # STM32 HAL & CMSIS
│
├── SkyForge/
│   ├── Framework/
│   │   ├── Application/
│   │   ├── BSP/
│   │   ├── Config/
│   │   ├── Drivers/
│   │   ├── Interfaces/
│   │   ├── Middleware/
│   │   ├── Services/
│   │   └── Utilities/
│   │
│   └── Docs/
│
├── SkyForge.ioc
└── README.md
```

---

## Current Development Status

### Platform

- [x] STM32CubeMX Project
- [x] BSP Layer
- [x] Common Utilities
- [ ] Logger
- [ ] Scheduler

### Sensor Drivers

- [ ] MPU6050
- [ ] BMP390
- [ ] GPS
- [ ] Magnetometer

### Algorithms

- [ ] PID Controller
- [ ] Complementary Filter
- [ ] Madgwick Filter
- [ ] Mahony Filter
- [ ] Extended Kalman Filter

### Flight Control

- [ ] Sensor Fusion
- [ ] Attitude Estimation
- [ ] Motor Mixing
- [ ] Flight Modes
- [ ] Failsafe
- [ ] Navigation

---

## Development Roadmap

### Phase 1

- BSP Layer
- Sensor Drivers
- Utilities
- Logging

### Phase 2

- IMU Service
- Sensor Fusion
- Calibration
- Filters

### Phase 3

- Flight Controller
- ESC Interface
- Motor Mixer
- Flight Modes

### Phase 4

- GPS Navigation
- Mission Planner
- Return To Home
- Autonomous Flight

### Phase 5

- Custom Flight Controller Hardware
- Heavy-Lift Drone Platform
- Autonomous Delivery Drone

---

## Hardware Platform

Current development board:

- STM32 NUCLEO-C031C6

Future targets:

- STM32F4 Series
- STM32G4 Series
- STM32H7 Series

---

## Development Tools

- STM32CubeMX
- STM32CubeIDE
- STM32 HAL
- Git
- GitHub

---

## Coding Standards

- Modular architecture
- Layered design
- BSP abstraction
- No direct HAL usage outside BSP
- Consistent naming conventions
- Allman brace style
- 4-space indentation

---

## Long-Term Goal

Develop a complete open-source embedded firmware framework capable of powering commercial-grade drones and robotics systems while documenting the engineering process from hardware abstraction to autonomous flight.

---

## License

This project is released under the MIT License.
