#pragma once


/*-----����ĸ����㷨��������С���˷��㷨------*/
double** newMatrix(int x, int y);                       //�����¾����ڴ�
double** newE(int n, double a);                        //����a*��λ������ع����ӵ�������
double** getAtrans(double** arcs, int x, int y); //ȡת�þ���
double** matrixMultiply(double** m1, double** m2, int x1, int y1, int x2, int y2); //����˷�
double** matrixAdd(double** m1, double** m2, int x, int y);
double getA(double** arcs, int n);                    //����һ��չ��������������ʽ|A|
double** getAStart(double** arcs, int n);         //����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ����ɰ������A*
double** getAinverse(double** arcs, int n);     //ȡ�����
double* linearFit(double xy[][2], int length);  //������Իع��Ӧ����

