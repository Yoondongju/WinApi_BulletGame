#pragma once

#include "CScene.h"

class CStage1_Scene : public CScene
{
public:
	CStage1_Scene();
	virtual ~CStage1_Scene();

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

