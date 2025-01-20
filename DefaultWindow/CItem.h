#pragma once
#include "Obj.h"
class CItem : public CObj
{
public:
	CItem();
	~CItem();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Render_Collision(HDC hDC) override;
	virtual void Release() override;


private:
	INFO	vTargetPos;
	INFO	vConstPos;

	int		iDir;			// æ∆¿Ã≈€ ∂≥±º øﬁ ø¿ πÊ«‚

	float	fDistance;
	
};

