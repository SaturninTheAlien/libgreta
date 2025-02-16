#!/usr/bin/env lua
local greta = require("greta")

greta.SetAssetsPath( os.getenv("HOME") .. "/c++/pk2_greta")

function FindTest()

    greta.SetEpisode("Debug Island", nil)

    print(greta.FindAsset("PiG.SpR2", "sprites"))
    print(greta.FindAsset("mune.spr2", "sprites", ""))
    print(greta.FindAsset("missing.spr", "sprites", "") == nil)

end

if debug.getinfo(1).what=="main" then
    FindTest()
end




