# APDOB - Adaptive Periodic-Disturbance Observer
#### Note

[GitHub - QDOB](https://github.com/HisayoshiMuramatsu/QDOB) provides an upgraded method for the periodic-disturbance observer component in this APDOB. However, the QDOB does not support fundamental frequency estimation.

#### APDOB

This is a control algorithm implementation in C++. It implements the control method proposed by [1] and developed by [2]. The adaptive periodic-disturbance observer (APDOB) has the following three aims.

1. Periodic-disturbance estimation and cancellation
2. Fundamental frequency estimation of a periodic disturbance
3. Frequency-varying periodic-disturbance estimation and cancellation

They are beneficial to realizing precise repetitive operations for automatic systems, such as actuators, industrial machines, robots, and so on.

[1] Hisayoshi Muramatsu and Seiichiro Katsura, “An Adaptive Periodic-Disturbance Observer for Periodic-Disturbance Suppression,” IEEE Transactions on Industrial Informatics, vol. 14, no. 10, pp. 4446-4456, Oct. 2018.  
IEEE Xplore: http://ieeexplore.ieee.org/document/8288655/
arXive: https://arxiv.org/abs/2004.00487  
[2] Hisayoshi Muramatsu and Seiichiro Katsura, “An Enhanced Periodic-Disturbance Observer for Improving Aperiodic-Disturbance Suppression Performance,” IEEJ Journal of Industry Applications, vol. 8, no. 2, pp. 177-184, May 2019. https://www.jstage.jst.go.jp/article/ieejjia/8/2/8_177/_article/-char/ja/

## Description

The APDOB includes a periodic-disturbance observer (PDOB) and adaptive notch filter (ANF). The PDOB can estimate and compensate for a periodic disturbance including a fundamental wave and harmonics. The ANF can estimate a fundamental frequency of a periodic disturbance. Accordingly, the APDOB can estimate and compensate for frequency-varying periodic disturbances.

## Example

There is a test program that simulates a position control system using a motor, proportional-and-derivative (PD) controller, and acceleration feedforward controller under a frequency-varying periodic disturbance.

## Licence

[MIT License](https://github.com/HisayoshiMuramatsu/APDOB/blob/master/LICENSE) © Hisayoshi Muramatsu
