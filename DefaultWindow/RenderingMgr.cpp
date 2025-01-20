#include "stdafx.h"
#include "RenderingMgr.h"

int CRenderingMgr::m_iBG_count = 0;
//int CRenderingMgr::m_GameOver_count = 0;

CRenderingMgr::CRenderingMgr()
{
}


CRenderingMgr::~CRenderingMgr()
{
}


void CRenderingMgr::Drawing_BackGround(HDC _Hdc, int _iMoveSpeed ,int  _iBG_Interval)
{

	float f_Interval_Width = (float)WINCX/ _iBG_Interval; 
	
	for (float i = 0; i < (float)WINCY / f_Interval_Width; ++i)  // 세로 나누기 가로간격
	{
		MoveToEx(_Hdc, 0,   m_iBG_count * _iMoveSpeed + i * f_Interval_Width, nullptr);
		LineTo(_Hdc, WINCX, m_iBG_count * _iMoveSpeed + i * f_Interval_Width);
	}

	for (float i = 0; i < (float)WINCX / f_Interval_Width; ++i)  // 세로 나누기 가로간격
	{
		MoveToEx(_Hdc, i * f_Interval_Width, 0, nullptr);
		LineTo(_Hdc,   i * f_Interval_Width, WINCY);
	}

	m_iBG_count++;
	if (_iMoveSpeed * m_iBG_count  > f_Interval_Width )  
		m_iBG_count = 0;



}

void CRenderingMgr::Drawing_Player(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom )
{
	HBRUSH myBrush;
	/*if (RED)
	{
		myBrush = (HBRUSH)CreateSolidBrush(RGB(0xFF, 0x00, 0X00)));
	}
	if (BLUE)
	{
		myBrush = (HBRUSH)CreateSolidBrush(RGB(0x00, 0x00, 0XFF)));
	}
	else if (PUPPLE)
	{
		myBrush = (HBRUSH)CreateSolidBrush(RGB(0x99, 0x00, 0XFF)));
	}*/
	myBrush = (HBRUSH)CreateSolidBrush(RGB(0xFF, 0x00, 0X00));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);


	float fLeft = (float)_ileft ;
	float fTop	= (float)_iTop ;
	float fRight	= (float)_iRight ;
	float fBottom	= (float)_iBottom ;



	float fWidth = abs(fLeft -fRight);
	float fHeight = abs(fTop - fBottom);
	
	Rectangle(_Hdc, fLeft, fTop,fRight, fBottom);
	Rectangle(_Hdc, fLeft - fWidth * 0.5f, fTop + fHeight * 0.5f, fLeft, fBottom + fHeight * 0.5f);
	Rectangle(_Hdc,fRight, fTop + fHeight * 0.5f,fRight + fWidth * 0.5f, fBottom + fHeight * 0.5f);
	MoveToEx(_Hdc, fLeft, fTop, nullptr);
	LineTo(_Hdc, fLeft + fWidth * 0.5f, fTop - fWidth * 0.5f * tan(PI * 60 / 180));
	LineTo(_Hdc,fRight, fTop);

	MoveToEx(_Hdc, fLeft - fWidth * 0.5f, fBottom, nullptr);
	LineTo(_Hdc, fLeft - fWidth, fTop + fHeight * 2.0l);
	LineTo(_Hdc, fLeft - fWidth * 0.5f, fTop + fHeight * 1.5l);

	MoveToEx(_Hdc,fRight + fWidth * 0.5f, fBottom, nullptr);
	LineTo(_Hdc,fRight + fWidth, fTop + fHeight * 2.0l);
	LineTo(_Hdc,fRight + fWidth * 0.5f, fTop + fHeight * 1.5l);

	SelectObject(_Hdc, oldBrush);
	DeleteObject(myBrush);

}



