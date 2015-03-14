function ttbuilder(/*arguments...*/) {
    var logger = function(m){console.log(m)};
    var binder = function(m){return function(){logger(m)}};
    var fargs = Array.prototype.slice.call(arguments).map(binder);
    var yielder = function(){var f = fargs.shift(); fargs.push(f); f();}
    return yielder;
}

var tt = ttbuilder('tick', 'tack', 'toe', 'fin');
tt(); tt(); tt(); tt(); tt(); tt(); tt(); tt(); tt();
