#include<malloc.h>

//ð������  ʱ�临�Ӷ�O(n^2)
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

//ѡ������  ʱ�临�Ӷ�O(n^2)
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

//�������� ʱ�临�Ӷ�O(n^2)
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

//ϣ������ ʱ�临�Ӷ�O(n^(1.4~2))
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

//��������   ʱ�临�Ӷ�O(nlogn)
void qSort(int* a, int low, int high) { 
	int i = low, j = high, key = a[low];

	if (low >= high) {        //���low >= high˵�����������
		return;
	}
	while (low < high) {      //��whileѭ������һ�α�ʾ�Ƚ���һ��
		while (low < high && key <= a[high]) {
			--high;           //��ǰѰ��
		}
		if (key > a[high]) {
			a[low] = a[high]; //ֱ�Ӹ�ֵ, ���ý���
			++low;
		}
		while (low < high && key >= a[low]) {
			++low;            //���Ѱ��
		}
		if (key < a[low]) {
			a[high] = a[low]; //ֱ�Ӹ�ֵ, ���ý���
			--high;
		}
	}
	a[low] = key;             //������һ�ֺ�keyֵ��λ, ���ñȽ�һ�ξͻ���һ�Ρ���ʱkeyֵ�����зֳ�����������
	qSort(a, i, low - 1);     //��ͬ���ķ�ʽ�Էֳ�������ߵĲ��ֽ���ͬ�ϵ�����
	qSort(a, low + 1, j);     //��ͬ���ķ�ʽ�Էֳ������ұߵĲ��ֽ���ͬ�ϵ�����
}

void quickSort(int arr[], int length) {
	int low, high;
	low = 0;
	high = length - 1;
	qSort(arr, low, high);
}

//һ�ζ�ɸѡ�Ĺ���
void heapAdjust(int arr[], int s, int m) {
	int rc, j;
	rc = arr[s];
	for (j = 2 * s; j <= m; j = j * 2) {//ͨ��ѭ���ؽϴ�ĺ��ӽ������ɸѡ
		if (j < m&& arr[j] < arr[j + 1]) j++;//jΪ�ϴ�ļ�¼���±�
		if (rc > arr[j]) break;
		arr[s] = arr[j]; s = j;
	}
	arr[s] = rc;//����
}

//������   ʱ�临�Ӷ�O(nlogn)
void heapSort(int arr[], int length) {
	int* arr2 = arr - 1;
	int temp, i, j;
	for (i = length / 2; i > 0; i--) {//ͨ��ѭ����ʼ������
		heapAdjust(arr2, i, length);
	}
	for (i = length; i > 0; i--) {
		temp = arr2[1];
		arr2[1] = arr2[i];
		arr2[i] = temp;//���Ѷ���¼��δ��������һ����¼����
		heapAdjust(arr2, 1, i - 1);//���µ���Ϊ����
	}
}

void merge(int SR[], int TR[], int i, int m, int n)//�鲢����
{
	int j, k, l;
	for (j = m + 1, k = i; i <= m && j <= n; k++)	/* ��SR�м�¼��С����ز���TR */
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)
	{
		for (l = 0; l <= m - i; l++)
			TR[k + l] = SR[i + l];		/* ��ʣ���SR[i..m]���Ƶ�TR */
	}
	if (j <= n)
	{
		for (l = 0; l <= n - j; l++)
			TR[k + l] = SR[j + l];		/* ��ʣ���SR[j..n]���Ƶ�TR */
	}
}


/* �ǵݹ鷨 */
/* ��SR[s..t]�鲢����ΪTR1[s..t] */
void mergePass(int SR[], int TR[], int s, int n)
{
	int i = 1;
	int j;
	while (i <= n - 2 * s + 1)
	{/* �����鲢 */
		merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	if (i < n - s + 1) /* �鲢����������� */
		merge(SR, TR, i, i + s - 1, n);
	else /* �����ֻʣ�µ��������� */
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}
//�鲢����   ʱ�临�Ӷ�O(nlogn)
void mergeSort(int arr[], int length)
{
	int* arr2 = arr - 1;
	int* TR = (int*)malloc(length * sizeof(int));/* �������ռ� */
	int k = 1;
	while (k < length)
	{
		mergePass(arr2, TR, k, length);
		k = 2 * k;/* �����г��ȼӱ� */
		mergePass(TR, arr2, k, length);
		k = 2 * k;/* �����г��ȼӱ� */
	}
}