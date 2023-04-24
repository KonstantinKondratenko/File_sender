#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <math.h>

int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    int i, pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("init SON_4: pid=%i ppid=%i",pid,ppid);

    printf ("\tполитика планирования:");
    switch (sched_getscheduler (0)) {
    case SCHED_FIFO:
        printf ("SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf ("SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf ("SCHED_OTHER\n");
        break;
    case -1:
        perror ("SCHED_GETSCHEDULER");
        break;
    default:
        printf ("Неизвестная политика планирования\n");
    }
    double sq = 0;
    for (int i = 0; i< 100; i++)
    {
        sq = sqrt(i+123);
        puts("\t\t\t\t4");
    }
    // if (sched_getparam (0, &shdprm) == 0)
    //     printf ("\tSON_4: приоритет процесса: %d\n", shdprm.sched_priority);
    // else
    //     perror ("SCHED_GETPARAM");

    return 0;
}