// ush.h
#ifndef CHEERS_H
#define CHEERS_H

// Include headers from standart libraries
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>
#include <sys/signal.h>
#include <strings.h>

// Include headers from local libraries
#include "libmx.h"
#include "json.h"
#include "libjson.h"
#include "vector.h"

// Include local headers
#include "definitions.h"
#include "enums.h"
#include "structs.h"
#include "error.h"
#include "functions.h"
#include "debug.h"


#define LEN_BUFF 1024

#endif // !CHEERS_H
