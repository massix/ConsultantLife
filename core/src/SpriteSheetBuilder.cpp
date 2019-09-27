#include <core/SpriteSheet.h>

using namespace cl::core;

Parameters::Builder& Parameters::Builder::withNature(std::string const& nature) {
	instance->nature = nature;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withXStart(uint32_t xStart) {
	instance->xStart = xStart;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withYStart(uint32_t yStart) {
	instance->yStart = yStart;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withXDistance(uint32_t xDistance) {
	instance->xDistance = xDistance;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withYDistance(uint32_t yDistance) {
	instance->yDistance = yDistance;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withPadding(uint32_t padding) {
	instance->padding = padding;
	return (*this);
}

Parameters::Builder& Parameters::Builder::withSplit(std::string const& split) {
	instance->split = split;
	return (*this);
}

Parameters::Builder& Parameters::Builder::addAnimation(Animation const& animation) {
	instance->animations.push_back(animation);
	return (*this);
}

Parameters* Parameters::Builder::build() {
	return instance;
}
