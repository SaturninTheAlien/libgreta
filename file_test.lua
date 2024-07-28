#!/usr/bin/env lua
local greta = require("greta")



greta.SetAssetsPath("/home/saturnin/c++/pk2_greta")
-------This also works:
-- greta.SetAssetsPath("/home/saturnin/c++/pk2_greta/res")

greta.SetEpisode("Debug Island")

print(greta.FindPK2Asset("PiG.SpR2", "sprites"))
print(greta.FindPK2Asset("mune.spr2", "sprites"))
print(greta.FindPK2Asset("missing.spr", "sprites") == nil)