void CRenderingMgr::Drawing_Boss_1(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom)
{


	float fLeft = (float)_ileft;
	float fTop = (float)_iTop;
	float fRight = (float)_iRight;
	float fBottom = (float)_iBottom;

	float fWidth = abs(fLeft - fRight);
	float fHeight = abs(fTop - fBottom);
	//가로 6등분 세로 10등분	
	float fWidth_interval = fWidth * 0.333f;
	float fWidth_interval_eye = fWidth * 0.2f;
	float fHeight_interval = fHeight * 0.1f;


	Ellipse(_Hdc, fLeft - fWidth_interval * 0.5f, fTop - fWidth_interval * 0.5f , fLeft  + fWidth_interval * 0.5f, fTop + fWidth_interval * 0.5f);
	Ellipse(_Hdc, fRight - fWidth_interval * 0.5f, fTop - fWidth_interval * 0.5f, fRight + fWidth_interval * 0.5f, fTop + fWidth_interval * 0.5f);
	Ellipse(_Hdc, fLeft - fWidth_interval * 0.5f, fBottom - fWidth_interval * 0.5f, fLeft  + fWidth_interval * 0.5f, fBottom + fWidth_interval * 0.5f);
	Ellipse(_Hdc, fRight - fWidth_interval * 0.5f  , fBottom - fWidth_interval * 0.5f, fRight + fWidth_interval * 0.5f, fBottom + fWidth_interval * 0.5f);
	Rectangle(_Hdc, fLeft, fTop, fRight, fBottom);


	Rectangle(_Hdc, fLeft + fWidth_interval_eye, fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 2.0f, fTop + fWidth_interval_eye * 2.0f);
	Rectangle(_Hdc, fLeft + fWidth_interval_eye * 3.0f, fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 4.0f, fTop + fWidth_interval_eye * 2.0f);

}
void CRenderingMgr::Drawing_Boss_2(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom)
{


	float fLeft = (float)_ileft;
	float fTop = (float)_iTop;
	float fRight = (float)_iRight;
	float fBottom = (float)_iBottom;

	float fWidth = abs(fLeft - fRight);
	float fHeight = abs(fTop - fBottom);
	//가로 6등분 세로 10등분	
	float fWidth_interval = fWidth * 0.333f;
	float fWidth_interval_eye = fWidth * 0.2f;
	float fHeight_interval = fHeight * 0.1f;



	Rectangle(_Hdc, fLeft, fTop, fRight, fBottom);


	MoveToEx(_Hdc, fLeft+ fWidth_interval , fTop, nullptr);
	LineTo(_Hdc, fLeft + fWidth_interval * 1.5f, fTop - tan(PI * 60 / 180) * fWidth_interval * 0.5f);
	LineTo(_Hdc, fLeft + fWidth_interval * 2.0f, fTop);
	MoveToEx(_Hdc, fLeft + fWidth_interval, fBottom, nullptr);
	LineTo(_Hdc, fLeft + fWidth_interval * 1.5f, fBottom + tan(PI * 60 / 180) * fWidth_interval * 0.5f);
	LineTo(_Hdc, fLeft + fWidth_interval * 2.0f, fBottom);

	MoveToEx(_Hdc, fLeft  , fTop + fWidth_interval, nullptr);
	LineTo(  _Hdc, fLeft - tan(PI * 60 / 180) * fWidth_interval * 0.5f, fTop + fWidth_interval * 1.5f);
	LineTo(  _Hdc, fLeft  , fTop + fWidth_interval * 2.0f);
	MoveToEx(_Hdc, fRight , fTop + fWidth_interval, nullptr);
	LineTo(  _Hdc, fRight + tan(PI * 60 / 180) * fWidth_interval * 0.5f, fTop + fWidth_interval * 1.5f);
	LineTo(  _Hdc, fRight , fTop + fWidth_interval * 2.0f);



	Rectangle(_Hdc, fLeft + fWidth_interval_eye, fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 2.0f, fTop + fWidth_interval_eye * 2.0f);
	Rectangle(_Hdc, fLeft + fWidth_interval_eye * 3.0f, fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 4.0f, fTop + fWidth_interval_eye * 2.0f);
	//Rectangle(_Hdc, fLeft + fWidth_interval * 2.0f, fTop - fWidth_interval, fRight, fTop);

}
void CRenderingMgr::Drawing_Boss_3(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom )
{


	float fLeft				= (float)_ileft;
	float fTop				= (float)_iTop;
	float fRight			= (float)_iRight;
	float fBottom			= (float)_iBottom;

	float fWidth			= abs(fLeft - fRight);
	float fHeight			= abs(fTop - fBottom);
	//가로 6등분 세로 10등분	
	float fWidth_interval	= fWidth * 0.333f;
	float fWidth_interval_eye = fWidth * 0.2f;
	float fHeight_interval  = fHeight * 0.1f;


	Rectangle(_Hdc, fLeft, fTop, fRight, fBottom);
	Rectangle(_Hdc, fLeft, fTop - fWidth_interval, fLeft + fWidth_interval, fTop);
	Rectangle(_Hdc, fLeft + fWidth_interval * 2.0f, fTop - fWidth_interval, fRight, fTop);



	Rectangle(_Hdc, fLeft + fWidth_interval_eye       , fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 2.0f, fTop + fWidth_interval_eye * 2.0f);
	Rectangle(_Hdc, fLeft + fWidth_interval_eye * 3.0f, fTop + fWidth_interval_eye, fLeft + fWidth_interval_eye * 4.0f, fTop + fWidth_interval_eye * 2.0f);
	//Rectangle(_Hdc, fLeft + fWidth_interval * 2.0f, fTop - fWidth_interval, fRight, fTop);



}

