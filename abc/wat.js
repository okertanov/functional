//
// https://www.destroyallsoftware.com/talks/wat
//

// via http://stackoverflow.com/questions/9032856/can-anyone-explain-these-bizarre-javascript-behaviours-mentioned-in-the-wat-ta/9033306#9033306
// and ECMA-262 standard.

/*
When using the addition operator, both the left and right operands are converted to primitives first (§11.6.1).
As per §9.1, converting an object (in this case an array) to a primitive returns its default value,
which for objects with a valid toString() method is the result of calling object.toString() (§8.12.8).
For arrays this is the same as calling array.join() (§15.4.4.2).
Joining an empty array results in an empty string, so step #7 of the addition operator returns
the concatenation of two empty strings, which is the empty string.
*/
[] + [] === ""

/*
Similar to [] + [], both operands are converted to primitives first. For "Object objects" (§15.2),
this is again the result of calling object.toString(), which for non-null,
non-undefined objects is "[object Object]" (§15.2.4.2).
*/
[] + {} === "[object Object]"

/*
The {} here is not parsed as an object, but instead as an empty block (§12.1, at least as long
as you're not forcing that statement to be an expression, but more about that later).
The return value of empty blocks is empty, so the result of that statement is the same as +[].
The unary + operator (§11.4.6) returns ToNumber(ToPrimitive(operand)).
As we already know, ToPrimitive([]) is the empty string, and according to §9.3.1, ToNumber("") is 0.
*/
{} + [] === 0

/*
Similar to the previous case, the first {} is parsed as a block with empty return value.
Again, +{} is the same as ToNumber(ToPrimitive({})), and ToPrimitive({}) is "[object Object]" (see [] + {}).
So to get the result of +{}, we have to apply ToNumber on the string "[object Object]".
When following the steps from §9.3.1, we get NaN as a result:
    If the grammar cannot interpret the String as an expansion of StringNumericLiteral,
    then the result of ToNumber is NaN.
*/
{} + {} === isNaN()

Array(16) === ,,,,,,,,,,,,,,,,

Array(16).join('wat') === wat 16 times

Array(16).join('wat' + 1) === wat1 16 times

/*
As per §15.4.1.1 and §15.4.2.2, Array(16) creates a new array with length 16. To get the value
of the argument to join, §11.6.2 steps #5 and #6 show that we have to convert both operands to a number using ToNumber.
ToNumber(1) is simply 1 (§9.3), whereas ToNumber("wat") again is NaN as per §9.3.1.
Following step 7 of §11.6.2, §11.6.3 dictates that
        If either operand is NaN, the result is NaN.
So the argument to Array(16).join is NaN. Following §15.4.4.5 (Array.prototype.join),
we have to call ToString on the argument, which is "NaN" (§9.8.1):
        If m is NaN, return the String "NaN".
Following step 10 of §15.4.4.5, we get 15 repetitions of the concatenation of "NaN" and the empty string,
which equals the result you're seeing. When using "wat" + 1 instead of "wat" - 1 as argument,
the addition operator converts 1 to a string instead of converting "wat" to a number,
so it effectively calls Array(16).join("wat1").

As to why you're seeing different results for the {} + [] case: When using it as a function argument,
you're forcing the statement to be an ExpressionStatement,
which makes it impossible to parse {} as empty block, so it's instead parsed as an empty object literal.
*/
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

