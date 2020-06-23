#include "Precompiled.h"
#include "Util.h"

std::string My::GetNowTime()
{
	char date[7][5] = {
		"SUN","MON","TUE","WED","THU","FRI","SAT"
	};

	std::string returnString;
	const int UTC = +9;

	std::stringstream ss;
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::tm today;
	__time64_t t = std::chrono::system_clock::to_time_t(now);
	_localtime64_s(&today, &t);

	ss << (today.tm_year + 1900) << '-'
		<< (today.tm_mon + 1) << '-'
		<< today.tm_mday << " "
		<< date[(today.tm_wday)] << " ";


	auto duration = now.time_since_epoch();

	typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<UTC>	>::type> Days;
	Days days = std::chrono::duration_cast<Days>(duration);
	duration -= days;
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	duration -= hours;
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	duration -= minutes;
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	duration -= seconds;
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	duration -= milliseconds;
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	duration -= microseconds;
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

	ss << today.tm_hour << "h"
		<< minutes.count() << "m"
		<< seconds.count() << "s "
		<< milliseconds.count() << " "
		<< microseconds.count() << " "
		<< nanoseconds.count();

	returnString = ss.str();

	return returnString;
}

