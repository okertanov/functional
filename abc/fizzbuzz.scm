#lang scheme

;;
;;  http://www.codinghorror.com/blog/2007/02/why-cant-programmers-program.html
;;
;;  Write a program that prints the numbers from 1 to 100.
;;  But for multiples of three print "Fizz" instead of the number and
;;  for the multiples of five print "Buzz".
;;  For numbers which are multiples of both three and five print "FizzBuzz".
;;

(let* ((range (cons 1 100))
      (fizz? (λ(n)(zero? (modulo n 3))))
      (buzz? (λ(n)(zero? (modulo n 5)))))
  (for/list ((i (stop-after
                  (in-naturals (car range))
                  (λ(s)(equal? s (cdr range))))))
    (or
      (and (fizz? i) (buzz? i) 'FizzBuzz)
      (and (fizz? i) 'Fizz)
      (and (buzz? i) 'Buzz)
      i)))
