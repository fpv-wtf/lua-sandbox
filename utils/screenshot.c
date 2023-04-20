#include "screenshot.h"
#include "../config.h"
#include "../deps/luavgl/deps/lvgl/src/extra/libs/png/lodepng.h"

char * takeScreenshot(screenshot_ctx * ctx, char * path) {
    if(*(ctx->fb0) != NULL && *(ctx->fb1) != NULL) {
        unsigned char* png;
        size_t pngsize;
        uint8_t* tmp = malloc(SCREEN_WIDTH*SCREEN_HEIGHT*BYTES_PER_PIXEL);
        if(tmp == NULL) {
            return "couldn't allocate memory for temporary snapshot buffer";
        }
        pthread_mutex_lock(ctx->fb_switch_lock);
        uint8_t* src=(*(ctx->whichfb) ? *(ctx->fb0) : *(ctx->fb1));
        //so the slow bit has less chance of hitting a changed out fb
        //of course we could have a mutex here but why not go bareback?
        memcpy(tmp, src, 1440*810*4);
        pthread_mutex_unlock(ctx->fb_switch_lock);

        for(int i = 0; i < 1440*810*4; i=i+4) {
            uint8_t swap = tmp[i];
            tmp[i]=tmp[i+2];
            //tmp[i+1]=src[i+1];
            tmp[i+2]=swap;
            tmp[i+3]=~tmp[i+3];
        }
        lodepng_encode32_file(path, tmp, 1440, 810);
        free(tmp);
        return NULL;
    }
    return "frame buffer not inited yet";
}
