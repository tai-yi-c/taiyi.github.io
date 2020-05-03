#include<cstdio>
#include<iostream>
#include<time.h>
using namespace std;
#define arraylength 10
#define lc(x) 2*x
#define rc(x) lc(x)+1
#define parent(x) x/2 //x����2һ���ܹ��õ����ڵ�
#define maxn 100000
void swap(int& a, int& b);

void bubble_sort(int* a, int length);
void mypractice_sort(int* a, int length);
void mypractice_sort2(int* a, int first, int last);
void insert_into(int* a, int first, int last);

void insertion_sort(int* a, int length);
void _insertion_sort(int* a, int first, int last);

void mergesort(int* a, int length);
void _mergesort(int* a, int first, int last);
void merge(int* a, int first, int mid, int last);

void combine_sort(int* a, int length, int k);
void _combine_sort(int* a, int first, int last, int k);

void quick_sort(int* a, int length);
void _quick_sort(int* a, int first, int last);

void random_quicksort(int* a, int length);
void _random_quicksort(int* a, int first, int last);
int partition(int* a, int first, int last);

void determinstic_quicksort(int* a, int length);
void _determinstic_quicksort(int* a, int first, int last);
void select_pivot(int* a, int first, int last);

void heap_sort(int* a, int length);
void heapify(int* a, int root,int last);

