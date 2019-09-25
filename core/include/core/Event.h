#pragma once

#include <core_export.h>

extern "C" {
	union ALLEGRO_EVENT;
	struct ALLEGRO_MOUSE_EVENT;
	struct ALLEGRO_KEYBOARD_EVENT;
	typedef unsigned int ALLEGRO_EVENT_TYPE;
}

namespace cl {
	namespace core {
		class CORE_EXPORT Event {
		public:
			Event();
			virtual ~Event();
			ALLEGRO_EVENT* getRawEvent();
			
			void loadEvent(ALLEGRO_EVENT*);
			ALLEGRO_EVENT_TYPE getType();

			ALLEGRO_MOUSE_EVENT getMouseEvent();
			ALLEGRO_KEYBOARD_EVENT getKeyboardEvent();

		private:
			ALLEGRO_EVENT* event;
		};
	}
}
