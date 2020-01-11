#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include "window.h"


#define WIDTH 1350
#define HEIGHT 700
#define INTER 50
#define START 300
#define DARKGREEN 0x00AA00
#define BUTTON_NORMAL 0xFF6600
#define BUTTON_FOCUS 0xFF9900
#define BUTTON_TOUCH 0xFFCC00
 

int* sortObj::transDim(int x, int y) {
	int* dim = (int*)malloc(2 * sizeof(int));
	dim[0] = START + x;
	dim[1] = HEIGHT - y - INTER;
	return dim;
}
sortObj::sortObj(const char* name, int color) {
	strcpy(this->name, name);
	this->color = color;
}
sortObj::sortObj(const char* name, int color, void (*sort)(int arr[], int length), int sortTime, int sortSpan) {
	strcpy(this->name, name);
	this->color = color;
	this->sort = sort;
	this->sortTime = sortTime;
	this->sortSpan = sortSpan;
}
void sortObj::setCoe(double* coe) {
	if(this->coe) 
		free(this->coe);
	this->coe = coe;
}
double* sortObj::getCoe() {
	return coe;
}
void sortObj::addPoint(double x, double y) {
	point[pointLength][0] = x;
	point[pointLength][1] = y;
	drawPoint((int)x / sortTime, (int)y / 100000);
	pointLength++;
}
void sortObj::drawPoint(int x, int y) {  //ɢ��ͼ���
	int* dim = transDim(x, y);
	x = dim[0];
	y = dim[1];
	free(dim);

	if ((x < WIDTH - INTER) && y > INTER) {
		setcolor(color);
		setfillcolor(color);
		fillcircle(x, y, 2);  //���ư뾶Ϊ2��Բ��
	}
}
void sortObj::drawFun() {
	int* dim;
	int i, len, x, y[1001];
	for (i = 1; i <= 1000; i++) {
		x = i * 100;
		y[i] = (coe[0] + coe[1] * x + coe[2] * x * x + coe[3] * x * x * x + coe[4] * log2(x) + coe[5] * x * log2(x)) / 100000;
		if (y[i] > 600) break;
		len = i;
	}
	setlinecolor(color);
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	moveto(START + 1, y[1] - INTER);
	dim = transDim(1, y[1]);
	moveto(dim[0], dim[1]);
	free(dim);

	for (i = 2; i <= len; i++) {
		dim = transDim(i, y[i]);
		lineto(dim[0], dim[1]);
		free(dim);
	}
}


button::button(int x, int y, const char* name, void(*fun)()) {
	this->x = x;
	this->y = y;
	this->name = name;
	this->fun = fun;
}
void button::setFun(void(*fun)()) {
	this->fun = fun;
}
void button::setxy(int x, int y) {
	this->x = x;
	this->y = y;
}


void button::draw(int status) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;                      // ��������߶�Ϊ 20
	strcpy_s(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setcolor(WHITE);

	switch (status)
	{
	case 0: setfillcolor(normal);
		break;
	case 1: setfillcolor(focus);
		break;
	case 2: setfillcolor(touch);
		break;
	default: setfillcolor(normal);
	}
	solidrectangle(x, y, x + width, y + height);

	setbkmode(TRANSPARENT);
	outtextxy(x + 75, y + 15, _T(name));
}




window::window() {

}

int window::getSortObj_length() {
	return sortObj_length;
}

void window::addSortObj(const char* name, void (*sort)(int arr[], int length), int sortTime, int sortSpan) {
	int color = this->colors[this->sortObj_length];
	this->sortObj_length++;
	this->sortObj_arr = (sortObj*)realloc(this->sortObj_arr, this->sortObj_length * sizeof(sortObj));
	if (this->sortObj_arr)
		this->sortObj_arr[sortObj_length - 1] = sortObj(name, color, sort, sortTime, sortSpan);

}

