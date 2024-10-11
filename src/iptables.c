#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 10

int accept_port(const int port, char *proto) {
    if (port <= 0 || port >= 65536)
        return -2;
    pid_t pid = fork();

    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        char str_port[BUFF_SIZE];
        sprintf(str_port, "%d", port);
        char *args[] = {"iptables", "-A", "INPUT", "-p", proto, "--dport", str_port, "-j", "ACCEPT", NULL};
        execvp(args[0], args);
        return 1;
    } 

    return 0;
}

int drop_port(const int port, char *proto) {
    if (port <= 0 || port >= 65536)
        return -2;
    pid_t pid = fork();

    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        char str_port[BUFF_SIZE];
        sprintf(str_port, "%d", port);
        char *args[] = {"iptables", "-A", "INPUT", "-p", proto, "--dport", str_port, "-j", "DROP", NULL};
        execvp(args[0], args);
        return 1;
    } 

    return 0;
}

int main() {
    drop_port(22, "tcp");
}