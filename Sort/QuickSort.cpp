#include <stdio.h>

void QuickSort(int Array[], int low, int high);
int Portition(int Array[], int low, int high);
int main()
{
    int Array[10] = {2,3,5,1,4,11,6,1,4,7};
    QuickSort(Array, 0, 9);
    for(int i=0;i<10;i++)
    {
        printf("%d ",Array[i]);
    }

    return 0;
}

void QuickSort(int Array[], int low, int high)
{
    if(low < high)
    {
        int pivotpos = Portition(Array,low, high);
        QuickSort(Array, low, pivotpos-1);
        QuickSort(Array, pivotpos+1, high);
    }

}
//{2,3,5,1,4,11,6,1,4,7};
int Portition(int Array[], int low, int high)
{
    int pivot = Array[low];
    while(low<high)
    {
        while(low<high && Array[high]>=pivot)   high--;
        Array[low] = Array[high];
        while(low<high && Array[low]<=pivot)    low++;
        Array[high] = Array[low];
    }
    Array[low] = pivot;
    return low;


}
