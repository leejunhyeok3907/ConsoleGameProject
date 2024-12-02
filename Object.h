#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

private:
	string m_strName;

	Vec2 m_vPos;

	bool m_bAlive;

public:
	GetSet(string, m_strName, strName);
	GetSet(Vec2, m_vPos, vPos);

	bool IsDead() { return !m_bAlive; }

public:
	virtual void init() {};
	virtual void update() PURE;
	virtual void render() {};
};

