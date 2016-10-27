#ifndef REDIS_H
#define REDIS_H
#include "global.h"
#include "xRedisClient.h"
unsigned int APHash(const char *str);

enum {
 CACHE_TYPE_1, 
 CACHE_TYPE_2,
 CACHE_TYPE_MAX,
};

#endif
