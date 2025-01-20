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
	// ������ pos�� �Ѿ��� pos�� ��// �̰� �� ��ü�� size/2 +size/2 �� ������ �浹��
	// X,Y ���ÿ� �����ؾ��� 
	// Rect �浹 �κ�

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
				
				// Ʈ���� ��Ƶΰ� ���Ǹ����ϸ� �� ���ؾ���
				Dst->SetCollision(true);
				Src->SetCollision(true);
			}
		}
	}
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	// �� �浹
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

