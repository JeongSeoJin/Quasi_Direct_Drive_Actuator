<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    tex2jax: {
      inlineMath: [['$','$'], ['\\(','\\)']],
      displayMath: [['$$','$$'], ['\\[','\\]']],
      processEscapes: true
    }
  });
</script>

<img src="Mechanical_IMG/image_4.jpg" style="max-width:510px; height:auto;" alt="Actuator image 1" />

# Cycloidal QDD Actuator for Dynamic Robots

> *Since it's an ongoing project. The contents are not totally well-documented especially '5. Control & Validation part' I hope you understand regarding this problem. I'll test it as fast as I can*


Table of contents

- [0. Layout](#0-layout)
- [1. Project Overview](#1-project-overview)
- [2. Actuator Design : Why QDD Actuator](#2-actuator-design-why-qdd-actuator)
- [3. System Architecture & Components](#3-system-architecture--components)
- [4. Fabrication & Assembly](#4-fabrication--assembly)
- [5. Control & Validation](#5-control--validation)

---

## 0. layout
- Mechanical_CAD_Design/ — CAD models(assembly file) (STEP/Source)  
- Motor_Control/ — Sources(if you're using esp32/arduino and drv8302 motor driver)
- Mechanical_IMG/ — photos and renders used in this README  
- OFF_THE_SHELF_SPECIFICATIONS/ — commercial component specs (bearings, shafts, controllers etc)  
- BOM/ — Bill of Materials (preparing)


## 1. Abstract
Rapid advancements in dynamic humanoid and quadruped robots have surged recently. However, high-performance actuators remain largely proprietary, restricting access for academic researchers and open-source communities. This project aims to democratize dynamic robotics by developing an open-source Quasi-Direct Drive (QDD) actuator tailored for mid-size humanoid robots.

Traditional high-ratio gearboxes suffer from poor back-drivability, low responsiveness and limited transmission transparency, making them unsuitable for safe Human-Robot Interaction (HRI) and uneven terrain locomotion. To address this, we propose a custom-designed QDD actuator featuring a 1:10 cycloidal reducer. This low-reduction architecture minimizes mechanical impedance, enabling back-drivable, high responsiveness and proprioceptive torque sensing via FOC algorithms without additional sensors.

The current prototype utilizes a 3D-printed and aluminium structure to ensure low cost and accessibility. Preliminary assessments estimate a maximum holding torque exceeding 7 Nm, with comprehensive performance verification currently underway. This work contributes to the robotic community by providing a scalable, affordable, and high-performance actuation solution.


  <table>
    <tr>
      <td><img src="Mechanical_IMG/image_1.jpg" width="250" alt="Actuator image 1" /></td>
      <td><img src="Mechanical_IMG/image1.png" width="250" alt="Actuator image 2" /></td>
    </tr>
  </table>

---

## 2. Actuator Design: Why QDD Actuator?

### 2.1 The Limitations of Traditional Actuators

**Conventional robotic actuators** typically utilize high gear reduction ratios (e.g., 1:100 or higher) to amplify torque. However, this approach introduces significant drawbacks for dynamic robots.

A high gear ratio leads to **high mechanical impedance**, primarily due to increased friction and reflected inertia compared to low-ratio systems.[[1]](#8-references)

This high impedance makes the motor response sluggish and susceptible to damage from sudden external impacts, as the actuators are too stiff to react compliantly. In other words, the actuator exhibits **poor back-drivability and low responsiveness**. Consequently, these properties hinder the robot's ability to interact safely with the environment, particularly in Human-Robot Interaction (HRI) scenarios or during dynamic locomotion.

As robots become more integrated into our daily lives, physical interaction and cooperation will become increasingly common. In these scenarios, traditional actuators pose a significant safety risk[[2]](#8-references). Since robots with stiff actuators struggle to sense external forces[[3]](#8-references), they can unintentionally injure people due to their lack of compliance. Furthermore, regarding locomotion, such robots cannot flexibly adapt to unpredictable environments, such as rough or uneven terrain, leading to instability.

### 2.2 The QDD System Solution
To address these issues, I adopted a **Quasi-Direct Drive (QDD) architecture**. A QDD system typically features a low gear reduction ratio, ranging from 1:3 to 1:10. By positioning itself between Direct Drive (1:1) and traditional high-ratio drives (1:50 or higher), it combines the structural advantages of both systems.

The low gear ratio significantly minimizes friction and reflected inertia, rendering the actuator **inherently compliant**. This compliance ensures the system is smoothly back-drivable and highly responsive to external interactions, effectively mitigating the stiffness drawbacks of conventional actuators.

Consequently, this **improved back-drivability and responsiveness** enable the robot to safely interact with humans and flexibly adapt to uneven terrain during dynamic locomotion.

**At this point, a critical question arises:** "How can the actuator generate sufficient torque for dynamic motions with such a low gear ratio?" The following section details the design strategy used to resolve this trade-off.


### 2.3 Motor Design Optimization
To achieve high torque density suitable for a Quasi-Direct Drive (QDD) system, I focused on the geometric parameters of the motor. According to the motor design principles outlined in the MIT Cheetah research, the continuous torque generation capability ($\tau$) is approximated by the following equation [[4]](#8-references):

$$\tau \propto \sigma \cdot l_{st} \cdot r_g^2$$

Where:
* **$\sigma$**: Shear stress density (magnetic flux density $\times$ current loading)
* **$l_{st}$**: Stack length of the motor
* **$r_g$**: Air gap radius

As shown in the equation, torque is linearly proportional to the stack length ($l_{st}$) but proportional to the **square of the air gap radius ($r_g^2$)**. This implies that increasing the motor diameter is significantly more efficient for boosting torque than increasing its length. Based on this principle, I selected a stator with a large diameter (8110 size) to maximize the air gap radius, thereby securing sufficient torque even with a low gear reduction ratio.

### 2.4 Transmission Selection: Why Cycloidal Reducer?

In dynamic legged locomotion, the actuator must withstand high impact loads caused by ground reaction forces. While **Harmonic Drives** are industry standards for zero-backlash precision, their flexible spline mechanism is notoriously fragile under shock loads.

Similarly, **Planetary Gearboxes**, though common, exhibit inherent backlash. **It works well with aluminum gears, but becomes significantly fragile when 3D printed.** In a 3D-printed planetary system, the stress concentrates on individual small gear teeth, making them prone to catastrophic failure under sudden external forces.

To ensure robustness, I selected a **Cycloidal Reducer** architecture. According to Sensinger's research, this mechanism **distributes the load across multiple lobes simultaneously**. This load-sharing capability provides significantly higher **Shock Resistance** compared to involute gears or fragile harmonic drives, making it the ideal candidate for a fully 3D-printed transmission **[5]**.

Furthermore, I optimized the internal mechanism for efficiency. While the outer profile uses a solid design for structural strength, the **internal output mechanism operates based on Rolling Contact**. By utilizing rolling pins for the output shaft transmission, I successfully minimized internal friction where structural fragility is less of a concern. This strategic design choice preserves the **Back-drivability** required for the QDD system while maintaining the robustness of the outer shell **[6]**.

---

## 3. System Architecture & Components

### 3.1 Mechanical Design (Cycloidal Reducer)
A custom **Cycloidal Quasi-Direct Drive Actuator** is designed to ensure high torque density, compactness, and compliance.

I utilized **Onshape 3D CAD** to design a **dual-disc cycloidal mechanism**. The two cycloidal discs are arranged with a **$180^\circ$ phase offset**. This configuration effectively cancels out the radial forces and vibrations induced by the eccentric input shaft, ensuring smooth operation.

To maximize efficiency, I integrated **rollers into the output pins**. Unlike simple sliding contacts, these rollers minimize internal friction at the output stage, contributing to the system's back-drivability.

For the current prototype, the gears and rotor are manufactured from **CNC-machined Aluminum 6061** to verify the design with a high strength-to-weight ratio. (Note: The final goal of this project is to optimize the design for a **fully 3D-printed, low-cost actuator**.)



  <table>
    <tr>
      <td><img src="Mechanical_IMG/image_2.jpg" width="250" alt="Actuator image 1" /></td>
      <td><img src="Mechanical_IMG/image4.png" width="250" alt="Actuator image 2" /></td>
    </tr>
  </table>

### 3.2 Electromagnetic Design (Custom BLDC)
Instead of using an off-the-shelf motor, the driving system was custom-built to fit the housing constraints.
* **Stator:** 8110 sized stator core, **hand-wound** for optimized fill factor using 0.4mm enameled wires.
* **Rotor:** Custom CNC aluminum shell.
* **Magnet Configuration:**  **42 x N52 Neodymium Magnets**.
    * Arranged in an alternating pole pattern (N-S-N-S) to maximize flux density.
    * Bonded using high-strength epoxy (**JB Weld**) to withstand centrifugal forces and thermal stress.
>This rotor needs to be redesigned using steel or a Halbach array to concentrate the magnetic field inward.

### 3.3 Electronics & Sensors
* **Motor Controller:** [Moteus-c1 Controller](https://github.com/mjbots/moteus)
    * **Control Method:** Field Oriented Control (FOC) for smooth torque generation.
    * **Specs:** 10-51V Input, 20A Peak Phase Current.

    <img src="Mechanical_IMG/controller.webp" width="250" alt="Actuator image 2" />
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
* **Design & Engineering:** Seo Jin Jeong
* **Manufacturing Sponsor:** [JLCCNC](https://jlccnc.com/)
* **Controller:** [Moteus-c1 Controller (mjbots)](https://mjbots.com/products/moteus-c1?pr_prod_strat=e5_desc&pr_rec_id=5a7f102a9&pr_rec_pid=7839892799649&pr_ref_pid=7358414749857&pr_seq=uniform)
* **Youtube** : [Engineering SeoJin](http://www.youtube.com/@engineeringseojin)
* **Instagram** : [engineering.seojin_n.n](https://www.instagram.com/engineering.seojin_n.n?utm_source=ig_web_button_share_sheet&igsh=ZDNlZDc0MzIxNw==)


## 8. References

[1] S. Seok, A. Wang, M. Y. Chuah, D. J. Hyun, J. Lee, D. M. Otten, and S. Kim, "Design principles for energy-efficient legged locomotion and robust force control," in *IEEE/ASME Transactions on Mechatronics*, vol. 20, no. 6, pp. 2817-2827, Dec. 2015.

[2] S. Haddadin, A. Albu-Schaffer, and G. Hirzinger, "Safety evaluation of physical human-robot interaction via crash-testing," in *Robotics: Science and Systems IV (RSS)*, Zurich, Switzerland, Jun. 2008.

[3] P. M. Wensing, A. Wang, S. Seok, D. Otten, J. Lang, and S. Kim, "Proprioceptive actuator design in the MIT Cheetah: Impact mitigation and high-bandwidth physical interaction," in *IEEE Transactions on Robotics*, vol. 33, no. 3, pp. 509-522, June 2017.

[4] S. Seok, A. Wang, M. Y. Chuah, D. J. Hyun, J. Lee, D. M. Otten, J. H. Lang, and S. Kim, "Design principles for energy-efficient legged locomotion and implementation on the MIT Cheetah robot," in IEEE/ASME Transactions on Mechatronics, vol. 20, no. 3, pp. 1117-1129, June 2015.

[5] J. W. Sensinger, "Unified approach to cycloidal drive profile design," in *ASME Journal of Mechanical Design*, vol. 132, no. 2, 2010.

[6] V. Macián, A. R. Gil, and R. Bernabeu, "Analytical model for the efficiency of cycloidal drives with clearances," in *Mechanism and Machine Theory*, vol. 127, pp. 26-42, 2018.

