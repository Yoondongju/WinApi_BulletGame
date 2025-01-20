#include "stdafx.h"

#include "EasyMonster.h"
#include "CBullet.h"

#include "MainGame.h"
#include "CScene.h"

#include "RenderingMgr.h"

#include "CItem.h"

CEasyMonster::CEasyMonster()
{
}

CEasyMonster::~CEasyMonster()
{
	Release();
}

void CEasyMonster::Initialize()
{
	m_vXY = { {200.f,-100.f},{400.f,-100.f},{600.f,-100.f}}; // 생성위치 
	m_tInfo = { 0, 0, 50.f, 50.f };
	m_MvRange = { 100, 50 };								 // 이동범위 Y론 이동안함
	m_fSpeed = 3.f;
	m_iAttackCycle = 20;									 // 공격 주기
	m_iHp = 100;
	m_iMaxHp = m_iHp;
	m_iLevel = 1;

	m_iAttackInfo = 5;
	m_MvY = 50.f;

	Set_RandomColor();
}

int CEasyMonster::Update()
{
	static int s_iAttackCount = 0;

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fY <= m_MvY) //일정거리까지 앞으로 나옴
	{
		m_tInfo.fX += 0.7f * abs(m_fSpeed) * (m_iIdx - 1);
		m_tInfo.fY += abs(m_fSpeed);

		if (m_tInfo.fX == WINCX * 0.5)
		{
			m_fDir = 90;
		}
		else
			m_fDir = atan((m_tInfo.fX - WINCX * 0.5) / 300);
	}
	else                    //이동패턴
	{
		m_fDir += 0.1;
		m_tInfo.fY += 10 * sin(m_fDir);
		m_tInfo.fX += 20 * cos(m_fDir);
	}
	if (s_iAttackCount++ % m_iAttackCycle == 0) 
	{
		switch (m_iLevel)
		{
		case 3:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 3,m_iAttackInfo));

		case 2:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 2, m_iAttackInfo));

		case 1:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 1, m_iAttackInfo));
			break;
		default:
			break;
		}
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CEasyMonster::Late_Update()
{
	//여기에 이동패턴 구현
	if (m_vXY[m_iIdx].first - m_MvRange.first >= m_tRect.left || m_vXY[m_iIdx].first + m_MvRange.first <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CEasyMonster::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	CRenderingMgr::Drawing_Boss_1(hDC,
		m_tRect.left
		, m_tRect.top
		, m_tRect.right
		, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}


void CEasyMonster::Release()
{
	CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::ITEM).push_back(CreateItem());
}
