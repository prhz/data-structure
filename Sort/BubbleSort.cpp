#include <stdio.h>

void BubbleSort(int Array[], int n);
int main()
{
    int Array[10] = {2,3,5,1,4,11,6,1,4,7};
    BubbleSort(Array, 10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",Array[i]);
    }

    return 0;
}
//{2,3,5,1,4,11,6,1,4,7};

void BubbleSort(int Array[], int n)
{
    for(int i = 0; i<n-1;i++) /* 外循环为排序趟数，len个数进行len-1趟 */
    {
        int temp;
        bool flag = true;
        for(int j=0; j<n-i-1;j++) /* 内循环为每趟比较的次数，第i趟比较len-i次 */
        {
            if(Array[j+1]<Array[j])
            {
                temp = Array[j+1];
                Array[j+1] = Array[j];
                Array[j] = temp;
                flag = false;
            }

        }
        if(flag){
            return;
        }
    }
}
