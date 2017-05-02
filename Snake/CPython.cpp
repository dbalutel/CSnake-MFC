#include"stdafx.h"
#include"CPython.h"

CPython::CPython() {
	CPoint point;

	point = CPoint(350, 350);
	python.push_back(point);
	point = CPoint(340, 350);
	python.push_back(point);
	point = CPoint(330, 350);
	python.push_back(point);

	default_state = python;

	direction = RIGHT;
	is_food = FALSE;
}

void CPython::generateFood() {
	CPoint point(100, 100);
	do {
		UINT x = rand() % (WIDTH - 20);
		UINT y = rand()%(HEIGHT-20);
		UINT X=10*(x/10)+10;
		UINT Y=10*(y/10)+10;
		point=CPoint(X,Y);
	} while(point==food);
	
	food = CPoint(point);
}

BOOL CPython::move()
{
	CPoint point;
	point = python[0];

	if (getDirection() == UP)
		point.y -= 10;
	else if (getDirection() ==DOWN)
		point.y += 10;
	else if (getDirection() == LEFT)
		point.x -= 10;
	else
		point.x += 10;

	if (point.x < 5 || point.x> WIDTH - 5 || point.y < 5 || point.y > HEIGHT - 5) {
		for (vector<CPoint>::iterator iter = python.end() - 1; iter != python.begin(); iter--) {
			iter->x = (iter - 1)->x;
			iter->y = (iter - 1)->y;
		}

		python.begin()->x = WIDTH - point.x;
		python.begin()->y = HEIGHT - point.y;

		return TRUE;
	}

	if(point==food)
	{
		python.push_back(*(python.end()-1));
		for(vector<CPoint>::iterator iter=python.end()-2; iter != python.begin(); iter--)
		{
			iter->x=(iter-1)->x;
			iter->y=(iter-1)->y;
		}
		python.begin()->x=point.x;
		python.begin()->y=point.y;
		generateFood();
	}
	else
	{
		for(vector<CPoint>::iterator iter=python.end()-1;
			iter!=python.begin();iter--)
		{
			iter->x=(iter-1)->x;
			iter->y=(iter-1)->y;
		}
		python.begin()->x=point.x;
		python.begin()->y=point.y;
	}

	for (vector<CPoint>::iterator iter = python.begin() + 1; iter != python.end(); ++iter) {
		if (python.front().x == iter->x && python.front().y == iter->y) {
			return FALSE;
		}
	}
	
	return TRUE;
}

void CPython::changeDirection(UINT ndir)
{
	direction=ndir;
}

UINT CPython::getDirection()
{
	return direction;
}
void CPython::setFood(BOOL n)
{
	is_food=n;
}

BOOL CPython::isFood()
{
	return is_food;
}