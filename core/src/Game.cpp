#include <core/Game.h>
#include <core/Constants.h>
#include <core/Bitmap.h>
#include <core/Event.h>
#include <core/EventQueue.h>
#include <core/InitFailedExc.h>
#include <core/Display.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>

using namespace cl::core;

Game::Game(std::string const& gameName) {
	this->gameName = gameName;
}

Game::~Game() {
	al_destroy_timer(this->alTimer);
	Display::free();
	delete this->eq;
	delete this->bossBitmap;
}

bool Game::init() {
	if (!al_init()) {
		return false;
	}

	if (!al_install_keyboard()) {
		return false;
	}

	if (!al_install_mouse()) {
		return false;
	}

	if (!al_init_image_addon()) {
		return false;
	}

	this->eq = new EventQueue();

	Display::initFullScreen();
	this->alTimer = al_create_timer(1.0 / Constants::FPS);

	this->eq->registerEventSource(Display::getEventSource());
	this->eq->registerEventSource(al_get_timer_event_source(this->alTimer));

	this->bossBitmap = new Bitmap("resources/BossWalking_01.png");
	this->bossBitmap->scaleWithFactor(5.0);

	al_set_window_title(Display::getDisplay(), this->gameName.c_str());

	if (this->alTimer == nullptr) {
		throw new InitializationFailed("Impossible to initialize the game.");
	}

	return true;
}

void Game::mainLoop() {
	al_start_timer(this->alTimer);
	Position bossPosition(8, Display::getHeight() - this->bossBitmap->getScaledSize().height - 10);

	this->eq->registerForEvent(ALLEGRO_EVENT_TIMER, [&](Event& e) -> void {
		if (this->eq->isEmpty()) {
			al_set_target_bitmap(al_get_backbuffer(Display::getDisplay()));
			al_clear_to_color(al_map_rgb(0, 0, 0));
			this->bossBitmap->draw(bossPosition);
			Display::flip();
		}
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_KEY_DOWN, [&](Event& e) {
		switch (e.getKeyboardEvent().keycode) {
		case ALLEGRO_KEY_ESCAPE:
			this->eq->endLoop();
			break;
		case ALLEGRO_KEY_UP:
			bossPosition.y -= 5;
			break;
		case ALLEGRO_KEY_DOWN:
			bossPosition.y += 5;
			break;
		case ALLEGRO_KEY_LEFT:
			bossPosition.x -= 5;
			break;
		case ALLEGRO_KEY_RIGHT:
			bossPosition.x += 5;
			break;
		}
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_DISPLAY_CLOSE, [&](Event& e) {
		this->eq->endLoop();
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, [&](Event& e) {
		if (e.getMouseEvent().button == 1) {
			Position mousePosition(e.getMouseEvent().x, e.getMouseEvent().y);
			if (this->bossBitmap->isPositionInBitmapPosition(mousePosition)) {
				al_show_native_message_box(Display::getDisplay(), this->getName().c_str(), "Clicked", "TOUCHY!", nullptr, 0);
			}
		}
	});

	this->eq->startLoop();
}

std::string const& Game::getName() const {
	return this->gameName;
}
