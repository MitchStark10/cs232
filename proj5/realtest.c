#include <tasktree.h>
#include <taskinfo.h>
#include <stdio.h>

int main(void) {
	struct task_struct * temp;
	int count;
	count = syscall(327, temp, 100, 2);
	printf("Count is: %d", count);
	return 0;
}
