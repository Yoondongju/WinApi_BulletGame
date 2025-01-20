#include "stdafx.h"
#include "CStage3_Scene.h"

#include "MainGame.h"
#include "Player.h"
#include "CMonster.h"
#include "HardMonster.h"

#include "CUI.h"
#include "CFeverUI.h"

#include "CCollisionMgr.h"

#include "AbstractFactory.h"

CStage3_Scene::CStage3_Scene()
{
}

CStage3_Scene::~CStage3_Scene()
{
}

void CStage3_Scene::Initialize()
{


}

int CStage3_Scene::Update()
{
	int iResult = 0;
	PassPlayerInfo();
	float fCurScore = static_cast<CPlayer*>(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front())->GetCurScore();
	if (fCurScore >= 3000.f)
	{
		CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::STAGEBOSS);
		return 0;
	}

	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Update();	// Bullet ������ ���� ���� ������ Player ������Ʈ���� ����������ϳ�?
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


void CStage3_Scene::Late_Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
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

void CStage3_Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			if ((*iter)->IsCollision())
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

				(*iter)->Render_Collision(hDC);

				SelectObject(hDC, oldBrush);	  // �پ��� ���� ó���۾�
				DeleteObject(myBrush);			  // �پ��� ���� ó���۾�
			}
			else
				(*iter)->Render(hDC);
		}
	}
}

void CStage3_Scene::PassPlayerInfo()
{
	for (auto iter : m_vecObj[(UINT)OBJECT_TYPE::MONSTER])
	{
		(*iter).m_tPlayerInfo.fX = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fX - iter->GetInfo().fX;
		(*iter).m_tPlayerInfo.fY = (m_vecObj[(UINT)OBJECT_TYPE::PLAYER]).front()->GetInfo().fY - iter->GetInfo().fY;
	}
}


void CStage3_Scene::Enter()
{
	// Stage1���� ������ Obj �ʱ�ȭ  Player�� �����ϸ�ȴ�
	// m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	SetPlayer(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front());
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front()->Initialize();


	for (int i = 0; i < 3; i++)
		m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(CEnemyFactory<CHardEnemy>::Create(i, &m_vecObj[(UINT)OBJECT_TYPE::OBJ_MONSTERBULLET]));


	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].front()->Initialize();

	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CFeverUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();
}

void CStage3_Scene::Exit()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{

		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			Safe_Delete<CObj*>(*iter);
		}
		m_vecObj[i].clear();
	}
	
}
