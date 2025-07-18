#!/usr/bin/env lua
local greta = require("greta_lua")

local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"
local episodeName = "Debug Island"

local fs = greta.EpisodeFS.new(assetsPath, episodeName)

function LoadSprite(name)
    local file = fs:findAsset(name, "sprites", ".spr")
    if file == nil then
        print(name .. " not found!")
        return nil
    end

    --print(file:getFilename())
    local sprite = greta.LoadSprite(file)
    print()
    print("name: ".. sprite.name)
    print("ammo1: "..sprite.ammo1)
    print("ammo2: "..sprite.ammo2)
    print("bonus: "..sprite.bonus)

    return sprite

end

function FSTest()
    LoadSprite("PiG.SpR2")
    LoadSprite("pumpki1.spr")
end

if ... == nil then
    FSTest()
end




