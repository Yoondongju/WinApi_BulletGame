#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	CObj(const char* _pName);
	virtual ~CObj();

	void Set_Pos(float _x, float _y)
	{
		m_tInfo.fX = _x;
		m_tInfo.fY = _y;
	}

	void Set_Size(float _x, float _y)
	{
		m_tInfo.fCX = _x;
		m_tInfo.fCY = _y;
	}

	int				Get_Hp() { return m_iHp; }
	void			Set_Hp(int _Hp) { m_iHp = _Hp; }
	int				Get_MaxHp() { return m_iMaxHp; }
	void			Set_MaxHp(int _Hp) { m_iMaxHp = _Hp; }


	void SetAtaackInfo(int _i) { m_iAttackInfo = _i; }
	int GetAttackInfo() { return m_iAttackInfo; }

	void Set_fDir(float _f)
	{
		m_fDir = _f;
	}

	void Set_eDir(DIRECTION _e)
	{
		m_eDir = _e;
	}

	float Get_fDir() { return m_fDir; }

	RECT GetRect() { return m_tRect; }
	INFO GetInfo() { return m_tInfo; }
	COLORSTATE		Get_Color() { return m_eColor; }
	void			Set_Color(COLORSTATE _color) { m_eColor = _color; }

	OBJECT_TYPE Get_MyObjType() { return m_eMyObjType; }


	void SetName(const char* _pName) { strcpy_s(m_szName,sizeof(m_szName), _pName); }
	char* GetName() { return m_szName; }

public:
	void SetCollision(bool _b) { m_bCollision = _b; }
	bool IsCollision() { return m_bCollision; }


public:
	void SetDead(bool _b) { m_bDead = _b; }
  	bool IsDead() { return m_bDead; }

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual     void		Late_Update()	PURE;

	virtual		void		Render(HDC hDC)	PURE;
	virtual		void        Render_Collision(HDC hDC) PURE;

	virtual		void		Release()		PURE;

	INFO		m_tPlayerInfo;


public:
	void SetLevel(int _i) 
	{ 
		if (3 == m_iLevel)
			return;
		m_iLevel = _i;
	}
	int GetLevel() { return m_iLevel; }

protected:
	void		Update_Rect();
	COLORREF	ChangeColor(COLORSTATE _color);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	float		m_fDir; // PI는 원의 반 둘레에 대한 비율이고 내가 원하는 영역의 호길이 만큼 가져오고 싶을때 그 각도의 비율은 PI / n;

	float		m_fSpeed;
	bool		m_bDead;

	bool		m_bCollision;

	char		m_szName[32];

	int			m_iLevel;
	float		m_fVec[2];
	int			m_iHp;
	int			m_iMaxHp;

	int			m_iAttackInfo;      // 몬스터 공격력

	COLORSTATE	m_eColor;
	OBJECT_TYPE m_eMyObjType;
};

