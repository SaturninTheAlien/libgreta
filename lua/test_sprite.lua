#!/usr/bin/env lua

local greta = require("greta")

function PigTest()
    local sprite = greta.LoadLegacySprite(os.getenv("HOME") .. "/c++/pk2_greta/res/episodes/Debug Island/sprites/flyp2.spr")
    print("The sprite name is: "..sprite.name)
    for i, ai in ipairs(sprite.ai) do
        print(i.." -> "..ai)
    end
    print(sprite.ammo1)
    print(sprite.ammo2)
    print(sprite.bonus)
    print(sprite.transformation)

    print(sprite.attack1_offset)
    print(sprite.attack2_offset)

    --print(sprite.)

    greta.SaveJsonSprite(sprite, "test.json")
end

function DinoTest()
    local sprite = greta.LoadJsonSprite("dino.spr2")

    print(sprite.ammo1)
    print(sprite.ammo2)
    print(sprite.bonus)
    print(sprite.transformation)
    print(sprite.attack1_offset)
    print(sprite.attack2_offset)

    greta.SaveJsonSprite(sprite, "test.json")
end

if ... == nil then
    greta.Test()
    PigTest()
    DinoTest()
end
