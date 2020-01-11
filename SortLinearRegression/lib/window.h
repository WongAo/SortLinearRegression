#pragma once



class sortObj {
private:
	double *coe = 0;  //参数数组，长度为6
	int* transDim(int x, int y);
public:
	char name[9];
	int color;
	double point[1001][2];
	int pointLength = 0;
	int sortDataLength = 100;  //数据集大小
	int sortOnceTime = 1;  //每组数据集排序的次数（多次排序，取平均值）
	int sortSpan = 10;  //每组数据集的间隔
	int isAlive = 0;
	void (*sort)(int arr[], int length);
	sortObj(const char* name, int color);

	sortObj(const char* name, int color, void (*sort)(int arr[], int length), int sortTime, int sortSpan);

	void setCoe(double* coe);

	double* getCoe();

	void addPoint(double x, double y);

	void drawPoint(int x, int y);

	void drawFun();
};



class button {
private:

	
public:
	int x;
	int y;
	int width = 230;
	int height = 50;
	int normal = 0xFF6600;
	int focus = 0xFF9900;
	int touch = 0xFFCC00;
	const char* name;
	void(* fun)();

	button(int x, int y, const char* name, void(*fun)());
	void draw(int status);
	void setFun(void(*fun)());
	void setxy(int x, int y);
};



class window{
private:
	int sortObj_length = 0;
	int button_length = 0;
	int colors[8] = { 0xFF0000, 0x00AA00, 0x0000FF, 0xFF9900, 0x00CCFF, 0x9900FF, 0xB3B34D, 0xFF0099 };
	void drawAxis();
	void drawLable();
public:
	sortObj* sortObj_arr;
	button* button_arr;
	window();
	int getSortObj_length();
	void addSortObj(const char* name, void(*sort)(int arr[], int length), int sortTime, int sortSpan);
	void addButton(const char* name, void(*fun)());
	void refresh();
	void show();
	void mouseListener();
	void drawResult();

	
};

