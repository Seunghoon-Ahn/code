#include"types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	int n;
	n = get_max_pid();
	printf(1, "Maximum PID: %d\n", n);
	exit();
}
