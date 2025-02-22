#!/usr/bin/env lua

local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"
local greta = require("greta")

local resetColor = "\x1B[0m"

local function zipHealthCheck(path)

    if not greta.fs.is_absolute(path) then
        path = assetsPath .. "/res/data/mapstore/" .. path
    end

    print("Checking zip file: "..path)
    local zip = greta.Zip.new(path)
    local zippedEpisodes = zip:findSubdirectories("episodes")

    if #zippedEpisodes == 0 then
        print("No PK2 episodes in the zip!")
        return

    else
        print("Found "..tostring(#zippedEpisodes).." episodes")
        for i, epName in ipairs(zippedEpisodes) do
            print("["..tostring(i).."] \x1B[1;36m"..epName..resetColor)
        end
    end

    local episodeTree = greta.EpisodeTree.new(assetsPath, "", zip)
    --episodeTree.debug = true
    for _, epName in ipairs(zippedEpisodes) do
        episodeTree:setEpisode(epName, zip)
        episodeTree:loadAllLevels()
    end

    local missingAssets = episodeTree:getMissingAssets()
    local malformedAssets = episodeTree:getMalformedAssets()

    if #missingAssets == 0 and #malformedAssets == 0 then
        print("\x1B[0;92mEverything is alright!" .. resetColor)
    else
        if #missingAssets > 0 then
            print("Missing assets: ")

            for _, asset in ipairs(missingAssets) do
                print("\x1B[1;31m" .. asset.filename .. resetColor)
                print(asset:getStackTrace())
            end
        end

        if #malformedAssets > 0 then
            print("Malformed assets: ")
            for _, asset in ipairs(malformedAssets) do
                print("\x1B[41m\x1B[1;33m" .. asset.filename .. resetColor)
                print(asset:getStackTrace())
            end
        end

    end

end


if debug.getinfo(1).what=="main" then
    local episode = assetsPath .. "/res/data/mapstore/tm.zip"

    if #arg >= 1 then
        episode = arg[1]
    end

    zipHealthCheck(episode)
    
end

return zipHealthCheck