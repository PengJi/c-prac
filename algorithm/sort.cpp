#include <iostream>
#include <stdio.h>

using namespace std;

void print(int a[], int n ,int i){
    //cout << "第" <<i <<"趟:";
    for(int j= 0; j < n; j++){
        cout<<a[j] <<" ";
    }
    cout<<endl;
}

void print(int a[], int n){  
    for(int j= 0; j<n; j++){  
        cout<<a[j] <<"  ";  
    }  
    cout<<endl;  
}

/*
 * 直接插入排序
 */
void InsertSort(int a[], int n)
{
    for(int i= 1; i<n; i++){
        if(a[i] < a[i-1]){               //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j= i-1;
            int x = a[i];        //复制为哨兵，即存储待排序元素
            a[i] = a[i-1];           //先后移一个元素
            while(x < a[j]){  //查找在有序表的插入位置
                a[j+1] = a[j];
                j--;         //元素后移
            }
            a[j+1] = x;      //插入到正确位置
        }
        //打印每趟排序的结果
        print(a,n,i);
    }

}

/* 
 * 希尔排序
 * dk为增量
 */
void ShellInsertSort(int a[], int n, int dk)
{
    for(int i= dk; i<n; ++i){
        if(a[i] < a[i-dk]){          //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j = i-dk;
            int x = a[i];           //复制为哨兵，即存储待排序元素
            a[i] = a[i-dk];         //首先后移一个元素
            while(x < a[j]){     //查找在有序表的插入位置
                a[j+dk] = a[j];
                j -= dk;             //元素后移
            }
            a[j+dk] = x;            //插入到正确位置
        }
        print(a, n,i );
    }

}
/*
 * 先按增量d（n/2,n为要排序数的个数进行希尔排序
 *
 */
void shellSort(int a[], int n){

    int dk = n/2;
    while( dk >= 1 ){
        ShellInsertSort(a, n, dk);
        dk = dk/2;
    }
}

/* 
 * 选择排序
 */
int SelectMinKey(int a[], int n, int i)
{
    int k = i;
    for(int j=i+1 ;j< n; ++j) {
        if(a[k] > a[j]) k = j;
    }
    return k;
}
//排序
void selectSort(int a[], int n){
    int key, tmp;
    for(int i = 0; i< n; ++i) {
        key = SelectMinKey(a, n,i);  //选择最小的元素
        if(key != i){
            tmp = a[i];  a[i] = a[key]; a[key] = tmp; //最小元素与第i位置元素互换
        }
        print(a,  n , i);
    }
}

/*
 * 二元选择排序
 */
 void SelectSort(int r[],int n) {
    int i ,j , min ,max, tmp;
    for (i=1 ;i <= n/2;i++) {
        // 做不超过n/2趟选择排序
        min = i; max = i ; //分别记录最大和最小关键字记录位置
        for (j= i+1; j<= n-i; j++) {
            if (r[j] > r[max]) {
                max = j ; continue ;
            }
            if (r[j]< r[min]) {
                min = j ;
            }
      }
      //该交换操作还可分情况讨论以提高效率
      tmp = r[i-1]; r[i-1] = r[min]; r[min] = tmp;
      tmp = r[n-i]; r[n-i] = r[max]; r[max] = tmp;

    }
}

/** 
 * 堆排序
 * 已知H[s…m]除了H[s] 外均满足堆的定义 
 * 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,  
 * 
 * @param H是待调整的堆数组 
 * @param s是待调整的数组元素的位置 
 * @param length是数组的长度 
 * 
 */  
//调整为大顶堆
void HeapAdjust(int H[],int s, int length)  
{  
    int tmp  = H[s];  
    int child = 2*s+1; //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)  
    while (child < length) {  
        if(child+1 <length && H[child]<H[child+1]) { // 如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)  
            ++child ;  
        }  
        if(H[s]<H[child]) {  // 如果较大的子结点大于父结点  
            H[s] = H[child]; // 那么把较大的子结点往上移动，替换它的父结点  
            s = child;       // 重新设置s ,即待调整的下一个结点的位置  
            child = 2*s+1;  
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出  
             break;  
        }  
        H[s] = tmp;         // 当前待调整的结点放到比其大的孩子结点位置上  
    }  
    print(H,length);  
} 
/** 
 * 初始堆进行调整 
 * 将H[0..length-1]建成堆 
 * 调整完之后第一个元素是序列的最小的元素 
 */  
void BuildingHeap(int H[], int length)  
{   
    //最后一个有孩子的节点的位置 i=  (length -1) / 2  
    for (int i = (length -1) / 2 ; i >= 0; --i)  
        HeapAdjust(H,i,length);  
}  
/** 
 * 堆排序算法 
 */  
void HeapSort(int H[],int length)  
{  
    //初始堆  
    BuildingHeap(H, length);  
    //从最后一个元素开始对序列进行调整  
    for (int i = length - 1; i > 0; --i)  
    {  
        //交换堆顶元素H[0]和堆中最后一个元素  
        int temp = H[i]; 
        H[i] = H[0]; 
        H[0] = temp;  
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整  
        HeapAdjust(H,0,i);  
  }  
}

