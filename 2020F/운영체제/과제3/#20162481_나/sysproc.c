#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

void
sys_hello(void)
{
	cprintf("helloxv6\n");
}

void
sys_helloname(void)
{	
	char *str;
	argstr(0, &str);
	//hello_name(str);
	cprintf("hello %s\n", str);
}

int
sys_get_num_proc(void)
{
	int n;
	n = proccnt();
	//cprintf("Total number of Active Processes: %d\n", n);
	return n;
}

int
sys_get_max_pid(void)
{
	int n;
	n = procmaxpid();
	//cprintf("Maximum PID: %d\n", n);
	return n;
}

int
sys_get_proc_info(void) {
	int n, ret;
	argint(0, &n);
	int pp;
	argint(1, &pp);
	
	ret = getprocinfo(n, pp);
	return ret;
}

int
sys_set_prio(void) {
	int n, ret;
	argint(0, &n);
	ret = setprio(n);
	return ret;
}

int
sys_get_prio(void) {
	int n;
	n = getprio();
	return n;
}
