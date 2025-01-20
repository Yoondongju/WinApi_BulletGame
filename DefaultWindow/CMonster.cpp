#include "stdafx.h"

#include "MainGame.h"
#include "CMonster.h"

#include "CBullet.h"
#include "Player.h"

#include "BlueBullet.h"
#include "PurpleBullet.h"
#include "RedBullet.h"

#include "CItem.h"


CMonster::CMonster()
	:m_pBullet(nullptr)
{
	m_eMyObjType = OBJECT_TYPE::MONSTER;
	m_vXY.reserve(5);
}

CMonster::CMonster(int _iIdx)
{
	m_vXY.reserve(5);
}

CMonster::~CMonster()
{

}

void CMonster::Initialize()
{
	m_eColor = COLORSTATE::COLOR_END;
}

void CMonster::Initialize(int _iIdx)
{
	m_tInfo.fX = m_vXY[_iIdx].first;
	m_tInfo.fY = m_vXY[_iIdx].second;
}	


CObj* CMonster::Create_Bullet(int _iTypeNum, int _iLevel, int _iAttack)
{
	// Player가 쏘는 총알은 승준이 3개 파생클래스로 구현하고잇음
	// Mon이 쏘는 총알은 어떻게 처리함?

	CObj* pBullet = nullptr;
	switch (_iTypeNum)
	{
	case (int)DIRECTION::BLUE:
		pBullet = new BlueBullet(_iLevel, m_tInfo);
		break;
	case (int)DIRECTION::RED:
		pBullet = new RedBullet(_iLevel, m_tInfo);
		break;
	case (int)DIRECTION::PURPLE:
		pBullet = new PurpleBullet(_iLevel, m_tInfo);
		break;
	default:
		break;
	}

	if (pBullet != nullptr)
	{
		pBullet->Set_eDir(DIRECTION::ENEMY);
		pBullet->m_tPlayerInfo = m_tPlayerInfo;
		pBullet->Initialize();
		pBullet->Set_Color(m_eColor);
		pBullet->SetAtaackInfo(_iAttack);
		dynamic_cast<CBullet*>(pBullet)->SetOwner(this);
	}
	
	return pBullet;
}

int CMonster::Update()
{

    return 0;
}


void CMonster::Late_Update()
{
	


}

void CMonster::Render(HDC hDC)
{
	

}

void CMonster::Render_Collision(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}



void CMonster::Release()
{


}

CObj* CMonster::CreateItem()
{
	CObj* pItem = new CItem;
	pItem->Set_Pos(m_tInfo.fX,m_tInfo.fY); 
	pItem->Set_Size(20.f, 20.f);
	pItem->Initialize();

	return pItem;
}


void CMonster::Set_RandomColor()
{
	int _color = rand() % 3;
	switch (_color)
	{
	case 0:
		m_eColor = COLORSTATE::RED;
		break;
	case 1:
		m_eColor = COLORSTATE::BLUE;
		break;
	case 2:
		m_eColor = COLORSTATE::PURPLE;
		break;
	default:
		m_eColor = COLORSTATE::RED;
		break;
	}
}




