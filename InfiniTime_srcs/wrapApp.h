#pragma once

#include "displayapp/apps/Apps.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/Controllers.h"
#include "Symbols.h"

#include "compat.h"

typedef bool (*touchCallback)(globalTouchEvent e); // needed for delegating event handlers.
namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class wrapApp : public Screen {
      public:
        wrapApp(AppControllers& controllers);
        ~wrapApp() override;
        bool OnTouchEvent(Pinetime::Applications::TouchEvents event) override;
	  private:
		touchCallback tcb = &default_OnTouchEvent;
		static bool default_OnTouchEvent(globalTouchEvent event);
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
