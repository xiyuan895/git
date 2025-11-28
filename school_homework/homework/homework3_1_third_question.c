void Transpose(int a[][N], int n);

void Swap(int *x, int *y)
{
int temp;
temp = *x;
*x = *y;
*y = temp;
}
void Transpose(int a[][N],int n)
{
    for(int i = 0;i < n;i++)//遍历行
    {
        for(int j = i + 1;j < n;j++)//遍历列
        {
            Swap(&a[i][j],&a[j][i]);//交换对角元素
        }
    }
}