void window::addButton(const char* name, void(*fun)()) {
	button_length++;
	button_arr = (button*)realloc(button_arr, button_length * sizeof(button));
	if (button_arr)
		button_arr[button_length - 1] = button(20, 125 + 50 * (sortObj_length - 1) + 60 * (button_length - 1), name, fun);
}

void window::drawLable() {
	if (sortObj_length) {
		int i;
		settextstyle(16, 0, _T("����"));   //�趨����������С

		setcolor(LIGHTGRAY);
		rectangle(20, INTER, START - 50, 105 + 50 * (sortObj_length - 1));

		for (i = 0; i < sortObj_length; i++) {
			setfillcolor(sortObj_arr[i].color);
			solidrectangle(30, INTER + 25 + i * 50, 140, INTER + 28 + i * 50);
			setcolor(BLACK);  //�趨����������ɫ
			outtextxy(150, INTER + 20 + i * 50, _T(sortObj_arr[i].name));

			/*���ƶ�ѡ��*/
			setfillcolor(WHITE);
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
			fillrectangle(224, INTER + 20 + i * 50, 240, INTER + 36 + i * 50);
			if (sortObj_arr[i].isAlive) {
				line(230, INTER + 32 + i * 50, 227, INTER + 26 + i * 50);
				line(230, INTER + 32 + i * 50, 238, INTER + 24 + i * 50);
			}
		}
	}
	if (button_length) {
		int i;
		for (i = 0; i < button_length; i++) {
			button_arr[i].setxy(20, 125 + 50 * (sortObj_length - 1) + 60 * i);
			button_arr[i].draw(0);
		}
	}
}

void window::show() {
	initgraph(WIDTH, HEIGHT);   //��ʼ������
	
	refresh();

}

void window::mouseListener() {
	MOUSEMSG m;		// ���������Ϣ
	HCURSOR cur_hand = LoadCursor(NULL, MAKEINTRESOURCE(32649));	 // ���͹��
	HCURSOR cur_arrow = LoadCursor(NULL, IDC_ARROW);		         // ��ͷ�͹��
	HCURSOR cur_wait = LoadCursor(NULL, IDC_WAIT);		             // �ȴ��͹��
	HWND hwnd = GetHWnd();							                 // ��ȡ��ͼ���ھ��
	SetClassLong(hwnd, GCL_HCURSOR, (long)cur_arrow);	             // ���ô�����������ʽ

	while (true) {
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		int x = m.x;
		int y = m.y;
		int i;
		
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			// ����ƶ�
			for (i = 0; i < button_length; i++) {
				int bx = button_arr[i].x;
				int by = button_arr[i].y;
				int width = button_arr[i].width;
				int height = button_arr[i].height;
				if (x > bx&& x<bx + width && y>by&& y < by + height) {
					button_arr[i].draw(1);
					SetClassLong(hwnd, GCL_HCURSOR, (long)cur_hand);
					break;
				}
				else {
					button_arr[i].draw(0);
				}
			}
			if (i == button_length)
				SetClassLong(hwnd, GCL_HCURSOR, (long)cur_arrow);

			for (i = 0; i < sortObj_length; i++) {
				int bx = 224;
				int by = INTER + 20 + i * 50;
				if (x > bx&& x<bx + 17 && y>by&& y < by + 17) {
					SetClassLong(hwnd, GCL_HCURSOR, (long)cur_hand);

				}
			}
			break;

		case WM_LBUTTONDOWN:
			// ��������
			for (i = 0; i < button_length; i++) {
				int bx = button_arr[i].x,
					by = button_arr[i].y,
					width = button_arr[i].width,
					height = button_arr[i].height;
				if (x > bx&& x<bx + width && y>by&& y < by + height) {
					button_arr[i].draw(2);
					SetClassLong(hwnd, GCL_HCURSOR, (long)cur_wait);
					button_arr[i].fun();
					SetClassLong(hwnd, GCL_HCURSOR, (long)cur_arrow);
				}
			}
			for (i = 0; i < sortObj_length; i++) {
				int bx = 224;
				int by = INTER + 20 + i * 50;
				if (x > bx&& x<bx + 17 && y>by&& y < by + 17) {
					setcolor(BLACK);
					setfillcolor(WHITE);
					setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
					fillrectangle(224, INTER + 20 + i * 50, 240, INTER + 36 + i * 50);
					if (sortObj_arr[i].isAlive) {
						sortObj_arr[i].isAlive = 0;
					}
					else {
						sortObj_arr[i].isAlive = 1;
						line(230, INTER + 32 + i * 50, 227, INTER + 26 + i * 50);
						line(230, INTER + 32 + i * 50, 238, INTER + 24 + i * 50);
					}
				}
			}
			break;
		case WM_RBUTTONUP:
			// ������Ҽ�
			break;
		}
	}
}

