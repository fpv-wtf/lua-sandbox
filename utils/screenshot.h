#ifndef SCREENSHOT
#define SCREENSHOT

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    void** fb0;
    void** fb1;
    bool* whichfb;
    pthread_mutex_t* fb_switch_lock;
} screenshot_ctx;


char * takeScreenshot(screenshot_ctx * ctx, char * path);

#endif