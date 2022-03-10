// init.c

#include "cheers.h"

app_t *app_init(void) {
	app_t *app = NULL;
 

	// allocate memory for app struct
	app = (app_t *) malloc(sizeof(app_t));
	if (app == NULL) return NULL;
	memset(app, 0, sizeof(app_t));

	
	return app;
}

void app_quit(app_t *app) {
	free(app);
}
