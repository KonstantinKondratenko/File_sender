#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
int main ()
{
    struct sched_param shdprm;
    int pid,ppid, status;
    int n = 60; // переменные для задания значений приоритетов,
    int prior = 10; //для повторного эксперимента с политикой FIFO
    char *arr[18] = {"son1", "son2", "son3", "son4", "son5", "son6", "son7", "son8", "son9", "son10", "son11", "son12", "son13", "son14", "son15", "son16", "son17", "son18"};
    int pid_son[18];
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid,ppid);
    shdprm.sched_priority = 10;
    if (sched_setscheduler (0, SCHED_FIFO, &shdprm) == -1)
    {
        perror ("SCHED_FIFO");
    }
    int counter = 1;
    while (counter > 0)
    {
        for (int i=17; i >= 0; i--)
        {
            if((pid_son[i]=fork()) == 0)
            {
                //shdprm.sched_priority = 20 - i;// приоритет по возратснию - новый процесс приоритетнее старого 
                //shdprm.sched_priority = 2 + i;// приоритет по убыванию - старый процесс приоритетнее нового 
                shdprm.sched_priority = 10;
                if (sched_setscheduler (pid_son[i], SCHED_FIFO, &shdprm) == -1)
                    perror ("SCHED_FIFO");
                execl(arr[i], arr[i], NULL);
            }
        }
        // for (int i=0; i <= 17; i++)
        // {
        //     printf("\t\t%d)pid = %d завершен\n",18-i, wait(&status));
        // }
        //sleep (1);
        //printf("\t************************************************************\n");
        counter --;
    }
    
    return 0;
}