#pragma once
#include "CBullet.h"

class RedBullet :
    public CBullet
{
public:
	RedBullet();
	RedBullet(int _iLevel, INFO _tInfo);
	virtual ~RedBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

