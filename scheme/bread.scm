#lang scheme

"Как два программиста хлеб пекли. http://habrahabr.ru/post/153225"

" — Нам нужно, чтобы делался хлеб."
(define (bread) '(bread))
(define (make thing) (thing))

(make bread)

" — Нам нужно, чтобы хлеб не просто делался, а выпекался в печке."
(define (bake thing)(λ() (thing)))

(make (bake bread))

" — Нам нужно, чтобы печки были разных видов."
(define-syntax use
  (syntax-rules (electric microwave gas oven)
    ((use electric <opt> ... oven <do> <thing>)
     (use oven <do> <thing>))
    ((use microwave <opt> ... oven <do> <thing>)
     (use oven <do> <thing>))
    ((use gas <opt> ... oven <do> <thing>)
     (cond ((> <opt> 0 ) ... (use oven <do> <thing>))
           (else (λ()(void)))))
    ((use oven <do> <thing>)
     (<do> <thing>))))

(make (use gas oven bake bread))
(make (use electric (220v 1/2A) oven bake bread))
(make (use microwave vendor: Panasonic™ model: EEM1100 oven bake bread))

" — Нам нужно, чтобы газовая печь не могла печь без газа."
(make (use gas 0 oven bake bread))
(make (use gas 5.75 oven bake bread))

" — Нам нужно, чтобы печки могли выпекать ещё и пирожки (отдельно — с мясом, отдельно — с капустой), и торты."
(define (pie filling) (λ()(list filling 'pie)))
(define (cake) '(cake))

(make (use gas oven bake (pie 'meat)))
(make (use gas oven bake (pie 'cabbage)))
(make (use gas oven bake cake))

" — Нам нужно, чтобы хлеб, пирожки и торты выпекались по разным рецептам."
(define (recipe what thing) (λ()(cons what (thing))))

(make (use gas oven bake (recipe "Brown bread" bread)))
(make (use gas oven bake (recipe "Kiev cake" cake)))

" — Нам нужно, чтобы в печи можно было обжигать кирпичи."
(define (brick) '(brick))
(define (burn thing)(λ() (thing)))

(make (use electric (380v 5A) oven burn brick))

;;
;; Output:
;;
;; "Как два программиста хлеб пекли. http://habrahabr.ru/post/153225"
;; " — Нам нужно, чтобы делался хлеб."
;; (bread)
;; " — Нам нужно, чтобы хлеб не просто делался, а выпекался в печке."
;; (bread)
;; " — Нам нужно, чтобы печки были разных видов."
;; (bread)
;; (bread)
;; (bread)
;; " — Нам нужно, чтобы газовая печь не могла печь без газа."
;; (bread)
;; " — Нам нужно, чтобы печки могли выпекать ещё и пирожки (отдельно — с мясом, отдельно — с капустой), и торты."
;; (meat pie)
;; (cabbage pie)
;; (cake)
;; " — Нам нужно, чтобы хлеб, пирожки и торты выпекались по разным рецептам."
;; ("Brown bread" bread)
;; ("Kiev cake" cake)
;; " — Нам нужно, чтобы в печи можно было обжигать кирпичи."
;; (brick)
;;

