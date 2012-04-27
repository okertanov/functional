;
; The Lambda Calculus by Ashley Feniello
; http://blogs.msdn.com/b/ashleyf/archive/2008/12/03/the-lambda-calculus.aspx
;

(define (true a b) a)
(define (false a b) b)
(define (if c a b) (c a b))

(define (cons a b) (λ (c) (if c a b)))
(define (car c) (c true))
(define (cdr c) (c false))

(define (zero  f) (λ (x) x))
(define (one   f) (λ (x) (f x)))
(define (two   f) (λ (x) (f (f x))))
(define (three f) (λ (x) (f (f (f x)))))

(define (print n) ((n (λ (n) (+ n 1))) 0))

(define (zero? n) ((n (λ (x) false)) true))

(define (succ n) (λ (f) (λ (x) (f ((n f) x)))))
(define (pred n) (cdr ((n (λ (p) (cons (succ (car p)) (car p)))) (cons zero zero))))

(define (sub a b) ((b pred) a))
(define (add a b) ((b succ) a))
(define (mult a b) ((a (λ (x) (add x b))) zero))

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

(define Z (λ (f) ((λ (x) (f (λ (y) ((x x) y)))) (λ (x) (f (λ (y) ((x x) y)))))))

(define fac (Z (λ (f) (λ (n) (if (zero? n) one (mult n (f (sub n one))))))))

(define fac ((λ (f) ((λ (x) (f (λ (y) ((x x) y)))) (λ (x) (f (λ (y) ((x x) y)))))) (λ (f) (λ (n) ((((λ (c) (λ (a) (λ (b) ((c a) b)))) ((λ (n) ((n (λ (x) (λ (a) (λ (b) b)))) (λ (a) (λ (b) a)))) n)) (λ (f) (λ (x) (f x)))) (((λ (a) (λ (b) ((a (λ (x) (((λ (a) (λ (b) ((b (λ (n) (λ (f) (λ (x) (f ((n f) x)))))) a))) x) b))) (λ (f) (λ (x) x))))) n) (f (((λ (a) (λ (b) ((b (λ (n) ((λ (c) (c (λ (a) (λ (b) b)))) ((n (λ (p) (((λ (a) (λ (b) (λ (c) ((((λ (c) (λ (a) (λ (b) ((c a) b)))) c) a) b)))) ((λ (n) (λ (f) (λ (x) (f ((n f) x))))) ((λ (c) (c (λ (a) (λ (b) a)))) p))) ((λ (c) (c (λ (a) (λ (b) a)))) p)))) (((λ (a) (λ (b) (λ (c) ((((λ (c) (λ (a) (λ (b) ((c a) b)))) c) a) b)))) (λ (f) (λ (x) x))) (λ (f) (λ (x) x))))))) a))) n) (λ (f) (λ (x) (f x)))))))))))
