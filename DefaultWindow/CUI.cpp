#include "stdafx.h"
#include "CUI.h"

#include "MainGame.h"
#include "CScene.h"

CUI::CUI()
    :m_fCount(1.f)
    , m_pPlayer(nullptr)   
{
    m_eMyObjType = OBJECT_TYPE::UI;
}


CUI::~CUI()
{
}

void CUI::Initialize()
{
    m_pPlayer = static_cast<CPlayer*>(CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::PLAYER).front());

  

    m_tInfo.fX = 100;
    m_tInfo.fY = WINCY - 50;

    m_tInfo.fCX = 200;
    m_tInfo.fCY = 30;
}

int CUI::Update()
{

    __super::Update_Rect();

    return 0;
}

void CUI::Late_Update()
{

}

void CUI::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // 하얀거

    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 0, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    if (m_tRect.right - m_fCount <= m_tRect.left)
        m_fCount = 0;
    
    int iPlayerMaxHp = m_pPlayer->Get_MaxHp();
    int iPlayerHp = m_pPlayer->Get_Hp(); // 1000이고 
   
    int f = m_tInfo.fCX / iPlayerMaxHp; // 비율적 차이가 f배 나는것
    m_fCount = (iPlayerMaxHp - iPlayerHp); // 차이값
    
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - (f * m_fCount), m_tRect.bottom); // 빨간거

    SelectObject(hDC, oldBrush);	  // 다쓰고 난후 처리작업
    DeleteObject(myBrush);			  // 다쓰고 난후 처리작업

    TCHAR	szBuff[32] = L"";
    swprintf_s(szBuff, L"Player_HP");

    
    TextOut(hDC, m_tInfo.fX-70, m_tInfo.fY-13, szBuff, lstrlen(szBuff));
}

void CUI::Release()
{

}
