(define (problem task)
(:domain astrobee_assemble)
(:objects
    r2d2 - robot
    wheels_zone steering_wheels_zone body_car_zone assembly_zone recharge_zone - zone
    wheel_1 wheel_2 wheel_3 body_car_1 body_car_2 body_car_3 steering_wheel_1 steering_wheel_2 steering_wheel_3 - piece
    car_1 car_2 car_3 - car
)
(:init
    (battery_full r2d2)

    (robot_available r2d2)

    (robot_at r2d2 wheels_zone)

    (piece_at wheel_1 wheels_zone)
    (piece_at wheel_2 wheels_zone)
    (piece_at wheel_3 wheels_zone)
    (piece_at body_car_1 body_car_zone)
    (piece_at body_car_2 body_car_zone)
    (piece_at body_car_3 body_car_zone)
    (piece_at steering_wheel_1 steering_wheels_zone)
    (piece_at steering_wheel_2 steering_wheels_zone)
    (piece_at steering_wheel_3 steering_wheels_zone)

    (piece_is_wheel wheel_1)
    (piece_is_wheel wheel_2)
    (piece_is_wheel wheel_3)

    (piece_is_body_car body_car_1)
    (piece_is_body_car body_car_2)
    (piece_is_body_car body_car_3)

    (piece_is_steering_wheel steering_wheel_1)
    (piece_is_steering_wheel steering_wheel_2)
    (piece_is_steering_wheel steering_wheel_3)

    (piece_not_used wheel_1)
    (piece_not_used wheel_2)
    (piece_not_used wheel_3)
    (piece_not_used body_car_1)
    (piece_not_used body_car_2)
    (piece_not_used body_car_3)
    (piece_not_used steering_wheel_1)
    (piece_not_used steering_wheel_2)
    (piece_not_used steering_wheel_3)

    (is_assembly_zone assembly_zone)

    (is_recharge_zone recharge_zone)


)
(:goal (and
    (car_assembled car_1)
    (car_assembled car_2)
    (car_assembled car_3)
))
)
