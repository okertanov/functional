;
; CC-GEN 
; Copyright (c) Oleg Kertanov <okertanov@gmail.com> 2011
;
; cc-gen-a.ss
;

(define sum
  (lambda (x . y)
    (apply + x y))) 

(display (sum 3 4 5 6 7 8 9)) (newline)
(display (sum 1/2 1/2)) (newline)
(display (car '(1 2 3 4 5))) (newline)

