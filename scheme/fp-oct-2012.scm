#lang scheme

;;
;; Октябрьский конкурс по ФП
;; 12 Окт, 2012 @ 08:16
;;
;; http://users.livejournal.com/_darkus_/679674.html
;;

(define-values
  (◠ ◡ ≣ ◉ ▢ ▨)
  (values '◠ '◡ '≣ '◉ '▢ '▨))

(define profile->top 
  '((◠ . ◉)
    (◡ . ▨)
    (≣ . ▢)))

(define profile->bottom 
  '((◠ . ▨)
    (◡ . ◉)
    (≣ . ▢)))

;;  (◠ . ◠)  X ->  1    1    false
;;  (◠ . ◡)    ->  1   -1    true
;;  (◠ . ≣)    ->  1    0    true
;;  (◡ . ◠)  X -> -1    1    false
;;  (◡ . ◡)  X -> -1   -1    false
;;  (◡ . ≣)    -> -1    0    true
;;  (≣ . ◠)    ->  0    1    true
;;  (≣ . ◡)    ->  0   -1    true
;;  (≣ . ≣)    ->  0    0    true

(define profile:segment->segment
  '((◠ . ◡)
    (◠ . ≣)
    (◡ . ≣)
    (≣ . ◠)
    (≣ . ◡)
    (≣ . ≣)))

(define top:segment->segment
  '((◉ . ▨)
    (◉ . ▢)
    (▨ . ▢)
    (▢ . ◉)
    (▢ . ▨)
    (▢ . ▢)))

(define (transform what table)
  "Transforms the list using pair association list"
  (map 
   (λ(w)
     (let
       ((pair (assoc w table)))
       (if pair
           (cdr pair)
           w)))
   what))

(define (profile bar)
  "Defines 3-segment bar"
  bar)

(define (top bar)
  "Transforms bar representation
  from profile view to the top view"
  (transform bar profile->top))

(define (bottom bar)
  "Transforms bar representation
  from profile view to the bottom view"
  (transform bar profile->bottom))

(define (dump lst)
  "Displays parameter's contents"
  (display lst))

(define (v-delimiter)
  "Emits new line into the port"
  (newline))

(define (segment-conforms-segment? s1 s2 table)
  "Finds whether the segment conforms rules"
  (cond
    ((list?
     (member (cons s1 s2) table)))
    (else #f)))

(define (bar-conforms-bar? bar1 bar2)
  "Finds whether the one bar conforms other one"
  (andmap
   (λ(s1 s2)
     (segment-conforms-segment?
      s1
      s2
      profile:segment->segment))
   bar1
   bar2))

(define (solve bars)
  "Main solver"
  bars)

(define (solved? bars)
  "Solved predicate"
  #f)

(let
  ((b1 '(◠ ◡ ≣))
   (b2 '(◠ ◡ ≣))
   (b3 '(◠ ≣ ◡))
   (b4 '(◠ ≣ ≣))
   (b5 '(◠ ◡ ◡))
   (b6 '(◠ ◡ ◠)))
  (let
    ((bars (list b1 b2 b3 b4 b5 b6)))
    (for-each (compose dump profile) bars)
    (v-delimiter)
    (for-each (compose dump top) bars)
    (v-delimiter)
    (for-each (compose dump bottom) bars)
    (v-delimiter)
    (let
      ((box (solve bars)))
      (solved? box))))
