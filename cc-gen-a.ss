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

