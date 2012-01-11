-- --------------------------------------------------
-- MainBot.lua - main module
-- okertanov@gmail.com (c) 2010
-- --------------------------------------------------

require 'pw'

local theGame = GameLogic:new();
theGame:Initialize();
theGame:Play();
theGame:Release();

