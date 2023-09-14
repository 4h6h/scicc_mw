/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_LOG_H
#define PINTSCH_LOG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stdio.h"

enum {
    TRACE = 0,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
} log_level;

#define log(level, X) fprintf(stderr, X)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PINTSCH_LOG_H */
