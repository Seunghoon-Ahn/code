#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	int n;
	n = get_num_proc();
	printf(1, "Total number of Active Processes: %d\n", n);
	exit();
}
