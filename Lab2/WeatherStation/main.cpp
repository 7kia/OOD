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

	wd.SetMeasurements(3, 0.7, 760);

	std::cout << std::endl;
	//wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);




	return 0;
}