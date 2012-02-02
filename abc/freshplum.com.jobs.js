// https://freshplum.com/jobs/
// Copyright © 2011 Oleg Kertanov <okertanov@gmail.com>

var a = []; 

for (i=0; i <= 100000; i++) { 
    x = Math.floor(Math.random() * 11) + Math.floor(Math.random() * 11); /*original expression*/ 
    a[x] == undefined ? a[x] = 0 : a[x] += 1; 
}; 

a.indexOf(  a.reduce(  function f(p,c,i,a) {
                           return (c > p ? c : p);
                       }, 
            -1 /*initial value*/ )
);
