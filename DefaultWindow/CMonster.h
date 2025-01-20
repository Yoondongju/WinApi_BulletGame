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
	list<CObj*>* m_pBullet;							// 총알리스트 포인터
	vector<pair<float, float>>	m_vXY;				// 초기 위치 담는 벡터
	int							m_iIdx = 0;			// 벡터 인덱스
	pair<float, float>			m_MvRange;			// 이동범위
	int							m_iAttackCycle;		// 공격주기
	int							m_MvY = 50.f;			// 어디까지 나올건지 ( 추가)
};

