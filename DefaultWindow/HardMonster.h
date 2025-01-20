#pragma once
#include "CMonster.h"

class CHardEnemy : public CMonster
{
public:
	CHardEnemy();
	virtual ~CHardEnemy();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};