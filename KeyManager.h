#pragma once
#include "Manager.h"

class KeyManager : public Manager
{
	SINGLE(KeyManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

