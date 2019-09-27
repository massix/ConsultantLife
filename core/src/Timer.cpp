#include <core/Timer.h>
#include <allegro5/allegro.h>

using namespace cl::core;


Timer::Timer(float fps) : timer(al_create_timer(fps)) {
}

Timer::~Timer() {
	al_destroy_timer(this->timer);
}

ALLEGRO_EVENT_SOURCE* Timer::getEventSource() {
	return al_get_timer_event_source(this->timer);
}

void Timer::start() {
	al_start_timer(this->timer);
}

void Timer::stop() {
	al_stop_timer(this->timer);
}

bool Timer::operator==(ALLEGRO_TIMER* t) {
	return t == this->timer;
}

bool Timer::operator==(Timer const& t) {
	return this->operator==(t.timer);
}

Timer::operator ALLEGRO_TIMER* () {
	return this->timer;
}
