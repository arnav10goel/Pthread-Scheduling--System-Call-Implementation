#include<linux/kernel.h>
#include<linux/syscalls.h>

SYSCALL_DEFINE4(kernel_2d_memcpy, float *, target, float *, source, int, rows, int, cols)
{
	float stock[rows][cols];
	if(__copy_from_user(stock, source, sizeof(stock)))
	{
		printk("copy_from_user failed. Look at manual for more details.\n");
		return -2;
	}
	if(__copy_to_user(target, stock, sizeof(stock)))
	{
		printk("copy_to_user failed. Look at manual for more details. \n");
		return -3;
	}
	return 1;
}

