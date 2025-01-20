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
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // �Ͼ��

    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 0, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    if (m_tRect.right - m_fCount <= m_tRect.left)
        m_fCount = 0;
    
    int iPlayerMaxHp = m_pPlayer->Get_MaxHp();
    int iPlayerHp = m_pPlayer->Get_Hp(); // 1000�̰� 
   
    int f = m_tInfo.fCX / iPlayerMaxHp; // ������ ���̰� f�� ���°�
    m_fCount = (iPlayerMaxHp - iPlayerHp); // ���̰�
    
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - (f * m_fCount), m_tRect.bottom); // ������

    SelectObject(hDC, oldBrush);	  // �پ��� ���� ó���۾�
    DeleteObject(myBrush);			  // �پ��� ���� ó���۾�

    TCHAR	szBuff[32] = L"";
    swprintf_s(szBuff, L"Player_HP");

    
    TextOut(hDC, m_tInfo.fX-70, m_tInfo.fY-13, szBuff, lstrlen(szBuff));
}

void CUI::Release()
{

}
