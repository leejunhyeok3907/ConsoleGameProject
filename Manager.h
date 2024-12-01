#pragma once
class Manager
{
public:
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

