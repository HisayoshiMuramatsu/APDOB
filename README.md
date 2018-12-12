# APDOB - Adaptive Periodic-Disturbance Observer

This is a control algorithm implementation in C++. It implements the control method proposed by [1]. The adaptive periodic-disturbance observer (APDOB) has the following three aims.

1. Periodic-disturbance estimation and cancellation
2. Fundamental frequency estimation of a periodic disturbance
3. Frequency-varying periodic-disturbance estimation and cancellation

They are beneficial to realizing precise repetitive operations for automatic systems, such as actuators, industrial machines, robots, and so on. The APDOB can be additionally implemented into existing control systems, and we can design controllers of the systems without considering periodic disturbances and the APDOB, as shown in Fig. 1.

[1] Hisayoshi Muramatsu and Seiichiro Katsura “An Adaptive Periodic-Disturbance Observer for Periodic-Disturbance Suppression,” IEEE Transactions on Industrial Informatics, vol. 14, no. 10, pp. 4446-4456, Oct. 2018.
(http://ieeexplore.ieee.org/document/8288655/)

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Concept.png" alt="Concept" width="100%" height="100%" />

Fig. 1. Concept of the periodic-disturbance estimation, cancellation, and fundamental frequency estimation of a periodic disturbance using the APDOB.

## Description

The APDOB includes a periodic-disturbance observer (PDOB) and adaptive notch filter (ANF). The PDOB can estimate and compensate for a periodic disturbance including a fundamental wave and harmonics. The ANF can estimate a fundamental frequency of a periodic disturbance. Accordingly, the APDOB can estimate and compensate for frequency-varying periodic disturbances.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_APDOB.png" alt="BlockDiagram_APDOB" width="90%" height="90%" />

Fig. 2. Block diagram of the APDOB in details.

## Example

There is a test program that simulates a position control system using a motor, proportional-and-derivative (PD) controller, and acceleration feedforward controller under a frequency-varying periodic disturbance. The block diagram of the position control system is shown in Fig. 3.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_Example.png" alt="BlockDiagram_Example" width="100%" height="100%" />

Fig. 3. Block diagram of the position control system using the APDOB.

You can get the following results from the test program. First, I show a simulation result without the APDOB.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_PD.png" alt="Position_PD" width="50%" height="50%" />

Fig. 4. Position response of the position control system without the APDOB.

The frequency-varying periodic disturbance causes the position tracking error (green line). The APDOB can attenuate the error.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_APDOB.png" alt="Position_APDOB" width="50%" height="50%" />

Fig. 5. Position response of the position control system with the APDOB.

In the APDOB, the ANF estimates the fundamental frequency of the frequency-varying periodic disturbance.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Freq_APDOB.png" alt="Freq_APDOB" width="50%" height="50%" />

Fig. 6. Fundamental frequency estimation using the ANF.

Using the estimated fundamental frequency, the APDOB estimates the frequency-varying periodic disturbance.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Force_APDOB.png" alt="Force_APDOB" width="50%" height="50%" />

Fig. 7. Estimated periodic disturbance from the APDOB between 9 s and 15 s.

Moreover, the APDOB has been successfully used for an actual industrial manipulator [1].

## Licence

[MIT License](https://github.com/HisayoshiMuramatsu/APDOB/blob/master/LICENSE) © Hisayoshi Muramatsu
