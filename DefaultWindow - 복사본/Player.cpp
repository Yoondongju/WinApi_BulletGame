#include "stdafx.h"
#include "Player.h"

#include "MainGame.h"
#include "CScene.h"

#include "CKeyMgr.h"

#include "CBullet.h"
#include "CPlayerShield.h"

float CPlayer::m_fCurScore = 0.f;

CPlayer::CPlayer()	
{

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo  = { WINCX / 2.f, WINCY / 2.f, 70.f, 70.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	Key_Input();
	__super::Update_Rect();

	++m_fCurScore;
	return 0;
}

void CPlayer::Late_Update()
{

}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY,nullptr);
	float f =  m_tInfo.fCY ;
	LineTo(hDC, m_tInfo.fX + f * cosf(m_fDir), m_tInfo.fY - (f * sinf(m_fDir)));
	
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{

	if ( CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD
		|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD
		|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD
		|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fDir);
		m_tInfo.fY -= m_fSpeed * sinf(m_fDir);
	}
		
	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::F) == KEY_STATE::HOLD)   // 각도 방향 조절
	{
		if (m_fDir >= 2 * PI)
			m_fDir = PI / 2.f;
		else
			m_fDir -= 0.1f;
	}
		
	
	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::BULLET).push_back(CreateBullet(m_fDir));
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::G) == KEY_STATE::TAP)
	{
		CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::PLAYER_SHIELD).push_back(CreateShield(m_fDir));
	}
	
}

CObj* CPlayer::CreateBullet(float _f)
{
	CObj* pBullet = new CBullet(this);
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_fDir(_f);
	pBullet->Initialize();

	

	return pBullet;
}

CObj* CPlayer::CreateShield(float _f)
{
	CObj* pPlayerShield = new CPlayerShield;
	pPlayerShield->Set_Pos(0.f,0.f);      // 의미가없음 어짜피 Shield 업뎃에서 위치 계속 갱신해줌     
	pPlayerShield->Set_fDir(_f);
	pPlayerShield->Initialize();
	static_cast<CPlayerShield*>(pPlayerShield)->SetOwner(this);

	return pPlayerShield;
}
