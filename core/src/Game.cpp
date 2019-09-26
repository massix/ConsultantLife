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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

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

	if (!al_init_font_addon()) {
		return false;
	}

	if (!al_init_ttf_addon()) {
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

	ALLEGRO_FONT* font = al_load_ttf_font("resources/yoster.ttf", 64, 0);
	ALLEGRO_FONT* debugFont = al_load_ttf_font("resources/Atarian.ttf", 32, 0);

	struct KeyPressed {
		bool shiftKey = false;
		bool rKey = false;
		bool gKey = false;
		bool bKey = false;
	} heldKeys;

	struct DebugColor {
		unsigned char red = 250;
		unsigned char green = 0;
		unsigned char blue = 0;
	} debugColor;

	this->eq->registerForEvent(ALLEGRO_EVENT_TIMER, [&](Event& e) -> void {
		std::ostringstream str;
		str << "Debug - Shift=" << heldKeys.shiftKey << ", R=" << heldKeys.rKey << ", G=" << heldKeys.gKey << ", B=" << heldKeys.bKey << "  ";
		str << "RGB(" << float(debugColor.red) << ", " << float(debugColor.green) << ", " << float(debugColor.blue) << ") ";
		str << "Timer: " << e.getRawEvent()->timer.count;
		float deltaR = 0;
		float deltaG = 0;
		float deltaB = 0;

		if (!heldKeys.rKey) deltaR = 0;
		if (!heldKeys.gKey) deltaG = 0;
		if (!heldKeys.bKey) deltaB = 0;

		if (heldKeys.rKey && heldKeys.shiftKey) {
			deltaR = -1.0;
		}
		if (heldKeys.rKey && !heldKeys.shiftKey) {
			deltaR = +1.0;
		}
		if (heldKeys.gKey && heldKeys.shiftKey) {
			deltaG = -1.0;
		}
		if (heldKeys.gKey && !heldKeys.shiftKey) {
			deltaG = +1.0;
		}
		if (heldKeys.bKey && heldKeys.shiftKey) {
			deltaB = -1.0;
		}
		if (heldKeys.bKey && !heldKeys.shiftKey) {
			deltaB = +1.0;
		}

		if (e.getRawEvent()->timer.count % 5 == 0) {
			debugColor.green += deltaG;
			debugColor.red += deltaR;
			debugColor.blue += deltaB;
		}

		if (debugColor.green > 250) debugColor.green = 250;
		if (debugColor.green < 10) debugColor.green = 10;
		if (debugColor.red > 250) debugColor.red = 250;
		if (debugColor.red < 10) debugColor.red = 10;
		if (debugColor.blue > 250) debugColor.blue = 250;
		if (debugColor.blue < 10) debugColor.blue = 10;

		if (this->eq->isEmpty()) {
			al_set_target_bitmap(al_get_backbuffer(Display::getDisplay()));
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, 
				al_map_rgb(255, 0, 0), 
				bossPosition.x + this->bossBitmap->getScaledSize().width, 
				bossPosition.y + (this->bossBitmap->getScaledSize().height / 2) - 32, 
				0, 
				this->getName().c_str());
			al_draw_text(debugFont,
				al_map_rgb(debugColor.red, debugColor.green, debugColor.blue),
				10,
				10,
				0,
				str.str().c_str());
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
		case ALLEGRO_KEY_LSHIFT:
			heldKeys.shiftKey = true;
			break;
		case ALLEGRO_KEY_R:
			heldKeys.rKey = true;
			break;
		case ALLEGRO_KEY_G:
			heldKeys.gKey = true;
			break;
		case ALLEGRO_KEY_B:
			heldKeys.bKey = true;
			break;
		}
	});

	this->eq->registerForEvent(ALLEGRO_EVENT_KEY_UP, [&](Event& e) {
		switch (e.getKeyboardEvent().keycode) {
		case ALLEGRO_KEY_LSHIFT:
			heldKeys.shiftKey = false;
			break;
		case ALLEGRO_KEY_R:
			heldKeys.rKey = false;
			break;
		case ALLEGRO_KEY_G:
			heldKeys.gKey = false;
			break;
		case ALLEGRO_KEY_B:
			heldKeys.bKey = false;
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
