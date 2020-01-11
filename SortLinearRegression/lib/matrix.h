#pragma once


/*-----矩阵的各种算法及矩阵最小二乘法算法------*/
double** newMatrix(int x, int y);                       //分配新矩阵内存
double** newE(int n, double a);                        //生成a*单位矩阵，岭回归所加的正则项
double** getAtrans(double** arcs, int x, int y); //取转置矩阵
double** matrixMultiply(double** m1, double** m2, int x1, int y1, int x2, int y2); //矩阵乘法
double** matrixAdd(double** m1, double** m2, int x, int y);
double getA(double** arcs, int n);                    //按第一行展开计算矩阵的行列式|A|
double** getAStart(double** arcs, int n);         //计算每一行每一列的每个元素所对应的余子式，组成伴随矩阵A*
double** getAinverse(double** arcs, int n);     //取逆矩阵
double* linearFit(double xy[][2], int length);  //拟合线性回归对应参数

