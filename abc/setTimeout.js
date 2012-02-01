
function func(x)
{
    console.log(x);
}

setTimeout(func(1), 1000)
setTimeout(func, 1, 1000)
setTimeout(func, 1000, 1)
setTimeout(function(x){return function(){func(x)};}(1),1000);

