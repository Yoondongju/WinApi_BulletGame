#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CEnemy::CEnemy() : m_pBullet(nullptr)
{
}

CEnemy::~CEnemy()
{
}

CObj* CEnemy::Create_Bullet(DIRECTION eDir)
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Dir(eDir);

	return pBullet;
}
