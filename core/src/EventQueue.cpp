#include <core/EventQueue.h>
#include <core/Event.h>
#include <core/InitFailedExc.h>
#include <allegro5/allegro.h>

using namespace cl::core;

EventQueue::EventQueue() {
	this->eq = al_create_event_queue();

	if (this->eq == nullptr) {
		throw new InitializationFailed("Can't initialize Event Queue :(");
	}

	this->looping = false;
	al_register_event_source(this->eq, al_get_keyboard_event_source());
	al_register_event_source(this->eq, al_get_mouse_event_source());
}

EventQueue::~EventQueue() {
	al_destroy_event_queue(this->eq);
}

void EventQueue::registerEventSource(ALLEGRO_EVENT_SOURCE* source) {
	al_register_event_source(this->eq, source);
}

void EventQueue::registerForEvent(uint32_t eventType, std::function<void(Event&)> callback) {
	this->receivers[eventType].push_back(callback);
}

void EventQueue::waitForEvent() {
	Event e;
	al_wait_for_event(this->eq, e.getRawEvent());

	for (auto f : this->receivers[e.getType()]) {
		f(e);
	}
}

bool cl::core::EventQueue::isEmpty() {
	return al_is_event_queue_empty(this->eq);
}

void EventQueue::startLoop() {
	this->looping = true;
	while (this->looping) {
		this->waitForEvent();
	}
}

void EventQueue::endLoop() {
	this->looping = false;
}
