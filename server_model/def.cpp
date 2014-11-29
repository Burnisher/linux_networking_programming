#include "def.h"

ssize_t readn(int fd, void *buf, int n){
    size_t nleft = n; //还需要读取的字节数
    char *bufptr = (char *)buf; //指向read函数当前存放数据的位置
    ssize_t  nread;
 
    while(nleft > 0){
        if((nread = read(fd, bufptr, n)) < 0){
            if(errno == EINTR){ //遇到中断
                continue;
            }
            else            // 其他错误
                return -1;
        }
        else if(nread == 0){ // 遇到EOF
            break;
        }
 
        nleft -= nread;
        bufptr += nread;
    }
 
    return (n - nleft);
}
/*
 * 这里的 writen 必须写满 n 个字节
 * 少于 n 就属于错误
 * 返回 n  或者 -1
 */
 
ssize_t writen(int fd, void *buf, int n){
    size_t nleft = n;
    char *bufptr = (char *)buf;
    ssize_t nwrite;
 
    while(nleft > 0){
        if((nwrite = write(fd, bufptr, n)) <= 0){
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
 
        nleft -= nwrite;
        bufptr += nwrite;
    }
 
    return n; //  注意这里必须是 n 因为这里保证了 n 字节都被写入
}

ssize_t readline(int fd, void *usrbuf, size_t maxlen)
{
    char *bufptr = (char *)usrbuf;
    char c;
    size_t nleft = maxlen - 1; // 为\0 预留一个位置
    int nread = 0;
 
    while(nleft > 0){
        if((nread = ::read(fd, &c, 1)) <  0){
            if(errno == EINTR){
                continue;
            }
            else
                return -1;
        }
        else if(nread == 0){ //EOF
            break;
        }
        *bufptr++ = c;
        nleft --;
        if(c == '\n'){ //遇到 \n 就结束
            break;
        }
    }
 
    *bufptr = '\0';
    return (maxlen - 1 - nleft);
}