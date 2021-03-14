#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <sys/sysinfo.h>
#include <proc/readproc.h>
#include "capteur.h"


proc_info_t *capteur()
{
	int cmpt=0;

	PROCTAB *tab_proc = openproc(PROC_FLAGS);
	
	proc_t **info = readproctab(PROC_FLAGS);


	closeproc(tab_proc);

	proc_info_t *machine = malloc(sizeof(proc_info_t));

	machine->info = info;

	while(machine->info[cmpt]!=NULL)
	{
		cmpt++;
	}
	machine->nb_process = cmpt;

	return machine;
}

void affiche_mytop(proc_info_t *m)
{
	if(!m)
	{
		exit(1);
	}

	printf("Process:  %ld\n", m->nb_process);

	printf("%20s: \t%10s  \t\t%5s  \t%5s  \t%5s\n", "COMMAND", "USER","PPID", "TID", "RSS");

	for(int i = 0; m->info[i] != NULL && i< m->nb_process; i++)
	{
		printf("%20s: \t%10s  \t\t%5d  \t%5d  \t%5ld\n", m->info[i]->cmd,m->info[i]->ruser,m->info[i]->ppid,m->info[i]->tid, m->info[i]->rss);


	}
}

void free_proc(proc_info_t *m)
{
	for (int i = 0; m->info[i] != NULL && i < m->nb_process; i++)
    	{
      		freeproc(m->info[i]);
    	}


  free(m);

}