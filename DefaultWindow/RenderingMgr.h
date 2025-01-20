#pragma once

#include "Obj.h"

class CRenderingMgr
{
public:
	CRenderingMgr();
	~CRenderingMgr();

public:
	static void Drawing_BackGround(HDC _Hdc, int _iMoveSpeed, int  _iBG_Interval);
	static void Drawing_Player(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);

	static void Drawing_Boss_1(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);

	static void Drawing_Boss_2(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);
	static void Drawing_Boss_3(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);
	static void Drawing_GameOver(HDC _Hdc);
	static void Drawing_Start(HDC _Hdc);
	static void Shrink_Circle(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);  //ÆøÅº°ü·ÃÇÔ¼ö
	static void Drawing_bomb(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);   //ÆøÅºÀç»ýÇÔ¼ö

	static void Drawing_Coin(HDC _Hdc, int _ileft, int _iTop, int _iRight, int _iBottom);

private:
	static int m_iBG_count;
	//static int m_GameOver_count;

};