#pragma once
#include "CScene.h"
class CScene_GameOver : public CScene
{
public:
	CScene_GameOver();
	~CScene_GameOver();
public:

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Enter() override;
	virtual void Exit() override;
};

