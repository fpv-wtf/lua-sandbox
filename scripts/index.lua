local function scripts_index()

    local focused = lvgl.Style({
        border_width = 5,
        border_color = "#a00",
    })

    local list = lvgl.List(nil, {
        pad_all = 10,
        x = 80,
        y = 40
    })
    list:add_text("Scripts:")

    -- local dir <close>, msg, code = lvgl.fs.open_dir(SCRIPT_PATH .. "/")
    local dir, msg, code = lvgl.fs.open_dir(SCRIPT_PATH .. "/" )
    if not dir then
        print("open dir failed: ", msg, code)
        return
    end

    while true do
        local d = dir:read()
        if not d then break end
        if string.byte(d, 1) == string.byte("/", 1) then
            local subdir, submsg, subcode = lvgl.fs.open_dir(SCRIPT_PATH .. "/" .. d .. "/"  )
            if not subdir then
                print("open dir failed: ", submsg, subcode)
                return
            end
            while true do
                local s = subdir:read()
                if not s then break end
                if s == "index.lua" then
                    list:add_btn(NULL, d):onClicked(function()
                        list:delete()
                        require( d .. "/index")
                    end)
                end
            end     
        end
    end
    dir:close()
end

scripts_index()
