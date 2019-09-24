#include <core/Bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace cl::core;

Bitmap::Bitmap(std::string const& filename) {
	this->filename = filename;

	this->bitmap = al_load_bitmap(this->filename.c_str());
	this->original.width = al_get_bitmap_width(this->bitmap);
	this->original.height = al_get_bitmap_height(this->bitmap);

	this->scaled.height = this->original.height;
	this->scaled.width = this->original.width;
}

Bitmap::~Bitmap() {
	al_destroy_bitmap(this->bitmap);
}

ALLEGRO_BITMAP* Bitmap::getRaw() {
	return this->bitmap;
}

void Bitmap::scale(uint32_t newWidth, uint32_t newHeight) {
	this->scaled.width = newWidth;
	this->scaled.height = newHeight;
}

void Bitmap::scaleWithFactor(float factor) {
	this->scaled.height = this->original.height * factor;
	this->scaled.width = this->original.width * factor;
}

void Bitmap::setPosition(Position const& position) {
	this->position = position;
}

void Bitmap::draw(Position const& newPosition) {
	this->setPosition(newPosition);
	if (this->scaled.width != this->original.width || this->scaled.height != this->original.height) {
		al_draw_scaled_bitmap(this->bitmap,
			0, 0,
			this->original.width, this->original.height,
			this->getPosition().x, this->getPosition().y,
			this->scaled.width, this->scaled.height,
			0);
	}
	else {
		al_draw_bitmap(this->bitmap, this->position.x, this->position.y, 0);
	}
}

Position const& Bitmap::getPosition() const {
	return this->position;
}

Size const& Bitmap::getOriginalSize() const {
	return this->original;
}

Size const& Bitmap::getScaledSize() const {
	return this->scaled;
}

bool Bitmap::isPositionInBitmapPosition(Position const& other) const {
	bool isX = this->getPosition().x < other.x && other.x < (this->getPosition().x + this->scaled.width);
	bool isY = this->getPosition().y < other.y && other.y < (this->getPosition().y + this->scaled.height);

	return (isX && isY);
}
