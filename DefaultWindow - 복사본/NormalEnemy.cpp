#include "stdafx.h"
#include "NormalEnemy.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CNormalEnemy::CNormalEnemy()
{
}

CNormalEnemy::~CNormalEnemy()
{
	Release();
}

void CNormalEnemy::Initialize()
{
	m_tInfo = { 200.f, 200.f, 50.f, 50.f };
	m_fSpeed = 3.f;
	m_iAttackCycle = 10;
	m_iHp = 100;
}

int CNormalEnemy::Update()
{
	static int s_iAttackCount = 0;

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fY <= 50.f) //일정거리까지 앞으로 나옴
		m_tInfo.fY += m_fSpeed;
	else                    //이동패턴
		m_tInfo.fX += m_fSpeed;

	if (s_iAttackCount++ % m_iAttackCycle == 0)
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWN));
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNLEFT));
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNormalEnemy::Late_Update()
{
	//여기에 이동패턴 구현
	if (0 >= m_tRect.left || WINCX <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CNormalEnemy::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CNormalEnemy::Release()
{
}
