#lang scheme

;;
;; fibonacci.scm
;;
;; @see http://en.wikipedia.org/wiki/Fibonacci_number
;;

;;
;; @fn fibonacci-naïve
;;
(define fibonacci-naïve
  (λ (n)
    "This function calculates the Fibonacci sequence naïvely."
    (cond
      ((or (= 0 n) (= 1 n)) n)
      (else (+ (fibonacci-naïve (- n 1))
               (fibonacci-naïve (- n 2)))))))

;;
;; @fn fibonacci-linear
;;
(define fibonacci-linear
  (λ (n)
    "This function calculates the Fibonacci sequence sequentially."
    (cond
      ((or (= 0 n) (= 1 n)) n)
      (else
       (cdr
        (for/fold ((acc (cons 0 1))) ((i (in-range 2 (+ n 1))))
          (cons (cdr acc) (+ (car acc) (cdr acc)))))))))

;;
;; @fn fibonacci-tail
;;
(define fibonacci-tail
  (λ (n)
    "This function calculates the Fibonacci sequence tail-optimized."
    (letrec
        ((fibonacci-t
          (λ (n p1 p2)
            (cond
              ((= n 0) p1)
              (else (fibonacci-t (- n 1) p2 (+ p1 p2)))))))
      (fibonacci-t n 0 1))))

;;
;; @fn fibonacci-dijkstra
;;
(define fibonacci-dijkstra
  (λ (n)
    "This function calculates the Fibonacci sequence with
     Edsger W. Dijkstra's algorithm."
    (letrec
        ((fibonacci-d
          (λ (a b p q c)
            (cond ((= c 0) b)
                  ((even? c) (fibonacci-d a
                                          b
                                          (+ (* p p) (* q q))
                                          (+ (* q q) (* 2 p q))
                                          (/ c 2)))
                  (else (fibonacci-d (+ (* b q) (* a q) (* a p))
                                     (+ (* b p) (* a q))
                                     p
                                     q
                                     (- c 1)))))))
      (fibonacci-d 1 0 0 1 n))))

;;
;; @fn syntax for run with ...
;;
(define-syntax run
  (syntax-rules (with list and time)
    ((_ <fn> <range>)
     (for ((i (in-range (car <range>) (cdr <range>))))(<fn> i)))
    ((_ with list <fn> <range>)
     (for/list ((i (in-range (car <range>) (cdr <range>))))(<fn> i)))
    ((_ with time <fn> <range>)
     (time (for ((i (in-range (car <range>) (cdr <range>))))(<fn> i))))
    ((_ with list and time <fn> <range>)
     (time (for/list ((i (in-range (car <range>) (cdr <range>))))(<fn> i))))))

;;
;; Tests
;;
(fibonacci-naïve 30)
(fibonacci-linear 100000)
(fibonacci-tail 100000)
(fibonacci-dijkstra 100000)

;;
;; Tests with the ranges
;;
(run with time fibonacci-naïve (cons 0 30))
(run with time fibonacci-linear (cons 0 1000))
(run with time fibonacci-tail (cons 0 1000))
(run with time fibonacci-dijkstra (cons 0 1000))

;;
;; Results
;;
;; cpu time: 1030 real time: 1061 gc time: 31
;; cpu time: 312 real time: 334 gc time: 63
;; cpu time: 266 real time: 262 gc time: 31
;; cpu time: 31 real time: 23 gc time: 0

