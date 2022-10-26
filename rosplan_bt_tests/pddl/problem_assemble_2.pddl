(define (problem task)
(:domain astrobee_assemble)

;; Instances
;; ------------
(:objects
  r2d2  - robot
  car_1 - car
  wheels_zone - zone
  wheel_1 body_car_1 steering_wheel_1 - piece


)

;; Predicates
;; -------------
(:init

  (robot_at r2d2 wheels_zone)

)

(:goal (and
  (robot_at r2d2 wheels_zone)
  )
)

)
