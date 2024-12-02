#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

protected:
	wstring m_strName;

	Vec2 m_Pos;

	bool m_bAlive;

public:
	GETSET(wstring, m_strName, strName);
	GETSET(Vec2, m_Pos, Pos);

	bool IsDead() { return !m_bAlive; }

	static bool IsInScreen(int _nx, int _ny);

public:
	virtual void init() {};
	virtual void update() PURE;
	virtual void render() {};
};

