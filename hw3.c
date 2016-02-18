/*
----------------------------------------------
These are the only libraries that can be used. Under no circumstances
can additional libraries be included.
----------------------------------------------
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/signal.h>
#include "shell.h"

/*
-----------------------------------
  Main function 
  Arguments:	argc = number of arguments suppled by user
                argv = array of argument values
-----------------------------------
*/
static void sig_child_handler(int sig);

int main(int argc, char **argv) {
    command_t cmd;
    char line[MAXSTRLEN];
    char fullpath[MAXSTRLEN];
    int done = FALSE;

    if (signal(SIGCHLD, sig_child_handler) == SIG_ERR) {

        perror("Unable to create new child signal handler!");
        exit(-1);

    }

    while (!done) {
        printf(">> ");
        fgets(line, MAXSTRLEN, stdin);
        line[my_strlen(line) - 1] = '\0'; // get rid of newline
        parse(line, &cmd);

        if (cmd.argc > 0) {   // fix for no command (ie white space) entered
            if (my_strequal(cmd.name, "exit")) {
                done = TRUE;
            }
            else if (is_builtin(&cmd)) {
                do_builtin(&cmd);
            }
            else if (find_fullpath(fullpath, &cmd)) {
                // NOTE: find_fullpath() is called again in execute
                execute(&cmd);
            }
            else {
                printf("invalid command\n");
            }
        }

        cleanup(&cmd);
    }

    return 0;
} // end main function

void sig_child_handler(int sig) {

    int status;
    wait (&status);

}
