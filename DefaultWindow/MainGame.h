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
	int		Update();		// �ǽð�����(�� �����Ӹ���) ����Ǵ� ���� ����� �Լ�
	void		Late_Update();

	void		Render();		// �ǽð�����(�� �����Ӹ���) ����ϴ� �Լ�
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
	CScene* m_pPreScene;  // ���� ��
	CScene* m_pCurScene;  // ���� ��


private:
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
};

