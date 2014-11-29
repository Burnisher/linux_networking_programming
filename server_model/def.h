#ifndef DEF_H_
#define DEF_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
 
/*
 * readn ºÍ wirten º¯Êý
 */
 
ssize_t readn(int fd, void *buf, int n);
ssize_t writen(int fd, void *buf, int n);
ssize_t readline(int fd, void *usrbuf, size_t maxlen);

#endif //DEF_H_