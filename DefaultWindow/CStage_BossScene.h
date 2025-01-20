#pragma once
#include "CScene.h"
class CStage_BossScene : public CScene
{
public:
	CStage_BossScene();
	~CStage_BossScene();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	void		 PassPlayerInfo();
	virtual void Enter() override;
	virtual void Exit() override;

public:
	void			CreateEasyEnemy();
private:
	bool			m_bShowOneTime = false;
};

