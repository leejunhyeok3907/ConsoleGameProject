#pragma once
#include "Object.h"

class Ground : public Object
{
public:
	Ground();
	Ground(Vec2 _LeftTop, Vec2 _RightBottom);
	virtual ~Ground();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	Vec2 m_LeftTop;
	Vec2 m_RightBottom;

	wstring m_GroundRender;

public:
	const Vec2& GetLeftTop() const { return m_LeftTop; }
	const Vec2& GetRightBottom() const { return m_RightBottom; }

	bool IsCollision(const Vec2& _pos);
};

