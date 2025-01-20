#include "stdafx.h"
#include "BossMonster.h"

#include "CBullet.h"

#include "MainGame.h"
#include "CScene.h"


#include "RenderingMgr.h"

CBossMonster::CBossMonster()
{
}

CBossMonster::~CBossMonster()
{
	Release();
}

void CBossMonster::Initialize()
{
	m_vXY = { {200.f,-100.f},{400.f,-100.f},{600.f,-100.f} };
	m_tInfo = { 0.f, 0.f, 100.f, 100.f };
	m_MvRange = { 200, 50 };
	m_fSpeed = 3.f;
	m_iAttackCycle = 10;			//공격주기
	m_iAttackChangeCycle = 5;		//공격패턴변경주기
	m_iHp = 2000;

	m_iMaxHp = m_iHp;
	m_iAttackInfo = 20;
	m_eMyObjType = OBJECT_TYPE::BOSS;

	Set_RandomColor();
}

int CBossMonster::Update()
{
	static int s_iAttackCount = 0;
	static int s_iAttackPattern = 0;

	if (m_bDead)
		return OBJ_DEAD;
	if (m_tInfo.fY <= 70.f) //일정거리까지 앞으로 나옴
		m_tInfo.fY += abs(m_fSpeed);
	else                    //이동패턴
	{
		m_tInfo.fX += m_fSpeed;
		m_bCanShowEnemy = true; //이거 추가 
	}

	if (++s_iAttackCount % m_iAttackCycle == 0)
	{
		if (s_iAttackCount % (m_iAttackCycle * m_iAttackChangeCycle) == 0)
		{
			s_iAttackPattern++; //공격패턴 바뀌고
			Set_RandomColor();	//보스 색 바뀜
		}
		switch (s_iAttackPattern % 2)
		{
		case 0:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)DIRECTION::BLUE, 1, m_iAttackInfo));
			break;
		case 1:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_MONSTERBULLET).push_back(Create_Bullet((int)DIRECTION::BLUE, 1, m_iAttackInfo));
			break;
		}
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update()
{
	//여기에 이동패턴 구현
	if (m_vXY[m_iIdx].first - m_MvRange.first >= m_tRect.left || m_vXY[m_iIdx].first + m_MvRange.first <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CBossMonster::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	
	CRenderingMgr::Drawing_Boss_3(hDC,
		m_tRect.left
		, m_tRect.top
		, m_tRect.right
		, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CBossMonster::Release()
{
}

void CBossMonster::SetAttackPattern(int _attackPattern) //여따가 공격패턴 구현
{
	//switch (_attackPattern)
	//{
	//case 0:
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWN));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNLEFT));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNRIGHT));
	//	break;
	//case 1:
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNLEFT));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNRIGHT));
	//	break;
	//case 2:
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, LEFT));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, RIGHT));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWN));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNLEFT));
	//	m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DOWNRIGHT));
	//	break;
	//}
}
