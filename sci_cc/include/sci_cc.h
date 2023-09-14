/*******************************************************************************
*
* Copyright (c) PINTSCH GmbH
*
* <description>
*
*********10********20********30********40********50********60********70********/

#ifndef PINTSCH_SCI_CC_H
#define PINTSCH_SCI_CC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* public methods */
void sci_cc_init(uint16_t _fd_q);
void sci_cc_event_loop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PINTSCH_SCI_CC_H */