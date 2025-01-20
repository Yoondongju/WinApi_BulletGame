#pragma once
#include "Obj.h"

class CPlayer;

class CUI : public CObj
{
public:
	CUI();
	~CUI();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual		void        Render_Collision(HDC hDC) {}
	virtual void Release() override;

protected:
	float m_fCount;
	CPlayer* m_pPlayer;

};

