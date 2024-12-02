#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//���� �������� ī���ð� ���� �������� ī���� ���� ���̸� ���Ѵ�.
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//���� ī��Ʈ ���� ���簪���� ����
	m_llPrevCount = m_llCurCount;

	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
}

void TimeManager::Render()
{
}