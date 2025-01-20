#include "stdafx.h"
#include "PurpleBullet.h"

PurpleBullet::PurpleBullet()
{
}

PurpleBullet::PurpleBullet(int _iLevel, INFO _tInfo)
{
    m_iLevel = _iLevel;
	switch (_iLevel)
	{
	case 3:
		m_tInfo = { _tInfo.fX - 100, _tInfo.fY, 50,50 };
		break;
	case 2:
		m_tInfo = { _tInfo.fX + 100, _tInfo.fY, 50,50 };
		break;
	case 1:
		m_tInfo = { _tInfo.fX, _tInfo.fY, 50,50 };
		break;
	default:
		break;
	}

	m_fSpeed = 4.f;


}

PurpleBullet::~PurpleBullet()
{
}

void PurpleBullet::Initialize()
{
	m_fVec[0] = m_tPlayerInfo.fX;
	m_fVec[1] = m_tPlayerInfo.fY;
	if (m_eDir == DIRECTION::ENEMY)
	{
		m_eMyObjType = OBJECT_TYPE::OBJ_MONSTERBULLET;
		m_fSpeed *= (-1);
	}
	else
		m_eMyObjType = OBJECT_TYPE::OBJ_BULLET;
}

int PurpleBullet::Update()
{
	switch (m_iLevel)
	{
	case 1:
		m_tInfo.fY -= m_fSpeed;
		break;
	case 2:
		m_tInfo.fY -= m_fSpeed;
		break;
	case 3:
		m_tInfo.fY -= m_fSpeed;
		break;
	default:
		break;
	}

	if (m_eDir == DIRECTION::ENEMY)
		m_tInfo.fX -= m_fVec[0] * m_fSpeed / m_fVec[1];
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void PurpleBullet::Late_Update()
{
	__super::Late_Update();
}

void PurpleBullet::Render(HDC hDC)
{
	if (m_eDir == DIRECTION::ENEMY)
	{
		m_eColor = COLORSTATE::COLOR_END;
	}

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void PurpleBullet::Release()
{
}
