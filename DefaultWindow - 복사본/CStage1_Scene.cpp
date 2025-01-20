#include "stdafx.h"
#include "CStage1_Scene.h"

#include "MainGame.h"
#include "Player.h"
#include "CMonster.h"
#include "CUI.h"
#include "CFeverUI.h"

#include "CCollisionMgr.h"

CStage1_Scene::CStage1_Scene()
{

}

CStage1_Scene::~CStage1_Scene()
{
}

void CStage1_Scene::Initialize()
{
	// Stage1���� ������ Obj �ʱ�ȭ
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].push_back(new CPlayer);
	m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front()->Initialize();
}

int CStage1_Scene::Update()
{
	float fCurScore = static_cast<CPlayer*>(m_vecObj[(UINT)OBJECT_TYPE::PLAYER].front())->GetCurScore();
	if (fCurScore >= 100.f)
	{
		CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::STAGE2);
		return SCENE_CHANGE;
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
			}
		}
	}

	return 0;
}


void CStage1_Scene::Late_Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			(*iter)->Late_Update();	
		}
	}

	CCollisionMgr::Collision_Rect(m_vecObj[(UINT)OBJECT_TYPE::MONSTER], m_vecObj[(UINT)OBJECT_TYPE::PLAYER]);
	CCollisionMgr::Collision_Sphere(m_vecObj[(UINT)OBJECT_TYPE::MONSTER], m_vecObj[(UINT)OBJECT_TYPE::BULLET]);
}

void CStage1_Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{
		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			if ((*iter)->IsCollision())
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 0, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

				(*iter)->Render(hDC);

				SelectObject(hDC, oldBrush);	  // �پ��� ���� ó���۾�
				DeleteObject(myBrush);			  // �پ��� ���� ó���۾�
			}
			else
				(*iter)->Render(hDC);
		}
	}
}


void CStage1_Scene::Enter()
{
	m_vecObj[(UINT)OBJECT_TYPE::MONSTER].push_back(new CMonster);	
	for (UINT i = 0; i < m_vecObj[(UINT)OBJECT_TYPE::MONSTER].size(); ++i)
	{
		m_vecObj[(UINT)OBJECT_TYPE::MONSTER].back()->Initialize();
	}

	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();

	m_vecObj[(UINT)OBJECT_TYPE::UI].push_back(new CFeverUI);
	m_vecObj[(UINT)OBJECT_TYPE::UI].back()->Initialize();

}

void CStage1_Scene::Exit()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)   // �Ѿ��� Player�� ������ ������Ʈ���ٰ��� list�̱⶧��
	{
		if (i == (UINT)OBJECT_TYPE::PLAYER)
			continue;

		for (auto iter = m_vecObj[i].begin(); iter != m_vecObj[i].end(); ++iter)
		{
			Safe_Delete<CObj*>(*iter);
		}
		m_vecObj[i].clear();
	}
	
}
