/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_PLATFORM_TYPES_H
#define PINTSCH_PLATFORM_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifndef TRUE
#   define TRUE true
#endif

#ifndef FALSE
#   define FALSE false
#endif

typedef uint8_t byte_t;
typedef char    char_t;
typedef bool    bool_t;

#define is_bigendian() ( (*(char*)&i) == 0 )

#endif /* PINTSCH_PLATFORM_TYPES_H */