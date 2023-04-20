
#include "debug_server.h"

#include <stdlib.h>
#include <lvgl.h>
#include <ifaddrs.h>
//#include "ifaddrs.h"
#include "../deps/EmbeddableWebServer/EmbeddableWebServer.h"

#include "../config.h"

static int counter = 0;
static struct Server server;
static screenshot_ctx *ctx;

void * acceptConnectionsThread(screenshot_ctx* _ctx) {
    ctx = _ctx;
    serverInit(&server);
    const uint16_t portInHostOrder = 8080;
    acceptConnectionsUntilStoppedFromEverywhereIPv4(&server, portInHostOrder);
    return NULL;
}


struct Response* createResponseForRequest(const struct Request* request, struct Connection* connection) {
	if (0 == strncmp(request->pathDecoded, "/png", 4)) {
		char* error = takeScreenshot(ctx, DEBUG_SNAPSHOT_PATH);
    if(error != NULL) {
      responseAlloc404NotFoundHTML(error);
    }
    return responseAllocWithFile(DEBUG_SNAPSHOT_PATH, "image/png");
	}
    return responseAllocServeFileFromRequestPath("/", request->path, request->pathDecoded, DEBUG_HTDOCS_PATH);
    
	//return responseAlloc404NotFoundHTML("What?!");
}