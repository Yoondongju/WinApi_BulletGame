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

		Dst->SetCollision(false);
		for (auto& Src : _Src)
		{
			Src->SetCollision(false);


			if ((Dst_fCX / 2.f) + (Src->GetInfo().fCX / 2.f) >= abs(Dst_fX - Src->GetInfo().fX)
				&& (Dst_fCY / 2.f) + (Src->GetInfo().fCY / 2.f) >= abs(Dst_fY - Src->GetInfo().fY))
			{
				if (OBJECT_TYPE::PLAYER == Dst->Get_MyObjType()
					&& OBJECT_TYPE::ITEM == Src->Get_MyObjType())
				{
					Dst->SetCollision(true);
					Src->SetCollision(true);

					// player �ɷ�ġ ����
					int iPlayerLevel = Dst->GetLevel();
					Dst->SetLevel(++iPlayerLevel);

					Src->SetDead(true);
				}
			}
		}
	}
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)  // ���ʹ� Rect�� �׸��鼭 ���Ϳ� �Ѿ� �浹������ �̰� ������
{
	// �� �浹
	for (auto& Dst : _Dst)
	{
		float Dst_fX = Dst->GetInfo().fX;
		float Dst_fY = Dst->GetInfo().fY;

		float Dst_fCX = Dst->GetInfo().fCX;
		float Dst_fCY = Dst->GetInfo().fCY;

		Dst->SetCollision(false);
		for (auto& Src : _Src)
		{
			Src->SetCollision(false);
			float fX = (Dst_fX - Src->GetInfo().fX) * (Dst_fX - Src->GetInfo().fX);
			float fY = (Dst_fY - Src->GetInfo().fY) * (Dst_fY - Src->GetInfo().fY);

			float h = sqrtf(fX + fY);

			float r1 = Dst_fCX / 2.f;
			float r2 =Src->GetInfo().fCX / 2.f;

			if (h <= r1 + r2)
			{
				if (OBJECT_TYPE::MONSTER == Dst->Get_MyObjType()
					&& OBJECT_TYPE::OBJ_BULLET == Src->Get_MyObjType())  
				{
					if (Check_Color(Dst, Src))     // Dst: ����  Src: �÷��̾� �Ѿ�
					{
 						Dst->SetCollision(true);
						Src->SetCollision(true);


						int iDstHP = Dst->Get_Hp();
						int iSrcAttack = Src->GetAttackInfo();
						Dst->Set_Hp(iDstHP - iSrcAttack);

						if (0 >= iDstHP)
						{
							Dst->SetDead(true);
							Dst->Set_Hp(0);
						}
			
						Src->SetDead(true);      
					}
				}

				else if (OBJECT_TYPE::OBJ_MONSTERBULLET == Dst->Get_MyObjType()		// Dst: ���� �Ѿ�  Src: �÷��̾� ����  
					&& OBJECT_TYPE::PLAYER_SHIELD == Src->Get_MyObjType())
				{
					Dst->SetCollision(true);
					Src->SetCollision(true);
					Dst->SetDead(true);
				}

				// ���� �浹ó���ϴ� ��ĵ� ������ ���� ��� ��ҵ��� �����ϰ� ó���޴°Ծƴ� ��� ObjType�� ���� �ݺ��� �������ϴ°� ������
				// �Ը����� �ڵ��̴� ���� if else �� ó�������� �̷��� �Ұ�� ù��° case�� �浹ó���� �ߴٸ� else�� �������ʾƼ� �ùٸ� �浹ó���� �ƴ�

				else                             // Dst:�÷��̾�  Src: ���� �Ѿ�    
				{
					Dst->SetCollision(true);
					Src->SetCollision(true);

					if (!(dynamic_cast<CPlayer*>(Dst)->IsFever()))
					{
						int iDstHP = Dst->Get_Hp();
						int iSrcAttack = Src->GetAttackInfo();
						Dst->Set_Hp(iDstHP - iSrcAttack);

						int iDstHP2 = Dst->Get_Hp();
						if (0 >= iDstHP2)
						{
							Dst->SetDead(true); // ���� üũ�� ���� 
							Dst->Set_Hp(0);
						}
					}					
											 // ����        // Player
					Src->SetDead(true);      // Player �Ѿ�   // ���� �Ѿ�
				}

			}
		}
	}

}

bool CCollisionMgr::Check_Color(CObj* pDst, CObj* pSrc)
{
	if (pDst->Get_Color() == pSrc->Get_Color())
		return true;
	return false;
}

