//
// Church Numerals in JS
//
// See
// https://en.wikipedia.org/wiki/Church_encoding
//
(function() {

//
// Pure Numerals
//
var _zero   = f => x => x
var _one    = f => x => f(x)
var _two    = f => x => f(f(x))
var _three  = f => x => f(f(f(x)))
var _four   = f => x => f(f(f(f(x))))
var _five   = f => x => f(f(f(f(f(x)))))
var _six    = f => x => f(f(f(f(f(f(x))))))
var _seven  = f => x => f(f(f(f(f(f(f(x)))))))
var _eight  = f => x => f(f(f(f(f(f(f(f(x))))))))
var _nine   = f => x => f(f(f(f(f(f(f(f(f(x)))))))))
var _ten    = f => x => f(f(f(f(f(f(f(f(f(f(x))))))))))

//
// Numerals via sequences
//
var pred = n => f => x => n(g => h => h(g(f)))(y => x)(x => x)
var succ = n => f => x => f(n(f)(x))
var zero = f => x => x
var one   = succ(zero)
var two   = succ(one)
var three = succ(two)
var four  = succ(three)
var five  = succ(four)
var six   = succ(five)
var seven = succ(six)
var eight = succ(seven)
var nine  = succ(eight)
var ten   = succ(nine)

//
// Math Operations
//
var add = (n, m) => f => x => n(f)(m(f)(x))
var sub = (n, m) => m(pred)(n)
var mul = (n, m) => f => n(m(f))
var exp = (n, m) => m(n)

//
// Helpers
//
var num = n => n((a) => ++a)(null)
var print = n => console.log(n)
var printn = n => print(num(n))
var printns = function() { print([].slice.call(arguments).map(n => num(n)).join('')) }

//
// Debug code
//
printns(_zero, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine, _ten)
printns(zero, one, two, three, four, five, six, seven, eight, nine, ten)
printn(add(ten, five))
printn(sub(nine, six))
printn(mul(three, seven))
printn(exp(two, eight))

})()
