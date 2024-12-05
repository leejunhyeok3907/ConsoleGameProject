#pragma once
#include "Monster.h"
class Boss :
    public Monster
{
public:
	Boss();
	virtual ~Boss();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

protected:
	virtual void DrawCharacter();

public:
	virtual void OnHited(int _Damage);

private:
	ULONGLONG SpawnTimer;

	int NextSpawnRate=3000;
};

