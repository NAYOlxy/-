#include<iostream>
#include<vector>
#include<memory>
using namespace std;

// 冒泡排序
// 从尾到头，小的往上冒
void BubbleSort(vector<int>& num) {
	for (int i = num.size(); i > 0; i--) {
		for (int j = i; j > 0; j--) {
			if (num[j] < num[j - 1]) {
				swap(num[j], num[j - 1]);
			}
		}
	}
}


// 选择排序
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

// 插入排序
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

//	希尔排序
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

//	归并排序
//  递归版本
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

//	非递归版本
template<typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
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

//	快排
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

//  	堆排序
//	大顶堆
void MaxHeapify(vector<int>& num, int start, int end) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && num[son] < num[son + 1])
			son++;
		if (num[dad] > num[son])
			return;
		else {
			swap(num[dad], num[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void HeapSort(vector<int>& num) {
	int len = num.size();
	//	第一轮先找出最大的值，放到最后
	for (int i = len / 2 - 1; i >= 0; i--)
		MaxHeapify(num, i, len - 1);
	//	后续几轮，分别把找到的最大的值依次放在后面，也就是i-1的位置，最终得到一个升序排列
	for (int i = len - 1; i > 0; i--) {
		swap(num[0], num[i]);
		MaxHeapify(num, 0, i - 1);
	}
}

//	基数排序
//	尚未理解
int Maxbit(vector<int>& num)
{
	int n = num.size();
	int maxData = num[0];
	for (int i = 1; i < n; ++i) {
		if (maxData < num[i])
			maxData = num[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p) {
		maxData /= 10;
		++d;
	}
	return d;
}

void RadixSort(vector<int>& num) {
	int n = num.size();
	int d = Maxbit(num);
	vector<int>tmp(n);
	vector<int>count(10);
	int i, j, k;
	int radix = 1;
	for (int i = 1; i <= d; i++) {
		for (j = 0; j < 10; j++)
			count[j] = 0;
		for (j = 0; j < n; j++) {
			k = (num[j] / radix) % 10;
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];
		for (j = n - 1; j >= 0; j--) {
			k = (num[j] / radix) % 10;
			tmp[count[k] - 1] = num[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) {
			num[j] = tmp[j];
			radix = radix * 10;
		}
	}
}

int main()
{
	vector<int> num = { 1,2,3,9,8,7,6,5 };
	ShellSort(num);
	for (auto item : num) {
		cout << item << " ";
	}
}
