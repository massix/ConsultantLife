#include <core/Game.h>
#include <core/Constants.h>
#include <core/Bitmap.h>
#include <core/Event.h>
#include <core/EventQueue.h>
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
	al_destroy_display(this->alDisplay);
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

	ALLEGRO_DISPLAY_MODE displayMode;
	al_get_display_mode(al_get_num_display_modes() - 1, &displayMode);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);

	this->alDisplay = al_create_display(displayMode.width, displayMode.height);
	this->alTimer = al_create_timer(1.0 / Constants::FPS);

	this->eq->registerEventSource(al_get_display_event_source(this->alDisplay));
	this->eq->registerEventSource(al_get_timer_event_source(this->alTimer));

	this->bossBitmap = new Bitmap("resources/BossWalking_01.png");
	this->bossBitmap->scaleWithFactor(5.0);

	al_set_window_title(this->alDisplay, this->gameName.c_str());
	return (this->alDisplay != nullptr || this->alTimer == nullptr);
}

void Game::mainLoop() {
	al_start_timer(this->alTimer);
	int32_t displayHeight = al_get_display_height(this->alDisplay);
	Position bossPosition(8, displayHeight - this->bossBitmap->getScaledSize().height - 10);

	this->eq->registerForEvent(ALLEGRO_EVENT_TIMER, [&bossPosition, this](Event& e) -> void {
		if (this->eq->isEmpty()) {
			al_set_target_bitmap(al_get_backbuffer(this->alDisplay));
			al_clear_to_color(al_map_rgb(0, 0, 0));
			int32_t displayHeight = al_get_display_height(this->alDisplay);
			this->bossBitmap->draw(bossPosition);
			al_flip_display();
		}
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_KEY_DOWN, [&bossPosition, this](Event& e) {
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

	this->eq->registerForEvent(ALLEGRO_EVENT_DISPLAY_CLOSE, [this](Event& e) {
		this->eq->endLoop();
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, [this](Event& e) {
		if (e.getMouseEvent().button == 1) {
			Position mousePosition(e.getMouseEvent().x, e.getMouseEvent().y);
			if (this->bossBitmap->isPositionInBitmapPosition(mousePosition)) {
				al_show_native_message_box(this->alDisplay, this->getName().c_str(), "Clicked", "TOUCHY!", nullptr, 0);
			}
		}
	});

	this->eq->startLoop();
}

std::string const& Game::getName() const {
	return this->gameName;
}
