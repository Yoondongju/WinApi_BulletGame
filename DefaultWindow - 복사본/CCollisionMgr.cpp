#include "stdafx.h"
#include "CCollisionMgr.h"

#include "CBullet.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr()
{


}

CCollisionMgr::~CCollisionMgr()
{


}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	// 몬스터의 pos와 총알의 pos의 차// 이게 각 물체의 size/2 +size/2 와 같으면 충돌임
	// X,Y 동시에 만족해야함 
	// Rect 충돌 부분

	for (auto& Dst : _Dst)
	{
		float Dst_fX = Dst->GetInfo().fX;
		float Dst_fY = Dst->GetInfo().fY;

		float Dst_fCX = Dst->GetInfo().fCX;
		float Dst_fCY = Dst->GetInfo().fCY;

		for (auto& Src : _Src)
		{
			Dst->SetCollision(false);
			Src->SetCollision(false);


			if ((Dst_fCX / 2.f) + (Src->GetInfo().fCX / 2.f) >= abs(Dst_fX - Src->GetInfo().fX)
				&& (Dst_fCY / 2.f) + (Src->GetInfo().fCY / 2.f) >= abs(Dst_fY - Src->GetInfo().fY))
			{
				// Dst->SetDead(true);
				// Src->SetDead(true);
				
				// 트리거 잡아두고 조건만족하면 색 변해야함
				Dst->SetCollision(true);
				Src->SetCollision(true);
			}
		}
	}
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	// 원 충돌
	for (auto& Dst : _Dst)
	{
		float Dst_fX = Dst->GetInfo().fX;
		float Dst_fY = Dst->GetInfo().fY;

		float Dst_fCX = Dst->GetInfo().fCX;
		float Dst_fCY = Dst->GetInfo().fCY;


		for (auto& Src : _Src)
		{
			float fX = (Dst_fX - Src->GetInfo().fX) * (Dst_fX - Src->GetInfo().fX);
			float fY = (Dst_fY - Src->GetInfo().fY) * (Dst_fY - Src->GetInfo().fY);

			float h = sqrtf(fX + fY);

			float r1 = Dst_fCX / 2.f;
			float r2 =Src->GetInfo().fCX / 2.f;

			if (h <= r1 + r2)
			{
				Dst->SetDead(true);
				Src->SetDead(true);
			}
		}
	}

}

