function perm_generate(a, n)
  if n == 0 then
    coroutine.yield(a)
  else
    for i=1,n do

      -- put i-th element as the last one
      a[n], a[i] = a[i], a[n]

      -- generate all permutations of the other elements
      perm_generate(a, n - 1)

      -- restore i-th element
      a[n], a[i] = a[i], a[n]

    end
  end
end


function permutation(a)
  local n = table.getn(a)
  return coroutine.wrap(function () perm_generate(a, n) end)
end


function print_result (a)
  for i,v in ipairs(a) do
    io.write(v, " ")
  end
  io.write("\n")
end

itable = {"0", "1", "2"};

for p in permutation(itable) do
  print_result(p)
end

