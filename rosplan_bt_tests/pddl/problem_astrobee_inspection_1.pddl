(define (problem problem_1) (:domain astrobee_inspection)

(:objects
  honey - robot
  bumble - robot
  wp0 - location
  wp1 - location
  wp2 - location
  wp3 - location
  wp4 - location
  wp5 - location
  honey_dock - location
  bumble_dock - location
)


(:init
  (robot_at honey honey_dock)
  (robot_at bumble bumble_dock)
  (robot_available honey)
  (robot_available bumble)
)

(:goal (and
         (location_inspected wp0)
         (location_inspected wp1)
         (location_inspected wp2)
         (location_inspected wp3)
         (location_inspected wp4)
         (location_inspected wp5)
;	 (robot_at honey honey_dock)
;	 (robot_at bumble bumble_dock)
       )
)

)