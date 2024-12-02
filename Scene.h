#pragma once

class Object;

class Scene
{
private:
	vector<Object*> m_Obj[(UINT)GROUP_TYPE::END];
	wstring	m_strName;

	Object* m_Player;

public:
	GETSET(wstring, m_strName, Name);

	virtual void init();
	virtual void update();
	virtual void render();

	virtual void Enter() PURE;//해당 Scene에 진입시 호출
	virtual void Exit() PURE;//해당 Scene의 탈출시 호출

public:
	void AddObject(Object* _pObj, GROUP_TYPE _eType)
	{
		m_Obj[(UINT)_eType].push_back(_pObj);
	}

	void RegisterPlayer(Object* _Player) { m_Player = _Player; }

	const vector<Object*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_Obj[(UINT)_eType];
	}

	void DeleteGroup(GROUP_TYPE _eType);
	void DeleteAll();

public:
	Scene();
	virtual ~Scene();
};

