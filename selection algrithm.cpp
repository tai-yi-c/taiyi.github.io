#include<cstdio>
#include<iostream>
#include<vector>
#include<time.h>
#include<math.h>
using namespace std;

#define arraylength 10
void out(int* a, int length);
void swap(int* a, int i, int j);
int selection(int* a, int length, int kth);
int _determinstic_selection(int* a, int first, int last, int rth);
int determinstic_selection(int* a, int length, int kth);
int simulation(int* a, int length, int kth, int sig);
int main() {
	//算法正确性验证
	//int* a = new int[arraylength];
	//int* b = new int[arraylength];
	//for (int i = 0; i < arraylength; i++) {
	//	a[i] = rand() % arraylength;
	//	b[i] = a[i];
	//}
	//cout << "selection选择前\n";
	//out(a, arraylength);
	//int kth = ceil(arraylength / 2.0);//中位数
	//int p=selection( a, arraylength, kth);
	//cout << "方法一中位数为  " << p<<"\n";

	//cout << "deter_ selection选择前\n";
	//out(b, arraylength);
	//int q=determinstic_selection(b, arraylength, kth);
	//cout << "方法二中位数为  " << q << "\n";


	//以下为测试

	int time1 = 0, time2 = 0;
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
			time1 += simulation(a, nlength, arraylength / 2, 0);//sig=0为random selection
			time2 += simulation(a, nlength, arraylength / 2, 1);//sig=1为determinstic selection
		}
		cout << "数据规模为：" << nlength << "\n";
		cout << "random selection       平均时间为  " << time1 / (1000 * cnt * 1.0) << "\n";
		cout << "determinstic selection 平均时间为  " << time2 / (1000 * cnt * 1.0) << "\n";

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
int simulation(int* a, int length, int kth, int sig) {
	clock_t startTime;
	clock_t endTime;
	if (sig == 0) {
		int* b = copy(a, length);
		startTime = clock();
		int tar = selection(b, length, kth);
		endTime = clock();
		delete[] b;
	}
	else if (sig == 1) {
		int* b = copy(a, length);
		startTime = clock();
		int tar2 = determinstic_selection(b, length, kth);
		endTime = clock();
		delete[] b;
	}
	return (endTime - startTime);
}
int partition(int* a, int first, int last) {
	int pivot = a[last];
	int i = first, j = last - 1;
	while (true)
	{
		while (a[i] < pivot) {
			i++;
			if (i == last) break;
		}
		while (a[j] >= pivot) {
			j--;
			if (j == first) break;
		}
		if (i >= j) break;
		swap(a, i, j);
	}
	swap(a, i, last);
	return i;
}



void out(int* a, int length) {

	for (int i = 0; i < length; i++) {
		cout << a[i] << "  ";
	}
	cout << "\n";
}

void swap(int* a, int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}


int _selection(int* a, int first, int last, int rth) { //rth是假设有序数组的位置
	if (rth > last) return -1;
	if (first >= last) return a[first];//有点不清晰
	int r = rand() % (last - first);
	r += first;
	swap(a, r, last);

	int p = partition(a, first, last);
	if (rth < p) return _selection(a, first, p - 1, rth);
	else if (rth == p) return a[p];
	else if (rth > p) return _selection(a, p + 1, last, rth);
}
int selection(int* a, int length, int kth) {
	int r = _selection(a, 0, length - 1, kth - 1);
	return r;
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
void _out(int* a, int first, int last) {
	for (int i = first; i <= last; i++) {
		cout << a[i] << "  ";
	}
	cout << "\n";
}
void select_pivot(int* a, int first, int last) {
	int n_num = ceil((last - first + 1) / 5.0); //除以5然后向上取整，注意是5.0
	int* b = new int[n_num];//b中装的将是小组中位数
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
	int element = _determinstic_selection(b, 0, n_num - 1, (n_num - 1) / 2);
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

int _determinstic_selection(int* a, int first, int last, int rth) {
	if (first >= last) return a[first];
	if (last - first + 1 < 10) {
		_insertion_sort(a, first, last);
		return a[rth];
	}
	select_pivot(a, first, last);
	int p = partition(a, first, last);
	if (rth < p) return _determinstic_selection(a, first, p - 1, rth);
	else if (rth == p) return a[p];
	else return _determinstic_selection(a, p + 1, last, rth);

}

int determinstic_selection(int* a, int length, int kth) {
	int r = _determinstic_selection(a, 0, length - 1, kth - 1);
	return r;
}