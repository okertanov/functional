//
// "A little JavaScript problem"
// The problem: define functions range, map, reverse and foreach,
// obeying the restrictions below, such that the following program works properly.
// It prints the squares of numbers from 1 to 10, in reverse order.
//
// See http://lisperator.net/blog/a-little-javascript-problem/
//

var range = function(from, to) {
  return function(cb) {
    for (var i = from; i <= to; i++) cb(i);
  }
}

var map = function(numbers, fn) {
  return function(cb) {
    numbers(function(i) { cb(fn(i)); });
  }
}
  
var reverse = function(numbers) {
  var continua = function(ofn, fn, param) {
    return function() { fn(param), ofn(fn, param); }  
  }
  
  return function(cb) {
    var inner = function() {};
    numbers(function(i) { inner = continua(inner, cb, i); });
    inner();
  }
}

var foreach = function(numbers, fn) {
  numbers(fn);
}

var numbers = range(1, 11);
numbers = map(numbers, function(n) { return n * n });
numbers = reverse(numbers);
foreach(numbers, console.log);

//
// Output:
//        100
//        81
//        64
//        49
//        36
//        25
//        16
//        9
//        4
//        1
//

