#include "stdafx.h"
#include "CPlayerShield.h"

CPlayerShield::CPlayerShield()
    :m_pOwner(nullptr)
{
}

CPlayerShield::~CPlayerShield()
{
}

void CPlayerShield::Initialize()
{
    m_tInfo.fCX = 25.f;
    m_tInfo.fCY = 25.f;

    m_fSpeed = 1.f;
}

int CPlayerShield::Update()
{
    m_tInfo.fX = m_pOwner->GetInfo().fX + (70.f  * cosf(m_fDir));
    m_tInfo.fY = m_pOwner->GetInfo().fY - (70.f  * sinf(m_fDir));

    // m_fDir // Obj�����ڿ��� 90�� ������ Player�� FŰ�� ���� Player ������ ���ϰ� �׶� Create�������� ������ ��� ������
    if (m_fDir >= 2 * PI)
        m_fDir = PI / 2.f;
    else
        m_fDir -= m_fSpeed * 0.1f;

    __super::Update_Rect();

    return 0;
}


void CPlayerShield::Late_Update()
{
}


void CPlayerShield::Render(HDC hDC)
{
    Ellipse(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);

}


void CPlayerShield::Release()
{

}
