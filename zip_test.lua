#!/usr/bin/env lua

local greta = require("greta")

greta.SetAssetsPath( os.getenv("HOME") .. "/c++/pk2_greta")

local zips = greta.SearchForZips()
for i, zipFile in ipairs(zips) do
    print("["..tostring(i).."] "..tostring(zipFile))
end



-- local zip = greta.PZip.new(os.getenv("HOME") .. "/c++/pk2_greta/res/data/mapstore/tm.zip")

-- local episodes = zip:findEpisodeNames()

-- for i, episode in ipairs(episodes) do
--     print("["..tostring(i).."] "..episode)
-- end

-- greta.SetEpisode("Time-Machine 2 - In The Future", zip)
-- local levelFiles = greta.SearchForLevels()

-- print(#levelFiles)

-- for i, file in ipairs(levelFiles) do
--     print("["..tostring(i).."] ".. tostring(file))
-- end

-- local crawler = greta.Crawler.new()
-- crawler.verbose = true

-- for _, file in ipairs(levelFiles) do
--     crawler:loadLevel(file)
-- end