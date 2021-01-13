#include <stdio.h>

void ShellSort(int Array[], int n);
int main()
{
    int Array[10] = {2,3,5,1,4,11,6,1,4,7};
    ShellSort(Array, 10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",Array[i]);
    }

    return 0;
}
//{2,3,5,1,4,11,6,1,4,7};
void ShellSort(int Array[], int n)
{
    int d; // 增量，初值为 n/2, 执行条件 d >= 1 ，每次 d 减半
    for(d = n/2; d >= 1; d = d/2)
    {
        for(int i = d; i < n; i ++) // 处理组
        {
            if(Array[i]<Array[i-d]){
                int temp = Array[i];
                int j;
                for(j = i-d; j>=0&&temp<Array[j]; j -=d){
                    Array[j+d] = Array[j];
                }
                Array[j+d] = temp;

            }// else 不动
        }

    }
}

