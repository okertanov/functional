;;
;; via http://thraxil.org/users/anders/posts/2008/09/15/My-Own-Javascript-Y-Combinator/
;;

;; Y = λf·(λx·f (x x)) (λx·f (x x))

(define Y
  (lambda (X)
    ((lambda (procedure)
       (X (lambda (arg) ((procedure procedure) arg))))
     (lambda (procedure)
       (X (lambda (arg) ((procedure procedure) arg)))))))

