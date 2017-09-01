#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
//todo move this to a different file
typedef struct loglist {
	struct loglist * next;
	char * loginfo;
} loglist;
///temp, remove
typedef struct tempops {
	unsigned int total_logs;
} tempopts;
tempopts opts = {100};
loglist * logs = NULL;
unsigned int log_count=0;
void log_append(char *logstr) {
	if (log_count == opts.total_logs) {
		if (logs) {
			free(logs->loginfo);
			logs->loginfo = strdup("logs truncated");
		}
	} else if (log_count < opts.total_logs) {
		loglist *newlog = calloc(sizeof(loglist), 1);
		newlog->next = logs;
		newlog->loginfo = strdup(logstr);
		logs = newlog;
	}
	log_count++;
}
void log_print() {
	loglist *tmp = logs;
	while(tmp) {
		if (tmp->loginfo) { // this should always be true, but just to be safe
			puts(tmp->loginfo);
		}
		tmp = tmp->next; // yeah, fuck it a linked list was fast to implement
	}
}
void log_free() {
	loglist *tmp = logs;
	if (tmp) {
		logs = tmp->next;
		if (tmp->loginfo) {
			free(tmp->loginfo); // always strdup'd in
		}
		free(tmp);
		log_free(); // wheeeeeeee
	}
}
void log_run(char *command){
	if (command /*&& !fork()*/) {
		FILE *forkd = popen(command, "r");
		if (forkd) {
			char line[128] = {0}; // fuck you and your long lines
			if (fgets(line, 128, forkd)) {
				log_append(line); // dont worry, it is memcpyd
			}
			fclose(forkd);
		}
//		exit(0);
	}
}

