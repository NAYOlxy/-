#include<iostream>
#include<vector>
#include<memory>
using namespace std;

// ð������
// ��β��ͷ��С������ð
void BubbleSort(vector<int>& num) {
	for (int i = num.size(); i > 0; i--) {
		for (int j = i; j > 0; j--) {
			if (num[j] < num[j - 1]) {
				swap(num[j], num[j - 1]);
			}
		}
	}
}


// ѡ������
void SelectionSort(vector<int>& num) {
	for (int i = 0; i < num.size(); i++) {
		int key = i;
		for (int j = i + 1; j < num.size(); j++) {
			if (num[j] < num[key]) {
				key = j;
			}
		}
		swap(num[i], num[key]);
	}
}

// ��������
void InsertSort(vector<int>& num) {
	for (int i = 1; i < num.size(); i++) {
		int key = num[i];
		int pos = i - 1;
		while (pos >= 0 && num[pos] > key) {
			num[pos + 1] = num[pos];
			pos--;
		}
		num[pos] = key;
	}
}

//	ϣ������
void ShellSort(vector<int>& num) {
	int h = 1;
	int len = num.size();
	while (h < len / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {		
		for (int i = h; i < len; i++) {
			for (int j = i; j >= h && num[j] < num[j - h]; j -= h) {
				swap(num[j], num[j - h]);
			}
		}
		h = h / 3;
	}
 }

//	�鲢����
//  �ݹ�汾
void Merge(vector<int>& num,int front,int mid,int end) {
	vector<int> LeftSubArray(num.begin() + front, num.begin() + mid + 1);
	vector<int> RightSubArray(num.begin() + mid+1, num.begin() + end + 1);
	int idxLeft = 0, idxRight = 0;
	LeftSubArray.insert(LeftSubArray.end(), numeric_limits<int>::max());
	RightSubArray.insert(RightSubArray.end(), numeric_limits<int>::max());
	for (int i = front; i <= end; i++) {
		if (LeftSubArray[idxLeft] < RightSubArray[idxRight]) {
			num[i] = LeftSubArray[idxLeft];
			idxLeft++;
		}
		else {
			num[i] = RightSubArray[idxRight];
			idxRight++;
		}
	}

}

void MergeSort(vector<int>& num, int front, int end) {
	if (front >= end)
		return;
	int mid = (front + end) / 2;
	MergeSort(num, front, mid);
	MergeSort(num, mid + 1, end);
	Merge(num, front, mid, end);
}

//	�ǵݹ�汾
template<typename T> // �������c���Կ�ʹ��,��Ҫʹ�����(class)�r����O��"С�"(<)���\���ӹ���
void merge_sort(T arr[], int len) {
	T* a = arr;
	T* b = new T[len];
	for (int seg = 1; seg < len; seg += seg) {
		for (int start = 0; start < len; start += seg + seg) {
			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		T* temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		for (int i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
	}
	delete[] b;
}

//	����
int Paritition(vector<int>& num, int low, int high) {
	int pivot = num[low];
	while (low < high) {
		while (low < high && num[high] >= pivot) {
			--high;
		}
		num[low] = num[high];
		while (low < high && num[low] <= pivot) {
			++low;
		}
		num[high] = num[low];
	}
	num[low] = pivot;
	return low;
}

void QuickSort(vector<int>& num, int low, int high) {
	if (low >= high) return;
	int pivot = Paritition(num, low, high);
	QuickSort(num, low, pivot - 1);
	QuickSort(num, pivot + 1, high);
}



int main()
{
	vector<int> num = { 1,2,3,9,8,7,6,5 };
	ShellSort(num);
	for (auto item : num) {
		cout << item << " ";
	}
}