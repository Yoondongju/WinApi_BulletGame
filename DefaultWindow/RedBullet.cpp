#include "stdafx.h"
#include "RedBullet.h"

RedBullet::RedBullet()
{
}

RedBullet::RedBullet(int _iLevel, INFO _tInfo)
{
	m_iLevel = _iLevel;
	m_tInfo = { _tInfo.fX, _tInfo.fY, 10,50 };
	m_fSpeed = 5.f;

}

RedBullet::~RedBullet()
{
}

void RedBullet::Initialize()
{
	if (m_eDir == DIRECTION::ENEMY)
	{
		m_eMyObjType = OBJECT_TYPE::OBJ_MONSTERBULLET;
		m_fSpeed *= (-1);
	}
	else
		m_eMyObjType = OBJECT_TYPE::OBJ_BULLET;
}

int RedBullet::Update()
{
	switch (m_iLevel)
	{
	case 1:
		m_tInfo.fY -= m_fSpeed;
		break;
	case 2:
		m_tInfo.fY -= m_fSpeed;
		m_tInfo.fX += 5;
		break;
	case 3:
		m_tInfo.fY -= m_fSpeed;
		m_tInfo.fX -= 5;
		break;
	default:
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void RedBullet::Late_Update()
{
	__super::Late_Update();
}

void RedBullet::Render(HDC hDC)
{
	if (m_eDir == DIRECTION::ENEMY)
	{
		m_eColor = COLORSTATE::COLOR_END;
	}

	// m_eColor Owner의 색을 따라가야함
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void RedBullet::Release()
{
}
