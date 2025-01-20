#pragma once

#include "Obj.h"
#include "CMonster.h"
#include "CBullet.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, DIRECTION eDir)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Dir(eDir);

		return pObj;
	}
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

template<typename T>
class CEnemyFactory
{
public:
	static CObj* Create(int _iIdx, list<CObj*>* pBullet)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		dynamic_cast<T*>(pObj)->Set_XY(_iIdx);
		dynamic_cast<T*>(pObj)->Set_Bullet(pBullet);
		return pObj;
	}
	static CObj* Create(int _iIdx, float _x, float _y, int _mvY, list<CObj*>* pBullet)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		dynamic_cast<T*>(pObj)->Set_XY(_iIdx, _x, _y);
		dynamic_cast<T*>(pObj)->Set_MvY(_mvY);
		dynamic_cast<T*>(pObj)->Set_Bullet(pBullet);
		return pObj;
	}
};
