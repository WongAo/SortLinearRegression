#include <time.h>
#include <windows.h>
#include <stdio.h>

int* copyArray(int arr[], int length) {  //��������
	int i;
	int* arr2 = (int*)malloc(sizeof(int) * length);

	for (i = 0; i < length; i++) {
		arr2[i] = arr[i];
	}

	return arr2;
}

double getRunTime(void (*sort)(int arr[], int length), int arr[], int length) {
	//int* tempArr = copyArray(arr, length);
	double run_time;
	LARGE_INTEGER time_start;	                     //��ʼʱ��
	LARGE_INTEGER time_over;	                     //����ʱ��
	double dqFreq;		                                     //��ʱ��Ƶ��
	LARGE_INTEGER f;	                                     //��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//��ʱ��ʼ
	(*sort)(arr, length);
	QueryPerformanceCounter(&time_over);	//��ʱ����
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq; //����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
	free(arr); //�ͷ��ڴ�
	return run_time;
}

double getO1() {
	int i = 10000, j = 1000;
	double run_time, sum = 0;
	LARGE_INTEGER time_start;	//��ʼʱ��
	LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		                //��ʱ��Ƶ��
	LARGE_INTEGER f;	                //��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;

	while (j--) {
		i = 10000;
		QueryPerformanceCounter(&time_start);	//��ʱ��ʼ
		while (i--) {}                                                 //ִ��10000��
		QueryPerformanceCounter(&time_over);	//��ʱ����
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
		sum += run_time;
		printf("%f\n", run_time / 10000); //��ȡһ����������ʱ��
	}
	printf("avg=%fus\n", sum / 10000 / 10000); //���ִ��һ������ƽ������ʱ�䣬��O(1)��ʱ��

	return sum / 10000 / 1000;
}

int* getRandomArray(int length) {                       //��ȡ�������
	int* arr = (int*)malloc(sizeof(int) * length);      //��̬�����ڴ�
	int i;

	srand((unsigned int)time(NULL));                    //�����������
	for (i = 0; i < length; i++) {
		arr[i] = rand() % (length + 1);
	}
	return arr;
}

