#include <core/Event.h>
#include <allegro5/allegro.h>

using namespace cl::core;

Event::Event() {
	this->event = new ALLEGRO_EVENT();
}

Event::~Event() {
	delete this->event;
}

ALLEGRO_EVENT* Event::getRawEvent() {
	return this->event;
}

ALLEGRO_EVENT_TYPE Event::getType() {
	return this->event->type;
}

ALLEGRO_MOUSE_EVENT Event::getMouseEvent() {
	return this->event->mouse;
}

ALLEGRO_KEYBOARD_EVENT Event::getKeyboardEvent() {
	return this->event->keyboard;
}
