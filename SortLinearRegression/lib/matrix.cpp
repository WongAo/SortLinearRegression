#include<stdlib.h>
#include<math.h>

double** newMatrix(int x, int y) {  //�����¾����ڴ�
	int i;
	double** m = (double**)malloc(x * sizeof(double*));
	for (i = 0; i < x; i++) {
		m[i] = (double*)malloc(y * sizeof(double));
	}
	return m;
}
void freeMatrix(double** m, int x) {
	for (int i = 0; i < x; i++) {
		free(m[i]);
	}
	free(m);
}
double** newE(int n, double a) {  //����a*��λ������ع����ӵ�������
	int i, j;
	double** e = newMatrix(n, n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) e[i][i] = a;
			else e[i][j] = 0;
		}
	}
	return e;
}
double** getAtrans(double** arcs, int x, int y) { //ȡת�þ���
	int i, j;
	double** atrans = newMatrix(y, x);
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			atrans[j][i] = arcs[i][j];
		}
	}

	return atrans;
}

double** matrixMultiply(double** m1, double** m2, int x1, int y1, int x2, int y2) { //����˷�
	int i, j, k;
	double sum;
	double** ans = newMatrix(x1, y2);
	for (i = 0; i < x1; i++) {
		for (j = 0; j < y2; j++) {
			sum = 0;
			for (k = 0; k < y1; k++) {
				sum += m1[i][k] * m2[k][j];
			}
			ans[i][j] = sum;
		}
	}
	return ans;
}
double** matrixAdd(double** m1, double** m2, int x, int y) {   //����ӷ�
	int i, j;

	double** ans = newMatrix(x, y);
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			ans[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return ans;
}
double getA(double** arcs, int n) {//����һ��չ��������������ʽ|A|
	if (n == 1) return arcs[0][0];

	double ans = 0;
	double** temp = newMatrix(n - 1, n - 1);
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			for (k = 0; k < n - 1; k++) {
				temp[j][k] = arcs[j + 1][(k >= i) ? k + 1 : k];
			}
		}
		double t = getA(temp, n - 1);
		if (i % 2 == 0) {
			ans += arcs[0][i] * t;
		}
		else {
			ans -= arcs[0][i] * t;
		}
	}
	return ans;
}
double** getAStart(double** arcs, int n) {//����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ����ɰ������A*
	double** ans = newMatrix(n, n);

	if (n == 1) {
		ans[0][0] = 1;
		return 0;
	}
	int i, j, k, t;
	double** temp = newMatrix(n - 1, n - 1);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n - 1; k++) {
				for (t = 0; t < n - 1; t++) {
					temp[k][t] = arcs[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
				}
			}
			ans[j][i] = getA(temp, n - 1);
			if ((i + j) % 2 == 1) {
				ans[j][i] = -ans[j][i];
			}
		}
	}
	return ans;
}

double** getAinverse(double** arcs, int n) {  //ȡ�����
	int i, j;
	double** ans = newMatrix(n, n);
	double** astart = getAStart(arcs, n);
	double a = getA(arcs, n);

	if (a == 0) return 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			ans[i][j] = astart[i][j] / a;
		}
	}

	return ans;
}

/*
������С���˷�����������ع�
b = (X^T��X + ��I)^-1��X^T��y
*/
double* linearFit(double xy[][2], int length) {  
	int i, j;
	double lambda = 1e8;  //L2�����ͷ��Ҳ������Ĵ�С
	double* b = (double*)malloc(6 * sizeof(double));  //ʱ�临�Ӷȸ���ϵ��
	double** m = newMatrix(length, 6);  //����X
	double** my = newMatrix(length, 1); //����y
	for (i = 0; i < length; i++) {
		double x = xy[i][0], y = xy[i][1];
		m[i][0] = 1;
		m[i][1] = x;
		m[i][2] = pow(x, 2);
		m[i][3] = pow(x, 3);
		m[i][4] = log2(x);
		m[i][5] = x * log2(x);
		my[i][0] = y;
	}
	double** mt = getAtrans(m, length, 6);
	double** theta = matrixMultiply(
		getAinverse(matrixAdd(matrixMultiply(mt, m, 6, length, length, 6), newE(6, lambda), 6, 6), 6),
		matrixMultiply(mt, my, 6, length, length, 1),
		6, 6, 6, 1);
	for (i = 0; i < 6; i++) {
		b[i] = theta[i][0];
	}
	freeMatrix(m, length); freeMatrix(my, length);freeMatrix(mt, 6); freeMatrix(theta, 6); //�ͷ��ڴ�
	return b;
}