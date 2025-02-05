#pragma once
#include "compat.h"

#include <FreeRTOS.h>
#include <timers.h>
#include <chrono>

namespace Pinetime {
	namespace Controllers {
		class CompatProvider {
			public:
				CompatProvider(void* _dpApp);
				// void timerLong_cbWrapper(TimerHandle_t xTimer);
				void* timer_getMake(int ID, timer_interrupt_callback action, int period_ms);
			private:
				// timer_interrupt_callback timerLong_callback;
				void* dpApp;
				TimerHandle_t timers[2] = {(void*) nullptr, (void*) nullptr};
		};
	}
}
