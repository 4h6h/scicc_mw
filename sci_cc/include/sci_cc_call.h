/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_SCI_CC_CALL_H
#define PINTSCH_SCI_CC_CALL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mw_queue_types.h"

/* Public required interface */
void mw_sci_cc_send(ipc_message_t *message);
void mw_sci_cc_receive(ipc_message_t *message); 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PINTSCH_SCI_CC_CALL_H */