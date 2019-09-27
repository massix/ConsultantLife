#include <core/Game.h>
#include <core/Constants.h>
#include <core/Bitmap.h>
#include <core/Event.h>
#include <core/EventQueue.h>
#include <core/InitFailedExc.h>
#include <core/Display.h>
#include <core/Timer.h>
#include <core/SpriteSheet.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <json11.hpp>


using namespace cl::core;

Game::Game(std::string const& gameName) : gameName(gameName) {
}

Game::~Game() {
	Display::free();
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

	Display::init(1024, 768);
	al_set_window_title(Display::getDisplay(), this->gameName.c_str());
	return true;
}

void Game::mainLoop() {
	Timer mainTimer(1.0 / Constants::FPS);
	Timer animationTimer(1.0 / Constants::ANIMATIONSFPS);
	EventQueue eq;
	SpriteSheet basicConsultant("resources/basic_character.json");
	SpriteSheet pinkConsultant("resources/pink_consultant.json");
	Bitmap bossBitmap("resources/BossWalking_01.png");
	
	bossBitmap.scaleWithFactor(5.0);
	basicConsultant.load();
	pinkConsultant.load();
	
	eq.registerEventSource(Display::getEventSource());
	eq.registerEventSource(mainTimer.getEventSource());
	eq.registerEventSource(animationTimer.getEventSource());


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


	Animation const& basicFakeShoot = basicConsultant.getAnimation("fake_shoot");
	uint32_t basicCurrentFrame = 0;

	Animation const& pinkStand = pinkConsultant.getAnimation("front_stand");
	uint32_t pinkCurrentFrame = 0;

	Position bossPosition(8, Display::getHeight() - bossBitmap.getScaledSize().height - 10);
	Position textPosition{ bossPosition.x + (int32_t) bossBitmap.getScaledSize().width, 
		bossPosition.y + (int32_t) (bossBitmap.getScaledSize().height / 2) - 32 };

	eq.registerForEvent(ALLEGRO_EVENT_TIMER, [&](Event& e) {
		if (mainTimer == e.getRawEvent()->timer.source) {
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

			if (eq.isEmpty()) {
				al_set_target_bitmap(al_get_backbuffer(Display::getDisplay()));
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(font,
							 al_map_rgb(255, 0, 0),
							 textPosition.x,
							 textPosition.y,
							 0,
							 this->getName().c_str());
				al_draw_text(debugFont,
							 al_map_rgb(debugColor.red, debugColor.green, debugColor.blue),
							 10,
							 10,
							 0,
							 str.str().c_str());

				bossBitmap.draw(bossPosition);

				basicConsultant.drawFrame("fake_shoot", basicCurrentFrame, Position{ 48, 48 });
				pinkConsultant.drawFrame("front_stand", pinkCurrentFrame, Position{ 48, 126 });
				Display::flip();
			}
		} else if (animationTimer == e.getRawEvent()->timer.source) {
			basicCurrentFrame = (basicCurrentFrame + 1) % basicFakeShoot.getFrames();
			pinkCurrentFrame = (pinkCurrentFrame + 1) % pinkStand.getFrames();
		}
	});

	eq.registerForEvent(ALLEGRO_EVENT_KEY_DOWN, [&](Event& e) {
		switch (e.getKeyboardEvent().keycode) {
		case ALLEGRO_KEY_ESCAPE:
			eq.endLoop();
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

	eq.registerForEvent(ALLEGRO_EVENT_KEY_UP, [&](Event& e) {
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

	eq.registerForEvent(ALLEGRO_EVENT_DISPLAY_CLOSE, [&](Event& e) {
		eq.endLoop();
	});

	eq.registerForEvent(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN, [&](Event& e) {
		if (e.getMouseEvent().button == 1) {
			Position mousePosition(e.getMouseEvent().x, e.getMouseEvent().y);
			if (bossBitmap.isPositionInBitmapPosition(mousePosition)) {
				if (animationTimer.isRunning()) {
					animationTimer.stop();
				} else {
					animationTimer.start();
				}
			}
		}
	});

	mainTimer.start();
	animationTimer.start();
	eq.startLoop();
}

std::string const& Game::getName() const {
	return this->gameName;
}
