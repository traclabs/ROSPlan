Number of literals: 64
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
All the ground actions in this problem are compression-safe
Initial heuristic = 9.000
b (7.000 | 5.000)b (5.000 | 15.002)b (3.000 | 25.004)b (2.000 | 60.011)b (1.000 | 95.018);;;; Solution Found
; States evaluated: 108
; Cost: 100.019
; Time 0.04
0.000: (transport r2d2 wheel_1 wheels_zone assembly_zone)  [5.000]
5.001: (move r2d2 assembly_zone body_car_zone)  [5.000]
10.002: (transport r2d2 body_car_1 body_car_zone assembly_zone)  [5.000]
15.003: (move r2d2 assembly_zone steering_wheels_zone)  [5.000]
20.004: (transport r2d2 steering_wheel_1 steering_wheels_zone assembly_zone)  [5.000]
25.005: (assemble r2d2 assembly_zone wheel_1 body_car_1 steering_wheel_1 car_1)  [5.000]
30.006: (move r2d2 assembly_zone body_car_zone)  [5.000]
35.007: (transport r2d2 body_car_2 body_car_zone assembly_zone)  [5.000]
40.008: (move r2d2 assembly_zone steering_wheels_zone)  [5.000]
45.009: (transport r2d2 steering_wheel_2 steering_wheels_zone assembly_zone)  [5.000]
50.010: (move r2d2 assembly_zone wheels_zone)  [5.000]
55.011: (transport r2d2 wheel_2 wheels_zone assembly_zone)  [5.000]
60.012: (assemble r2d2 assembly_zone wheel_2 body_car_2 steering_wheel_2 car_2)  [5.000]
65.013: (move r2d2 assembly_zone body_car_zone)  [5.000]
70.014: (transport r2d2 body_car_3 body_car_zone assembly_zone)  [5.000]
75.015: (move r2d2 assembly_zone steering_wheels_zone)  [5.000]
80.016: (transport r2d2 steering_wheel_3 steering_wheels_zone assembly_zone)  [5.000]
85.017: (move r2d2 assembly_zone wheels_zone)  [5.000]
90.018: (transport r2d2 wheel_3 wheels_zone assembly_zone)  [5.000]
95.019: (assemble r2d2 assembly_zone wheel_3 body_car_3 steering_wheel_3 car_3)  [5.000]
