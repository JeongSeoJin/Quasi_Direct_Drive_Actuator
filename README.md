# QDD Actuator for Humanoid Robotics

An open-source project implementing a quasi-direct-drive cycloidal actuator. This repository contains CAD models, parts lists, assembly photos, and ongoing design updates.

Table of contents

- [0. Repository Layout](#0-repository-layout)
- [1. Project Overview](#1-project-overview)
- [2. Actuator Design : Why QDD Actuator](#2-actuator-design-why-qdd-actuator)
- [3. System Architecture & Components](#3-system-architecture--components)
- [4. Fabrication & Assembly](#4-fabrication--assembly)
- [5. Control & Validation](#5-control--validation)

---

## 0. Repository layout
- Mechanical_CAD_Design/ — CAD models(assembly file) (STEP/Source)  
- Motor_Control/ — Sources(if you're using esp32/arduino and drv8302 motor driver)
- Mechanical_IMG/ — photos and renders used in this README  
- OFF_THE_SHELF_SPECIFICATIONS/ — commercial component specs (bearings, shafts, controllers etc)  
- BOM/ — Bill of Materials (preparing)



> *Custom-designed Quasi-Direct Drive (QDD) actuator featuring a dual-disk cycloidal reducer with 1:10 ratio and It has about 7Nm Max Holding Torque*

## 1. Project Overview
This project focuses on the design, fabrication, and control of a custom actuator intended for a **future humanoid robot platform**. To achieve dynamic human-robot interaction, the actuator is designed based on the **Quasi-Direct Drive (QDD)** architecture, prioritizing back-drivability, responsiveness and torque density over pure holding force.

The project involves complex mechanical design (cycloidal gearing), electromagnetic integration (custom rotor/stator), and advanced motor control (Moteus-c1 FOC driver).

* **Role:** Mechanical Design, Fabrication, Motor Winding, Control Implementation
* **Manufacturing Partner:** [JLCCNC](https://jlcpcb.com/cnc) (CNC Machining)
* **Status:** Prototype Assembly & Validation is ongoing

---

## 2. Actuator Design: Why QDD Actuator?

### 2.1 The Limitations of Traditional Actuators
Conventional robotic joints typically utilize high gear reduction ratios (e.g., 1:100 or higher) to amplify torque from small motors. However, this approach introduces significant drawbacks for dynamic robots:
* **High Impedance:** The joints become stiff and rigid.
* **Low Back-drivability & Responsiveness:** The robot cannot passively absorb external impacts. 
* **Safety Risks:** Rigid joints pose a danger during human-robot interaction.

### 2.2 The QDD Solution
To address these issues, this actuator adopts a **Quasi-Direct Drive** architecture:
1.  **Low Reduction Ratio (1:10):**
  * Minimizes friction and reflected inertia, allowing the actuator to be "compliant" (responsive to external forces and backdrivable).
2.  **High Torque Density Motor:**
  * Torque is proportional to the rotor diameter, specifically the square of the radius ($T \propto r^2).
  * By increasing the stator diameter (using an 8110 motor), I exponentially increased the torque output, allowing for a lower gear reduction ratio.


---

## 3. System Architecture & Components

### 3.1 Mechanical Design (Cycloidal Reducer)
A custom **1:10 Cycloidal Drive** was designed to ensure compactness and shock load resistance.
* **Dual-Disk Setup:** Two cycloidal discs are arranged with a **180° phase shift**. This configuration cancels out eccentric forces, significantly reducing vibration and oscillation.
* **Rolling Contact Elements:** rollers are integrated into the output pins to minimize friction and improve efficiency compared to sliding contacts.
* **Material:** * **Gears & Rotor:** CNC-machined Aluminum (AL6061) for high strength-to-weight ratio.
    * **Housing:** 3D Printed / Hybrid materials.

### 3.2 Electromagnetic Design (Custom BLDC)
Instead of using an off-the-shelf motor, the driving system was custom-built to fit the housing constraints.
* **Stator:** 8110 sized stator core, **hand-wound** for optimized fill factor using 0.4mm enameled wires.
* **Rotor:** Custom CNC aluminum shell.
* **Magnet Configuration:**  **42 x N52 Neodymium Magnets**.
    * Arranged in an alternating pole pattern (N-S-N-S) to maximize flux density.
    * Bonded using high-strength epoxy (**JB Weld**) to withstand centrifugal forces and thermal stress.
>This rotor needs to be redesigned using steel or a Halbach array to concentrate the magnetic field inward.

### 3.3 Electronics & Sensors
* **Motor Controller:** [Moteus C1 Controller](https://github.com/mjbots/moteus)
    * **Control Method:** Field Oriented Control (FOC) for smooth torque generation.
    * **Specs:** 10-51V Input, 20A Peak Phase Current.

---

## 4. Fabrication & Assembly

The manufacturing process utilized a hybrid approach to balance cost and precision:
* **CNC Machining:** Critical components (cycloidal gears, eccentric shafts, rotor) were manufactured by **JLCCNC** to ensure tight tolerances required for the gear mechanism.
* **3D Printing:** Rapid prototyping of housing and non-load-bearing components.
> I'll build my actuator fully 3d printed for future


**Assembly Highlights:**
* Precise alignment of the dual cycloidal discs to match the eccentric shaft phase.
* Grease lubrication applied to all rolling contact surfaces to prevent wear.
* Stator installed securely within the housing to handle reaction torque.

---

## 5. Control & Validation
preparing


---

## 6. Future Works
preparing

---

## 7. Credits
* **Design & Engineering:** [Seo Jin Jeong]
* **Manufacturing Sponsor:** JLCCNC
* **Controller:** Moteus-c1 Controller (mjbots)