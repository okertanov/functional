--
-- Lua scripting demo
-- Copyright (c) Oleg Kertanov 2014
--

 local function l_dump_globals()
    for k, v in pairs(_G) do
        print(k, v)
    end
end

local function l_mul(a, b)
    return a * b;
end

l_bootstrap = function ()
    -- l_dump_globals()
    print(l_mul(111, 111))
    return cmul(11, 12)
end