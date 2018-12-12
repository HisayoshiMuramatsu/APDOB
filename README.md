# APDOB - Adaptive Periodic-Disturbance Observer

This is a control algorithm implementation in C++. It implements the control method proposed by [1]. The adaptive periodic-disturbance observer (APDOB) can achieve the following three objectives.
1. Periodic-disturbance estimation and compensation
2. Fundamental frequency estimation of a periodic disturbance
3. Frequency-varying periodic-disturbance estimation and compensation
The functions are beneficial to realizing precise repetitive operations for automatic systems, such as actuators, industrial machines, robots, and so on.

[1] Hisayoshi Muramatsu and Seiichiro Katsura “An Adaptive Periodic-Disturbance Observer for Periodic-Disturbance Suppression,” IEEE Transactions on Industrial Informatics, vol. 14, no. 10, pp. 4446-4456, Oct. 2018.
(http://ieeexplore.ieee.org/document/8288655/)

## Description

The APDOB includes a periodic-disturbance observer (PDOB) and adaptive notch filter (ANF). The PDOB can estimate and compensate for a periodic disturbance including a fundamental wave and harmonics. The ANF can estimate a fundamental frequency of a periodic disturbance. Accordingly, the APDOB can estimate and compensate for frequency-varying periodic disturbances.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_APDOB.png" alt="BlockDiagram_APDOB" width="70%" height="70%" />

Fig. 1. Block diagram of the APDOB.

## Example

There is a test program that simulates a position control system using a motor, proportional-and-derivative (PD) controller, and acceleration feedforward controller under a frequency-varying periodic disturbance. The block diagram of the position control system is shown in Fig. 2.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_Example.png" alt="BlockDiagram_Example" width="100%" height="100%" />

Fig. 2. Block diagram of the position control system using the APDOB.

You can get the following results from the test program. First, I show the position control results without the APDOB.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_PD.png" alt="Position_PD" width="50%" height="50%" />

Fig. 3. Position response of the position control system without the APDOB.

The added frequency-varying periodic disturbance causes the position tracking error (green line). The error can be attenuated by the APDOB.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_APDOB.png" alt="Position_APDOB" width="50%" height="50%" />

Fig. 4. Position response of the position control system with the APDOB.

In the APDOB, the ANF estimated the fundamental frequency of the frequency-varying periodic disturbance.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Freq_APDOB.png" alt="Freq_APDOB" width="50%" height="50%" />

Fig. 5. Fundamental frequency estimation using the ANF.

Using the estimated fundamental frequency, the APDOB estimated the frequency-varying periodic disturbance.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Force_APDOB.png" alt="Force_APDOB" width="50%" height="50%" />

Fig. 6. Estimated periodic disturbance from the APDOB.

## Licence

[MIT License](https://github.com/HisayoshiMuramatsu/APDOB/blob/master/LICENSE) © Hisayoshi Muramatsu
