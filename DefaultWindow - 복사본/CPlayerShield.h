#pragma once
#include "Obj.h"
class CPlayerShield :public CObj
{
public:
	CPlayerShield();
	~CPlayerShield();

public:
	void SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	CObj* GetOwner() { return m_pOwner; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CObj* m_pOwner;

};

