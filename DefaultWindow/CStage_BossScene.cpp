#include "stdafx.h"
#include "CStage_BossScene.h"

#include "MainGame.h"
#include "Player.h"
#include "CMonster.h"
#include "EasyMonster.h"
#include "BossMonster.h"

#include "CUI.h"
#include "CFeverUI.h"

#include "CCollisionMgr.h"

#include "AbstractFactory.h"

CStage_BossScene::CStage_BossScene()
{
}

CStage_BossScene::~CStage_BossScene()
{
}

void CStage_BossScene::Initialize()
{
	// Stage1에서 관리할 Obj 초기화  Player는 삭제하면안댐
	// m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(CMainGame::CreateSingleTonInst()->GetPlayer());
}

void	CStage_BossScene::CreateEasyEnemy()
{
	if (m_vecObj[(UINT)OBJECT_TYPE::MONSTER].empty() == true && m_bShowOneTime)
	{
		for (int i = 0; i < 3; i++)
			m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(CEnemyFactory<CEasyMonster>::Create(i, m_vecObj[(UINT)OBJECT_TYPE::BOSS].front()->GetInfo().fX,
				m_vecObj[(UINT)OBJECT_TYPE::BOSS].front()->GetInfo().fY, 200.f, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));
	}
	else if (dynamic_cast<CBossMonster*>(m_vecObj[(UINT)OBJECT_TYPE::BOSS].front())->GetCanShowEnemy() && !m_bShowOneTime)
	{
		for (int i = 0; i < 3; i++)
			m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(CEnemyFactory<CEasyMonster>::Create(i, m_vecObj[(UINT)OBJECT_TYPE::BOSS].front()->GetInfo().fX,
				m_vecObj[(UINT)OBJECT_TYPE::BOSS].front()->GetInfo().fY, 200.f, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));
		m_bShowOneTime = true;
	}
}

int CStage_BossScene::Update()
{
	//float fCurScore = static_cast<CPlayer*>(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front())->GetCurScore();
	//if (fCurScore >= 1000.f)
	//	CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::STAGE3);

	int iResult = 0;

	PassPlayerInfo();
	CreateEasyEnemy();


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


void CStage_BossScene::Late_Update()
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

void CStage_BossScene::Render(HDC hDC)
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

void CStage_BossScene::PassPlayerInfo()
{
	for (auto iter : m_vecObj[(UINT)OBJECT_TYPE::MONSTER])
	{
		(*iter).m_tPlayerInfo.fX = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fX - iter->GetInfo().fX;
		(*iter).m_tPlayerInfo.fY = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fY - iter->GetInfo().fY;
	}
}


void CStage_BossScene::Enter()
{
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	SetPlayer(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front());
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front()->Initialize();

	m_vecObj[(UINT)OBJECT_TYPE::BOSS].push_back(CEnemyFactory<CBossMonster>::Create(1, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));


	//for (int i = 0; i < 3; i++)
	//	m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(CEnemyFactory<CBossMonster>::Create(i, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));


	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].front()->Initialize();

	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CFeverUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();
}

void CStage_BossScene::Exit()
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
