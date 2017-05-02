#include"stdafx.h"
#include<vector>
#include<iterator>

using namespace std;

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define HEIGHT 600
#define WIDTH  600

/*
	Главный "герой" игры.

	Класс представляет собой сущность "змейки". 
	Определены все действия: поедание, передвижение (обработка всех возможных ситуаций), расширение.

	Так же отвечает за генерацию еды.
*/
class CPython:public CObject {
public:
	CPython();
	BOOL move();
	void generateFood();
	void changeDirection(UINT);
	UINT getDirection();
	BOOL isFood();
	void setFood(BOOL);
	vector<CPoint> python;
	vector<CPoint> default_state;
	CPoint food;
private:
	UINT direction;
	BOOL is_food;
};