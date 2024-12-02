#pragma once
#include "Manager.h"

struct KeyInfo
{
	KEY_STATE state;
	bool prevPushed;
};

class KeyManager : public Manager
{
	SINGLE(KeyManager);

private:
	vector<KeyInfo> m_Keys;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:
	KEY_STATE GetKeyState(KEY_TYPE _key) { return m_Keys[(int)_key].state; }
};

