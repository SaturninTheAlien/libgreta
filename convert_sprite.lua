#!/usr/bin/env lua

--[[
A script to find sprites to the new format
]]

local greta = require("greta")

local function endswith(str, suffix)
    return str:sub(-#suffix) == suffix
end

local function convertSprite(fileIn, fileOut)
    local sprite = greta.LoadSprite(greta.File.new(fileIn))
    greta.SaveJsonSprite(sprite, fileOut)
end



if #arg == 2 then
    convertSprite(arg[1], arg[2])

elseif #arg == 1 and endswith(arg[1], ".spr") then
    convertSprite(arg[1], arg[1] .. "2")

else
    print("Usage ./convert_sprite old_sprite.spr new_sprite.spr2")
end


