#pragma once
#include "CBullet.h"
class BlueBullet :
    public CBullet
{
public:
	BlueBullet();
	BlueBullet(int _iLevel, INFO _tInfo);
	virtual ~BlueBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};