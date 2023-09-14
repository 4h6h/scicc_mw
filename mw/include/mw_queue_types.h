/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_MW_QUEUE_TYPES_H
#define PINTSCH_MW_QUEUE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "std_types.h"
#include "mw_queue_types_Cfg.h"

enum mesg_type {
    LST = 0,
    CCX,
};

typedef uint8_t mesg_type_t;

struct __attribute__((__packed__)) _ipc_message {
    mesg_type_t    type;
    char_t         payload[MAX_MSGQ_PAYLOAD-sizeof(mesg_type_t)];
};
typedef struct _ipc_message ipc_message_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PINTSCH_MW_QUEUE_TYPES_H */