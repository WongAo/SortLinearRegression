#pragma once

#include<malloc.h>

#define MAXSIZE 100000
/*-----��ͬʱ�临�Ӷȵ������㷨------*/
void buddleSort(int arr[], int length);       //ð������ ʱ�临�Ӷ�O(n^2)
void selectionSort(int arr[], int length);    //ѡ������ ʱ�临�Ӷ�O(n^2)
void insettionSort(int arr[], int length);    //�������� ʱ�临�Ӷ�O(n^2)
void shellSort(int arr[], int length);        //ϣ������ ʱ�临�Ӷ�O(n^(1.4~2))
void qSort(int* a, int low, int high);        //�������� ʱ�临�Ӷ�O(nlogn)
void quickSort(int arr[], int length);        //��������ִ�к���
void heapAdjust(int arr[], int s, int m);     //����
void heapSort(int arr[], int length);         //������  ʱ�临�Ӷ�O(nlogn)
void merge(int SR[], int TR[], int i, int m, int n);
void mergePass(int SR[], int TR[], int s, int n);
void mergeSort(int arr[], int length);



