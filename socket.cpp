#include "iostream"
#include "socket.h"

//using namespace std;
void err_cout(string str)
{
    cout<<str<<endl;
    abort();
    exit(1);
}

void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_cout("write error");
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
	ssize_t		n;

	if ( (n = readline(fd, ptr, maxlen)) < 0)
		err_cout("readline error");
	return(n);
}

int Socket(int family,int type,int protocol)
{
    int result=socket(AF_INET,SOCK_STREAM,0);
    if(result<0)
     {
         err_cout("socket err");
     }
    else
        return result;
}

void Bind(int sockfd, const struct sockaddr *myaddr,socklen_t addrlen)
{
    if(bind(sockfd,myaddr,addrlen)<0)
    {
        err_cout("bind err");
    }
}

void Listen(int fd,int backlog)
{
    if(listen(fd,backlog)<0)
        err_cout("listrn err");
}

int Accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen)
{
    int n;
    if( (n=accept(sockfd,cliaddr,addrlen))<0 )
        err_cout("accept err");
    else
        return n;
}

void Close(int sockfd)
{
    if(close(sockfd)<0)
        err_cout("close err");
    else
        return;
}

pid_t Fork(void)
{
	pid_t	pid;
	if ( (pid = fork()) == -1)
		err_cout("fork error");
	return(pid);
}

void Fputs(const char *ptr, FILE *stream)
{
	if (fputs(ptr, stream) == EOF)
		err_cout("fputs error");
}

ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = (char*)vptr;
	for (n = 1; n < maxlen; n++) {
again:
		if ( (rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} else if (rc == 0) {
			*ptr = 0;
			return(n - 1);	/* EOF, n - 1 bytes were read */
		} else {
			if (errno == EINTR)
				goto again;
			return(-1);		/* error, errno set by read() */
		}
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}
ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = (char*)vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
void
Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		err_cout("writen error");
}

