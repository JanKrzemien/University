#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "funkcje.h"

#define _XOPEN_SOURCE 500

// funkcja wypisująca identyfikatory procesu
void wypiszIDProcesu()
{
    printf("UID = %u | GID = %u | PID = %u | PPID = %u | PGID = %u\n",
          getuid(), getgid(), getpid(), getppid(), getpgrp());
    return;
}
