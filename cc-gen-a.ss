;
; cc-gen-a.ss
;

(define sum
  (lambda (x . y)
    (apply + x y))) 

(display (sum 1 2 3 4 5)) (newline)

