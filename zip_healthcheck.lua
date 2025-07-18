#!/usr/bin/env lua

local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"
local greta = require("greta_lua")

local resetColor = "\x1B[0m"

local function zipHealthCheck(path, verbose)

    if not greta.fs.is_absolute(path) then
        path = assetsPath .. "/res/data/mapstore/" .. path
    end

    if verbose then
        print("Checking zip file: "..path)
    end

    local res = {status = 0}
    local zip = greta.Zip.new(path)
    local zippedEpisodes = zip:findSubdirectories("episodes")

    if #zippedEpisodes == 0 then

        if verbose then
            print("No PK2 episodes in the zip!") 
        end

        res.status = 1
        return res

    elseif verbose then

        print("Found "..tostring(#zippedEpisodes).." episodes")
        for i, epName in ipairs(zippedEpisodes) do
            print("["..tostring(i).."] \x1B[1;36m"..epName..resetColor)
        end
    end

    local episodeTree = greta.EpisodeTree.new(assetsPath, "", zip)
    --episodeTree.debug = true
    for _, epName in ipairs(zippedEpisodes) do
        episodeTree:setEpisode(epName, zip)

        if episodeTree:loadAllLevels() == 0 then
            res.status = 2;

            if verbose then
                print("\x1B[1;33mEpisode has no levels!" .. resetColor)
            end

            return res
        end
    end

    local missingAssets = episodeTree:getMissingAssets()
    local malformedAssets = episodeTree:getMalformedAssets()

    if #missingAssets == 0 and #malformedAssets == 0 then

        if verbose then
            print("\x1B[0;92mEverything is alright!" .. resetColor)
        end
        
        res.status = 0
        return res
    else

        res.status = 3
        res.missing = missingAssets
        res.malformed = malformedAssets

        if verbose and #missingAssets > 0 then
            print("Missing assets: ")

            for _, asset in ipairs(missingAssets) do
                print("\x1B[1;31m" .. asset.filename .. resetColor)
                print(asset:getStackTrace())
            end
        end

        if verbose and #malformedAssets > 0 then
            print("Malformed assets: ")
            for _, asset in ipairs(malformedAssets) do
                print("\x1B[41m\x1B[1;33m" .. asset.filename .. resetColor)

                print(asset.what)

                print(asset:getStackTrace())
            end
        end

    end

    return res

end


local episode = "/home/saturnin/games/PK2/Rajdh n Kiolp Complete Saga/rajdh_n_kiolp_complete_saga_fixed.zip"
if #arg >= 1 then
    episode = arg[1]
    print(episode)
end

zipHealthCheck(episode, true)