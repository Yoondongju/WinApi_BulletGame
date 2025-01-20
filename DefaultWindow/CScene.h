#pragma once

#include "Define.h"

class CObj;

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();


public:
	list<CObj*>& GetTypeObj(OBJECT_TYPE _e) { return m_vecObj[(UINT)_e]; }

	SCENE_TYPE GetSceneType() { return m_eSceneType; }

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;

	virtual void Render(HDC hDC) PURE;

public:
	//void SceneChangeCheck() PURE;


public:
	virtual void Enter() PURE;
	virtual void Exit() PURE;


protected:
	list<CObj*>	m_vecObj[(UINT)OBJECT_TYPE::END];

	SCENE_TYPE m_eSceneType;

public:
	static int iSceneCount;
};