void out(int* a, int length);
int simulation(int* a, int length,int sig);
int main() {
	//int* a = new int[arraylength];
	//for (int i = 0; i < arraylength; i++) {
	//	a[i] = rand() % arraylength;
	//}
    //cout << "����ǰ" << "\n";
    //out(a, arraylength);
    
    //bubble_sort(a, arraylength);
    //mypractice_sort(a, arraylength);
    //mypractice_sort2(a, 0,arraylength-1);
    //insertion_sort(a, arraylength);
    //mergesort(a, arraylength);
    //combine_sort(a, arraylength, 10);
    //quick_sort(a, arraylength);
    //random_quicksort(a, arraylength);
    //determinstic_quicksort(a, arraylength);
    //heap_sort(a, arraylength);
    
    //cout << "�����" << "\n";
    //out(a, arraylength);
    int time[7] = {0};
    int nlength = arraylength;
    int cnt = 50;
    for (int i = 1; i <= 5; i++) {//10^i*arraylength
        nlength = nlength * 10;
        int* a = new int[nlength];
        for (int i = 0; i < nlength; i++) {
            a[i] = rand() % nlength;
        }
        for (int j = 1; j <= cnt; j++) {
            //simulation�Դ���������
            time[1] += simulation(a, nlength, 1);
            time[2] += simulation(a, nlength, 2);
            time[3] += simulation(a, nlength, 3);
            time[4] += simulation(a, nlength, 4);
            time[5] += simulation(a, nlength, 5);
            time[6] += simulation(a, nlength, 6);
        }
        cout << "���ݹ�ģΪ��" << nlength << "\n";
        cout << "mergesort              ƽ��ʱ��Ϊ  " << time[1] / (1000 * cnt * 1.0) << "\n";
        cout << "combine_sort           ƽ��ʱ��Ϊ  " << time[2] / (1000 * cnt * 1.0) << "\n";
        cout << "quick_sort             ƽ��ʱ��Ϊ  " << time[3] / (1000 * cnt * 1.0) << "\n";
        cout << "random_quicksort       ƽ��ʱ��Ϊ  " << time[4] / (1000 * cnt * 1.0) << "\n";
        cout << "determinstic_quicksort ƽ��ʱ��Ϊ  " << time[5] / (1000 * cnt * 1.0) << "\n";
        cout << "heap_sort              ƽ��ʱ��Ϊ  " << time[6] / (1000 * cnt * 1.0) << "\n";
    
    }



	return 0;
}
int* copy(int* a, int length) {
    int* b = new int[length];
    for (int i = 0; i < length; i++) {
        b[i] = a[i];
    }
    return b;
}
int simulation(int* a, int length,int sig) {
    clock_t startTime;
    clock_t endTime;
    if (sig == 1) {
        int* b = copy(a, length);
        startTime = clock();
        mergesort(b, length);
        endTime = clock();
        delete[] b;
    }
    else if (sig == 2) {
        int* b = copy(a, length);
        startTime = clock();
        combine_sort(b, length, 10);
        endTime = clock();
        delete[] b;
    }
    else if (sig == 3) {
        int* b = copy(a, length);
        startTime = clock();
        quick_sort(b, length);
        endTime = clock();
        delete[] b;
    }
    else if (sig == 4) {
        int* b = copy(a, length);
        startTime = clock();
        random_quicksort(b, length);
        endTime = clock();
        delete[] b;
    }
    else if (sig == 5) {
        int* b = copy(a, length);
        startTime = clock();
        determinstic_quicksort(b, length);
        endTime = clock();
        delete[] b;
    }
    else if (sig == 6) {
        int* b = copy(a, length);
        startTime = clock();
        heap_sort(b, length);
        endTime = clock();
        delete[] b;
    }
    return (endTime - startTime);
}
void out(int* a, int length) {
    for (int i = 0; i < length; i++) {
        cout << a[i] << "   ";
    }
    cout << "\n";
}
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void bubble_sort(int* a, int length) {
    while (true) {
        int sig = 1;//���������־
        for (int i = 0; i < length-1; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                sig = 0;
            }
        }
        /*if() break;
        ����ط�ֵ��һ�ᣬ��ѭ������ȥ�ķ�ʽ������:
        1.����ÿ�ζ���һ��Ԫ�ع�λ����ôСѭ��ִ��length-1�κ�һ������
        2.��ǰ������жϣ����ĳһ��û�з���swap()����ô�ôξ�һ���Ѿ������ˣ���������
        */
        if (sig == 1)break;
    }
}
void mypractice_sort(int* a, int length) {
    int k = length - 1;
    while (true) {
        int imax = 0;
        int sig = 1;
        for (int i = 0; i <= k; i++) {
            if (a[imax] < a[i]) {
                imax = i;
                sig++;
            }
        }
        swap(a[imax], a[k]); k--;
        /*if() break;
        ����ط�ֵ��һ�ᣬ��ѭ��Ҳ�а취��ǰ����ȥ:
        1.ÿ�ι�λ���Ԫ�أ���ôѭ��length-1�Σ�һ������ȫ����λ
        2.��ǰ������ĳ��ѭ����sig�ﵽ�ôε����鳤��k��˵���Ѿ�����
        �����ֲ���֮�£�ʵ����Ҳ�����ж��Ƿ����򣬵�sig++һ�ζ�ûִ�й�����˵��������
        */
        if (sig == k+2 || k == 0) break;
    }
}
void mypractice_sort2(int* a, int first, int last) {
    if (last == first + 1) {
        if (a[first] > a[last]) swap(a[first], a[last]);
    }
    mypractice_sort2(a, first, last - 1);
    insert_into(a, first, last);
}
void insert_into(int* a, int first, int last) {
    int key = a[last];
    for (int i = last - 1; i >= first; i--) {
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
        }
        else break;
    }
}
/*
��ʵ���ַ�����û���𵽷ֶ���֮�����ã��ݹ����̫�࣬ÿ�ζ������������ģ��С��һ��Ԫ�أ�����ֻ��һ�ֵݹ�д��
*/
void insertion_sort(int* a, int length) {
    _insertion_sort(a, 0, length - 1);
}
void _insertion_sort(int* a, int first, int last) {
    for (int i = first + 1; i <= last; i++) {
        int temp = a[i];
        //int p = i - 1;
        //    for (; p >= first; p--) {
        //        int temp = a[i];//����ط������ݴ�a[i]
        //        if (a[p] > temp) {//��������������д��ѭ���壬��Ϊ��������������֮�л�Խ�磬���Ǻ�ϰ��
        //            a[p + 1] = a[p];
        //        }
        //        else break;
        //    }
        //a[p + 1] = temp;
        //����һ��д����Ҳ�ܹ���Ԫ�ز嵽��ȷ��λ����ȥ
        //���ú���bubble_sort����ʵ˵��bubble_sortҲ�����
        //for(int p=i-1;p>=first;p--){
        //   if(a[p]>a[p+1]){
        //        swap(a[p],a[p+1]);
        //    }else break;
        //}
        //��ô����д�������滵�������أ���Ҫ����Ϊswap�ڲ���������������������

        
        
        //���б��д�������ҵ���һ�α�tempС��λ�ã�Ȼ������λ���ұߵ�Ԫ���������ƣ�
        //Ȼ���ٰ�Ԫ�ز����λ��
        int p = i - 1;
        for(;p>=first;p--){
            if(a[p]<=temp) break;
        }
        for(int k=i-1;k>=p+1;k--){
            a[k+1]=a[k];
        }
        a[p+1]=temp;
        //�Զ��׼����ǣ�����д����������д��������һģһ���ģ�Ȼ���ٿ�����forѭ����
        //���Է���ѭ�����ڲ���������һģһ���ģ�Ҳ����˵���������д�����Կ����Ǻϲ�
        //ͬ�������֤�����ڴ���֮�У����ֺϲ�ͬ�������Ĵ���Ҳ����ȷ�ġ�
        
    }
}
void mergesort(int* a, int length) {
    _mergesort(a, 0, length - 1);
}
/*
mergesort��������������������⣺
1.���ֻ��һ��Ԫ�أ���������
2.ѡȡ�е㣬Ȼ������߲��֣��ٽ���ұ߲��֣����ʱ���㷨��ûд�꣬���Ǿ��Ѿ��ٶ��㷨�ض�������ȷ���ؽ��
3.��Ϸ��ؽ��

��ȫ���Կ����ǣ���n=1ʱ����������n=kʱ������Ȼ��֤����n=k+1ʱ����������ѧ���ɷ���˼ά������
*/
void _mergesort(int* a, int first, int last) {
    if (first >= last) return;//��д�ݹ����һ����ϰ��
    int p = (first + last) / 2;
    _mergesort(a, first, p);
    _mergesort(a, p + 1, last);
    merge(a, first, p, last);
}
void merge(int* a, int first, int mid, int last) {
    //Ҫע��ԭ�����Ǵ�first��last����a1 a2���Ǵ�0��ʼ��Ȼ��n1-1,n2-1��������Ҫ���
    //��ȫ���Կ�1�����飬���Ƕ�˼ά�����ĸ��󣬿��ܸ����׳�bug
    int n1 = mid - first + 1;
    int n2 = last - mid;
    int* a1 = new int[n1];
    int* a2 = new int[n2];
    //Ϊ�˱�������[]�ڲ��ı��ʽ����Ȼ������ָ����ж�λ������û�б�Ҫ���������׳�bug
    for (int i = 0; i < n1; i++) {
        a1[i] = a[i + first];
    }
    for (int i = 0; i < n2; i++) {
        a2[i] = a[i + mid + 1];
    }
    //for (int k = first, i = 0, j = 0; k <= last; k++) {//kָʾ������ iָʾa1 jָʾa2
    //    if (i >= n1) a[k] = a2[j++];
    //    else if (j >= n2) a[k] = a1[i++];
    //    else if (a1[i] < a2[j]) a[k] = a1[i++];
    //    else if (a2[j] <= a1[i]) a[k] = a2[j++];
    //}
    //delete[] a1; delete[] a2;//��ɾ���з���
    //���a1��a2�ķ�������һ�����廪���ϳ���
    //��������߼�:
    //ѭ����������i����jָ��û��ȫ������ !(i>=n1 && j>=n2)�����õ�Ħ���ɴ����ţ�
    //�����Ҿ��������ȽϺ���⡣
    //����a1����������a1�Ƚ�С����jָ������ (j>=n2 || (a1[i]<=a2[j] && j<n2))
    //����a2����������a2�Ƚ�С����iָ������ (i>=n1 || (a2[j]<a1[i] && i<n1))
    int k=first;
    int i=0;
    int j=0;
    while(i<n1 || j<n2){
        if (j >= n2 || (a1[i] <= a2[j] && i < n1)) {
            a[k]=a1[i];k++;i++;
        }
        else if (i >= n1 || (a2[j] < a1[i] && j<n2)) {
            a[k]=a2[j];k++;j++;
        }
    }
    //����д�����߼����൱������������һ�����ʣ�����(j>=n2 || a1[i]<=a2[j])����д����
    //��j�Ѿ�Խ�������»᲻��ִ��a2[j]��һ����
    //��һ��д���������е��������д�����и��ӵ������Ҳ����׳�bug


    //ҪС��һ�㣬��һ�д�����������߼����������ǻ�������
    //���������Ĵ����ֵ�����һ����ִ�бȽϹ��ܣ��ڶ����ְ�ʣ�µ��������
    //��ô����:
    //int k=first;
    //int i=0;
    //int j=0;
    //int sig=0;
    //while(true){
    //    if(a1[i]<=a2[j]){
    //        a[k]=a1[i];k++;i++;
    //        if(i>=n1){
    //            sig=1;
    //            break;
    //        }
    //    }
    //    else if(a2[j]<a1[i]){
    //        a[k]=a2[j];k++;j++;
    //        if(j>=n2){
    //             sig=2;
    //             break;
    //        }
    //    }
    //}
    //if(sig==1){
    //    while(j<n2) a[k++]=a2[j++];
    //}else if(sig==2){
    //    while(i<n1) a[k++]=a1[i++];
    //}
    //����д�����ǰһ�֣��߼��������������Ǵ�������Ҳ�������ӣ��߼�ֱ�ӣ�������д������
    //��϶��ԣ�Ŀǰ��һ��д�����߼�������������дҲ�ٵĴ��룬����ȡ
    /*int k = first, i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (a1[i] <= a2[j]) a[k++] = a1[i++];
        else a[k++] = a2[j++];
    }
    while (i < n1) a[k++] = a1[i++];
    while (j < n2) a[k++] = a2[j++];*/
}
void combine_sort(int* a, int length, int k) {
    _combine_sort(a, 0, length - 1, k);
}
void _combine_sort(int* a, int first, int last, int k) {
    if (last - first + 1 <= k) {//��д�ݹ����һ�ֺ�ϰ��
        _insertion_sort(a, first, last);
        return;
    }
    else {
        int p = (first + last) / 2;
        _combine_sort(a, first, p, k);
        _combine_sort(a, p + 1, last, k);
        merge(a, first, p, last);
    }
}

