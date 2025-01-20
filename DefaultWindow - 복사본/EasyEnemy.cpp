#include "stdafx.h"
#include "EasyEnemy.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CEasyEnemy::CEasyEnemy()
{
}

CEasyEnemy::~CEasyEnemy()
{
	Release();
}

void CEasyEnemy::Initialize()
{
	m_tInfo = { 200.f, 200.f, 50.f, 50.f };
	m_fSpeed = 3.f;
	m_iAttackCycle = 20;
	m_iHp = 100;
}

int CEasyEnemy::Update()
{
	static int s_iAttackCount = 0;

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fY <= 50.f) //�����Ÿ����� ������ ����
		m_tInfo.fY += m_fSpeed;
	else                    //�̵�����
		m_tInfo.fX += m_fSpeed;

	if (s_iAttackCount++ % m_iAttackCycle == 0) 
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWN)); //���������� �����Ǵ� �κ� (���� ������ bullet �ȿ���)
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CEasyEnemy::Late_Update()
{
	//���⿡ �̵����� ����
	if (0 >= m_tRect.left || WINCX <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CEasyEnemy::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CEasyEnemy::Release()
{
}
