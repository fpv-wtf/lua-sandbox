cmake_minimum_required(VERSION 3.10)

project(lua-sandbox)

add_custom_target(run COMMAND lua-sandbox)

option(BUILD_SIMULATOR "Build lvgl simulator with luavgl support" OFF)

option(LUA_START_PATH "Lua script to execute on startup" "/opt/share/lua-sandbox/scripts/index.lua")
add_compile_definitions(LUA_START_PATH="${LUA_START_PATH}")

option(DEBUG_HTDOCS_PATH "Where to serve debug server from" "/opt/share/lua-sandbox/htdocs/")
add_compile_definitions(DEBUG_HTDOCS_PATH="${DEBUG_HTDOCS_PATH}")


add_subdirectory(deps/Lua)
list(APPEND LUA_LINK_LIBS lua_static)

set(FIND_LUA_PACKAGE OFF CACHE BOOL "" FORCE)
set(PKG_CONFIG_EXECUTABLE "/bin/false" CACHE STRING "" FORCE)

add_subdirectory(deps/luavgl)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/luavgl/deps/lua-compat-5.3/c-api)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hal)

set(LV_CONF_INCLUDE_SIMPLE "true" CACHE STRING "" FORCE)
add_subdirectory(deps/luavgl/deps/lvgl)
target_include_directories(luavgl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/luavgl/deps/lvgl) # need lvgl.h
target_include_directories(luavgl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hal) # need lv_conf.h 
add_subdirectory(libshims)

add_compile_options(-g -O3)
add_executable(lua-sandbox 
    main.c 
    extension.c 
    hw/dji_display.c 
    hw/dji_services.c 
    hal/evdev.c 
    utils/screenshot.c
    debug_server/ifaddrs.c 
    debug_server/debug_server.c 
    deps/luavgl/deps/lvgl/src/extra/libs/png/lodepng.c
)

target_link_libraries(lua-sandbox luavgl lvgl duml_hal ${LUA_LINK_LIBS})
target_include_directories(lua-sandbox PRIVATE ${LUA_INCLUDE_DIRS})