void window::drawAxis() {
	int i;
	char s[5] = { 0 };

	int interX = (WIDTH - START - INTER) / 20;                          //������x����
	int interY = (HEIGHT - 2 * INTER) / 20;                                 //������y����
	settextstyle(16, 0, _T("����"));                                               //�趨����������С
	setcolor(BLACK);                                                                   //�趨����������ɫ
	outtextxy(START + (WIDTH - START - INTER) / 2, HEIGHT - INTER + 25, _T("���鳤��(x1000)"));  //���ƺ���������
	outtextxy(START, 25, _T("��������(x100000)"));                    //��������������
	setcolor(LIGHTGRAY);                                                           //�趨��������ɫ
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 1);                       //�趨ֱ����ʽ

	rectangle(START, INTER, WIDTH - INTER, HEIGHT - INTER);  //�������������
	_itoa_s(0, s, 10);
	outtextxy(START - 20, HEIGHT - INTER + 5, s);
	for (i = 1; i < 20; i++) {  //����������
		line(START + i * interX, INTER, START + i * interX, HEIGHT - INTER);
		_itoa_s(i * interX, s, 10);
		outtextxy(START + i * interX - 10, HEIGHT - INTER + 5, s);

		line(START, INTER + interY * i, WIDTH - INTER, INTER + interY * i);
		_itoa_s(interY * i, s, 10);
		outtextxy(START - 30, HEIGHT - INTER - interY * i - 8, s);
	}
	_itoa_s(i * interX, s, 10);
	outtextxy(START + i * interX - 10, HEIGHT - INTER + 5, s);

	_itoa_s(interY * i, s, 10);
	outtextxy(START - 30, HEIGHT - INTER - interY * i - 8, s);
}

void test() {

}

void window::refresh() {
	setbkcolor(WHITE);                //���ñ���ɫΪ��ɫ
	cleardevice();
	drawAxis();
	drawLable();
	for (int i = 0; i < sortObj_length; i++) 
		sortObj_arr[i].pointLength = 0;
	
}

void window::drawResult() {
	int i, j, alive = 0;
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 16;                      // ��������߶�Ϊ 21
	strcpy_s(f.lfFaceName, _T("����"));    // ��������
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);   //�趨����

	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_DASH, 2);
	settextcolor(BLACK);

	for (i = 0; i < sortObj_length; i++) {
		if (sortObj_arr[i].isAlive)
			alive++;
	}

	fillrectangle(START + 290, INTER + 20, START + 980, INTER + 30 + 50 * alive);//�������

	for (i = 0, j = 0; i < sortObj_length; i++) {
		if (!sortObj_arr[i].isAlive)
			continue;
		double* coe = sortObj_arr[i].getCoe();
		char* name = sortObj_arr[i].name;
		char expr[100];
		sprintf(expr, "%s: o(n)=(%.2f)*1+(%.2f)n+(%.2f)n^2+(%.2f)n^3+(%.2f)logn+(%.2f)nlogn",
			name, coe[0], coe[1], coe[2], coe[3], coe[4], coe[5]);
		outtextxy(START + 300, INTER + 40 + 50 * (j++), expr);
	}
}