void quick_sort(int* a, int length) {
    _quick_sort(a, 0, length - 1);
}
void _quick_sort(int* a, int first, int last) {
    if (first >= last) return;//��д�ݹ��
    int p = partition(a, first, last);//partitionĬ�Ͻ�����ĩβԪ�ع�λ
    _quick_sort(a, first, p - 1);
    _quick_sort(a, p + 1, last);
}
int partition(int* a, int first, int last) {
    int temp = a[last];
    int i = first, j = last - 1;//iָʾС������jָʾ���ڵ�����
    while (true) {
        while (a[i] < temp) {//ÿһ��ͣ�ڴ��ڵ���temp�ĵط�
            i++;
            if (i == last) break;
        }
        while (a[j] >= temp) {//ÿһ��ͣ��С��temp�ĵط�
            j--;
            if (j == first) break;
        }
        if (i >= j) break;//���жϣ�������󽻻�
        swap(a[i], a[j]);
    }
    /*
    ���յ�i�ض�ͣ�ڵ�һ�����ڵ���temp��λ�ã�jͣ���ڵ�һ��С��temp��λ�ã�
    ���Խ�������a[i]��a[last]�����ǽ�����a[i-1]��a[last],���һ��С��
    temp��Ԫ�ؽ��������ұ�ȥ
    */
    swap(a[i], a[last]);
    return i;//��������a[last]ֵ����Ӧ���ڵ�λ��
}
/*
partition�б��д����������˫ָ��ͬʱ���м��ƶ�����󽻻㣬��ʵ˫ָ�����
ͬ���ƶ������е�ָ���д��
*/
void random_quicksort(int* a, int length) {
    _random_quicksort(a, 0, length - 1);
}
void _random_quicksort(int* a, int first, int last) {
    if (first >= last) return;
    else {
        int r = rand() % (last - first + 1) + first;
        swap(a[r], a[last]);
        int p = partition(a, first, last);

        _random_quicksort(a, first, p - 1);
        _random_quicksort(a, p + 1, last);
    }
}
void determinstic_quicksort(int* a, int length) {
    _determinstic_quicksort(a, 0, length - 1);
}
void _determinstic_quicksort(int* a, int first, int last) {
    if (last - first + 1 <= 10) _insertion_sort(a, first, last);//�ݹ����С��10��Ԫ��ֱ�Ӳ�������
    else {
        select_pivot(a, first, last);//����ҵ���λ�����ҽ�����ĩβ�Ĺ���
        int p = partition(a, first, last);
        _determinstic_quicksort(a, first, p - 1);
        _determinstic_quicksort(a, p + 1, last);
    }
}
/*
select_pivot������nlogn������С��ʱ�����ҵ���λ��������۾��ǲ��ɳ��ܵ�
*/
void select_pivot(int* a, int first, int last) {
    int num = ceil((last - first + 1) / 5.0);//5��Ԫ��һ��
    int* b = new int[num];//�洢ÿ�������λ��
    int k = 0;
    /*
    ���forѭ����3.2n��ʱ�����
    */
    for (int i = first; i <= last; i += 5) {
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
    int* c = new int[num];
    for (int i = 0; i < num; i++) c[i] = b[i];
    int p = 0;
    //�������determinstic��ĸ��죬����ط���Ҫʹ����
    _determinstic_quicksort(b, 0, num - 1);
    for (int i = 0; i < num; i++) {
        if (c[i] == b[(num - 1) / 2]) {
            p = i;
            break;
        }
    }
    p = first + p * 5;//��λ����һ����ԭ����֮�е�ͷ��
    if (p + 4 <= last) swap(a[p + 2], a[last]);
    else swap(a[(p + last) / 2], a[last]);
}

void heapify(int* a, int root, int last) {
    for (int i = lc(root); i <= last; i = lc(i)) {
        if (a[i + 1] > a[i] && i < last) i += 1;
        if (a[i] > a[parent(i)]) swap(a[i], a[parent(i)]);
        else break;
    }
}
/*
��һ�����˵ĵݹ�д��:
//1.Ѱ���ӽڵ��е����ֵ,����ֻ��һ���ӽڵ�
//2.�븸�ڵ�Ƚ�
//3.�����ͻ����������µ��ã�С�ͷ���
//�ϲ�ͬ����:����ֱ�ӷ��غͼ����������ֿ���
*/
//void heapify(int* a, int root, int last) {
//    if (lc(root) > last) return;
//    else {
//        int p = lc(root);//p�ڵ�ָʾ��һ�εݹ��λ��
//        //����ط���Ӧ���ȼ���һ�����ֵ���Լ�С�Ƚϴ������������
//        if (a[p + 1] > a[p] && p + 1 <= last) p = p + 1;
//        if (a[p] > a[root]) swap(a[p], a[root]);
//        else return;
//        heapify(a, p, last);
//    }
//}
void heap_sort(int* a, int n) {
    int* b = new int[n + 1]; b[0] = maxn;//�ڱ��ڵ�
    for (int i = 0; i < n; i++) {
        b[i + 1] = a[i];//��Ϊa�������b��1��n
    }
    for (int i = parent(n); i >= 1; i--) {
        heapify(b, i, n);//���¶��ϵ����ˣ���floyd�㷨 nlognʱ���ڽ���
    }
    for (int i = n; i >= 1; i--) {//��n��1�����1��nҪ�����һ��
        swap(b[1], b[i]);//�Ȱ����ֵ������ĩβ
        a[i - 1] = b[i];//Ȼ���ĩβ��ֵ����a��ĩβ a��b��Ӧ���±���Զ��1
        heapify(b, 1, i);//ÿ���õ�һ��Ԫ�ض����Сһ����ģ
    }
    delete[] b;
}
