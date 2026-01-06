# SpeedSense-Arduino
⚡ A High-Performance Human Reaction Tester with Dynamic Difficulty Scaling. Independently developed and field-tested at HMTI Weekly Training to analyze human-to-hardware latency. 🚀
# ⚡ SpeedSense: Advanced Reaction Speed Tester v2.5

![Build Status](https://img.shields.io/badge/Build-Stable-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![License](https://img.shields.io/badge/License-MIT-yellow)

> **"How fast can you think?"** SpeedSense is an independently developed embedded system designed to challenge and measure human neuro-motor response times.

---

## 🚀 The Innovation
Unlike static reaction testers, **SpeedSense** features a **Dynamic Difficulty Scaling (DDS)** algorithm. The system "learns" your progress—every 4 successful hits, the reaction window narrows, forcing the user into a high-focus state.

### 🎮 Game Features
- **3 Difficulty Tiers**: 
  - 🟢 **Romawi (Level 1)**: For beginners.
  - 🟡 **Glory (Level 2)**: For enthusiasts.
  - 🔴 **Immortal (Level 3)**: Human-limit challenge (450ms).
- **Dual Mode Architecture**: Toggle between *Classic Practice* and *Ranked Competition*.
- **Jukebox Module**: Integrated 8-bit melody synthesizer for user engagement.
- **Fail-Safe Exit**: Long-press triple-button interrupt to prevent hardware lock-up.

---

## 🛠️ Hardware Stack
| Component | Role |
| :--- | :--- |
| **Arduino Uno R3** | Central Processing Unit |
| **LCD 16x2 I2C** | Real-time Telemetry & UI |
| **Tactile Array** | High-response Input |
| **Buzzer** | Acoustic Feedback |

---

## 📊 Real-World Implementation
This project wasn't just built in a room—it was stress-tested by dozens of users during the **HMTI Weekly Training** session. 



**Key Findings from Field Test:**
- **Human Limit**: Users recorded a 90% failure rate when speed dropped below 380ms.
- **Hardware Latency**: The system maintained sub-1ms polling rates for input detection.

---

## 📂 Documentation
For a deep dive into the schematics, flowcharts, and on-site event photos:
📂 **[Download Technical Report (PDF)](./docs/Reaction_Speed_Tester_Documentation.pdf)**

---

## 👨‍💻 Developer
**Muhamad Rizal Prasetyo** *Technology Information Student @ UNIPI* Inquisitive Minds | Embedded Systems Enthusiast

---
*Disclaimer: This is a personal project. HMTI was the official implementation partner for testing and demonstration.*
