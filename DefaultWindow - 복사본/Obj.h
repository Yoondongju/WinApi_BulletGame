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

	void Set_Dir(DIR _e)
	{
		m_eDir = _e;
	}

	void Set_fDir(float _f)
	{
		m_fDir = _f;
	}

	float Get_fDir() { return m_fDir; }

	RECT GetRect() { return m_tRect; }
	INFO GetInfo() { return m_tInfo; }

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
	virtual		void		Release()		PURE;


protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIR			m_eDir;       

	float		m_fDir; // PI는 원의 반 둘레에 대한 비율이고 내가 원하는 영역의 호길이 만큼 가져오고 싶을때 그 각도의 비율은 PI / n;

	float		m_fSpeed;
	bool		m_bDead;

	bool		m_bCollision;

	char		m_szName[32];
};

