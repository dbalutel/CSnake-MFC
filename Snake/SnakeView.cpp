
// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"
#include "SnakeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Resource.h";

// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_START, &CSnakeView::OnSTART)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSnakeView construction/destruction

CSnakeView::CSnakeView(){
	// TODO: add construction code here
}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSnakeView drawing

/*
	Отрисовывает все основыне геймплейны компонеты: Змейку, еду, фон, фон для счета, счет.
*/
void CSnakeView::OnDraw(CDC* pdc)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//TODO: add draw code for native data here
	CRect rect;

	GetClientRect(rect);
	SetRect(rect, 0, 0, WIDTH, HEIGHT+100);
	CBrush yellow(RGB(255, 253, 150));
	pdc->FillRect(rect, &yellow);

	CRect rect1;
	CBrush grey(RGB(88, 89, 89));
	{
		SetRect(rect1, 0, 600, WIDTH, HEIGHT+100);
		pdc->FillRect(rect1, &grey);
	}

	CBrush red(RGB(193, 0, 79));
	{
		SetRect(rect, snake.food.x - 5, snake.food.y - 5,
			snake.food.x + 5, snake.food.y + 5);
		pdc->FillRect(rect, &red);
	}

	CBrush blue(RGB(40, 186, 239));
	for (vector<CPoint>::iterator iter = snake.python.begin(); iter != snake.python.end(); ++iter) {
		SetRect(rect, (*iter).x - 5, (*iter).y - 5,
			(*iter).x + 5, (*iter).y + 5);
		pdc->FillRect(rect, &blue);
	}

	CString score;
	score.Format(_T("SCORE: %d"), (-3 + snake.python.size())*5);
	pdc->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	pdc->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	pdc->DrawText(score, -1, rect1, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
}

void CSnakeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSnakeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS

#endif
}

// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG

// CSnakeView message handlers

void CSnakeView::OnTimer(UINT_PTR nIDEvent)
{
	if (snake.move() != TRUE)
	{
		KillTimer(nIDEvent);
	}
	Invalidate();

	CView::OnTimer(nIDEvent);
}

/*
	Обработка нажатия клавишь клавиатуры и реакции главно персонажа.
*/
void CSnakeView::OnUp()
{
	if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
		snake.changeDirection(UP);
}
void CSnakeView::OnDown()
{
	if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
		snake.changeDirection(DOWN);
}
void CSnakeView::OnLeft()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(LEFT);
}
void CSnakeView::OnRight()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(RIGHT);
}

void CSnakeView::OnSTART()
{
	SetTimer(1, 100, NULL);
	srand((unsigned)time(NULL));
    snake.generateFood();
	snake.python = snake.default_state;
}

void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
		OnUp();
	if (nChar == VK_DOWN)
		OnDown();
	if (nChar == VK_LEFT)
		OnLeft();
	if (nChar == VK_RIGHT)
		OnRight();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}