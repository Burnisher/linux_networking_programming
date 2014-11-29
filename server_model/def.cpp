#include "def.h"

ssize_t readn(int fd, void *buf, int n){
    size_t nleft = n; //����Ҫ��ȡ���ֽ���
    char *bufptr = (char *)buf; //ָ��read������ǰ������ݵ�λ��
    ssize_t  nread;
 
    while(nleft > 0){
        if((nread = read(fd, bufptr, n)) < 0){
            if(errno == EINTR){ //�����ж�
                continue;
            }
            else            // ��������
                return -1;
        }
        else if(nread == 0){ // ����EOF
            break;
        }
 
        nleft -= nread;
        bufptr += nread;
    }
 
    return (n - nleft);
}
/*
 * ����� writen ����д�� n ���ֽ�
 * ���� n �����ڴ���
 * ���� n  ���� -1
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
 
    return n; //  ע����������� n ��Ϊ���ﱣ֤�� n �ֽڶ���д��
}

ssize_t readline(int fd, void *usrbuf, size_t maxlen)
{
    char *bufptr = (char *)usrbuf;
    char c;
    size_t nleft = maxlen - 1; // Ϊ\0 Ԥ��һ��λ��
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
        if(c == '\n'){ //���� \n �ͽ���
            break;
        }
    }
 
    *bufptr = '\0';
    return (maxlen - 1 - nleft);
}