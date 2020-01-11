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
	
	w.addSortObj("ð������", buddleSort, 100, 1);
	w.addSortObj("ѡ������", selectionSort, 100, 1);
	w.addSortObj("��������", insettionSort, 100, 2);
	w.addSortObj("ϣ������", shellSort, 100, 10);
	w.addSortObj("������", heapSort, 100, 10);
	w.addSortObj("�鲢����", mergeSort, 100, 10);
	w.addSortObj("��������", quickSort, 100, 10);
	w.addButton("��ʼ����", startSort);
	w.addButton("���Իع�", startFit);

	w.show();
	
	w.mouseListener();
	return 0;
}

void startSort() {
	int i, j;

	w.refresh();                                     //ˢ��ҳ��
	for (i = 0; i < w.getSortObj_length(); i++) {    //���������㷨��������ĳ���ѭ��
		if (!w.sortObj_arr[i].isAlive)               //�ж��Ƿ���Ҫ���и��㷨
			continue;

		int sortDataLength = w.sortObj_arr[i].sortDataLength,    //��ȡ�������ݼ���С
			sortOnceTime = w.sortObj_arr[i].sortOnceTime,  //��ȡÿ�����ݼ�����Ĵ���
			sortSpan = w.sortObj_arr[i].sortSpan;    //��ȡ�������鳤�ȼ��

		for (j = 1; j <= sortDataLength; j++) {
			int temp = j * sortDataLength * sortSpan;
			int* arr = getRandomArray(temp);         //������������������������������
			double time = 0; 
			for (int k = 0; k < sortOnceTime; k++) {
				time += getRunTime(w.sortObj_arr[i].sort, arr, temp) / timeO1; //��ȡ��������ʱ��
			}
			time /= sortOnceTime;
			free(arr);
			w.sortObj_arr[i].addPoint((double)temp, time);  //��������ʱ��-������
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