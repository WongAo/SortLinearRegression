#include <time.h>
#include <windows.h>
#include <stdio.h>

int* copyArray(int arr[], int length) {  //复制数组
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
	LARGE_INTEGER time_start;	                     //开始时间
	LARGE_INTEGER time_over;	                     //结束时间
	double dqFreq;		                                     //计时器频率
	LARGE_INTEGER f;	                                     //计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
	(*sort)(arr, length);
	QueryPerformanceCounter(&time_over);	//计时结束
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq; //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	free(arr); //释放内存
	return run_time;
}

double getO1() {
	int i = 10000, j = 1000;
	double run_time, sum = 0;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		                //计时器频率
	LARGE_INTEGER f;	                //计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;

	while (j--) {
		i = 10000;
		QueryPerformanceCounter(&time_start);	//计时开始
		while (i--) {}                                                 //执行10000次
		QueryPerformanceCounter(&time_over);	//计时结束
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
		sum += run_time;
		printf("%f\n", run_time / 10000); //获取一行所需运行时间
	}
	printf("avg=%fus\n", sum / 10000 / 10000); //获得执行一行所需平均运行时间，即O(1)的时间

	return sum / 10000 / 1000;
}

int* getRandomArray(int length) {                       //获取随机数组
	int* arr = (int*)malloc(sizeof(int) * length);      //动态分配内存
	int i;

	srand((unsigned int)time(NULL));                    //置随机数种子
	for (i = 0; i < length; i++) {
		arr[i] = rand() % (length + 1);
	}
	return arr;
}

