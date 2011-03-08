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
        (apply + x y)
    )
) 

(display (car '(1 2 3 4 5))) (newline)
(display (sum 3 4 5 6 7 8 9)) (newline)
(display (sum 0.5 0.2)) (newline)

;
; day 2
;
(define on-every-item
    (lambda (lst)
        (if (not (null? lst))
            (begin (display (car lst)) 
                   (display " ")
                   (on-every-item (cdr lst)))
            (begin (newline)
                   '())
        )
    )
)

(on-every-item '(a b c d))

;
; day 3
;
(define on-every-item-2
    (lambda (lst)
        (map (lambda (x) (display x) (display " ")) lst)
        (newline)
    )
)

(on-every-item-2 '(10 20 30 40 50))

;
; day 4
;
(define square
    (lambda (i)
        (* i i)
    )
)

(define cube
    (lambda (i)
        (* i i i)
    )
)

(define (apply-func f)
    (lambda (x)
        (f x)
    )
)

(display ((apply-func square) 3)) (newline)
(display ((apply-func cube) 3)) (newline)

;
; day 5
;
(define (iterate-with f)
    (lambda (lst)
        (map (lambda (x) (f x)) lst)
    )
)

(define output-pair
    (lambda (p)
        (display (car p))
        (display " => ") 
        (display (cdr p)) (newline)
    )
)

(let ((cube-and-print-for (iterate-with (lambda (i)(output-pair (cons i (cube i)))))))
    (cube-and-print-for '(1 2 3 4 5 6 7))
)

;
; day 6
;
(let ((print-for (iterate-with (lambda (i)(display i)))))
    (print-for '((+ -) (* /) (square cube)))
)

(newline)

