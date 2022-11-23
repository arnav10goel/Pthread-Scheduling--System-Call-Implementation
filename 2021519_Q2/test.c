#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define sys_kernel_2d_memcpy 451

int main()
{
	int row_count;
	int col_count;
	printf("Enter the no of rows you want in the matrix?: ");
	scanf("%i", &row_count);
	printf("Enter the no of columns you want in the matrix?: ");
	scanf("%i", &col_count);

	float source_matrix[row_count][col_count];
	float dest_matrix[row_count][col_count];

	for(int i = 0; i < row_count; i++){
		for(int j = 0; j < col_count; j++){
			printf("Enter the value for row %i and column %i: ", i, j);
			scanf("%f", &source_matrix[i][j]);
		}
	}
	
	printf("Here is the source matrix:\n");
	for(int i = 0; i < row_count; i++){
		for(int j = 0; j < col_count; j++){
			printf("%f ", source_matrix[i][j]);
		}
		printf("\n");
	}
	int status;
		
	status = syscall(sys_kernel_2d_memcpy, dest_matrix, source_matrix, row_count, col_count);
	if(status == 0)
	{
		printf("Copying successful: Successfully invoked system call kernel_2d_memcpy\n");
	}
	else{
		printf("Syscall failed\n");
	}
	
	printf("Here is the copied matrix:\n");
	for(int i = 0; i < row_count; i++){
		for(int j = 0; j < col_count; j++){
			printf("%f ", dest_matrix[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

