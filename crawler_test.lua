#!/usr/bin/env lua

local greta = require("greta")

greta.SetAssetsPath( os.getenv("HOME") .. "/c++/pk2_greta")
greta.SetEpisode("Debug Island", nil)

function CrawlerTest()
    local crawler = greta.Crawler.new()
    crawler.verbose = true

    local sprite = crawler:loadSprite("dino.spr")
    print(sprite)
    print(sprite.prototype)
    
end

if debug.getinfo(1).what=="main" then
    CrawlerTest()
end