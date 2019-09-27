#include <json11.hpp>
#include <core/SpriteSheet.h>
#include <core/PositionSize.h>
#include <allegro5/allegro.h>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <exception>

using namespace cl::core;

SpriteSheet::SpriteSheet(std::string const& fileName) : 
	jsonFilename(fileName),
	json(nullptr), 
	parameters(nullptr),
	bitmap(nullptr) 
{

}

SpriteSheet::~SpriteSheet() {
	if (json != nullptr) {
		delete json;
	}

	if (parameters != nullptr) {
		delete parameters;
	}

	if (bitmap != nullptr) {
		al_destroy_bitmap(bitmap);
	}
}

void SpriteSheet::load() {
	std::stringstream content;
	std::string error;
	std::ifstream i(jsonFilename);

	content << i.rdbuf();
	i.close();

	// Double copy, let's go!
	// TODO: make this more efficient.
	json = new json11::Json(json11::Json::parse(content.str(), error));
	auto const& params = (*json)["parameters"];

	auto builder = Parameters::Builder()
		.withNature(params["nature"].string_value())
		.withXStart(params["x_start_at"].number_value())
		.withYStart(params["y_start_at"].number_value())
		.withXDistance(params["x_distance"].number_value())
		.withYDistance(params["y_distance"].number_value())
		.withPadding(params["padding"].number_value())
		.withSplit(params["split"].string_value());

	uint32_t index = 0;
	for (auto const& anim : params["animations"].array_items()) {
		builder.addAnimation(Animation(anim["name"].string_value(), anim["frames"].number_value(), index++));
	}

	parameters = builder.build();

	bitmap = al_load_bitmap(getSpriteSheetFilename().c_str());
	if (bitmap == nullptr) {
		throw new std::exception("Could not load bitmap file");
	}
}

std::string const& SpriteSheet::getName() const {
	return (*json)["name"].string_value();
}

std::string const& SpriteSheet::getSpriteSheetFilename() const {
	return (*json)["file"].string_value();
}

std::string const& SpriteSheet::getDescription() const {
	return (*json)["description"].string_value();
}

std::string const& SpriteSheet::getFormat() const {
	return (*json)["format"].string_value();
}

Animation const& SpriteSheet::getAnimation(std::string const& animationName) {
	for (auto const& anim : getParameters()->getAnimations()) {
		if (anim.getName() == animationName) {
			return anim;
		}
	}

	throw new std::exception();
}

void SpriteSheet::drawFrame(std::string const& animationName, uint8_t frame, Position const& position) {
	Animation const& animation = getAnimation(animationName);
	uint32_t xStart = getParameters()->getXStart() + (frame * getParameters()->getXDistance());
	uint32_t yStart = getParameters()->getYStart() + (animation.getIndex() * getParameters()->getYDistance());

	al_draw_bitmap_region(bitmap, 
						  xStart, 
						  yStart, 
						  getParameters()->getXDistance(), 
						  getParameters()->getYDistance(), 
						  position.x, 
						  position.y, 
						  0);
}

Parameters const* SpriteSheet::getParameters() const {
	return parameters;
}

std::string const& Parameters::getNature() const {
	return nature;
}

uint32_t const Parameters::getXStart() const {
	return xStart;
}

uint32_t const Parameters::getYStart() const {
	return yStart;
}

uint32_t const Parameters::getXDistance() const {
	return xDistance;
}

uint32_t const Parameters::getYDistance() const {
	return yDistance;
}

std::string const& Parameters::getSplit() const {
	return split;
}

std::vector<Animation> const& Parameters::getAnimations() const {
	return animations;
}

uint8_t const Animation::getFrames() const {
	return frames;
}

std::string const& Animation::getName() const {
	return name;
}

uint8_t const Animation::getIndex() const {
	return index;
}

Animation::~Animation() {
}
