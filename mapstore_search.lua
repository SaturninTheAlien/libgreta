#!/usr/bin/env lua

--[[
A script to find sprites and other assets

]]

local greta = require("greta")


local assetsPath = os.getenv("HOME") .. "/c++/pk2_greta"
local mapstore_dir = os.getenv("HOME") .. "/games/PK2/PK2_mapstore/old_not_repacked"


local function map(sequence, transformation)
    local newlist = { }
    for i, v in ipairs(sequence) do
        newlist[i]=transformation(v)
    end
    return newlist
end


local function endswith(str, suffix)
    return str:sub(-#suffix) == suffix
end


local function f1(a)
    return a.filename.. " ("..a.dir..") found in "..#a.episodes
end


local function report(a)

    if #a.episodes > 0 then
        print("Asset "..a.filename.." found in:")
        for _, episode in ipairs(a.episodes) do
            print(" -> " .. episode)
        end
    else
        print("Asset "..a.filename.." not found!")
    end
    
end

local function mapstore_search(_assets, verbose)

    local assets = map(_assets, function (a)
        local obj = {
            filename = a.filename,
            type = a.type,
            dir = greta.getDefaultDirForAssetType(a.type),
            episodes = {},
            report = report
        }

        return setmetatable(obj, {
            __tostring = f1
        })
    end)
    
    for _, zip_file in ipairs(greta.fs.scan_dir(mapstore_dir, ".zip")) do
        local zip = greta.Zip.new(tostring(zip_file))

        for _, episode in ipairs(zip:findSubdirectories("episodes")) do

            local episodeFS = greta.EpisodeFS.new(assetsPath, episode, zip)

            for _, a in ipairs(assets) do

                if a.type == 2 then

                    local name = a.filename
                    if endswith(name, ".spr") then
                        name = name .. "2"
                    end

                    if episodeFS:findAsset(name, "sprites", ".spr") then
                        table.insert(a.episodes, zip_file:getFilename() )
                    end
                else
                    if episodeFS:findAsset(a.filename, a.dir, "") then
                        table.insert(a.episodes, zip_file:getFilename() )
                    end
                end

            end

            --print(episode)
        end
    end

    if verbose then
        for _, value in ipairs(assets) do
            --print(value)
            value:report()
        end 
    end

    return assets
end



if ... == nil then


    local testAssets = {
        -- 
        -- {
        --     filename = "tei.spr",
        --     type = 2
        -- }
        {
            filename = "bbtrea1.spr",
            type = 2
        },
        {
            filename = "factory.bmp",
            type = 6
        }
    }

    mapstore_search(testAssets, true)

end


return mapstore_search
