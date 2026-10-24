#ifndef serialCommand_h_included
#define serialCommand_h_included

#define SERIAL_COMMAND_LENGTH 15

#include "constants.h"

#ifdef DEV_SERIAL
void SerialMessageCallback(const char *data);
bool SerialCallback_Command(void *data);
#endif

#endif