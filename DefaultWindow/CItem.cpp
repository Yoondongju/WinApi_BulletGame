#include "stdafx.h"
#include "CItem.h"
#include <time.h> 

#include "RenderingMgr.h"

CItem::CItem()
{
    
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
    fDistance = 70.f;

    vTargetPos.fX = m_tInfo.fX + fDistance;
    vTargetPos.fY = m_tInfo.fY + fDistance;   // 내가 도달할 좌표 설정 해주고


    m_tInfo.fY = m_tInfo.fY + fDistance;

    vConstPos.fX = m_tInfo.fX;
    vConstPos.fY = m_tInfo.fY;

    srand(time(NULL));
    iDir = rand() % 2;
    m_fDir = 90.f;

    m_eColor = (COLORSTATE)RGB(100, 150, 150);
    m_eMyObjType = OBJECT_TYPE::ITEM;
}

int CItem::Update()
{
    if (iDir == 0)
    {
        if (m_fDir <= 180.f)  // 내가 도달할 좌표에 도달하지 못할때마다 위치 갱신 
        {
            m_fDir += 3.f;

            m_tInfo.fX = vConstPos.fX + fDistance * cosf(m_fDir * PI / 180);
            m_tInfo.fY = vConstPos.fY - fDistance * sinf(m_fDir * PI / 180);
        }
    }
    else
    {
        if (m_fDir >= 0.f)  // 내가 도달할 좌표에 도달하지 못할때마다 위치 갱신 
        {
            m_fDir -= 3.f;

            m_tInfo.fX = vConstPos.fX + fDistance * cosf(m_fDir * PI / 180);
            m_tInfo.fY = vConstPos.fY - fDistance * sinf(m_fDir * PI / 180);

        }
    }

    __super::Update_Rect();

    return 0;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC hDC)
{
    CRenderingMgr::Drawing_Coin(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void CItem::Render_Collision(HDC hDC)
{
}

void CItem::Release()
{
}
