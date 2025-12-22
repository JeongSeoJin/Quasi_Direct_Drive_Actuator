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

<img src="actual-img/image_4.jpg" style="max-width:510px; height:auto;" alt="Actuator image 1" />

# Cycloidal QDD Actuator for Dynamic Robots

> *Note: This is an ongoing project. Please note that some sections, particularly '5. Control & Validation', are currently being documented. New test results and updates will be uploaded soon.*

[=> view this page in github with resources](https://github.com/JeongSeoJin/quasi-direct-drive-actuator)

Table of contents

- [1. Abstract](#1-abstract)
- [2. Actuator Design : Why Cycloidal QDD Actuator?](#2-actuator-design-why-qdd-actuator)
- [3. System Architecture & Components](#3-system-architecture--components)
- [4. Assembly](#4-assembly)
- [5. Control & Validation](#5-control--validation)
- [6. Limitations & Future Works](#6-limitations--future-works)
- [7. Credits](#7-credits)
- [8. References](#8-references)

---

## 1. Abstract
Rapid advancements in dynamic humanoid and quadruped robots have surged recently. However, high-performance actuators remain largely proprietary, restricting access for academic researchers and open-source communities. This project aims to democratize dynamic robotics by developing an open-source Quasi-Direct Drive (QDD) actuator tailored for mid-size humanoid robots.

Traditional high-ratio gearboxes suffer from poor back-drivability, low responsiveness and limited transmission transparency, making them unsuitable for safe Human-Robot Interaction (HRI) and uneven terrain locomotion. To address this, I propose a custom-designed QDD actuator featuring a 1:10 cycloidal reducer. This low-reduction architecture minimizes mechanical impedance, enabling back-drivable, high responsiveness and proprioceptive torque sensing via FOC algorithms without additional sensors.

The current prototype utilizes a 3D-printed and aluminium structure to ensure low cost and accessibility. Preliminary assessments estimate a maximum holding torque exceeding 7 Nm, with comprehensive performance verification currently underway. This work contributes to the robotic community by providing a scalable, affordable, and high-performance actuation solution.


  <table>
    <tr>
      <td><img src="actual-img/image_1.jpg" width="250" alt="Actuator image 1" /></td>
      <td><img src="actual-img/image1.png" width="250" alt="Actuator image 2" /></td>
    </tr>
  </table>

---

## 2. Actuator Design: Why QDD Actuator?

### 2.1 The Limitations of Traditional Actuators

**Conventional robotic actuators** typically utilize high gear reduction ratios (e.g., 1:100 or higher) to amplify torque. However, this approach introduces significant drawbacks for dynamic robots.

A high gear ratio leads to **high mechanical impedance**, primarily due to increased friction and reflected inertia compared to low-ratio systems [[1]](#8-references).

This high impedance makes the motor response sluggish and susceptible to damage from sudden external impacts, as the actuators are too stiff to react compliantly. In other words, the actuator exhibits **poor back-drivability and low responsiveness**. Consequently, these properties hinder the robot's ability to interact safely with the environment, particularly in Human-Robot Interaction (HRI) scenarios or during dynamic locomotion.

As robots become more integrated into our daily lives, physical interaction and cooperation will become increasingly common. In these scenarios, traditional actuators pose a significant safety risk. Since robots with stiff actuators struggle to sense external forces [[2]](#8-references), they can unintentionally injure people due to their lack of compliance. Furthermore, regarding locomotion, such robots cannot flexibly adapt to unpredictable environments, such as rough or uneven terrain, leading to instability.

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

Similarly, **Planetary Gearboxes**, though common, exhibit inherent backlash. It works well with aluminum gears, but becomes significantly fragile when 3D printed. In a 3D-printed planetary system, the stress concentrates on individual small gear teeth, making them prone to catastrophic failure under sudden external forces.

To ensure robustness, I selected a **Cycloidal Reducer** architecture. According to Sensinger's research, this mechanism distributes the load across multiple lobes simultaneously. This load-sharing capability provides significantly higher Shock Resistance compared to involute gears or fragile harmonic drives, making it the ideal candidate for a fully 3D-printed transmission [[3]](#8-references).

Furthermore, I optimized the internal mechanism for efficiency. While the outer profile uses a solid design for structural strength, the internal output mechanism operates based on Rolling Contact. By utilizing rolling pins for the output shaft transmission, I successfully minimized internal friction where structural fragility is less of a concern. This strategic design choice preserves the Back-drivability required for the QDD system while maintaining the robustness of the outer shell.

---

## 3. System Architecture & Components

### 3.1 Mechanical Design (Cycloidal Reducer)
A custom **Cycloidal Quasi-Direct Drive Actuator** is designed to ensure high torque density, compactness, and compliance.

I utilized Onshape 3D CAD to design a dual-disc cycloidal mechanism. The two cycloidal discs are arranged with a $180^\circ$ phase offset. This configuration effectively cancels out the radial forces and vibrations induced by the eccentric input shaft, ensuring smooth operation.

To maximize efficiency, I integrated rollers into the output pins. Unlike simple sliding contacts, these rollers minimize internal friction at the output stage, contributing to the system's back-drivability.

For the current prototype, the gears, shafts and rotor are manufactured from CNC-machined Aluminum to verify the design with a high strength-to-weight ratio. (Note: The final goal of this project is to optimize the design for a fully 3D-printed, low-cost actuator for dynamic robots.)

  <table>
    <tr>
      <td><img src="actual-img/image_2.jpg" width="250" alt="Actuator image 1" /></td>
      <td><img src="actual-img/image4.png" width="250" alt="Actuator image 2" /></td>
    </tr>
  </table>

### 3.2 Electromagnetic Design (Custom BLDC)

To optimize torque density within the compact housing, I integrated a **custom-built frameless Brushless DC (BLDC) motor** instead of using a standard motor.

For the stator, I utilized a standard 8110 stator core. To achieve the desired current capacity and fill factor, the stator was hand-wound using 0.4mm enameled copper wire. I applied a Wye (Star) termination with 6 parallel strands and 5 turns per tooth, following the optimal winding scheme calculated via open-source tools [[4]](#8-references).


The motor adopts a 36N42P configuration (36 slots, 42 poles) to maximize torque output. For the rotor, 42 N52-grade Neodymium magnets were installed. These magnets were precisely bonded using high-strength epoxy (JB Weld) in an alternating polarity pattern (N-S-N-S) to maximize magnetic flux density and ensure structural integrity under high rotation speeds. Crucially, the rotor geometry was optimized to achieve a minimal air gap of 0.5mm. This tight clearance maximizes the magnetic flux linkage between the rotor and stator, thereby significantly enhancing the electromagnetic force and overall torque efficiency.


### 3.3 Electronics & Sensors
For precise torque control and dynamic response, I integrated the **Moteus-c1 controller** (mjbots). This controller is widely adopted in the dynamic robotics community for its compact form factor and high bandwidth.

It implements **Field Oriented Control (FOC)**, which is essential for smooth torque generation and the proprioceptive capabilities mentioned earlier. With a wide input range (10-51V) and 20A peak phase current, it provides sufficient power capacity to drive the custom-wound 8110 stator to its full potential.

<img src="actual-img/controller.webp" width="250" alt="Actuator image 2" />
---

## 4. Assembly
Precise assembly is critical to minimize backlash and ensure the longevity of the reducer. I implemented distinct **tolerance strategies** based on the material properties of each component.

### 4.1 Bearing Installation & Fits
For the housing components printed in PA-CF12 (Carbon Fiber Nylon), I designed a 0.1mm interference fit. This accounts for the material's slight compliance and thermal shrinkage during printing, ensuring a secure press-fit without cracking the part.

Conversely, for the CNC-machined Aluminum parts, a tighter 0.02mm interference fit was applied due to the metal's rigidity. To prevent any micro-movements or slippage under high torque loads, I reinforced these metal-to-bearing interfaces with a thin application of JB Weld epoxy.


### 4.2 Output Mechanism
The output transmission relies on smooth rolling contact. I installed six M2x20mm stainless steel shafts to serve as the carrier pins. These shafts were precision-aligned to allow the external rollers to rotate freely, minimizing friction at the output stage while maintaining structural rigidity.

---

## 5. Control & Validation
preparing 


---

## 6. Limitations & Future Works
### 6.1 Limitations of the Current Prototype

Through the testing and assembly process, two primary limitations were identified regarding the actuator's performance and structural dynamics.

First, Suboptimal Magnetic Flux Path (Rotor Design)
The current rotor design does not incorporate a ferromagnetic back-iron or a Halbach array arrangement. Consequently, the magnetic flux is not effectively focused inward toward the stator, leading to flux leakage.

Since air-gap flux density directly correlates with torque generation, this lack of magnetic circuit optimization results in a lower torque density than theoretically possible. In future iterations, adding a steel back-iron will be essential to maximize torque output.

Second, Structural Rigidity of the Eccentric Shaft
The second issue lies in the assembly of the eccentric input shaft. Currently, it is constructed as a multi-part assembly fastened with bolts and nuts, rather than a single monolithic part. 

During operation, the strong radial magnetic attraction between the rotor and stator exerts significant force on the shaft. This force compromises the alignment of the multi-part shaft assembly, causing slight structural deflection. This misalignment leads to unwanted oscillation and vibration, particularly at higher rotational speeds. A monolithic (single-piece) shaft design is required to resolve this issue.

### 6.2 Future Works

Moving forward, I aim to integrate these custom QDD actuators into a mid-size bipedal robot to validate their performance in a complete system. The target platform will feature a total of 10 degrees of freedom (DoF), with 5 actuators allocated to each leg, specifically designed to handle dynamic walking tasks. This project will serve as a crucial step in verifying the scalability of my hardware design while providing a physical testbed for implementing advanced locomotion control algorithms.


---

## 7. Credits
* Design, Engineering and Documentation: [Seo Jin Jeong](https://jeongseojin.github.io/)
* Manufacturing Sponsor: [JLCCNC](https://jlccnc.com/)
* Motor Controller: [Moteus-c1 Controller (mjbots)](https://mjbots.com/products/moteus-c1?pr_prod_strat=e5_desc&pr_rec_id=5a7f102a9&pr_rec_pid=7839892799649&pr_ref_pid=7358414749857&pr_seq=uniform)
* Youtube : [Engineering SeoJin](http://www.youtube.com/@engineeringseojin)
* Instagram : [engineering.seojin_n.n](https://www.instagram.com/engineering.seojin_n.n?utm_source=ig_web_button_share_sheet&igsh=ZDNlZDc0MzIxNw==)


## 8. References

[1] S. Seok et al., "Design Principles for Energy-Efficient Legged Locomotion and Implementation on the MIT Cheetah Robot," in IEEE/ASME Transactions on Mechatronics, vol. 20, no. 3, pp. 1117-1129, June 2015, doi: 10.1109/TMECH.2014.2339013. 

[2] P. M. Wensing, A. Wang, S. Seok, D. Otten, J. Lang and S. Kim, "Proprioceptive Actuator Design in the MIT Cheetah: Impact Mitigation and High-Bandwidth Physical Interaction for Dynamic Legged Robots," in IEEE Transactions on Robotics, vol. 33, no. 3, pp. 509-522, June 2017, doi: 10.1109/TRO.2016.2640183.

[3] Sensinger, J. W. (February 9, 2010). "Unified Approach to Cycloid Drive Profile, Stress, and Efficiency Optimization." ASME. J. Mech. Des. February 2010; 132(2): 024503. https://doi.org/10.1115/1.4000832

[4] "bavaria-direct.co.za - Homebuilt Electric Motors," [Online]. Available: https://www.bavaria-direct.co.za/scheme/calculator/.
