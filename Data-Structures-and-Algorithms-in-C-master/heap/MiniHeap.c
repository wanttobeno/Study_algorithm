// 寻找最大的K个数（最小堆实现）
// https://blog.csdn.net/scs343657368/article/details/7901314


#include <stdio.h>

#define COUNT 100
//static const int COUNT=100;

void MinHeapify(int origin[],int i,int heapsize);
void BuildMinHeap(int origin[],int heapsize);

void swap(int* i, int* j);

int main(int argc, char* argv[])
{
    int origin[COUNT];
    int k;
    printf("origin array:\n");
    for(int i=0;i<COUNT;i++)
    {
        origin[i]=rand()%(COUNT+1);
        printf("%d ",origin[i]);
    }
    printf("\n请输入你想找最大数的个数: \n");
    scanf("%d",&k);
    BuildMinHeap(origin,k);
    for(int i=k;i<COUNT;i++)
    {
        if(origin[i]>origin[0])
        {
            swap(&origin[0],&origin[i]);
            MinHeapify(origin,0,k);
        }
    }
    for(int j=0;j<COUNT;j++)
    {
        printf("%d ",origin[j]);
    }
    return 0;
}
void swap(int* i, int* j)
{
		int temp = i;
		i = j;
		i= temp;
}

void MinHeapify(int origin[],int i,int heapsize)//保持最小堆的性质
{
    int smallest;
    int l=2*i+1;
    int r=2*i+2;
    if(l<heapsize&&origin[i]>origin[l])
    {
        smallest=l;
    }
    else
    {
        smallest=i;
    }
    if(r<heapsize&&origin[r]<origin[smallest])
    {
        smallest=r;
    }
    if(smallest!=i)
    {
        swap(origin[i],origin[smallest]);
        MinHeapify(origin,smallest,heapsize);
    }
}
void BuildMinHeap(int origin[],int heapsize)//构建最小堆
{
    for(int i=heapsize/2-1;i>=0;i--)
    {
        MinHeapify(origin,i,heapsize);
    }
}
