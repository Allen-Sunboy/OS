#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char buf;
    
    if(fork() == 0)
    {
        close(p1[1]);
        read(p1[0], &buf, sizeof(buf));
        printf("%d: received ping\n", getpid());
        close(p2[0]);
        write(p2[1], &buf, sizeof(buf));
    }
    else
    {
        close(p1[0]);
        write(p1[1], &buf, sizeof(buf));
        close(p2[1]);
        read(p2[0], &buf, sizeof(buf));
        printf("%d: received pong\n", getpid());
    }
    exit(0);
    
}