void CRenderingMgr::Drawing_Start(HDC _Hdc)
{
	RECT rt = { 50,50,700,500 };


	LPCWSTR str2 = //TEXT("DrawText() 함수를 테스트합니다.\n")

		TEXT("Colorful 1945\n")
		TEXT("4조작품_최승준,윤동주,이현희,이준식\n")
		TEXT("<조작법> 이동-방향키:\n")
		TEXT("색전환-Z , 총알발사-Space \n")
		;
		//TEXT("    \n");


	DrawText(_Hdc, str2, -1, &rt, DT_LEFT | DT_WORDBREAK);
}

void CRenderingMgr::Drawing_GameOver(HDC _Hdc)
{
	//int I_GO_Count = 0;
	RECT rt = { 300,200,700,700 };


	LPCWSTR str2 = //TEXT("DrawText() 함수를 테스트합니다.\n")

	TEXT("Game over !\n")
	TEXT("Press any key \n")
	TEXT("to continued...  \n");


	DrawText(_Hdc, str2, -1, &rt, DT_LEFT | DT_WORDBREAK);

}

void CRenderingMgr::Shrink_Circle(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom)
{
	float fLeft = (float)_ileft;
	float fTop = (float)_iTop;
	float fRight = (float)_iRight;
	float fBottom = (float)_iBottom;

	float fWidth = abs(fLeft - fRight);

	float fShrink_interval = fWidth * 0.05f;  //20분할
	HBRUSH myBrush;
	HBRUSH oldBrush;

	for (int i = 0; i < 20; ++i)
	{
		if (!i)
		{
			myBrush = (HBRUSH)CreateSolidBrush(RGB(0x00, 0x00, 0x00)); //Black
			oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);
		}
	}

	//for(int i= 0; i<= ;++i)

	myBrush = (HBRUSH)CreateSolidBrush(RGB(0x00, 0x00, 0x00)); //Black
	oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);


	Ellipse(_Hdc, _ileft, _iTop, _iRight, _iBottom);
	
	SelectObject(_Hdc, oldBrush);
	DeleteObject(myBrush);


	myBrush = (HBRUSH)CreateSolidBrush(RGB(0x00, 0x00, 0x00));
	oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);


	Ellipse(_Hdc, _ileft, _iTop, _iRight, _iBottom);

	SelectObject(_Hdc, oldBrush);
	DeleteObject(myBrush);

}

void CRenderingMgr::Drawing_Coin(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom)
{

	float fLeft = (float)_ileft;
	float fTop = (float)_iTop;
	float fRight = (float)_iRight;
	float fBottom = (float)_iBottom;

	float fWidth = abs(fLeft - fRight);
	float fHeight = abs(fTop - fBottom);
	//가로 6등분 세로 10등분	


	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0xFF, 0xFF, 0X33));  //yellow
	HBRUSH oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);
	Ellipse(_Hdc, fLeft, fTop, fRight, fBottom);
	SelectObject(_Hdc, oldBrush);
	DeleteObject(myBrush);



	myBrush = (HBRUSH)CreateSolidBrush(RGB(0xFF, 0xFF, 0XFF));  //2nd Rect- white
	oldBrush = (HBRUSH)SelectObject(_Hdc, myBrush);
	Rectangle(_Hdc,
		fLeft + fWidth * 0.25f,
		fTop + fWidth * 0.25f,
		fRight - fHeight * 0.25f,
		fBottom - fHeight * 0.25f);
	SelectObject(_Hdc, oldBrush);
	DeleteObject(myBrush);

}
