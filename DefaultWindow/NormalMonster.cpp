#include "stdafx.h"
#include "NormalMonster.h"

#include "CBullet.h"

#include "MainGame.h"
#include "CScene.h"


#include "RenderingMgr.h"

CNormalMonster::CNormalMonster()
{
}

CNormalMonster::~CNormalMonster()
{
	Release();
}

void CNormalMonster::Initialize()
{
	m_vXY = { {200.f,-100.f},{400.f,-100.f},{600.f,-100.f} };
	m_tInfo = { 0, 0, 50.f, 50.f };
	m_MvRange = { 100, 50 };
	m_fSpeed = 3.f;
	m_iAttackCycle = 20;
	m_iHp = 200;
	m_iMaxHp = m_iHp;
	m_iLevel = 2;
	m_iAttackInfo = 10;

	Set_RandomColor();
}

int CNormalMonster::Update()
{
	static int s_iAttackCount = 0;

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fY <= 50.f) //일정거리까지 앞으로 나옴
		m_tInfo.fY += abs(m_fSpeed);
	else                    //이동패턴
		m_tInfo.fX += m_fSpeed;

	if (s_iAttackCount++ % m_iAttackCycle == 0)
	{
		switch (m_iLevel)
		{
		case 3:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)m_eColor, 3, m_iAttackInfo));

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

void CNormalMonster::Late_Update()
{
	//여기에 이동패턴 구현
	if (m_vXY[m_iIdx].first - m_MvRange.first >= m_tRect.left || m_vXY[m_iIdx].first + m_MvRange.first <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CNormalMonster::Render(HDC hDC)
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

void CNormalMonster::Release()
{
	CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::ITEM).push_back(CreateItem());
}
