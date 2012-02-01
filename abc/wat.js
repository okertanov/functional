//
// https://www.destroyallsoftware.com/talks/wat
//

[] + [] === ""

[] + {} === "[object Object]"

{} + [] === 0

{} + {} === isNaN()

Array(16) === ,,,,,,,,,,,,,,,,

Array(16).join('wat') === wat 16 times

Array(16).join('wat' + 1) === wat1 16 times

Array(16).join('wat' - 1) + " Batman!" === NaN 16 times Batman!

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Math.min() < Math.max() === false

var foo = [0];
console.log(foo == !foo);
console.log(foo == foo);

typeof NaN === "number"

3..toString() === "3"

console.log( (![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]] )

var Z = "constructor";
Z[Z][Z]("alert('wtfjs!')")();

"222" - -"111" === 333

undefined = 42;

[] == ![]

parseInt('06') == 6
parseInt('08') == 0

