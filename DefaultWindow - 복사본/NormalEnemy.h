#pragma once
#include "Enemy.h"

class CNormalEnemy : public CEnemy
{
public:
	CNormalEnemy();
	virtual ~CNormalEnemy();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};