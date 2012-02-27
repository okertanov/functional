function Y(dn) {
    return function(fn) {
        return fn(fn);
    }(function(fn) {
        return dn(function(x) {
            return fn(fn)(x);
        });
    });
}

var Y = function(f) {
  return (function(g) {
    return g(g);
  })(function(h) {
    return function() {
      return f(h(h)).apply(null, arguments);
    };
  });
};

var factorial = Y(function(recurse) {
  return function(x) {
    return x == 0 ? 1 : x * recurse(x-1);
  };
});

factorial(5)  // -> 120

