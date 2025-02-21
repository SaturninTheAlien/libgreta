#!/usr/bin/env lua

local greta = require("greta")

greta.SetAssetsPath( os.getenv("HOME") .. "/c++/pk2_greta")
greta.SetEpisode("Debug Island", nil)


function EpisodeTest()
    local levelFiles = greta.SearchForLevels()

    -- print(#levelFiles)

    -- for i, file in ipairs(levelFiles) do
    --     print(tostring(i) .. " -> " .. tostring(file))
    -- end

    local crawler = greta.Crawler.new()
    crawler.verbose = true

    for _, file in ipairs(levelFiles) do
        crawler:loadLevel(file)
    end
end


function LevelTest()
    local crawler = greta.Crawler.new()
    crawler.verbose = true

    crawler:loadLevel(
        greta.File.new(
            greta.GetAssetsPath() .. "/episodes/Debug Island/episodes/Debug Island/lua_cult.map"
        )
    )
end


function SpriteTest()
    local crawler = greta.Crawler.new()
    crawler.verbose = true

    local sprite = crawler:loadSprite("dino.spr")
    print(sprite)
    print(sprite.prototype)
    
end

if debug.getinfo(1).what=="main" then
    --SpriteTest()
    --LevelTest()

    EpisodeTest()
end