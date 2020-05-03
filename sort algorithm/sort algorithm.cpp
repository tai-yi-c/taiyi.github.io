#include<cstdio>
#include<iostream>
#include<time.h>
using namespace std;
#define arraylength 10
#define lc(x) 2*x
#define rc(x) lc(x)+1
#define parent(x) x/2 //x除以2一定能够得到父节点
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
    //cout << "排序前" << "\n";
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
    
    //cout << "排序后" << "\n";
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
            //simulation自带复制数组
            time[1] += simulation(a, nlength, 1);
            time[2] += simulation(a, nlength, 2);
            time[3] += simulation(a, nlength, 3);
            time[4] += simulation(a, nlength, 4);
            time[5] += simulation(a, nlength, 5);
            time[6] += simulation(a, nlength, 6);
        }
        cout << "数据规模为：" << nlength << "\n";
        cout << "mergesort              平均时间为  " << time[1] / (1000 * cnt * 1.0) << "\n";
        cout << "combine_sort           平均时间为  " << time[2] / (1000 * cnt * 1.0) << "\n";
        cout << "quick_sort             平均时间为  " << time[3] / (1000 * cnt * 1.0) << "\n";
        cout << "random_quicksort       平均时间为  " << time[4] / (1000 * cnt * 1.0) << "\n";
        cout << "determinstic_quicksort 平均时间为  " << time[5] / (1000 * cnt * 1.0) << "\n";
        cout << "heap_sort              平均时间为  " << time[6] / (1000 * cnt * 1.0) << "\n";
    
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
        int sig = 1;//这是有序标志
        for (int i = 0; i < length-1; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                sig = 0;
            }
        }
        /*if() break;
        这个地方值得一提，大循环跳出去的方式有两种:
        1.由于每次都有一个元素归位，那么小循环执行length-1次后一定有序
        2.提前有序的判断，如果某一次没有发生swap()，那么该次就一定已经有序了，可以跳出
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
        这个地方值得一提，大循环也有办法提前跳出去:
        1.每次归位最大元素，那么循环length-1次，一定可以全部归位
        2.提前跳出，某次循环，sig达到该次的数组长度k，说明已经有序
        在这种策略之下，实际上也可以判断是否逆序，当sig++一次都没执行过，就说明逆序了
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
其实这种方法并没有起到分而治之的作用，递归次数太多，每次都仅仅把问题规模减小了一个元素，所以只是一种递归写法
*/
void insertion_sort(int* a, int length) {
    _insertion_sort(a, 0, length - 1);
}
void _insertion_sort(int* a, int first, int last) {
    for (int i = first + 1; i <= last; i++) {
        int temp = a[i];
        //int p = i - 1;
        //    for (; p >= first; p--) {
        //        int temp = a[i];//这个地方必须暂存a[i]
        //        if (a[p] > temp) {//不建议把这个条件写到循环体，因为可能在其他情形之中会越界，不是好习惯
        //            a[p + 1] = a[p];
        //        }
        //        else break;
        //    }
        //a[p + 1] = temp;
        //这是一种写法，也能够把元素插到正确的位置上去
        //长得很像bubble_sort，其实说是bubble_sort也差不多了
        //for(int p=i-1;p>=first;p--){
        //   if(a[p]>a[p+1]){
        //        swap(a[p],a[p+1]);
        //    }else break;
        //}
        //那么这种写法比上面坏在哪里呢，主要是因为swap内部有三个操作，开销更大

        
        
        //还有别的写法，先找到第一次比temp小的位置，然后把这个位置右边的元素依次右移，
        //然后再把元素插入该位置
        int p = i - 1;
        for(;p>=first;p--){
            if(a[p]<=temp) break;
        }
        for(int k=i-1;k>=p+1;k--){
            a[k+1]=a[k];
        }
        a[p+1]=temp;
        //显而易见的是，这种写法，与最后的写法意义是一模一样的，然后再看两个for循环，
        //可以发现循环体内部的条件是一模一样的，也就是说，最上面的写法可以看做是合并
        //同类项。容易证明，在代码之中，这种合并同类项最后的代码也是正确的。
        
    }
}
void mergesort(int* a, int length) {
    _mergesort(a, 0, length - 1);
}
/*
mergesort的语句很容易在语义上理解：
1.如果只有一个元素，立即返回
2.选取中点，然后解决左边部分，再解决右边部分（这个时候算法都没写完，但是就已经假定算法必定可以正确返回结果
3.组合返回结果

完全可以看做是：当n=1时成立，假设n=k时成立，然后保证下面n=k+1时成立，和数学归纳法的思维很相似
*/
void _mergesort(int* a, int first, int last) {
    if (first >= last) return;//先写递归基是一个好习惯
    int p = (first + last) / 2;
    _mergesort(a, first, p);
    _mergesort(a, p + 1, last);
    merge(a, first, p, last);
}
void merge(int* a, int first, int mid, int last) {
    //要注意原数组是从first到last，而a1 a2都是从0开始，然后到n1-1,n2-1结束，不要搞混
    //完全可以开1个数组，但是对思维的消耗更大，可能更容易出bug
    int n1 = mid - first + 1;
    int n2 = last - mid;
    int* a1 = new int[n1];
    int* a2 = new int[n2];
    //为了避免数组[]内部的表达式，当然可以用指针进行定位，但是没有必要，还更容易出bug
    for (int i = 0; i < n1; i++) {
        a1[i] = a[i + first];
    }
    for (int i = 0; i < n2; i++) {
        a2[i] = a[i + mid + 1];
    }
    //for (int k = first, i = 0, j = 0; k <= last; k++) {//k指示大数组 i指示a1 j指示a2
    //    if (i >= n1) a[k] = a2[j++];
    //    else if (j >= n2) a[k] = a1[i++];
    //    else if (a1[i] < a2[j]) a[k] = a1[i++];
    //    else if (a2[j] <= a1[i]) a[k] = a2[j++];
    //}
    //delete[] a1; delete[] a2;//不删除有风险
    //组合a1与a2的方法还有一种在清华书上出现
    //先理清楚逻辑:
    //循环条件——i或者j指针没有全部走完 !(i>=n1 && j>=n2)可以用德摩根律打开括号，
    //但是我觉得这样比较好理解。
    //放置a1的条件——a1比较小或者j指针走完 (j>=n2 || (a1[i]<=a2[j] && j<n2))
    //放置a2的条件——a2比较小或者i指针走完 (i>=n1 || (a2[j]<a1[i] && i<n1))
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
    //这种写法在逻辑上相当繁琐，不过有一个疑问，对于(j>=n2 || a1[i]<=a2[j])这种写法，
    //在j已经越界的情况下会不会执行a2[j]这一步？
    //第一种写法，把所有的情况拆开来写，所有更加的清晰且不容易出bug


    //要小心一点，想一行代码解决过多的逻辑问题往往是会出问题的
    //如果把上面的代码拆分掉，第一部分执行比较功能，第二部分把剩下的数组填充
    //那么就有:
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
    //这种写法相比前一种，逻辑更加清晰，但是代码行数也显著增加，逻辑直接，但是书写繁琐。
    //相较而言，目前第一种写法是逻辑清晰，兼有书写也少的代码，更可取
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
    if (last - first + 1 <= k) {//先写递归基是一种好习惯
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
    if (first >= last) return;//先写递归基
    int p = partition(a, first, last);//partition默认将数组末尾元素归位
    _quick_sort(a, first, p - 1);
    _quick_sort(a, p + 1, last);
}
int partition(int* a, int first, int last) {
    int temp = a[last];
    int i = first, j = last - 1;//i指示小于区，j指示大于等于区
    while (true) {
        while (a[i] < temp) {//每一次停在大于等于temp的地方
            i++;
            if (i == last) break;
        }
        while (a[j] >= temp) {//每一次停在小于temp的地方
            j--;
            if (j == first) break;
        }
        if (i >= j) break;//先判断，以免错误交换
        swap(a[i], a[j]);
    }
    /*
    最终的i必定停在第一个大于等于temp的位置，j停留在第一个小于temp的位置，
    所以交换的是a[i]与a[last]，若是交换了a[i-1]与a[last],会把一个小于
    temp的元素交换到最右边去
    */
    swap(a[i], a[last]);
    return i;//返回最终a[last]值最终应该在的位置
}
/*
partition有别的写法，上面是双指针同时往中间移动，最后交汇，其实双指针可以
同向移动，还有单指针的写法
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
    if (last - first + 1 <= 10) _insertion_sort(a, first, last);//递归基，小于10个元素直接插入排序
    else {
        select_pivot(a, first, last);//完成找到中位数并且交换到末尾的功能
        int p = partition(a, first, last);
        _determinstic_quicksort(a, first, p - 1);
        _determinstic_quicksort(a, p + 1, last);
    }
}
/*
select_pivot必须在nlogn甚至更小的时间内找到中位数否则代价就是不可承受的
*/
void select_pivot(int* a, int first, int last) {
    int num = ceil((last - first + 1) / 5.0);//5个元素一组
    int* b = new int[num];//存储每个组的中位数
    int k = 0;
    /*
    这个for循环在3.2n的时间完成
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
    //如果相信determinstic真的更快，这个地方就要使用它
    _determinstic_quicksort(b, 0, num - 1);
    for (int i = 0; i < num; i++) {
        if (c[i] == b[(num - 1) / 2]) {
            p = i;
            break;
        }
    }
    p = first + p * 5;//定位到这一组在原数组之中的头部
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
试一下下滤的递归写法:
//1.寻找子节点中的最大值,可能只有一个子节点
//2.与父节点比较
//3.如果大就互换继续往下调用，小就返回
//合并同类项:分作直接返回和继续调用两种可能
*/
//void heapify(int* a, int root, int last) {
//    if (lc(root) > last) return;
//    else {
//        int p = lc(root);//p节点指示下一次递归的位置
//        //这个地方就应该先假设一个最大值，以减小比较次数，精简代码
//        if (a[p + 1] > a[p] && p + 1 <= last) p = p + 1;
//        if (a[p] > a[root]) swap(a[p], a[root]);
//        else return;
//        heapify(a, p, last);
//    }
//}
void heap_sort(int* a, int n) {
    int* b = new int[n + 1]; b[0] = maxn;//哨兵节点
    for (int i = 0; i < n; i++) {
        b[i + 1] = a[i];//因为a对齐的是b从1到n
    }
    for (int i = parent(n); i >= 1; i--) {
        heapify(b, i, n);//自下而上的下滤，是floyd算法 nlogn时间内建堆
    }
    for (int i = n; i >= 1; i--) {//从n到1比起从1到n要好理解一点
        swap(b[1], b[i]);//先把最大值交换到末尾
        a[i - 1] = b[i];//然后把末尾的值赋给a的末尾 a与b对应的下标永远少1
        heapify(b, 1, i);//每次拿掉一个元素都会减小一个规模
    }
    delete[] b;
}
