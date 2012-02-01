Y = function (f)
   return function(p)
      return
        (function(x) return x(x) end)(function(x) return f(function(y) return x(x)(y) end) end)(p)
   end
end

factorial1 = function(f) return function(n) return n > 0 and n * f(n-1) or 1 end end
factorialR = Y(factorial1)

print(factorialR(7))

