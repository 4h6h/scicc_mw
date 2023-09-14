/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_SCI_CC_CFG_H
#define PINTSCH_SCI_CC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "std_types.h"

#define MAX_CLIENTS ((uint16_t)30)
#define PORT        (8888)

#define MAX_PENDING_CONS ((uint8_t)3)

#define READ_BUFFER_LENGTH ((uint16_t)1024)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PINTSCH_SCI_CC_CFG_H */
