#pragma once
#include "Obj.h"



class CBullet : public CObj
{
public:
	CBullet(CObj* _pOnwer);
	virtual ~CBullet();

public:
	CObj* GetOwner() { return m_pOwner; }

public:
	virtual		void Initialize();
	virtual		int  Update();
	virtual     void Late_Update();

	virtual		void Render(HDC hDC);
	virtual		void Release();

private:
	void CollideCheckBox();

private:
	bool IsDead;
	CObj* m_pOwner;

};

