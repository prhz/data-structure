#include <stdio.h>

void InsertSort(int Array[], int n);
int main()
{
    int Array[10] = {2,3,5,1,4,11,6,1,4,7};
    InsertSort(Array, 10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",Array[i]);
    }

    return 0;
}

// {2,3,5,1,4,11,6,1,4,7} 增序
void InsertSort(int Array[], int n)
{
    for(int i = 1; i < n; i++)
    {
        if(Array[i] < Array[i-1]){
            int temp = Array[i];
            int j;
            for(j = i-1; Array[j]>temp&&j >= 0; j--){
             // 向后移动元素
                Array[j+1] = Array[j];
            }
            Array[j+1] = temp;
        }
        // else Array[i] >= Array[i-1] 不动，进行下一个元素排序
    }

}


