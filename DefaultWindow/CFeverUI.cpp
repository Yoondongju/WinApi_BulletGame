#include "stdafx.h"
#include "CFeverUI.h"

#include "MainGame.h"
#include "CScene.h"


CFeverUI::CFeverUI()
    :m_fCount(1.f)
{
}

CFeverUI::~CFeverUI()
{
}

void CFeverUI::Initialize()
{
    m_pPlayer = static_cast<CPlayer*>(CMainGame::CreateSingleTonInst()->GetCurScene()->GetTypeObj(OBJECT_TYPE::PLAYER).front());

    m_tInfo.fX = 100;
    m_tInfo.fY = WINCY - 20;

    m_tInfo.fCX = 200;
    m_tInfo.fCY = 30;
}

int CFeverUI::Update()
{
    __super::Update_Rect();

	return 0;
}

void CFeverUI::Late_Update()
{
}

void CFeverUI::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); // �Ͼ��

    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    
    float fFever = m_pPlayer->GetFeverGauge();
    float f = (m_tInfo.fCX / MAXFEVER);


    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right - f*(MAXFEVER - fFever), m_tRect.bottom); // ������

    SelectObject(hDC, oldBrush);	  // �پ��� ���� ó���۾�
    DeleteObject(myBrush);			  // �پ��� ���� ó���۾�

    TCHAR	szBuff[32] = L"";
    swprintf_s(szBuff, L"Player_FeverGauge");


    TextOut(hDC, m_tInfo.fX - 70, m_tInfo.fY-13, szBuff, lstrlen(szBuff));
}

void CFeverUI::Release()
{
}
