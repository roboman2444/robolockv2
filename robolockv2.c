#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>	//for write and close
#include <linux/oom.h>	//for oom nokill
#include <fcntl.h>	//for oomnokill


#include "auth.h"
#include "log.h"

#define TRUE 1
#define FALSE 0


int outofmemnokill(void){
	#define OOMVALLEN 64
	char value [OOMVALLEN];
	int file = open("/proc/self/oom_score_adj", O_WRONLY);
	if(file < 0 && errno == ENOENT){
		return FALSE;
	}
	int len = snprintf(value, OOMVALLEN, "%d\n", OOM_SCORE_ADJ_MIN);
	if(len > OOMVALLEN) return FALSE;
	if(file < 0|| write(file, value, len) != len || close(file) != 0) return FALSE;
	return TRUE;
}

int main(const int argc, const char **argv){
	outofmemnokill();

	log_run("date");
	log_print();
	log_free();
	//todo parse options
	//todo pam setup
	if(!auth_init()) return 1;

	//setup callbacks
	//call screen setup

	//call screen lock

	//unlock
	//call screne unlock
	//clean up
	return 0;
}
