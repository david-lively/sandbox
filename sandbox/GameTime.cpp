#include "GameTime.h"
#include "Log.h"
//#include "Common.h"

GameTime currentTime;

GameTime::GameTime()
{
	m_totalSeconds = GetTickCount() / 1000.f; 
	m_elapsedSeconds = 0;

	m_elapsedTimeIndex = 0;
	m_frameNumber = 0;
	m_elapsedTimeHistoryTotal = 0.0f;

	m_framesPerSecond = 0.0f;

	//clear(m_elapsedTimeHistory, 0.0f);
}


const GameTime& GameTime::Update()
{
	float newTotalSeconds = static_cast<float>(GetTickCount() / 1000.f);

	float elapsed = newTotalSeconds - m_totalSeconds;

	Scale = m_elapsedSeconds  <= 0 ? 1 : elapsed / m_elapsedSeconds;

	m_elapsedSeconds = elapsed;
	m_totalSeconds = newTotalSeconds;

	m_elapsedTimeHistoryTotal -= m_elapsedTimeHistory[m_elapsedTimeIndex];
	m_elapsedTimeHistoryTotal += m_elapsedSeconds;

	m_elapsedTimeHistory[m_elapsedTimeIndex] = m_elapsedSeconds;
	m_elapsedTimeIndex = (m_elapsedTimeIndex + 1) % m_elapsedTimeHistory.size();

	if (m_elapsedTimeIndex == 0)
	{
		m_framesPerSecond = m_elapsedTimeHistory.size() / m_elapsedTimeHistoryTotal;
	}

	m_frameNumber++;

	return *this;
}


GameTime& GameTime::Current()
{
	return currentTime;
}


