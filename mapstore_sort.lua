#!/usr/bin/env lua

local greta = require("greta")
local mapstore_dir = "/home/saturnin/games/PK2/PK2_mapstore/old_not_repacked"

local target_good_zips = "/home/saturnin/games/PK2/PK2_mapstore/good"
local target_bad_zips = "/home/saturnin/games/PK2/PK2_mapstore/bad"

local zipHealthCheck = require("zip_healthcheck")

for _, zip_file in ipairs(greta.fs.scan_dir(mapstore_dir, ".zip")) do

    

    local res = zipHealthCheck(tostring(zip_file))

    if res.status == 0 then

        print( tostring(zip_file) .. "is \x1B[1;92mgood\x1B[0m")
        os.execute("cp \"".. tostring(zip_file) .."\" " .. target_good_zips)
    else

        print( tostring(zip_file) .. "is \x1B[1;31bad\x1B[0m")
        os.execute("cp \"".. tostring(zip_file) .."\" " .. target_bad_zips)
    end

    --print(res.status)
end
