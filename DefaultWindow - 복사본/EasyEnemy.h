#pragma once
#include "Enemy.h"

class CEasyEnemy : public CEnemy
{
public:
	CEasyEnemy();
	virtual ~CEasyEnemy();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};
