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
	int cmpt;

	PROCTAB *tab_proc = openproc(PROC_FLAGS);
	
	if(!tab_proc)
	{
		perror("openproc");
	}
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

	printf("%s: \t%s  \t%s  \t%s\n", "COMMAND", "PPID", "TID", "RSS");

	for(int i = 0; m->info[i] != NULL && i< m->nb_process; i++)
	{
		printf("%s: \t%d  \t%d  \t%ld\n", m->info[i]->cmd, m->info[i]->ppid,m->info[i]->tid, m->info[i]->rss);


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
