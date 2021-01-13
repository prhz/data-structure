#include <stdio.h>

void BinaryInsertSort(int Array[], int n);
int main()
{
    int Array[10] = {2,3,5,1,4,11,6,1,4,7};
    BinaryInsertSort(Array, 10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",Array[i]);
    }

    return 0;
}

void BinaryInsertSort(int Array[], int n)
{
    int low, mid, high;
    for(int i = 1; i< n;i++)
    {
        int temp = Array[i];
        low = 0; high = i-1;
        while(low<=high){
            mid = (low+high)/2;
            if(temp<Array[mid])
            {
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        for(int j = i-1;j>=low;j--){
            Array[j+1] = Array[j];
        }
        Array[low] = temp;

    }
}


