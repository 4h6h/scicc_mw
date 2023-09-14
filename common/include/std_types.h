/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_STD_TYPES_H
#define PINTSCH_STD_TYPES_H

#include "platform_types.h"

#ifndef MIN
#   define MIN(_x,_y) (((_x) < (_y)) ? (_x) : (_y))
#endif

#ifndef MAX
#   define MAX(_x,_y) (((_x) > (_y)) ? (_x) : (_y))
#endif

typedef uint8_t std_return_t;
#define E_OK        (std_return_t)0
#define E_NOT_OK    (std_return_t)1

#define _PRIVATE static
#define _PUBLIC  extern

#endif /* PINTSCH_STD_TYPES_H */