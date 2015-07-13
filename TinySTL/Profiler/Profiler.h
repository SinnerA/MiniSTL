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
			typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime; //ʱ������λΪ��
		public:
			static void start(); //��ʼ��ʱ
			static void finish();//������ʱ
			static void dumpDuringTime(std::ostream& os = std::cout);//��ӡʱ��
			
			static double second();      //����Ϊ��λ����ʱ��
			static double milliseconds();//�Ժ���Ϊ��λ����ʱ��
		private:
			static TimePoint startTime;
			static TimePoint finishTime;
			static DurationTime duringTime;
		};
	}
}
#endif