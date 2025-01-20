#include "stdafx.h"
#include "CStage1_Scene.h"

#include "MainGame.h"
#include "Player.h"
#include "CMonster.h"

#include "EasyMonster.h"
#include "BossMonster.h"


#include "CUI.h"
#include "CFeverUI.h"

#include "CCollisionMgr.h"

#include "AbstractFactory.h"



CStage1_Scene::CStage1_Scene()
{

}

CStage1_Scene::~CStage1_Scene()
{
}

void CStage1_Scene::Initialize()
{
	
}

int CStage1_Scene::Update()
{
	int iResult = 0;
	PassPlayerInfo();

	float fCurScore = static_cast<CPlayer*>(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front())->GetCurScore();
	if (fCurScore >= 1000.f)
	{
		CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::STAGE2);
		return 0;
	}
		
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // 총알은 Player가 별도로 업데이트해줄것임 list이기때문
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Update();	// Bullet 삭제가 되질 않음 별도로 Player 업데이트에서 삭제해줘야하나?
				++iter;
			}
			else
			{
				Safe_Delete<CObj*>((*iter));
				iter = m_vecObj[i].erase(iter);
				
				if (i == (UINT)OBJECT_TYPE::PLAYER)
				{					
					SetPlayer(nullptr);
					CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::GAMEOVER);
				}
			}
		}
	}

	return iResult;
}


void CStage1_Scene::Late_Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // 총알은 Player가 별도로 업데이트해줄것임 list이기때문
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			(*iter)->Late_Update();	
		}
	}

	CCollisionMgr::Collision_Rect(m_vecObj[(UINT)OBJECT_TYPE::PLAYER], m_vecObj[(UINT)OBJECT_TYPE::ITEM]);
	CCollisionMgr::Collision_Sphere(m_vecObj[(UINT)OBJECT_TYPE::MONSTER], m_vecObj[(UINT)OBJECT_TYPE::OBJ_BULLET]);
	CCollisionMgr::Collision_Sphere(m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET], m_vecObj[(UINT)OBJECT_TYPE::PLAYER_SHIELD]);

	CCollisionMgr::Collision_Sphere(m_vecObj[(UINT)OBJECT_TYPE::PLAYER], m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]);
}

void CStage1_Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // 총알은 Player가 별도로 업데이트해줄것임 list이기때문
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			if ((*iter)->IsCollision())
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

				(*iter)->Render_Collision(hDC);

				SelectObject(hDC, oldBrush);	  // 다쓰고 난후 처리작업
				DeleteObject(myBrush);			  // 다쓰고 난후 처리작업
			}
			else
				(*iter)->Render(hDC);
		}
	}
}

void CStage1_Scene::PassPlayerInfo()
{
	for (auto iter : m_vecObj[(UINT)OBJECT_TYPE::MONSTER])
	{
		(*iter).m_tPlayerInfo.fX = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fX - iter->GetInfo().fX;
		(*iter).m_tPlayerInfo.fY = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fY - iter->GetInfo().fY;
	}
}


void CStage1_Scene::Enter()
{
	PlaySound(L"Sound.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	// Stage1에서 관리할 Obj 초기화
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	SetPlayer(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front());
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front()->Initialize();



	for (int i = 0; i < 3; i++)
		m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(CEnemyFactory<CEasyMonster>::Create(i, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));


	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();

	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CFeverUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();

}

void CStage1_Scene::Exit()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // 총알은 Player가 별도로 업데이트해줄것임 list이기때문
	{

		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			Safe_Delete<CObj*>(*iter);
		}
		m_vecObj[i].clear();
	}
	
}
