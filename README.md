# APDOB - Adaptive Periodic-Disturbance Observer

This is a control algorithm implementation in C++. It implements the control method proposed by [1]. The adaptive periodic-disturbance observer (APDOB) can achieve the following three objectives.
1. Periodic-disturbance estimation and compensation
2. Fundamental frequency estimation of a periodic disturbance
3. Frequency-varying periodic-disturbance estimation and compensation
The functions are beneficial to realizing precise repetitive operations for automatic systems, such as actuators, industrial machines, robots, and so on.

[1] Hisayoshi Muramatsu and Seiichiro Katsura “An Adaptive Periodic-Disturbance Observer for Periodic-Disturbance Suppression,” IEEE Transactions on Industrial Informatics, vol. 14, no. 10, pp. 4446-4456, Oct. 2018.
(http://ieeexplore.ieee.org/document/8288655/)

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_APDOB.png" alt="BlockDiagram_APDOB" width="50%" height="50%" align="right" />

## Description

The APDOB includes a periodic-disturbance observer (PDOB) and adaptive notch filter (ANF). The PDOB can estimate and compensate for a periodic disturbance including a fundamental wave and harmonics. The ANF can estimate a fundamental frequency of a periodic disturbance. Accordingly, the APDOB can estimate and compensate for frequency-varying periodic disturbances.

## Example

There is a test program that simulates a position control system using a motor, a proportional-and-derivative (PD) controller and an acceleration feedforward controller under a frequency-varying periodic disturbance.

<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/BlockDiagram_Example.png" alt="BlockDiagram_Example" width="100%" height="100%" />

The position response of the system without the APDOB:
<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_PD.png" alt="Position_PD" width="50%" height="50%" />

The position response of the system with the APDOB:
<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Position_APDOB.png" alt="Position_APDOB" width="50%" height="50%" />

The fundamental frequency estimation of the ANF:
<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Freq_APDOB.png" alt="Freq_APDOB" width="50%" height="50%" />

The estimated periodic disturbance of the APDOB between 9 s and 15 s:
<img src="https://raw.githubusercontent.com/HisayoshiMuramatsu/APDOB/master/images/Force_APDOB.png" alt="Force_APDOB" width="50%" height="50%" />


## Licence

[MIT License](https://github.com/APDOB/APDOB/blob/master/LICENSE) © Hisayoshi Muramatsu










