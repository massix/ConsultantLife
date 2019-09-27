#pragma once
#include <core_export.h>


extern "C" {
	struct ALLEGRO_DISPLAY;
	struct ALLEGRO_EVENT_SOURCE;
}

namespace cl {
	namespace core {
		class CORE_EXPORT Display {
		public:
			static void init(int w, int h);
			static void initFullScreen();
			static void free();
			static void flip();
			static ALLEGRO_EVENT_SOURCE* getEventSource();
			static int32_t getWidth();
			static int32_t getHeight();
			
			static ALLEGRO_DISPLAY* getDisplay();

		private:
			Display();
			Display(Display const&) = delete;
			Display& operator=(Display const&) = delete;

			static ALLEGRO_DISPLAY* display;
		};
	}
}
