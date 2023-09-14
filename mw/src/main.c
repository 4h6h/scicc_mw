#include "std_types.h"
#include "mw.h"

int main(int argc, char* argv[])
{
    (void)argc; /* unused */
    (void)argv; /* argv */

    mw_init();
    mw_event_loop();

    return E_OK;
}