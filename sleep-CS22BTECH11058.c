#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2, "Usage: sleep <ticks>\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);
     ticks = ticks * 10;

    if(ticks <= 0){
        fprintf(2, "Invalid number of ticks: %d\n", ticks);
        exit(1);
    }

    sleep(ticks);

    exit(0);
}