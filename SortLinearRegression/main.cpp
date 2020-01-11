#include "window.h"
#include "sort.h"
#include "runtime.h"
#include "matrix.h"

double timeO1;
window w;

void startSort();
void startFit();

int main(void) {
	timeO1 = getO1();
	
	w.addSortObj("冒泡排序", buddleSort, 100, 1);
	w.addSortObj("选择排序", selectionSort, 100, 1);
	w.addSortObj("插入排序", insettionSort, 100, 2);
	w.addSortObj("希尔排序", shellSort, 100, 10);
	w.addSortObj("堆排序", heapSort, 100, 10);
	w.addSortObj("归并排序", mergeSort, 100, 10);
	w.addSortObj("快速排序", quickSort, 100, 10);
	w.addButton("开始测试", startSort);
	w.addButton("线性回归", startFit);

	w.show();
	
	w.mouseListener();
	return 0;
}

void startSort() {
	int i, j;

	w.refresh();                                     //刷新页面
	for (i = 0; i < w.getSortObj_length(); i++) {    //根据排序算法对象数组的长度循环
		if (!w.sortObj_arr[i].isAlive)               //判断是否需要运行该算法
			continue;

		int sortDataLength = w.sortObj_arr[i].sortDataLength,    //获取排序数据集大小
			sortOnceTime = w.sortObj_arr[i].sortOnceTime,  //获取每组数据集排序的次数
			sortSpan = w.sortObj_arr[i].sortSpan;    //获取排序数组长度间隔

		for (j = 1; j <= sortDataLength; j++) {
			int temp = j * sortDataLength * sortSpan;
			int* arr = getRandomArray(temp);         //根据排序次数和排序间隔生成随机数组
			double time = 0; 
			for (int k = 0; k < sortOnceTime; k++) {
				time += getRunTime(w.sortObj_arr[i].sort, arr, temp) / timeO1; //获取排序运行时间
			}
			time /= sortOnceTime;
			free(arr);
			w.sortObj_arr[i].addPoint((double)temp, time);  //存入运行时间-样本数
		}
	}
}

void startFit() {
	int i;

	for (i = 0; i < w.getSortObj_length(); i++) {
		if (!w.sortObj_arr[i].isAlive)
			continue;
		double* coe = linearFit(w.sortObj_arr[i].point, w.sortObj_arr[i].pointLength);
		w.sortObj_arr[i].setCoe(coe);
		w.sortObj_arr[i].drawFun();
	}
	w.drawResult();
}