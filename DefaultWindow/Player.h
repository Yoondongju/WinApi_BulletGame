#pragma once

#include "Obj.h"

class CBullet;


#define MAXFEVER	100

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
	CObj* GetMyShield() { return m_pPlayerShield; }


public:
	void SetFeverGauge(float _f) { m_fFeverGauge = _f; }
	float GetFeverGauge() { return m_fFeverGauge; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update();

	virtual void Render(HDC hDC) override;
	virtual		void        Render_Collision(HDC hDC);
	virtual void Release() override;


public:
	bool	IsFever() { return m_bInvincibility; }

private:
	void FeverIn();
	void FeverOut();


private:
	void		Key_Input();
	CObj* CreateBullet(int _iTypeNum, int _iLevel);

	CObj* CreateShield(float _f);


private:
	static float	m_fCurScore;
	list<CObj*>		m_Bullet;
	CObj*  m_pPlayerShield;

	DWORD	m_dwFeverTime;

	int			iTypeNum;
	float		m_fFeverGauge;
	bool		m_bInvincibility;
};

