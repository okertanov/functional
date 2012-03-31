// via Oliver Caldwell, http://oli.me.uk/2012/03/14/writing-great-javascript

;(function(exports) {
    'use strict';

    // First you define your class
    function SomeClass() {
        // code...
    }

    SomeClass.prototype.foo = function() {
        // code...
    };

    // And then you expose it
    exports.SomeClass = SomeClass;
}(this)); // <-- this = the global object is passed as exports


// This is only required for server side environments such as node.js
// In the browser you would use a script tag to load it
var SomeClass = require('someclass').SomeClass;

// Then you can call the class like this
var foo = new SomeClass();

