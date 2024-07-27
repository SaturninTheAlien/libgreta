#!/usr/bin/env lua

local greta = require("greta")
greta.Test()

local sprite = greta.LoadLegacySprite("/home/saturnin/c++/pk2_greta/res/episodes/Debug Island/sprites/flyp2.spr")

print("The sprite name is: "..sprite.name)

for i, ai in ipairs(sprite.ai) do
    print(i.." -> "..ai)
end

print(sprite.ammo1)
print(sprite.ammo2)

print(sprite.bonus)

print(sprite.transformation)

greta.SaveJsonSprite(sprite, "test.json")