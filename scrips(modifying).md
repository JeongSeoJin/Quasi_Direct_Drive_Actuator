# 🎥 Video Script: Custom QDD Actuator

> **Note:** This script is written in a spoken style for voice-over recording.
> **Bold text** indicates words that should be emphasized.

---

## Part 1: Introduction

**[Scene: Face to camera or Cinematic shots of the actuator]**

"Hi guys! In this video, I’m going to introduce my **own actuator** that I designed from scratch."

"I designed it aiming specifically for my **future humanoid robot project**."

"For the build, I used 3D printing and CNC machining. I was able to manufacture the metal parts easily thanks to **JLCCNC**."

"Now, I’m going to show you the **assembly process** along with some explanations on why I designed it this way."

---

## Part 2: What is QDD and Why?

**[Scene: Technical diagrams or close-up of the motor]**

"First, **what is a QDD actuator?**"

"It stands for **Quasi-Direct Drive** actuator."

"Here is the thing: Motors usually **cannot** produce high torque on their own. So, they need a **reducer** (or gearbox) to get high torque."

"Traditional robotic actuators used very **high gear ratios**. By the way, there is a problem with that."

"They have **too much reduction** to respond well to external interactions. It implies that robots **cannot interact** safely with humans. They could actually **hurt** people because they are too stiff."

**[Scene: Showing the large stator and gear mechanism]**

"So, to get **responsiveness**, we can lower the reduction ratio—for example, from **1:10** (one to ten) to **1:3** (one to three)."

"Then, to sustain the torque, we can make the **diameter** of the motor larger."

"Because the **larger** the diameter motors have, the **more torque** they can produce."

"Thus, I adapted this concept to my actuator. It has a **1:10 reduction ratio** and a **large diameter stator** (the 8110) to ensure high performance."

---

## Part 3: Assembly Process

**[Scene: Components laid out on the desk]**

"Alright, **let’s assemble it!**"

"These are the components of my actuator from **JLCCNC**."

"Approximately, it consists of **five main parts**:"

1.  "The **Housing**,"
2.  "The **Cycloidal gears**,"
3.  "The **Output shafts**,"
4.  "The **Rotor**,"
5.  "And the **Stator** with the outer gear."

"Among these, only the gears, rotor, and eccentric shafts are made of **Aluminum**."

**[Scene: Assembling the gears]**

"Let's start with the **cycloidal gears**."

"This is a **dual-disk** setup. This design prevents the **oscillation** (vibration) caused by the eccentric shafts."

"The output shafts have **rollers** like this."

"These rollers make the cycloidal gears rotate much **more smoothly**."

"Here is a key point: We must make sure the two cycloidal gears are kept in an **inverted phase**—exactly **180 degrees** apart."

"This is because they have to **cancel out** the eccentric forces to balance the system."

**[Scene: Putting parts into the housing]**

"Next, I put the gearbox into the housing, followed by the stator that I wound by myself."

"Make sure to **fasten** everything tightly."

**[Scene: Applying grease]**

"Oh, I almost forgot **lubricating** the gears! We have to do this. It is **essential** to prevent wear from friction."

**[Scene: Rotor assembly]**

"Then, I install the **rotor**."

"I used **42** pieces of **N52 permanent magnets** for this rotor."

"They are placed in an **alternating pattern**—North pole, South pole, North, South."

"To fasten them to the rotor, I used **JB Weld** glue."

**[Scene: Encoder magnet and final look]**

"This small piece is a permanent magnet for the **magnetic encoder**."

"It senses the N and S poles to calculate the **position**, **angular speed**, and **acceleration** of the rotor."

"And that was the last step. Finally, I have **assembled** all of them!"

---

## Part 4: Motor Driver & Testing

**[Scene: Showing the Moteus controller board]**

"For the motor driver, I’m using the **Moteus Controller C1**."

"It is a 3-phase brushless **FOC** (Field Oriented Control) based controller."

"The specs are perfect for my actuator:"
* "Voltage Input: **10 to 51 Volts**"
* "Peak phase current: **20 Amps**"

**[Scene: Computer screen showing graphs or the motor moving]**

"First, I am **calibrating** the motor for the first time."

"Then, I tested some control modes: **Torque control** and **Position control**."

"I set a **limited control range** for safety—from **0 to 2 radians**."

"If the rotor **deviates** from this range, the signal cuts off, and the actuator moves **freely**."