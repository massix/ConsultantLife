#include <core/Game.h>
#include <core/Constants.h>
#include <core/Bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>

using namespace cl::core;

Game::Game(std::string const& gameName) {
	this->gameName = gameName;
	this->over = false;
}

Game::~Game() {
	al_destroy_event_queue(this->alEventQueue);
	al_destroy_timer(this->alTimer);
	al_destroy_display(this->alDisplay);
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

	ALLEGRO_DISPLAY_MODE displayMode;
	al_get_display_mode(al_get_num_display_modes() - 1, &displayMode);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);

	this->alDisplay = al_create_display(displayMode.width, displayMode.height);
	this->alEventQueue = al_create_event_queue();
	this->alTimer = al_create_timer(1.0 / Constants::FPS);

	this->bossBitmap = new Bitmap("resources/BossWalking_01.png");
	this->bossBitmap->scaleWithFactor(5.0);

	al_set_window_title(this->alDisplay, this->gameName.c_str());
	al_register_event_source(this->alEventQueue, al_get_keyboard_event_source());
	al_register_event_source(this->alEventQueue, al_get_timer_event_source(this->alTimer));
	al_register_event_source(this->alEventQueue, al_get_display_event_source(this->alDisplay));
	al_register_event_source(this->alEventQueue, al_get_mouse_event_source());
	
	return (this->alDisplay != nullptr || this->alEventQueue != nullptr || this->alTimer == nullptr);
}

void Game::mainLoop() {
	al_start_timer(this->alTimer);
	bool redraw = false;

	while (!this->over) {
		ALLEGRO_EVENT event;
		al_wait_for_event(this->alEventQueue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				this->over = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			this->over = true;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (event.mouse.button == 1) {
				Position mousePosition(event.mouse.x, event.mouse.y);
				std::cout << "Clicked @ " << std::string(mousePosition) << std::endl;
				std::cout << "Boss @ " << std::string(this->bossBitmap->getPosition()) << std::endl;
				std::cout << "Boss @ " << std::string(this->bossBitmap->getScaledSize()) << std::endl;
				if (this->bossBitmap->isPositionInBitmapPosition(mousePosition)) {
					std::cout << "Clicked on boss bitmap!\n";
					al_show_native_message_box(this->alDisplay, this->gameName.c_str(), "Clicked", "TOUCHY!", nullptr, 0);
				}
			}
			break;
		}

		if (redraw && al_is_event_queue_empty(this->alEventQueue)) {
			al_set_target_bitmap(al_get_backbuffer(this->alDisplay));
			al_clear_to_color(al_map_rgb(0, 0, 0));
			int32_t displayHeight = al_get_display_height(this->alDisplay);
			this->bossBitmap->draw(Position(8, displayHeight - this->bossBitmap->getScaledSize().height - 10));
			al_flip_display();
			redraw = false;
		}
	}
}

std::string const& Game::getName() const {
	return this->gameName;
}