/*
int main(){  
    int H[10] = {3,1,5,7,2,4,9,6,10,8};  
    cout<<"初始值：";  
    print(H,10);  
    HeapSort(H,10);  
    //selectSort(a, 8);  
    cout<<"结果：";  
    print(H,10);  
  
}
 */

/*
 * 冒泡排序
 */
void bubbleSort(int a[], int n){
    for(int i =0 ; i< n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(a[j] > a[j+1])
            {
                int tmp = a[j] ; a[j] = a[j+1] ;  a[j+1] = tmp;
            }
        }
    }
}

/*
 * 冒泡排序的改进
 */
void Bubble_1 (int r[], int n) {
    int i= n -1;  //初始时,最后位置保持不变
    while ( i> 0) {
        int pos= 0; //每趟开始时,无记录交换
        for (int j= 0; j< i; j++)
            if (r[j]> r[j+1]) {
                pos= j; //记录交换的位置
                int tmp = r[j]; r[j]=r[j+1];r[j+1]=tmp;
            }
        i= pos; //为下一趟排序作准备
     }
}

/*
 * 快速排序
 */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int partition(int a[], int low, int high)
{
    int privotKey = a[low];                             //基准元素
    while(low < high){                                   //从表的两端交替地向中间扫描
        while(low < high  && a[high] >= privotKey) 
            --high;  //从high 所指位置向前搜索，至多到low+1 位置。将比基准元素小的交换到低端
        swap(&a[low], &a[high]);
        while(low < high  && a[low] <= privotKey ) 
            ++low;
        swap(&a[low], &a[high]);
    }
    //print(a,10);
    return low;
}
void quickSort(int a[], int low, int high){
    if(low < high){
        int privotLoc = partition(a,  low,  high);  //将表一分为二
        quickSort(a,  low,  privotLoc -1);          //递归对低子表递归排序
        quickSort(a,   privotLoc + 1, high);        //递归对高子表递归排序
    }
}

/*
 * 归并排序
 * 1 个元素的表总是有序的。所以对n 个元素的待排序列，
 * 每个元素可看成1 个有序子表。对子表两两合并生成n/2个子表，
 * 所得子表除最后一个子表长度可能为1 外，其余子表长度均为2。
 * 再进行两两合并，直到生成n 个元素按关键码有序的表。
 */
// 将r[i…m]和r[m +1 …n]归并到辅助数组rf[i…n]  
void Merge(int *r,int *rf, int i, int m, int n)
{  
    int j,k;  
    for(j=m+1,k=i; i<=m && j <=n ; ++k){  
        if(r[j] < r[i]) 
            rf[k] = r[j++];  
        else 
            rf[k] = r[i++];  
    }   
    while(i <= m)  rf[k++] = r[i++];  
    while(j <= n)  rf[k++] = r[j++];  
    print(rf,n+1);
}
void MergeSort(int *r, int *rf, int length)  
{   
    int len = 1;  
    int *q = r ;   
    int *tmp ;   
    while(len < length) {   
        int s = len;  
        len = 2 * s ;   
        int i = 0;  
        while(i+ len <length){  
            Merge(q, rf,  i, i+ s-1, i+ len-1 ); //对等长的两个子表合并  
            i = i+ len;  
        }   
        if(i + s < length){  
            Merge(q, rf,  i, i+ s -1, length -1); //对不等长的两个子表合并  
        }   
        //交换q,rf，以保证下一趟归并时，仍从q 归并到rf  
        tmp = q; 
        q = rf; 
        rf = tmp; 
    }   
}
//两路归并的递归算法
void MSort(int *r, int *rf,int s, int t)  
{   
    int *rf2;  
    if(s==t)
        r[s] = rf[s];  
    else  
    {   
        int m=(s+t)/2;          /*平分*p 表*/  
        MSort(r, rf2, s, m);        /*递归地将p[s…m]归并为有序的p2[s…m]*/  
        MSort(r, rf2, m+1, t);      /*递归地将p[m+1…t]归并为有序的p2[m+1…t]*/  
        Merge(rf2, rf, s, m+1,t);   /*将p2[s…m]和p2[m+1…t]归并到p1[s…t]*/  
    }  
}  
void MergeSort_recursive(int *r, int *rf, int n)  
{   /*对顺序表*p 作归并排序*/  
    MSort(r, rf,0, n-1);  
}

int main(){
	int a[8] = {3,1,4,56,76,7,8,9};

	InsertSort(a,8);
	print(a,8,8);

	shellSort(a,8);
	print(a,8,8);

	selectSort(a, 8);
	print(a,8,8);

	int b[10] = {3,1,5,7,2,4,9,6,10,8};
    quickSort(b,0,9);

    int c[10];
    MergeSort(b,c,10);
    print(b,10);

	return 0;
}

