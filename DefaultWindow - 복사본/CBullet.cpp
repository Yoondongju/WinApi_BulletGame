#include "stdafx.h"
#include "CBullet.h"

CBullet::CBullet(CObj* _pOnwer)
	:m_pOwner(nullptr)
{
	m_pOwner = _pOnwer;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{		
	m_tInfo.fX += m_fSpeed * cosf(m_fDir);
	m_tInfo.fY -= m_fSpeed * sinf(m_fDir);
	
	Update_Rect();
	
	return 0;
}

void CBullet::Late_Update()
{
	if (m_tInfo.fX <= 0
		|| m_tInfo.fX >= WINCX
		|| m_tInfo.fY <= 0
		|| m_tInfo.fY >= WINCY)
	{
		m_bDead = true;
	}

}

void CBullet::Render(HDC hDC)
{
	Ellipse(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

}

void CBullet::Release()
{
	
}

void CBullet::CollideCheckBox()
{
	
}
