#pragma once
#include "CUI.h"
class CFeverUI : public CUI
{
public:
	CFeverUI();
	~CFeverUI();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	float m_fCount;


};

