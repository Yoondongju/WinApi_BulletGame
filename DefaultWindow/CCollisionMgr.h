#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	SINGLE(CCollisionMgr)

public:
	static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);

	static bool Check_Color(CObj* pDst, CObj* pSrc);
};

