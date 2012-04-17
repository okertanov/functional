#lang racket

(require racket/base racket/list racket/class racket/gui/base)
(require slideshow/base slideshow/code slideshow/pict slideshow/flash)

;
; Dotted pairs aka Ordered pair
;
'(1 . (2 . (3 . null)))

;
; Higher order sequence processing - map
;
(map
  (lambda [x] (* 2 x))
  (cons 1 (list 2 3 4 5 6 7)))

;
; Symbol with ||
;
(let ([|asdf foo bar baz| 'O] [ya 'ne])
  (display |asdf foo bar baz|) (displayln ya))

;
; To cons two atoms onto ordered pair
;
(list 1 2) (cons 1 2)
(equal? (list 1 2) (cons 1 2))

;
; To cons atom onto list
;
(list 1 2 3) (cons 1 (list 2 3))
(equal? (list 1 2 3) (cons 1 (list 2 3)))

;
; Predicates and contract system
;
(define atom? (or/c number? symbol? boolean? string?))

;
; GUI
;
(define frame-caption "Hello, Scheme!")
(define w 640)
(define h 480)
(define text-to-draw  "")

(define pictures
  (list
    (colorize (filled-flash 50 50) "yellow")
    (colorize (circle 10) "red")))

(define main-frame 
  (new frame% 
    [label frame-caption]
    [width w]	 
    [height h]
    [style '(toolbar-button)]))

(define canvas-painter 
  (lambda (canvas dc)
    ; Base drawing
    (send dc set-scale 4 4)
    (send dc set-background (send the-color-database find-color "floralwhite"))
    (send dc clear)
    (send dc set-text-foreground "black")
    (send dc draw-text text-to-draw 32 32)
    ; Drawlers
    (map 
     (lambda [picture]
       (let ([drawer (make-pict-drawer picture)])
         (drawer dc 0 0)))
     pictures)))

(define root-canvas 
  (new canvas%
    [parent main-frame]
    [style '(border no-autoclear)]
    [paint-callback canvas-painter]))

(send main-frame show #t)

