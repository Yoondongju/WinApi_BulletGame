#pragma once

#include "CScene.h"

class CStage2_Scene : public CScene
{
public:
	CStage2_Scene();
	virtual ~CStage2_Scene();

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

