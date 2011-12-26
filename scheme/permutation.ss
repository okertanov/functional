;
; CC-GEN
; Copyright (c) Oleg Kertanov <okertanov@gmail.com> 2011
;
; permutation.ss
;
; see also
;     http://paste.lisp.org/display/11447
;

;
; day 0
;
(display "Inside permutation.ss")

;
; day 1
;
(define remove
    (lambda (item lst)
        (cond
            ((equal? item (car lst)) (cdr lst))
            (else (cons (car lst) (remove item (cdr lst)))))
    )
)

(define permute
    (lambda (lst)
        (cond
            ((= (length lst) 1) (list lst))
            (else (apply append (map (lambda (i) (map (lambda (j) (cons i j)) (permute (remove i lst)))) lst)))
        )
    )
)

(newline)
(map
    (lambda (r) (map (lambda (x) (display x) (display " ")) r) (newline))
    (map (lambda (p) p) (permute '(0 1 2)))
)
(newline)
