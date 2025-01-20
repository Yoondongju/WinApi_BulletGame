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

					// player 능력치 변경
					int iPlayerLevel = Dst->GetLevel();
					Dst->SetLevel(++iPlayerLevel);

					Src->SetDead(true);
				}
			}
		}
	}
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)  // 몬스터는 Rect로 그리면서 몬스터와 총알 충돌판정은 이걸 쓸거임
{
	// 원 충돌
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
					if (Check_Color(Dst, Src))     // Dst: 몬스터  Src: 플레이어 총알
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

				else if (OBJECT_TYPE::OBJ_MONSTERBULLET == Dst->Get_MyObjType()		// Dst: 몬스터 총알  Src: 플레이어 쉴드  
					&& OBJECT_TYPE::PLAYER_SHIELD == Src->Get_MyObjType())
				{
					Dst->SetCollision(true);
					Src->SetCollision(true);
					Dst->SetDead(true);
				}

				// 지금 충돌처리하는 방식도 문제가 있음 모든 요소들이 동일하게 처리받는게아님 모든 ObjType에 따라 반복을 돌려야하는게 맞지만
				// 규모가작은 코드이다 보니 if else 로 처리하지만 이렇게 할경우 첫번째 case때 충돌처리를 했다면 else에 들어오지않아서 올바른 충돌처리가 아님

				else                             // Dst:플레이어  Src: 몬스터 총알    
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
							Dst->SetDead(true); // 데드 체크로 인해 
							Dst->Set_Hp(0);
						}
					}					
											 // 몬스터        // Player
					Src->SetDead(true);      // Player 총알   // 몬스터 총알
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

