;
;    @file       factorial.scm
;    @brief      Scheme language primer
;
;    @author     Oleg Kertanov <okertanov@gmail.com>
;    @date       April 2012
;    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
;    @license    BSD
;    @see        LICENSE file
;

;
; Language
;
#lang scheme

;
; Recursive and iterative factorial functions in Scheme
;

;
; Factorial maker with common pre-condition
;
(define make-factorial
  (λ (f)
    (λ (n)
      (cond
        ((not (integer? n)) +nan.0)
        ((negative? n) -inf.0)
        (else (f n))))))

;
; Recursive factorial function
;
(define factorial-re (λ (n)
  (cond
    ((zero? n) 1)
    (else (* n (factorial-re (- n 1)))))))

;
; Iterative (and imperative) factorial function
;
(define factorial-nr (λ (n)
  (begin
    (define p 1)
    (for ((i (in-range 1 (+ 1 n)))) (set! p (* p i))))
    (values p)))

;
; Applicate both of them
;
(time
  (let
    ((number 5))
      (let
        ((f1 ((make-factorial factorial-re) number))
         (f2 ((make-factorial factorial-nr) number)))
        "Dump and check for equality"
        (list (cons f1 f2) (eq? f1 f2)))))

;
; Result
;

#|
    cpu time: 0 real time: 0 gc time: 0
    ((120 . 120) #t)
|#

;
; Declarative factorial function in Scheme
;

;
; Syntactic sugar
;
(define-syntax-rule (the a b)
  (begin (define a b) a))

(define-syntax-rule (is e) e)

(define-syntax-rule (to e) e)

(define less/than? (λ (a b)
  (< a b)))

;
; Formal description
;

#|
    http://en.wikipedia.org/wiki/Factorial

    The factorial of a non-negative integer n, denoted by n!,
    is the product of all positive integers less than or equal to n.
    The value of 0! is 1.
|#

;
; Definition
;
(the factorial/of
  (λ (a)
    (let ((n a))
      (cond
        ((and (not (negative? n)) (integer? n))
          "denoted by n!"
          (is
            (the of/all
              (for/product
                ((i ((λ (s)
                  (stop-before (in-naturals)
                    (λ (i) (not (or (less/than? i s) (equal? i s))))
                  )
                )(to n))))
                (cond
                  ((and (positive? i) (integer? i)) i)
                  ((zero? i) "the value of 0! is 1" 1)
                  (else -inf.0)
                )
              )
            )
          )
        )
      )
    )
  )
)

;
; Application
;
(factorial/of 5)

;
; Result
;

#|
    #<procedure:factorial/of>
    120
|#
