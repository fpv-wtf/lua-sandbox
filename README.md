## A Lua and LVGL sandbox for the DJI Goggles

### Running
Grab the .apk from releases, install and select from the main menu

- The record button takes a screenshot to the sdcard if present
- The back button reloads the lua context
- Use the channel up and down buttons to navigate between elements
- Except when navigating within a widget such as the keyboard or a dropdown, then use the 5d joystic to navigate up/down/left/right
- Click the 5d joystick to confirm selection

Yes, this is garbage and needs improvement.

### Editing Lua
Please find varying examples in the [scripts](scripts/) directory. Once installed as a package, sandbox's lua scripts are stored in `/opt/share/lua-sandbox/scripts/`.

It is reccomended to create a new directory with an entry point of index.lua to add new scripts to the main menu. The provided default index.lua will pick them up automatically.

Alternatively if you want to create a standalone lua application package see package.sh and how it creates the flappy-bird ipk.

### Preview on PC
A very low fps preview that causes high CPU load is available at: http://192.168.42.5:8080/

### Buidling from source and running
```
git clone --recurse-submodules -j8 https://github.com/fpv-wtf/lua-sandbox.git

```

Make sure ANDROID_NDK_HOME is set, r23b is tested and known to be good. Then run:
```
./start.sh
```

This won't interfere with any package installations as everything is installed in /tmp. Since /tmp is an in-memory tmpfs this can affect your memory usage.

### Todo
- Long press back to exit application
- Figure out what to do with LVGL default input key logic (next/prev vs up/down/left/right)
- Shared runtime for stand-alone applications (change a few paths based on argv)
- Navigation logic to push() and pop() full screen views
    - Enable back button navigation
- dji_glasses integration
- Co-existence with msp-osd
    - Either by switching who gets the framebuffer
    - Or by using lvgl as the backend for msp-osd
    - Eventually by replacing the original GUI layer
- Widgets
    - lvgl native widgets don't all have bindings
    - Upstream plans to add them(?)
    - We require a menu for example
- Telemetry streaming and osd widgets system
- Drawing optimzation
    - Current pixel based callbacks aren't optimal
    - Alpha channel reversal needs to be solved to use native framebuffer pointers
- Native module support (should be packaged .so)
    - Proper fonts
    - DUML messaging bindings
    - Native settings bindings
    - JSON libs
    - A better fs lib
- Linting in vscode
- Hot reload

### Contributing
PRs more than welcome.