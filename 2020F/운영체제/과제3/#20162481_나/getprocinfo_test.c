#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "processInfo.h"

int main(void) {
	int n = get_max_pid();
	int i, ret;
	struct processInfo *pi = malloc(sizeof(struct processInfo));
	printf(1, "PID     PPID    SIZE    Number of Context Switch\n");
	for(i = 1; i <= n; i++) {
		ret = get_proc_info(i, pi);
		if(ret == -1)
			continue;
		else
			printf(1, "%d       %d       %d   %d\n", i, pi->ppid, pi->psize, pi->numberContextSwitches); 
	}

	exit();
}
