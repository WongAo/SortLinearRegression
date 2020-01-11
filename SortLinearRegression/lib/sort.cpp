#include<malloc.h>

//冒泡排序  时间复杂度O(n^2)
void buddleSort(int arr[], int length) {
	int i, j, temp;

	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//选择排序  时间复杂度O(n^2)
void selectionSort(int arr[], int length) {
	int i, j, temp;

	for (i = 0; i < length; i++) {
		for (j = i + 1; j < length; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

//插入排序 时间复杂度O(n^2)
void insettionSort(int arr[], int length) {
	int i, j;

	for (i = 1; i < length; i++) {
		int tmp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > tmp; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

//希尔排序 时间复杂度O(n^(1.4~2))
void shellSort(int arr[], int length) {
	int i, j, temp, gap;

	for (gap = length / 2; gap > 0; gap /= 2) {
		for (i = gap; i < length; i++) {
			temp = arr[i];
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

//快速排序   时间复杂度O(nlogn)
void qSort(int* a, int low, int high) { 
	int i = low, j = high, key = a[low];

	if (low >= high) {        //如果low >= high说明排序结束了
		return;
	}
	while (low < high) {      //该while循环结束一次表示比较了一轮
		while (low < high && key <= a[high]) {
			--high;           //向前寻找
		}
		if (key > a[high]) {
			a[low] = a[high]; //直接赋值, 不用交换
			++low;
		}
		while (low < high && key >= a[low]) {
			++low;            //向后寻找
		}
		if (key < a[low]) {
			a[high] = a[low]; //直接赋值, 不用交换
			--high;
		}
	}
	a[low] = key;             //查找完一轮后key值归位, 不用比较一次就互换一次。此时key值将序列分成左右两部分
	qSort(a, i, low - 1);     //用同样的方式对分出来的左边的部分进行同上的做法
	qSort(a, low + 1, j);     //用同样的方式对分出来的右边的部分进行同上的做法
}

void quickSort(int arr[], int length) {
	int low, high;
	low = 0;
	high = length - 1;
	qSort(arr, low, high);
}

//一次堆筛选的过程
void heapAdjust(int arr[], int s, int m) {
	int rc, j;
	rc = arr[s];
	for (j = 2 * s; j <= m; j = j * 2) {//通过循环沿较大的孩子结点向下筛选
		if (j < m&& arr[j] < arr[j + 1]) j++;//j为较大的记录的下标
		if (rc > arr[j]) break;
		arr[s] = arr[j]; s = j;
	}
	arr[s] = rc;//插入
}

//堆排序   时间复杂度O(nlogn)
void heapSort(int arr[], int length) {
	int* arr2 = arr - 1;
	int temp, i, j;
	for (i = length / 2; i > 0; i--) {//通过循环初始化顶堆
		heapAdjust(arr2, i, length);
	}
	for (i = length; i > 0; i--) {
		temp = arr2[1];
		arr2[1] = arr2[i];
		arr2[i] = temp;//将堆顶记录与未排序的最后一个记录交换
		heapAdjust(arr2, 1, i - 1);//重新调整为顶堆
	}
}

void merge(int SR[], int TR[], int i, int m, int n)//归并操作
{
	int j, k, l;
	for (j = m + 1, k = i; i <= m && j <= n; k++)	/* 将SR中记录由小到大地并入TR */
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)
	{
		for (l = 0; l <= m - i; l++)
			TR[k + l] = SR[i + l];		/* 将剩余的SR[i..m]复制到TR */
	}
	if (j <= n)
	{
		for (l = 0; l <= n - j; l++)
			TR[k + l] = SR[j + l];		/* 将剩余的SR[j..n]复制到TR */
	}
}


/* 非递归法 */
/* 将SR[s..t]归并排序为TR1[s..t] */
void mergePass(int SR[], int TR[], int s, int n)
{
	int i = 1;
	int j;
	while (i <= n - 2 * s + 1)
	{/* 两两归并 */
		merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	if (i < n - s + 1) /* 归并最后两个序列 */
		merge(SR, TR, i, i + s - 1, n);
	else /* 若最后只剩下单个子序列 */
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}
//归并排序   时间复杂度O(nlogn)
void mergeSort(int arr[], int length)
{
	int* arr2 = arr - 1;
	int* TR = (int*)malloc(length * sizeof(int));/* 申请额外空间 */
	int k = 1;
	while (k < length)
	{
		mergePass(arr2, TR, k, length);
		k = 2 * k;/* 子序列长度加倍 */
		mergePass(TR, arr2, k, length);
		k = 2 * k;/* 子序列长度加倍 */
	}
}