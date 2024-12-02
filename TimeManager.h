#pragma once
#include "Manager.h"

class TimeManager : public Manager
{
	SINGLE(TimeManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDeltaTime;	//������ ������ �ð���
	double			m_dAcc;			//1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	//�Լ� ȣ�� Ƚ��
	UINT			m_iFPS;			//�ʴ� ȣ�� Ƚ��

public:
	double GetDT() { return m_dDeltaTime; }
	float GetfDT() { return (float)m_dDeltaTime; }
};

