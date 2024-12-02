#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	//현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임의 카운팅과 현재 프레임의 카운팅 값의 차이를 구한다.
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//이전 카운트 값을 현재값으로 갱신
	m_llPrevCount = m_llCurCount;

	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
}

void TimeManager::Render()
{
}