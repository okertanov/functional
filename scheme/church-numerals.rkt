#lang racket

;;
;; https://courses.cs.washington.edu/courses/csep505/13sp/lectures/church.rkt
;;
;; https://gist.github.com/vivekhaldar/2438498
;;
;; http://www.cs.unc.edu/~stotts/723/Lambda/church.html
;;
;; Defines several concepts using only functions; namely:
;; - booleans and conditionals
;; - pairs
;; - natural numbers and arithmetic operators
;; - recursion
;;
;; Defines factorial in terms of these functions, along with a
;; way to convert from Church numerals to Racket numbers in order
;; to verify the result.

;; Converts a Church numeral to a Racket number.
(define (as-number n)
  ((n add1) 0))

;; Converts a Church boolean to a Racket boolean.
(define (as-bool b)
  ((b #t) #f))

;; Church numeral representation of 0.
(define zero (λ (f) (λ (x) x)))

;; Returns the next Church numeral after n.
(define (succ n)
  (λ (f) (λ (x) (f ((n f) x)))))

;; Church numerals.
(define one   (succ zero))
(define two   (succ one))
(define three (succ two))
(define four  (succ three))
(define five  (succ four))
(define six   (succ five))
(define seven (succ six))
(define eight (succ seven))
(define nine  (succ eight))
(define ten   (succ nine))

;; Adds two Church numerals.
(define (add n m)
  (λ (f) (λ (x) ((n f) ((m f) x)))))

;; Debug.
(as-number zero)
(as-number one)
(as-number two)
(as-number three)


;; Multiplies two Church numerals.
(define (mult n m)
  (λ (f)
    (n (m f))))

;; Computes n^m with Church numerals.
(define (exp n m)
  (m n))

;; Church encoding of true.
(define true (λ (x) (λ (y) x)))

;; Church encoding of false.
(define false zero)

;; Church encoding of the pair (x, y).
(define (make-pair x y)
  (λ (selector) ((selector x) y)))

;; Returns the first element of a pair.
(define (fst p)
  (p true))

;; Returns the second element of a pair.
(define (snd p)
  (p false))

;; Returns (x, x+1).
(define (self-and-succ x)
  (make-pair x (succ x)))

;; Given (x, y), returns (y, y+1).
(define (shift p)
  (self-and-succ (snd p)))

;; Returns the predecessor to the Church numeral n by
;; applying n to shift and (0, 0), then taking the first
;; element of the pair.
(define (pred n)
  (fst ((n shift) (make-pair zero zero))))

;; The eager Y combinator.
(define (fix f)
  ((λ (x) (λ (y) ((f (x x)) y)))
   (λ (x) (λ (y) ((f (x x)) y)))))

;; Returns whether a Church numeral is 0.
(define (is0 n)
  ((n (λ (x) false)) true))

;; An "if-then-else" function (the then and else branches
;; must be wrapped in zero-argument lambdas).
(define (ifte c t e)
  (((c t) e)))

;; The factorial function.
(define fact
  (fix (λ (f)
         (λ (n)
           (ifte (is0 n)
                 (λ () one)
                 (λ () (mult n (f (pred n)))))))))

