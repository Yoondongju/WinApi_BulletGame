#include "stdafx.h"
#include "MainGame.h"
#include "CKeyMgr.h"

#include "CMonster.h"

#include "CStage1_Scene.h"
#include "CStage2_Scene.h"
#include "CStage3_Scene.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr)
	, m_pPreScene(nullptr)
	, m_pCurScene(nullptr)
	, m_iFPS(0)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CKeyMgr::CreateSingleTonInst()->init();

	m_vecGameScene.push_back(new CStage1_Scene);
	m_vecGameScene.push_back(new CStage2_Scene);
	m_vecGameScene.push_back(new CStage3_Scene);
	m_pCurScene = m_vecGameScene[(UINT)SCENE_TYPE::STAGE1];

	m_pCurScene->Initialize();  // Player 생성
	m_pPlayer = m_pCurScene->GetTypeObj(OBJECT_TYPE::PLAYER).front();

	m_pCurScene->Enter();
}

void CMainGame::Update()
{
	CKeyMgr::CreateSingleTonInst()->Update();

	if (m_pPreScene && m_pPreScene != m_pCurScene)
	{
		m_pCurScene->Initialize();
		m_pCurScene->Enter();
		++CScene::iSceneCount;

		m_pPreScene = m_pCurScene;
	}

	int iResult = m_pCurScene->Update();
	switch (iResult)
	{
	case SCENE_CHANGE:
	{
		
	}
		break;

	default:
		break;
	}

}


void CMainGame::Late_Update()
{
	m_pCurScene->Late_Update();

}


void CMainGame::Render()
{
	m_iFPS++;

	if ((GetTickCount() - m_dwTime) >= 1000)  // 이건 진짜 fps이 아님
	{
		swprintf_s(m_szFPS, L"현재 FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	m_pCurScene->Render(m_hDC);


	
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"현재 Score: %f", dynamic_cast<CPlayer*>(m_pPlayer)->GetCurScore());
	TextOut(m_hDC, 10, 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"현재 Stage: %d", CScene::iSceneCount);
	TextOut(m_hDC, 10, 40, szBuff, lstrlen(szBuff));
}

void CMainGame::Release()
{
	m_pCurScene->Exit();
	m_pCurScene = nullptr;


	for (UINT i = 0; i < m_vecGameScene.size(); ++i)
		Safe_Delete<CScene*>(m_vecGameScene[i]);
	m_vecGameScene.clear();

	ReleaseDC(g_hWnd, m_hDC);
}


void CMainGame::SceneChange(SCENE_TYPE _e)
{
	m_pCurScene->Exit();
	m_pPreScene = m_pCurScene;
	m_pCurScene = m_vecGameScene[(UINT)_e];

}

