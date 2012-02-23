Mowa the Language
=================

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

Generic Forms
-------------
    http://stackoverflow.com/questions/4589366/the-most-minimal-lisp
    http://stackoverflow.com/questions/3482389/how-many-primitives-does-it-take-to-build-a-lisp-machine-ten-seven-or-five

### Courtesy of Paul Graham, here's a Common Lisp implementation of John McCarthy's original LISP:
    It assumes:
    quote, atom, eq, cons, car, cdr, and cond,
    and defines null, and, not, append, list, pair, assoc, eval, evcon and evlis.

### http://hyperpolyglot.org/lisp#ten-primitives
    On this site they say there are 10 LISP primitives.
    The primitives are: atom, quote, eq, car, cdr, cons, cond, lambda, label, apply.

### McCarthy's Elementary S-functions and Predicates were:
    1 atom
    Which was necessary because car and cdr are undefined for lists, which means you cannot count
    on any sort of answer to indicate what was happening if you gave car an atom.
    2 eq
    For testing equality between atoms.
    3 car
    For returning the first half (address) of the cons cell. (Contents of address register).
    4 cdr
    For returning the second half (decrement) of the cons cell. (Contents of decrement register).
    5 cons
    For making a new cons cell, with the address half containing the first argument to cons,
    and the decrement half containing the second argument.

### Tying it together: S-Functions
    He then went on to add to his basic notation, to enable writing what he called S-functions:
    1 quote
    To represent an expression without evaluating it.
    2 cond
    The basic conditional to be used with the previously described predicates.
    3 lambda
    To denote a function.
    4 label
    Though he didn't need this for recursion, he might not have known about the Y-Combinator (according to Paul Graham),
    he added this for convenience and to enable easy recursion.

    atom could be discarded if you defined the car operation on atoms to return NIL. 


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

TODO
----
crucially based -- which uses an infinite tower of interpreters;

Inject/hoist minimally needed forms into the global ctx.
cons, define, lambda, etc...


Links
[Lexing and Parsing with Marpa](http://savage.net.au/Ron/html/graphviz2.marpa/Lexing.and.Parsing.with.Marpa.html)
[Lexing](http://en.wikipedia.org/wiki/Lexing)
[LL_parser](http://en.wikipedia.org/wiki/LL_parser)
[The most minimal LISP? - closed](http://stackoverflow.com/questions/4589366/the-most-minimal-lisp)
[How many primitives does it take to build a LISP machine? Ten, seven or five?](http://stackoverflow.com/questions/3482389/how-many-primitives-does-it-take-to-build-a-lisp-machine-ten-seven-or-five)
[What the Read Function Accepts](http://www.cs.cmu.edu/Groups/AI/html/cltl/clm/node188.html)
