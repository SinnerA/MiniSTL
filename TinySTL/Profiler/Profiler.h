#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>

namespace TinySTL{
	namespace Profiler{
		class ProfilerInstance{
		public:
			typedef std::chrono::steady_clock SteadyClock;
			typedef SteadyClock::time_point TimePoint;
			typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime; //时间间隔单位为秒
		public:
			static void start(); //开始计时
			static void finish();//结束计时
			static void dumpDuringTime(std::ostream& os = std::cout);//打印时间
			
			static double second();      //以秒为单位返回时间
			static double milliseconds();//以毫秒为单位返回时间
		private:
			static TimePoint startTime;
			static TimePoint finishTime;
			static DurationTime duringTime;
		};
	}
}
#endif