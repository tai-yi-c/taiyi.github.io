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
	//�㷨��ȷ����֤
	//int* a = new int[arraylength];
	//int* b = new int[arraylength];
	//for (int i = 0; i < arraylength; i++) {
	//	a[i] = rand() % arraylength;
	//	b[i] = a[i];
	//}
	//cout << "selectionѡ��ǰ\n";
	//out(a, arraylength);
	//int kth = ceil(arraylength / 2.0);//��λ��
	//int p=selection( a, arraylength, kth);
	//cout << "����һ��λ��Ϊ  " << p<<"\n";

	//cout << "deter_ selectionѡ��ǰ\n";
	//out(b, arraylength);
	//int q=determinstic_selection(b, arraylength, kth);
	//cout << "��������λ��Ϊ  " << q << "\n";


	//����Ϊ����

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
			//simulation�Դ���������
			time1 += simulation(a, nlength, arraylength / 2, 0);//sig=0Ϊrandom selection
			time2 += simulation(a, nlength, arraylength / 2, 1);//sig=1Ϊdeterminstic selection
		}
		cout << "���ݹ�ģΪ��" << nlength << "\n";
		cout << "random selection       ƽ��ʱ��Ϊ  " << time1 / (1000 * cnt * 1.0) << "\n";
		cout << "determinstic selection ƽ��ʱ��Ϊ  " << time2 / (1000 * cnt * 1.0) << "\n";

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


int _selection(int* a, int first, int last, int rth) { //rth�Ǽ������������λ��
	if (rth > last) return -1;
	if (first >= last) return a[first];//�е㲻����
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
	int n_num = ceil((last - first + 1) / 5.0); //����5Ȼ������ȡ����ע����5.0
	int* b = new int[n_num];//b��װ�Ľ���С����λ��
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
	int element = _determinstic_selection(b, 0, n_num - 1, (n_num - 1) / 2);
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