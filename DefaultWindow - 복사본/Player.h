#pragma once

#include "Obj.h"

class CBullet;

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();


public:
	void SetCurScore(float _f) { m_fCurScore += _f; }
	float GetCurScore() { return m_fCurScore; }
	list<CObj*>& GetBulletList() { return m_Bullet; }


public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update();

	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	void		Key_Input();
	CObj* CreateBullet(float _f);
	CObj* CreateShield(float _f);


private:
	static float	m_fCurScore;
	list<CObj*> m_Bullet;



};

