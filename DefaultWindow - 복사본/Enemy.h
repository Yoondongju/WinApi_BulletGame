#pragma once
#include "Obj.h"

class CEnemy : public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();

public:
	void		Set_Bullet(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}
	CObj* Create_Bullet(DIRECTION eDir);

public:
	virtual void Initialize() {}
	virtual int Update() { return 0; }
	virtual void Late_Update() {}
	virtual void Render(HDC hDC) {}
	virtual void Release() {}

protected:
	list<CObj*>*	m_pBullet;			// 총알리스트 포인터
	int				m_iAttackCycle;		// 공격주기
};