#include "stdafx.h"
#include "Player.h"

#include "MainGame.h"
#include "CScene.h"

#include "CKeyMgr.h"

#include "CBullet.h"
#include "CPlayerShield.h"

#include "BlueBullet.h"
#include "PurpleBullet.h"
#include "RedBullet.h"

float CPlayer::m_fCurScore = 0.f;

CPlayer::CPlayer()
	: iTypeNum(0)
	, m_fFeverGauge(0.f)
	, m_bInvincibility(false)
	, m_dwFeverTime(GetTickCount())
	, m_pPlayerShield(nullptr)
{
	m_fDir = PI / 4.f;
	m_eMyObjType = OBJECT_TYPE::PLAYER;
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo  = { WINCX / 2.f, WINCY / 2.f, 30.f, 30.f };
	m_fSpeed = 10.f;

	m_iHp = 200;
	m_iMaxHp = m_iHp;

	m_iAttackInfo = 10;
}

int CPlayer::Update()
{
	if (0 >= m_iHp)
		return PLAYER_DIE;

	Key_Input();
	__super::Update_Rect();

	++m_fCurScore;
	return 0;
}

void CPlayer::Late_Update()
{
	if (m_bInvincibility)
	{
		bool static bCheck = false;
		if (!bCheck)
		{
			m_dwFeverTime = GetTickCount();
			bCheck = true;
		}
		
		if (m_dwFeverTime + 3000 < GetTickCount())
		{
			FeverOut();
			m_dwFeverTime = GetTickCount();
			bCheck = false;
		}
	}

	if (m_fFeverGauge >= MAXFEVER)
		m_fFeverGauge = MAXFEVER;
	else
	{
		if(!m_bInvincibility)   // 피버상태가 아닐때만
			m_fFeverGauge += 0.5;
	}
		
}

void CPlayer::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);



	float fLeft = (float)m_tRect.left;
	float fTop = (float)m_tRect.top;
	float fRight = (float)m_tRect.right;
	float fBottom = (float)m_tRect.bottom;



	float fWidth = abs(fLeft - fRight);
	float fHeight = abs(fTop - fBottom);

	Rectangle(hDC, fLeft, fTop, fRight, fBottom);
	Rectangle(hDC, fLeft - fWidth * 0.5f, fTop + fHeight * 0.5f, fLeft, fBottom + fHeight * 0.5f);
	Rectangle(hDC, fRight, fTop + fHeight * 0.5f, fRight + fWidth * 0.5f, fBottom + fHeight * 0.5f);
	MoveToEx(hDC, fLeft, fTop, nullptr);
	LineTo(hDC, fLeft + fWidth * 0.5f, fTop - fWidth * 0.5f * tan(PI * 60 / 180));
	LineTo(hDC, fRight, fTop);

	MoveToEx(hDC, fLeft - fWidth * 0.5f, fBottom, nullptr);
	LineTo(hDC, fLeft - fWidth, fTop + fHeight * 2.0l);
	LineTo(hDC, fLeft - fWidth * 0.5f, fTop + fHeight * 1.5l);

	MoveToEx(hDC, fRight + fWidth * 0.5f, fBottom, nullptr);
	LineTo(hDC, fRight + fWidth, fTop + fHeight * 2.0l);
	LineTo(hDC, fRight + fWidth * 0.5f, fTop + fHeight * 1.5l);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CPlayer::Render_Collision(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::FeverIn()
{
	m_fSpeed = 20.f;
	m_bInvincibility = true;

	m_fFeverGauge = 0.f;
}

void CPlayer::FeverOut()
{
	m_fSpeed = 10.f;
	m_bInvincibility = false;
}

void CPlayer::Key_Input()
{
	

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
		m_tInfo.fY -= m_fSpeed * sinf(m_fDir);

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
		m_tInfo.fY += m_fSpeed * sinf(m_fDir);

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
		m_tInfo.fX -= m_fSpeed * cosf(m_fDir);

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
		m_tInfo.fX += m_fSpeed * cosf(m_fDir);

		
	//if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::F) == KEY_STATE::HOLD)   // 각도 방향 조절
	//{
	//	if (m_fDir >= 2 * PI)
	//		m_fDir = PI / 2.f;
	//	else
	//		m_fDir -= 0.1f;
	//}
		
	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::G) == KEY_STATE::TAP)
	{
		if(!m_pPlayerShield)   // Shield는 한개만 가질수잇음
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::PLAYER_SHIELD).push_back(CreateShield(m_fDir));
		
	}

	
	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		switch (m_iLevel) // BRP
		{
		case 3: //3랩부터 1랩까지 다 실행
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_BULLET).push_back(CreateBullet(iTypeNum, 3));

		case 2:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_BULLET).push_back(CreateBullet(iTypeNum, 2));

		case 1:
			CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::OBJ_BULLET).push_back(CreateBullet(iTypeNum, 1));

		default:
			break;
		}
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
	{
		iTypeNum += 1;
		iTypeNum %= 3;
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::X) == KEY_STATE::TAP)
	{
		switch (m_eColor)  // 여기서 Player의 색깔이 바뀌고 총알 색깔도 맞춰서 바껴야함
		{				   // Bullet 색은 Bullet에서 Owner를 통해 바꿔줄것임
		case COLORSTATE::RED:
			m_eColor = COLORSTATE::BLUE; 
			break;
		case COLORSTATE::BLUE:
			m_eColor = COLORSTATE::PURPLE;
			break;
		case COLORSTATE::PURPLE:
			m_eColor = COLORSTATE::RED;
			break;
		}
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::C) == KEY_STATE::TAP)
	{
		if (m_fFeverGauge >= MAXFEVER)
		{
			FeverIn();
		}
	}

	
	
}

CObj* CPlayer::CreateBullet(int _iTypeNum, int _iLevel)
{
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
		pBullet->Initialize();
		pBullet->Set_Color(m_eColor);
		pBullet->SetAtaackInfo(m_iAttackInfo);
		dynamic_cast<CBullet*>(pBullet)->SetOwner(this);
	}


	return pBullet;
}

CObj* CPlayer::CreateShield(float _f)
{
	CObj* pPlayerShield = new CPlayerShield;
	pPlayerShield->Set_Pos(0.f,0.f);      // 의미가없음 어짜피 Shield 업뎃에서 위치 계속 갱신해줌     
	pPlayerShield->Set_fDir(_f);
	m_pPlayerShield = pPlayerShield;					// Player의 멤버로 얘를 알고있어야함
	static_cast<CPlayerShield*>(pPlayerShield)->SetOwner(this);
	pPlayerShield->Initialize();

	return pPlayerShield;
}
