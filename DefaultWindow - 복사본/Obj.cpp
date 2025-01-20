#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f)
	, m_bDead(false)
	, m_fDir(PI/2.f)
	, m_bCollision(false)
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
