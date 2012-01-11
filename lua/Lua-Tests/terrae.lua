--[[
-------------------------------------------------------------------------
    HTTP Stress Test Script
    Copyright (c) 2009-2010 A&H Software House, Inc. All Rights Reserved.
-------------------------------------------------------------------------
]]

-------------------------------------------------------------------------
module("terrae", package.seeall)
-------------------------------------------------------------------------

-------------------------------------------------------------------------
-- Pretty print helper obj
prettyprint = {
    width   = 32,
    header  = "=",
    row     = "-",
    footer  = "=",

    -- Line Spacer
    line = function (this, d, n)
        io.write(string.rep(d, n or this.width));
        io.write("\n");
    end,

    -- A regular printf
    printf = function (_, ...)
        io.write(string.format(...));
    end
}
-------------------------------------------------------------------------

-------------------------------------------------------------------------
dumper = {
    -- A simple Table dumper
    dump_table = function (_, m)
        local scoped_idx = 0;
        for k, v in pairs(m) do
            local idx = scoped_idx;
            print(idx..": ", k, "=>", v);
            scoped_idx = idx + 1;
        end
    end,

    -- Much more complex key-value dumper
    make_dumper_kv = function (_, delim)
        local scoped_idx = 0;
        return function(k, v)
            local idx = scoped_idx;
            print(idx..": ", k, delim, v);
            scoped_idx = idx + 1;
        end
    end
}
-------------------------------------------------------------------------

