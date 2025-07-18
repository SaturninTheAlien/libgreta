#!/usr/bin/env lua

local greta = require("greta_lua")

local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"
local episodeName = "Debug Island"


function EpisodeTest()
    

    local episode = greta.EpisodeTree.new(assetsPath, episodeName)
    episode.debug = true

    local levelFiles = episode:searchForLevels()

    print(#levelFiles)

    for i, file in ipairs(levelFiles) do
        print(tostring(i) .. " -> " .. tostring(file))
    end


    for _, file in ipairs(levelFiles) do
        episode:loadLevel(file)
    end
end


-- function LevelTest()
--     local episode = greta.EpisodeTree.new()
--     episode.verbose = true

--     episode:loadLevel(
--         greta.File.new(
--             greta.GetAssetsPath() .. "/episodes/Debug Island/lua_cult.map"
--         )
--     )
-- end


-- function SpriteTest()
--     local episode = greta.EpisodeTree.new()
--     episode.verbose = true

--     local sprite = episode:loadSprite("dino.spr")
--     print(sprite)
--     print(sprite.prototype)
    
-- end

if ... == nil then
    --SpriteTest()
    --LevelTest()

    EpisodeTest()
end