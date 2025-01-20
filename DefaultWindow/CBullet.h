#pragma once
#include "Obj.h"



class CBullet : public CObj 
{
public:
	CBullet();
	CBullet(CObj* _pOnwer);
	virtual ~CBullet();

public:
	void SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	CObj* GetOwner() { return m_pOwner; }

public:
	virtual		void Initialize();
	virtual		int  Update() PURE;
	virtual     void Late_Update();

	virtual		void Render(HDC hDC);
	virtual		void       Render_Collision(HDC hDC);

	virtual		void Release();

	

private:
	void CollideCheckBox();

private:
	bool IsDead;
	CObj* m_pOwner;



};

