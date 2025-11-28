#include<stdio.h>
#define ROW 2
#define COL 3

// 函数功能：计算矩阵相乘之积，结果存于二维数组c中
MultiplyMatrix(int a[ROW][COL], int b[COL][ROW], int c[ROW][ROW]① )
{
	int i, j, k;
	for( i=0; i<ROW; i++)
	{
		for( j=0; j<ROW; j++)
		{
			c[i][j]=  0②      ;
			for( k=0; k<COL; k++)
			{
				c[i][j]+= a[i][k] * b[k][j]      ③             ;
			}
		}
	}
}         
// 函数功能：输出矩阵a中的元素
void PrintMatrix(int a[ROW][ROW])
{
	int i, j;
	for( i=0; i<ROW; i++)
	{
		for( j=0; j<ROW; j++)
		{
			printf("%6d”, a[i][j]");
		}
		    printf("\n")④    ;
	}
}
int main(void)
{
	int a[ROW][COL], b[COL][ROW], c[ROW][ROW], i, j;
	printf(“Input 2*3 matrix a:\n”);
	for( i=0; i<ROW; i++)
	{
		for( j=0; j<COL; j++)
		{
			scanf(“%d”,     &a[i][j]⑤     );
		}
	}
	printf(“Input 3*2 matrix b:\n”);
	for( i=0; i<COL; i++)
	{
		for( j=0; j<ROW; j++)
		{
			scanf(“%d”,    &b[i][j]⑥    );
		}
	}
	MultiplyMatrix(     a,b,c⑦     );
	printf("Results:\n");
	PrintMatrix(c);
	return 0;
}