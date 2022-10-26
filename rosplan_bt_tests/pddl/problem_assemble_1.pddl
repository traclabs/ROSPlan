(define (problem task)
(:domain astrobee_assemble)

;; Instances
;; ------------
(:objects
  r2d2  - robot
  car_1 - car
  car_2 - car
  car_3 - car

  wheels_zone - zone
  steering_wheels_zone - zone
  body_car_zone - zone
  assembly_zone - zone
  recharge_zone - zone

  wheel_1 - piece
  wheel_2 - piece
  wheel_3 - piece

  body_car_1 - piece
  body_car_2 - piece
  body_car_3 - piece

  steering_wheel_1 - piece
  steering_wheel_2 - piece
  steering_wheel_3 - piece 
)

;; Predicates
;; -------------
(:init

  (is_assembly_zone assembly_zone)
  (is_recharge_zone recharge_zone)

  (piece_is_wheel wheel_1)
  (piece_is_wheel wheel_2)
  (piece_is_wheel wheel_3)
  (piece_at wheel_1 wheels_zone)
  (piece_at wheel_2 wheels_zone)
  (piece_at wheel_3 wheels_zone)

  (piece_is_body_car body_car_1)
  (piece_is_body_car body_car_2)
  (piece_is_body_car body_car_3)
  (piece_at body_car_1 body_car_zone)
  (piece_at body_car_2 body_car_zone)
  (piece_at body_car_3 body_car_zone)

  (piece_is_steering_wheel steering_wheel_1)
  (piece_is_steering_wheel steering_wheel_2)
  (piece_is_steering_wheel steering_wheel_3)
  (piece_at steering_wheel_1 steering_wheels_zone)
  (piece_at steering_wheel_2 steering_wheels_zone)
  (piece_at steering_wheel_3 steering_wheels_zone)
  (robot_at r2d2 wheels_zone)
  (battery_full r2d2)
  (robot_available r2d2)
  (piece_not_used wheel_1)
  (piece_not_used wheel_2)
  (piece_not_used wheel_3)
  (piece_not_used body_car_1)
  (piece_not_used body_car_2)
  (piece_not_used body_car_3)
  (piece_not_used steering_wheel_1)
  (piece_not_used steering_wheel_2)
  (piece_not_used steering_wheel_3)

)

(:goal (and
  (car_assembled car_1)
  (car_assembled car_2)
  (car_assembled car_3)
  )
)

) ; End of define
