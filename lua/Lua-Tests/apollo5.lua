#!/usr/bin/lua
--[[
-------------------------------------------------------------------------
    HTTP Stress Test Script
    Copyright (c) 2009-2010 A&H Software House, Inc. All Rights Reserved.
-------------------------------------------------------------------------
]]

-------------------------------------------------------------------------
require("impact")
require("terrae")
-------------------------------------------------------------------------

-------------------------------------------------------------------------
-- Local (ok, lexically local) data table:
-- An Array emulation with a Table, where keys are 1..n.
local state_map = {"A", "B", "C", "D"};

-- And then let's see what's up
terrae.prettyprint:line(terrae.prettyprint.header);
-- Dump the header: table + num of table's elements
print(state_map, #state_map, table.getn(state_map));

terrae.prettyprint:line(terrae.prettyprint.row);
-- Dump the data table by ref
terrae.dumper:dump_table(state_map);

-- But let's break the Logic above, add definitely valid [0] element
state_map[0] = "~";

terrae.prettyprint:line(terrae.prettyprint.header);
-- Dump the header: table + num of table's elements
print(state_map, #state_map, table.getn(state_map));

terrae.prettyprint:line(terrae.prettyprint.row);
-- Dump the same but using table.foreach with closure magic indeed
table.foreach(state_map, terrae.dumper:make_dumper_kv("->"));

terrae.prettyprint:line(terrae.prettyprint.footer);
-------------------------------------------------------------------------

