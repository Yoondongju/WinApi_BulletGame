#pragma once
#include "Obj.h"

class CPlayer;

class CMonster abstract : public CObj
{
public:
	CMonster();
	CMonster(int _iIdx);
	~CMonster();

public:
	virtual		void		Initialize();
	virtual		void		Initialize(int _iIdx);
	virtual		int			Update();
	virtual     void		Late_Update();
	virtual		void		Render(HDC hDC);
	virtual		void        Render_Collision(HDC hDC);

	virtual		void		Release();

public:
	CObj* CreateItem();


public:
	void			Set_Bullet(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}
	void			Set_MvY(int _y) { m_MvY = _y; };
	void			Set_XY(int _iIdx)
	{
		m_iIdx = _iIdx;
		m_tInfo.fX = m_vXY[_iIdx].first;
		m_tInfo.fY = m_vXY[_iIdx].second;
	}
	void			Set_XY(int _iIdx, float _x, float _y)
	{
		m_iIdx = _iIdx;
		m_tInfo.fX = _x;
		m_tInfo.fY = _y;
	}
	void		Set_RandomColor();

public:
	pair<int, int>	Get_vXY(int _iIdx) { return m_vXY[_iIdx]; }
	CObj* Create_Bullet(int _iTypeNum, int _iLevel,int _iAttack);




protected:
	list<CObj*>* m_pBullet;							// �Ѿ˸���Ʈ ������
	vector<pair<float, float>>	m_vXY;				// �ʱ� ��ġ ��� ����
	int							m_iIdx = 0;			// ���� �ε���
	pair<float, float>			m_MvRange;			// �̵�����
	int							m_iAttackCycle;		// �����ֱ�
	int							m_MvY = 50.f;			// ������ ���ð��� ( �߰�)
};

