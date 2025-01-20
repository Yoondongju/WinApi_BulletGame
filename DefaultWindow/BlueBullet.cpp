#include "stdafx.h"
#include "BlueBullet.h"

BlueBullet::BlueBullet()
{
}


BlueBullet::BlueBullet(int _iLevel, INFO _tInfo)
{
	m_iLevel = _iLevel;
	m_tInfo = { _tInfo.fX, _tInfo.fY, 30.f,30.f };
	m_fSpeed = 5.f;
}

BlueBullet::~BlueBullet()
{
}

void BlueBullet::Initialize()
{
	if (m_eDir == DIRECTION::ENEMY)
	{
		m_eMyObjType = OBJECT_TYPE::OBJ_MONSTERBULLET;
		m_fSpeed *= (-1);
	}
	else
		m_eMyObjType = OBJECT_TYPE::OBJ_BULLET;
}

int BlueBullet::Update()
{
	m_fDir += 10;
	switch (m_iLevel)
	{
	case 1:
		m_tInfo.fY -= m_fSpeed;
		m_tInfo.fX += m_fSpeed * cos(m_fDir * 3.14 / 180);
		break;
	case 2:
		m_tInfo.fY -= m_fSpeed;
		m_tInfo.fX -= m_fSpeed * cos(m_fDir * 3.14 / 180);
		break;
	case 3:
		m_tInfo.fY -= m_fSpeed;   //player 스피드 양수니까 위로 가는거맞고 몬스터는 이니셜에서
		break;
	default:
		break;
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void BlueBullet::Late_Update()
{
	__super::Late_Update();
}

void BlueBullet::Render(HDC hDC)
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

void BlueBullet::Release()
{
}