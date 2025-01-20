#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f)
	, m_bDead(false)
	, m_fDir(0.f)
	, m_bCollision(false)
	, m_iLevel(1)
	, m_eColor(COLORSTATE::RED)

{
	ZeroMemory(m_szName, sizeof(m_szName));
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::CObj(const char* _pName)
{
	strcpy_s(m_szName, sizeof(m_szName), _pName);
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

}

COLORREF CObj::ChangeColor(COLORSTATE _color)
{
	m_eColor = _color;
	switch (m_eColor)
	{
	case COLORSTATE::RED:
		return RGB(200, 0, 0);
	case COLORSTATE::BLUE:
		return RGB(0, 0, 200);
	case COLORSTATE::PURPLE:
		return RGB(200, 0, 250);
	case COLORSTATE::COLOR_END:
		return RGB(0, 0, 0);
	}
}
