#pragma once
#include "CMonster.h"

class CBossMonster : public CMonster
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		SetAttackPattern(int _attackPattern);
	bool		GetCanShowEnemy() { return m_bCanShowEnemy; }
	void		SetCanShowEnemy(bool _canShowEnemy) { m_bCanShowEnemy = _canShowEnemy; }
private:
	int			m_iAttackChangeCycle = 0;
	bool			m_bCanShowEnemy = false;
};