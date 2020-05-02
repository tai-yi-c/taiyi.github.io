#include<cstdio>
#include<iostream>
#include<math.h>
using namespace std;
void out(int* a, int length);
int random_selection(int a[], int first, int last, int k);
int partition(int a[], int first, int last);
void swap(int& a, int& b);
int determinstic_selection(int a[], int first, int last, int k);
void select_pivot(int a[], int first, int last);
#define arraylength 10
int main() {
    int* a = new int[arraylength];
    int* b = new int[arraylength];
    for (int i = 0; i < arraylength; i++) {
        a[i] = rand() % arraylength;
        b[i] = a[i];
    }
    cout << "排序前" << "\n";
    int k = 10;
    out(a, arraylength);
    int tar = random_selection(a, 0,arraylength-1, k);
    out(b, arraylength);
    int tar2 = determinstic_selection(b, 0, arraylength - 1, k);
    //cout << "排序后" << "\n";
    //out(a, arraylength);
    cout << "第"<<k<<"小的结果\n";
    cout << "selection结果" << tar << "\n";
    cout << "determinstic_selection结果" << tar2 << "\n";

    return 0;
}
void out(int* a, int length) {

    for (int i = 0; i < length; i++) {
        cout << a[i] << "  ";
    }
    cout << "\n";
}
int random_selection(int a[], int first, int last, int k) {
    if (k > last + 1) return -1;
    if (first >= last) return a[first];//递归基，按照原理来说，其实不用它也不会出错
    else {
        int p = (rand() % (last - first + 1)) + first;//first不要漏加
        swap(a[p], a[last]);
        int pivot_r = partition(a, first, last);
        if (k - 1 > pivot_r) {
            return random_selection(a, pivot_r + 1, last, k);//多个功能相似的函数一起写的时候，这个地方不要不小心写错
        }
        else if (k - 1 == pivot_r) {
            return a[pivot_r];
        }
        else {
            return random_selection(a, first, pivot_r - 1, k);
        }
    }
    
}
int partition(int a[], int first, int last) {
    int pivot = a[last];
    int i = first, j = last - 1;//左边是first右边是last，绝对不要默认是从0到length
    while (true) {
        while (a[i] < pivot) {
            i++;
            if (i == last) break;//不要漏写，因为对于升序的数组，是有可能会到末尾的，要防止越界
        }
        while (a[j] >= pivot) {
            j--;
            if (j == first) break;//不要漏写，因为对于降序的数组，是有可能会到末尾的，要防止越界
        }
        if (i >= j) break;//注意跳出条件，也必须要写在交换前，否则会导致错误的交换
        swap(a[i], a[j]);
    }
    swap(a[i], a[last]);
    return i ;
}
void swap(int& a, int& b) {//交换注意要使用引用
    int t = a;
    a = b;
    b = t;
}
void _insertion_sort(int* a, int first, int last) {
    for (int i = first + 1; i <= last; i++) {
        int temp = a[i];
        int p = i - 1;
        for (; a[p] > temp && p >= first; p--) {
            a[p + 1] = a[p];
        }
        a[p + 1] = temp;
    }
}
int determinstic_selection(int a[], int first, int last, int k) {
    if (first >= last) return a[first];
    if (last - first + 1 < 10) {
        _insertion_sort(a, first, last);
        return a[k - 1];
    }
    select_pivot(a, first, last);
    int p = partition(a, first, last);
    if (k - 1 < p) return determinstic_selection(a, first, p - 1, k);
    else if (k - 1 == p) return a[p];
    else return determinstic_selection(a, p + 1, last, k);
}
void select_pivot(int* a,int first,int last) {
    int n_num = ceil((last - first + 1) / 5.0); //除以5然后向上取整，注意是5.0
    int* b = new int [n_num];//b中装的将是小组中位数
    int k = 0;//k指示b的元素;

    for (int i = first; i <= last; i += 5) {  //i指示每一组的头部
        int j = i + 4;
        if (j <= last) {
            _insertion_sort(a, i, j);
            b[k] = a[i + 2]; k++;
        }
        else {
            _insertion_sort(a, i, last);
            b[k] = a[(i + last) / 2]; k++;
        }
    }

    //selection_sort(b,0,n_num-1); 这种做法是有问题的，万一b很长，时间很长

    int* c = new int[n_num];
    for (int i = 0; i < n_num; i++) c[i] = b[i];
    int element = determinstic_selection(b, 0, n_num - 1, (n_num - 1) / 2);
    int rank = 0;//指示中位数在原始的b中的位置，借此可以求出中位数在a中的位置
    for (int i = 0; i < n_num; i++) {
        if (c[i] == element) {
            rank = i;
            break;
        }  
    }
    if (first + rank * 5 + 4 > last) {
        rank = (first + rank * 5 + last) / 2; //这是中位数在数组a中的位置
    }
    else {
        rank = (first + rank * 5 + 2);
    }
    swap(a[rank], a[last]);
}