function Y(dn) {
    return function(fn) {
        return fn(fn);
    }(function(fn) {
        return dn(function(x) {
            return fn(fn)(x);
        });
    });
}