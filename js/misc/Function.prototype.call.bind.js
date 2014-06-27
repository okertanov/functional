// http://habrahabr.ru/post/199456/

var bind = Function.prototype.call.bind(Function.prototype.bind); // #fp

// Создадим простой объект, чтобы использовать его в качестве контекста
var context = { foo: "bar" };

// Функция, которая возвращает свойство «foo» контекста «this»
function returnFoo () {
  return this.foo;
}

// Свойства не существует в текущей области видимости, поэтому undefined
returnFoo(); // => undefined

// Но если мы свяжем эту функцию с контекстом
var bound = returnFoo.bind(context);

// Свойство теперь в области видимости
bound(); // => "bar"

//
// Так работает Function.prototype.bind.
// Так как returnFoo — это функция, она наследует прототип Function.prototype
//

// Существует несколько способов связывания функции с контекстом
// Call и apply позволяют вам вызывать функцию с нужным контекстом
returnFoo.call(context); // => bar
returnFoo.apply(context); // => bar

// Так же можно вложить функцию в объект
context.returnFoo = returnFoo;
context.returnFoo(); // => bar

//
// Теперь давайте немного усложним
//

// В Array.prototype есть замечательный метод slice.
// При вызове на массиве он возвращает копию массива
// от начального индекса до конечного (исключительно)
[1,2,3].slice(0,1); // => [1]

// Мы берем slice и присваиваем его локальной переменной
var slice = Array.prototype.slice;

// slice теперь оторван от контекста. Из-за того, что Array.prototype.slice
// работает с данным ему контекстом «this», метод больше не работает
slice(0, 1); // => TypeError: can't convert undefined to object
slice([1,2,3], 0, 1); // => TypeError: ...

// Но мы можем использовать apply и call, они позволяют нам передавать нужный контекст
slice.call([1,2,3], 0, 1); // => [1]

// Apply работает как call, но принимает аргументы в виде массива
slice.apply([1,2,3], [0,1]); // => [1]

// Немного надоедает использовать .call каждый раз. Может воспользоваться bind?
// Точно! Давайте привяжем функцию call к контексту slice.
slice = Function.prototype.call.bind(Array.prototype.slice);

// Теперь slice использует первый аргумент в качестве контекста
slice([1,2,3], 0, 1); // => [1]

//
// Неплохо, правда? Но у меня осталась еще кое-что.
//

// Давайте проделаем с самим bind то же,
// что мы делали со slice
var bind = Function.prototype.call.bind(Function.prototype.bind);

// Обдумайте то, что мы только что сделали.
// Что происходит? Мы оборачиваем call, возвращая функцию, которая принимает функцию и контекст
// и возвращает связанную с контекстом функцию.

// Вернемся к нашему первоначальному примеру
var context = { foo: "bar" };
function returnFoo () {
  return this.foo;
}

// И к нашему новому bind
var amazing = bind(returnFoo, context);
amazing(); // => bar

// Reference: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
