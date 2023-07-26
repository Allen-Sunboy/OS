#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    int i;
    char *args[MAXARG];
    char buf[MAXARG * 32];
    char block[MAXARG * 32];
    int num;
    for(i = 1, num = 0; i < argc; i++, num++)
        args[num] = argv[i];
    
    char *p = buf;

    int len;
    int pose = 0;
    while((len = read(0, block, sizeof(block))) > 0)
    {
        for(i = 0; i < len; i++)
        {
            if(block[i] == '\n')
            {
                buf[pose] = '\0';
                args[num] = p;
                num++;
                args[num] = 0;
                pose = 0;
                p = buf;
                num = argc - 1;
                if(fork() == 0)
                    exec(argv[1], args);
                wait(0);
            }
            else
            {
                buf[pose] = block[i];
                pose++;
            }
        }
    }
    exit(0);

}