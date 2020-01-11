#pragma once

/*-----数组及时间操作------*/

double getRunTime(void (*sort)(int arr[], int length), int arr[], int length); //获取排序算法消耗的时间
double getO1();                                                 //获取执行一行代码所需的时间
int* getRandomArray(int length);                     //获得一个随机数组
int* copyArray(int arr[], int length);                  //复制数组

