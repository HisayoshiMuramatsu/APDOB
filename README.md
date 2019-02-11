# APDOB - Adaptive Periodic-Disturbance Observer

This is a control algorithm implementation in C++. It implements the control method proposed by [1]. The adaptive periodic-disturbance observer (APDOB) has the following three aims.

1. Periodic-disturbance estimation and cancellation
2. Fundamental frequency estimation of a periodic disturbance
3. Frequency-varying periodic-disturbance estimation and cancellation

They are beneficial to realizing precise repetitive operations for automatic systems, such as actuators, industrial machines, robots, and so on. The APDOB can be additionally implemented into existing control systems, and we can design controllers of the systems without considering periodic disturbances and the APDOB, as shown in Fig. 1.

[1] Hisayoshi Muramatsu and Seiichiro Katsura “An Adaptive Periodic-Disturbance Observer for Periodic-Disturbance Suppression,” IEEE Transactions on Industrial Informatics, vol. 14, no. 10, pp. 4446-4456, Oct. 2018.
(http://ieeexplore.ieee.org/document/8288655/)

<img src="https://github.com/HisayoshiMuramatsu/APDOB/blob/master/images/Concept.png" alt="Concept" width="100%" height="100%" />

Fig. 1. Concept of the periodic-disturbance estimation, cancellation, and fundamental frequency estimation of a periodic disturbance using the APDOB.

## Description

The APDOB includes a periodic-disturbance observer (PDOB) and adaptive notch filter (ANF). The PDOB can estimate and compensate for a periodic disturbance including a fundamental wave and harmonics. The ANF can estimate a fundamental frequency of a periodic disturbance. Accordingly, the APDOB can estimate and compensate for frequency-varying periodic disturbances.

<img src="https://github.com/HisayoshiMuramatsu/APDOB/blob/master/images/BlockDiagram_APDOB.png" alt="BlockDiagram_APDOB" width="90%" height="90%" />

Fig. 2. Block diagram of the APDOB in details.

## Example

There is a test program that simulates a position control system using a motor, proportional-and-derivative (PD) controller, and acceleration feedforward controller under a frequency-varying periodic disturbance. The block diagram of the position control system is shown in Fig. 3.

<img src="https://github.com/HisayoshiMuramatsu/APDOB/blob/master/images/BlockDiagram_Example.png" alt="BlockDiagram_Example" width="100%" height="100%" />

Fig. 3. Block diagram of the position control system using the APDOB.

## Licence

[MIT License](https://github.com/HisayoshiMuramatsu/APDOB/blob/master/LICENSE) © Hisayoshi Muramatsu
