#!/usr/bin/env lua

local greta = require("greta")
local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"


function ListEpisodes()
    local zip = greta.Zip.new(assetsPath .. "/res/data/mapstore/tm.zip")
    local episodes = zip:findSubdirectories("episodes")

    print(#episodes)

    for index, value in ipairs(episodes) do
        print("["..tostring(index).."] "..tostring(value))
    end

end

function SagaTest()
    local zip = greta.Zip.new(assetsPath .. "/res/data/mapstore/tm.zip")
    local episode = greta.EpisodeTree.new(assetsPath, "Time-Machine 2 - In The Future", zip)

    -- episode.debug = true
    
    local levelFiles = episode:searchForLevels()
    for i, file in ipairs(levelFiles) do
        print(tostring(i) .. " -> " .. tostring(file))
    end

    for _, file in ipairs(levelFiles) do
        episode:loadLevel(file)
    end

    print("Missing assets:")
    for _, missing in ipairs(episode:getMissingAssets()) do
        print("Missing: ".. missing.filename)
        print(missing:getStackTrace())

    end
    
end

if debug.getinfo(1).what=="main" then
    --ListEpisodes()
    SagaTest()
end

--local episodeName = "Debug Island"
