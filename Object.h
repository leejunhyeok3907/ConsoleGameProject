#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

private:
	wstring m_strName;

	Vec2 m_vPos;

	bool m_bAlive;

public:
	GetSet(wstring, m_strName, strName);
	GetSet(Vec2, m_vPos, Pos);

	bool IsDead() { return !m_bAlive; }

public:
	virtual void init() {};
	virtual void update() PURE;
	virtual void render() {};
};

