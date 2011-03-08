;
; CC-GEN 
; Copyright (c) Oleg Kertanov <okertanov@gmail.com> 2011
;
; cc-gen-a.ss
;

;
; day 1
;
(define sum
    (lambda (x . y)
        (apply + x y))) 

(display (sum 3 4 5 6 7 8 9)) (newline)
(display (sum 0.5 0.2)) (newline)
(display (car '(1 2 3 4 5))) (newline)

;
; day 2
;
(define on-every-item
    (lambda (lst)
        (if (not (null? lst))
            (begin (display (car lst)) 
                   (newline)
                   (on-every-item (cdr lst)))
            '()
        )
    )
)

(on-every-item '(a b c d))

;
; day 3
;
(define on-every-item-2
    (lambda (lst)
        (map (lambda (x) (display x) (newline)) lst)
    )
)

(on-every-item-2 '(10 20 30 40 50))

