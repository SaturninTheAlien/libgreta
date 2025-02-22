#!/usr/bin/env lua
local greta = require("greta")

greta.SetAssetsPath( os.getenv("HOME") .. "/c++/pk2_greta")
greta.SetEpisode("Debug Island", nil)

function FindTest()
    print(greta.FindAsset("mune.spr2", "sprites"))
    print(greta.FindAsset("missing1.spr", "sprites") == nil)

    print(greta.FindAsset("PiG.SpR", "sprites", ".spr2"))

end

function LoadSprite(name)
    local file = greta.FindAsset(name, "sprites", ".spr")
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

function LoadSpriteTest()
    LoadSprite("PiG.SpR2")
    --LoadSprite("pig3.spr2")
    --print("TEST")
    LoadSprite("pumpki1.spr")
end

if debug.getinfo(1).what=="main" then
    LoadSpriteTest()
    --FindTest()
end




