#include "stdafx.h"
#include "HardMonster.h"

#include "CBullet.h"

#include "MainGame.h"
#include "CScene.h"


#include "RenderingMgr.h"

CHardEnemy::CHardEnemy()
{
}

CHardEnemy::~CHardEnemy()
{
	Release();
}

void CHardEnemy::Initialize()
{
	m_vXY = { {200.f,-100.f},{400.f,-100.f},{600.f,-100.f}};
	m_tInfo = { 0.f, 0.f, 70.f, 70.f };
	m_MvRange = { 100, 50 };
	m_fSpeed = 3.f;
	m_iAttackCycle = 100;	//공격주기
	m_iHp = 300;
	m_iMaxHp = m_iHp;
	m_iLevel = 3;

	m_iAttackInfo = 15;

	Set_RandomColor();
}

int CHardEnemy::Update()
{
	static int s_iAttackCount = 0;

	if (m_bDead)
		return OBJ_DEAD;
	if (m_tInfo.fY <= 50.f) //일정거리까지 앞으로 나옴
	{
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

		m_fDir += 1;
		m_tInfo.fY += m_fSpeed * sin(m_fDir * 3.14 / 180);
		m_tInfo.fX += m_fSpeed * cos(m_fDir * 3.14 / 180);
	}

	if (s_iAttackCount++ % m_iAttackCycle == 0)
	{
		switch (m_iLevel)
		{
		case 3:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 3, m_iAttackInfo));

		case 2:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 2, m_iAttackInfo));

		case 1:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 1,m_iAttackInfo));
			break;
		default:
			break;
		}
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CHardEnemy::Late_Update()
{
	//여기에 이동패턴 구현
	if (m_vXY[m_iIdx].first - m_MvRange.first >= m_tRect.left || m_vXY[m_iIdx].first + m_MvRange.first <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CHardEnemy::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	
	CRenderingMgr::Drawing_Boss_2(hDC,
		m_tRect.left
		, m_tRect.top
		, m_tRect.right
		, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CHardEnemy::Release()
{
	CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::ITEM).push_back(CreateItem());
}
