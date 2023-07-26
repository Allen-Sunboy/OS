#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int list[40];
    int i;
    for(i = 0; i <= 33; i++)
        list[i] = i + 2;
    int p[2];
    int buf;
    int num = 34;
    while(num > 0)
    {
        pipe(p);
        int head = list[0];
        printf("prime %d\n", head);
        if(fork() == 0)
        {
            close(p[0]);
            for(i = 0; i < num; i++)
                write(p[1], &list[i], sizeof(int));
            exit(0);
        }
        else
        {
            close(p[1]);
            num = 0;
            while(read(p[0], &buf, sizeof(buf)))
            {
                int tmp = buf;
                if(tmp % head)
                {
                    list[num] = tmp;
                    num++;
                }
            }
        }
        wait(0);
    }
    exit(0);

}
