#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6
#define BUFSIZE WIDTH * 100

#ifndef LUA_START_PATH
#define LUA_START_PATH "/opt/share/lua-playground/scripts/index.lua"
#endif

#ifndef DEBUG_SNAPSHOT_PATH
#define DEBUG_SNAPSHOT_PATH "/blackbox/snapshot.png"
#endif

#ifndef DEBUG_HTDOCS_PATH
#define DEBUG_HTDOCS_PATH "/opt/share/lua-playground/htdocs/"
#endif