#lang scheme

; Syntactic sugar
(define ^ expt)
(define << arithmetic-shift)

; Как можно получать степени двойки:
; арифметически, алгоритмически, императивно
; и рекурсивно.

(* 2 2 2)
(^ 2 3)
(<< 1 3)

(define nexpt
  (λ (n p)
    (cond
      ((< p 1) 1)
      (else (* n (nexpt n (- p 1)))))))

(nexpt 2 3)

;
; 8
; 8
; 8
; 8
;
