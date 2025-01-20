#include "stdafx.h"
#include "CPlayerShield.h"
#include "Player.h"

CPlayerShield::CPlayerShield()
    :m_pOwner(nullptr)
{
}

CPlayerShield::~CPlayerShield()
{
    CObj* pOwnerShield = m_pOwner->GetMyShield();
    if(pOwnerShield)
        pOwnerShield = nullptr;

    m_pOwner = nullptr;
}

void CPlayerShield::Initialize()
{
    m_tInfo.fCX = 25.f;
    m_tInfo.fCY = 25.f;

    m_fSpeed = 1.f;

    m_eMyObjType = OBJECT_TYPE::PLAYER_SHIELD;
   
}

int CPlayerShield::Update()
{
    m_eColor = m_pOwner->Get_Color();
    m_tInfo.fX = m_pOwner->GetInfo().fX + (70.f  * cosf(m_fDir));
    m_tInfo.fY = m_pOwner->GetInfo().fY - (70.f  * sinf(m_fDir));

    // m_fDir // Obj생성자에서 90도 유지후 Player의 F키를 통해 Player 각도가 변하고 그때 Create했을때의 각도가 담긴 상태임
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
    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(ChangeColor(m_eColor));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

    Ellipse(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);

    SelectObject(hDC, oldBrush);
    DeleteObject(myBrush);
}

void CPlayerShield::Render_Collision(HDC hDC)
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
