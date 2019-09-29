#include <allegro5/allegro.h>
#include <core/Display.h>
#include <core/InitFailedExc.h>

using namespace cl::core;

ALLEGRO_DISPLAY* Display::display = nullptr;

void Display::init(int w, int h) {
	display = al_create_display(w, h);
	if (display == nullptr) {
		throw new InitializationFailed("Could not initialize display.");
	}
}

void Display::initFullScreen() {
	ALLEGRO_DISPLAY_MODE displayMode;
	al_get_display_mode(al_get_num_display_modes() - 1, &displayMode);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);

	display = al_create_display(displayMode.width, displayMode.height);
	if (display == nullptr) {
		throw new InitializationFailed("Could not initialize display");
	}
}

void Display::setTarget() {
	al_set_target_bitmap(al_get_backbuffer(Display::getDisplay()));
}

ALLEGRO_DISPLAY* Display::getDisplay() {
	return display;
}

void Display::flip() {
	al_flip_display();
}

void Display::free() {
	al_destroy_display(display);
}

ALLEGRO_EVENT_SOURCE* Display::getEventSource() {
	return al_get_display_event_source(display);
}

int32_t Display::getHeight() {
	return al_get_display_height(display);
}

int32_t Display::getWidth() {
	return al_get_display_width(display);
}

Display::Display() {}
