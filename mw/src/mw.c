
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mqueue.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#include <pthread.h>

#include "std_types.h"

#include "mw.h"
#include "mw_Cfg.h"

#include "mw_sci_cc.h"

_PRIVATE mqd_t msq_id = -1;

_PRIVATE void mw_sci_cc_init(void) 
{
    struct mq_attr attr;
    memset(&attr, 0, sizeof(attr));
    attr.mq_msgsize = MAX_MSGQ_PAYLOAD;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;

    msq_id = mq_open(MSG_Q_NAME, O_RDWR | O_CREAT | O_NONBLOCK | O_EXCL,
                         0777, &attr);
    if(msq_id < 0)
    {   
        perror("could not open message queue");
        exit(EXIT_FAILURE);
    }
}

_PUBLIC void mw_sci_cc_send(ipc_message_t *message)
{
    if( mq_send(msq_id, (const char_t *)message, MAX_MSGQ_PAYLOAD, 0) < 0)
    {
        perror( "mq_send failed" );
        exit( EXIT_FAILURE );
    }
}

_PUBLIC void mw_sci_cc_receive(ipc_message_t *message)
{
    if ( mq_receive(msq_id, (char_t *)message, MAX_MSGQ_PAYLOAD, NULL) < 0)
    {
        perror("mq_receive failed");
        exit( EXIT_FAILURE );
    }
}

_PUBLIC void mw_init(void)
{
    mw_sci_cc_init();
    sci_cc_init(msq_id);
}

_PUBLIC void mw_event_loop(void)
{
    while (true)
    {
        sci_cc_event_loop();
    }
}