#pragma once
#include "CMonster.h"
class CEasyMonster : public CMonster
{
public:
	CEasyMonster();
	virtual ~CEasyMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};
