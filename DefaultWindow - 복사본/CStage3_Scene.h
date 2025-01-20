#pragma once

#include "CScene.h"

class CStage3_Scene :public CScene
{
public:
	CStage3_Scene();
	virtual ~CStage3_Scene();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();

	virtual void Render(HDC hDC);

public:
	virtual void Enter();
	virtual void Exit();

private:

};

