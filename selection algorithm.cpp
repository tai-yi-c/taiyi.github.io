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
    cout << "����ǰ" << "\n";
    int k = 10;
    out(a, arraylength);
    int tar = random_selection(a, 0,arraylength-1, k);
    out(b, arraylength);
    int tar2 = determinstic_selection(b, 0, arraylength - 1, k);
    //cout << "�����" << "\n";
    //out(a, arraylength);
    cout << "��"<<k<<"С�Ľ��\n";
    cout << "selection���" << tar << "\n";
    cout << "determinstic_selection���" << tar2 << "\n";

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
    if (first >= last) return a[first];//�ݹ��������ԭ����˵����ʵ������Ҳ�������
    else {
        int p = (rand() % (last - first + 1)) + first;//first��Ҫ©��
        swap(a[p], a[last]);
        int pivot_r = partition(a, first, last);
        if (k - 1 > pivot_r) {
            return random_selection(a, pivot_r + 1, last, k);//����������Ƶĺ���һ��д��ʱ������ط���Ҫ��С��д��
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
    int i = first, j = last - 1;//�����first�ұ���last�����Բ�ҪĬ���Ǵ�0��length
    while (true) {
        while (a[i] < pivot) {
            i++;
            if (i == last) break;//��Ҫ©д����Ϊ������������飬���п��ܻᵽĩβ�ģ�Ҫ��ֹԽ��
        }
        while (a[j] >= pivot) {
            j--;
            if (j == first) break;//��Ҫ©д����Ϊ���ڽ�������飬���п��ܻᵽĩβ�ģ�Ҫ��ֹԽ��
        }
        if (i >= j) break;//ע������������Ҳ����Ҫд�ڽ���ǰ������ᵼ�´���Ľ���
        swap(a[i], a[j]);
    }
    swap(a[i], a[last]);
    return i ;
}
void swap(int& a, int& b) {//����ע��Ҫʹ������
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
    int n_num = ceil((last - first + 1) / 5.0); //����5Ȼ������ȡ����ע����5.0
    int* b = new int [n_num];//b��װ�Ľ���С����λ��
    int k = 0;//kָʾb��Ԫ��;

    for (int i = first; i <= last; i += 5) {  //iָʾÿһ���ͷ��
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

    //selection_sort(b,0,n_num-1); ����������������ģ���һb�ܳ���ʱ��ܳ�

    int* c = new int[n_num];
    for (int i = 0; i < n_num; i++) c[i] = b[i];
    int element = determinstic_selection(b, 0, n_num - 1, (n_num - 1) / 2);
    int rank = 0;//ָʾ��λ����ԭʼ��b�е�λ�ã���˿��������λ����a�е�λ��
    for (int i = 0; i < n_num; i++) {
        if (c[i] == element) {
            rank = i;
            break;
        }  
    }
    if (first + rank * 5 + 4 > last) {
        rank = (first + rank * 5 + last) / 2; //������λ��������a�е�λ��
    }
    else {
        rank = (first + rank * 5 + 2);
    }
    swap(a[rank], a[last]);
}