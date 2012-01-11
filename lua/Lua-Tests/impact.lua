--[[
-------------------------------------------------------------------------
    HTTP Stress Test Script
    Copyright (c) 2009-2010 A&H Software House, Inc. All Rights Reserved.
-------------------------------------------------------------------------
]]

-------------------------------------------------------------------------
module("impact", package.seeall)
-------------------------------------------------------------------------

-------------------------------------------------------------------------
-- What the rules of the game are?
assert(0);
assert("0");
assert(nil == nil);
assert(undef_a == nil);
assert(0 == 0);
assert("0" == "0");
assert("0" ~= "1");
assert("0" ~= 0);
assert("0" ~= 1);
assert(true);
assert(not false);
assert(type(true) == "boolean");
assert(type(false) == "boolean");
assert(type(1==1) == "boolean");
assert(type(undef_a) == "nil");
assert(type(nil) == "nil");
assert(type(0) == "number");
assert(type("0") == "string");
assert(type(3.141592) == "number");
assert(type(_G) == "table");
assert(type({}) == "table");
assert(type(function()end) == "function");
assert(type(assert) == "function");
assert(type(math) == "table");
assert(type(math.pi) == "number");
assert(type(os.date) == "function");
-------------------------------------------------------------------------

