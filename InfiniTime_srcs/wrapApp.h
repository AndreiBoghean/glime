#pragma once

#include "displayapp/apps/Apps.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/Controllers.h"
#include "Symbols.h"

#include "compat.h"
#include <cstdint>

typedef int (*touchCallback)(globalTouchEvent e); // needed for delegating event handlers.
typedef int (*touchCallback_xy)(uint16_t x, uint16_t y); // needed for delegating event handlers.
namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class wrapApp : public Screen {
      public:
        wrapApp(AppControllers& controllers);
        ~wrapApp() override;
        bool OnTouchEvent(Pinetime::Applications::TouchEvents event) override;
        bool OnTouchEvent(uint16_t x, uint16_t y) override;
	  private:
		touchCallback tcb = &default_OnTouchEvent;
		touchCallback_xy tcb_xy = &default_OnTouchEvent_xy;
		lv_task_t* timers_freeable[4];
		static int default_OnTouchEvent(globalTouchEvent event);
		static int default_OnTouchEvent_xy(uint16_t x, uint16_t y);
      };
    }
    
    template <>
    struct AppTraits<Apps::wrapApp> {
      static constexpr Apps app = Apps::wrapApp;
      // static constexpr const char* icon = Screens::Symbols::myApp;
      static constexpr const char* icon = Screens::Symbols::dice;
      static Screens::Screen* Create(AppControllers& controllers) {
        return new Screens::wrapApp(controllers);
      }
    };
  }
}
