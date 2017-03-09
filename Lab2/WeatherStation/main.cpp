#include "WeatherData.h"

#include <unordered_map>
#include <string>
int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);
	//CStatsDisplay statsDisplay2;
	//wd.RegisterObserver(statsDisplay2, 1);
	//CStatsDisplay statsDisplay3;
	//wd.RegisterObserver(statsDisplay, 2);

	std::set<std::pair<int, std::set<int*>>> m_observers;
	int observer = 0;

	for (auto & element : m_observers)
	{
	}
	std::set<std::pair<int, std::set<int*>>>::iterator priorityIter = m_observers.end();
	for (std::set<std::pair<int, std::set<int*>>>::iterator iter = m_observers.begin(); iter != m_observers.end(); ++iter)
	{
		if (iter->first == 0)
		{
			auto i = iter->second;
			i.emplace(&observer);
			return;
		}
	}


	wd.SetMeasurements(3, 0.7, 760);

	std::cout << std::endl;
	//wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);




	return 0;
}