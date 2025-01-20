#pragma once
#include "CBullet.h"

class PurpleBullet : public CBullet
{
public:
	PurpleBullet();
	PurpleBullet(int _iLevel, INFO _tInfo);
	virtual ~PurpleBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


};

