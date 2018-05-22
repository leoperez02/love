/** @brief: Este programa muestra el uso del UART
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int config_serial ( char *, speed_t );
void proceso(char *cadena);
