The Language
============

Rationale
---------
To create
    simple
    functional
    sexp-based
    self-hosting
    crucially interpreted
    turing-complete
    homoiconic
    lexically scoped
    programming language.

Free grammar
------------
* atom (number, symbol, keyword)
    123
    '123
    1e2
    abc
    'abc
    :cde
* cell
    (1 . 2) - pair
    (1 . (2 . (3 . nil))) - list
* list (of atoms or cells or lists or empty)
    (list 1 2 3)
    (list (1 . 2) (3 . 4))
    (list (list 1 2 3) (list 'a 'b 'c))
    ()
* form
    lambda
    list
    cons
    car
    cdr
    quote
    define
    let
    syntax(macro?)
    if
    loop
* macro
* expression (sexp)
    (map (lambda [x] (* 2 x)) (cons 1 (list 2 3 4 5 6 7)))
    '(1 . (2 . (3 . nil)))
    (let ([|asdf foo bar baz| 'O] [ya 'ne])
        (display |asdf foo bar baz|) (display ya))
* sugar
    ' for quote
    '() for list
    [] for ()
    #t & #f for (.) and ()
    nil for ()
    # for macro?
    equal? for predicate
    "" for string
    space for dotted pair
    " for comment
    + - * / operators for add subtract multiply divide functions
    &#955; for lambda
* other
    runtime
    ffi
    gc
    tail recursion
    lazy evaluation

Lexical grammar
---------------

High level structure
--------------------
* read
* write
* eval
* apply
* print

Naming
------
* mowa
* lamed
* bicycle-like

??
--
crucially based -- which uses an infinite tower of interpreters;
