#pragma once

#include<malloc.h>

#define MAXSIZE 100000
/*-----不同时间复杂度的排序算法------*/
void buddleSort(int arr[], int length);       //冒泡排序 时间复杂度O(n^2)
void selectionSort(int arr[], int length);    //选择排序 时间复杂度O(n^2)
void insettionSort(int arr[], int length);    //插入排序 时间复杂度O(n^2)
void shellSort(int arr[], int length);        //希尔排序 时间复杂度O(n^(1.4~2))
void qSort(int* a, int low, int high);        //快速排序 时间复杂度O(nlogn)
void quickSort(int arr[], int length);        //快速排序执行函数
void heapAdjust(int arr[], int s, int m);     //建堆
void heapSort(int arr[], int length);         //堆排序  时间复杂度O(nlogn)
void merge(int SR[], int TR[], int i, int m, int n);
void mergePass(int SR[], int TR[], int s, int n);
void mergeSort(int arr[], int length);



