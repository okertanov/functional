#lang scheme

;;
;; Operations
;;
(define-syntax-rule (add l r) (+ l r))
(define-syntax-rule (sub l r) (- l r))
(define-syntax-rule (mul l r) (* l r))
(define-syntax-rule (div l r) (/ l r))

;;
;; Destructuring environment & evaluation
;;
(define-syntax evaluate-e-a
  (syntax-rules ()
    ((_ ((sym val)...) body)
     (match-let* ([sym val]...)
       body))))

;;
;; Execution
;;
(evaluate-e-a
  ((a 1)(b 2))
  (add a (mul 2 b)))

