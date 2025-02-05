#include "components/compatProvider/compatProvider.h"

using namespace Pinetime::Controllers;

CompatProvider::CompatProvider(void* _dpApp) {
	this->dpApp = _dpApp;
}

void timerLong_cbWrapper(TimerHandle_t xTimer) {
	// this->timerLong_callback();
	((timer_interrupt_callback) pvTimerGetTimerID(xTimer))();
	// if (xTimer) return;
}

void* CompatProvider::timer_getMake(int ID, timer_interrupt_callback action, int period_ms)
{
	// timerLong_callback = action;
	if (this->timers[ID] == (void*) nullptr)
	{
		// void* test = xTimerCreate("Timer", 1, pdFALSE, (void*) action, timerLong_cbWrapper);
		// xTimerChangePeriod(test, pdMS_TO_TICKS(period_ms), 0);
		// return test;

		this->timers[ID] = xTimerCreate("Timer", 1, pdFALSE, (void*) action, timerLong_cbWrapper);
		xTimerChangePeriod(this->timers[ID], pdMS_TO_TICKS(period_ms), 0);
	}
	else {
		set_colours(0xAAAA00, 0x000000);
	}

	return this->timers[ID];
	if (this->dpApp) return this->timers[ID];
}
