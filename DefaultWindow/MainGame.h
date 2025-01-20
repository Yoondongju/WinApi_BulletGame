#pragma once

#include "Define.h"
#include "Player.h"


class CScene;

class CMainGame
{
	SINGLE(CMainGame)

public:
	CObj* GetPlayer() { return m_pPlayer; }

public:
	CScene* GetCurScene() { return m_pCurScene; }

public:
	void		Initialize();
	int		Update();		// 실시간으로(매 프레임마다) 변경되는 값을 만드는 함수
	void		Late_Update();

	void		Render();		// 실시간으로(매 프레임마다) 출력하는 함수
	void		Release();


public:
	void SceneChange(SCENE_TYPE _e);


public:
	DWORD GetTimeCount() { return m_dwTime; }





private:
	friend void SetPlayer(CObj* _p);


private:	
	static CObj* m_pPlayer;

	vector<CScene*>	m_vecGameScene;
	CScene* m_pPreScene;  // 이전 씬
	CScene* m_pCurScene;  // 현재 씬


private:
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
};

