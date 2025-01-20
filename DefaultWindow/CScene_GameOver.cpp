#include "stdafx.h"
#include "CScene_GameOver.h"

#include "RenderingMgr.h"
#include "CKeyMgr.h"

#include "MainGame.h"

CScene_GameOver::CScene_GameOver()
{
    m_eSceneType = SCENE_TYPE::GAMEOVER;
}

CScene_GameOver::~CScene_GameOver()
{
}

void CScene_GameOver::Initialize()
{
}

int CScene_GameOver::Update()
{
    if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::ENTER) == KEY_STATE::TAP)
    {
        CMainGame::CreateSingleTonInst()->SceneChange(SCENE_TYPE::STAGE1);
    }
    return 0;
}

void CScene_GameOver::Late_Update()
{
}

void CScene_GameOver::Render(HDC hDC)
{
    CRenderingMgr::Drawing_GameOver(hDC);
}

void CScene_GameOver::Enter()
{

}

void CScene_GameOver::Exit()
{

}
