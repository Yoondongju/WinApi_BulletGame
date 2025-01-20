#pragma once
#include "Obj.h"

class CPlayer;

class CPlayerShield :public CObj
{
public:
	CPlayerShield();
	~CPlayerShield();

public:
	void SetOwner(CPlayer* _pOwner) { m_pOwner = _pOwner; }
	CPlayer* GetOwner() { return m_pOwner; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual		void        Render_Collision(HDC hDC);

	virtual void Release() override;

private:
	CPlayer* m_pOwner;

};

