#include <core/Bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace cl::core;

Bitmap::Bitmap(std::string const& filename) : filename(filename), owner(true) {
	bitmap = al_load_bitmap(filename.c_str());
	original.width = al_get_bitmap_width(bitmap);
	original.height = al_get_bitmap_height(bitmap);

	scaled.height = original.height;
	scaled.width = original.width;
}

Bitmap::Bitmap(uint32_t w, uint32_t h) : owner(true) {
	bitmap = al_create_bitmap(w, h);

	original.width = w;
	original.height = h;

	scaled.width = w;
	scaled.height = h;
}

Bitmap::Bitmap(ALLEGRO_BITMAP* bitmap) : owner(false), bitmap(bitmap) {
	original.width = al_get_bitmap_width(bitmap);
	original.height = al_get_bitmap_height(bitmap);

	scaled.width = original.width;
	scaled.height = original.height;
}

void Bitmap::setOwner(bool isOwner) {
	owner = isOwner;
}

bool Bitmap::isOwner() const {
	return owner;
}

Bitmap::~Bitmap() {
	if (isOwner() && bitmap != nullptr) {
		al_destroy_bitmap(bitmap);
	}
}

ALLEGRO_BITMAP* Bitmap::getRaw() {
	return bitmap;
}

void Bitmap::scale(uint32_t newWidth, uint32_t newHeight) {
	scaled.width = newWidth;
	scaled.height = newHeight;
}

void Bitmap::scaleWithFactor(float factor) {
	scaled.height = original.height * factor;
	scaled.width = original.width * factor;
}

void Bitmap::setPosition(Position const& newPosition) {
	position = newPosition;
}

void Bitmap::draw(Position const& newPosition) {
	setPosition(newPosition);
	if (scaled.width != original.width || scaled.height != original.height) {
		al_draw_scaled_bitmap(bitmap,
			0, 0,
			original.width, original.height,
			getPosition().x, getPosition().y,
			scaled.width, scaled.height,
			0);
	}
	else {
		al_draw_bitmap(bitmap, position.x, position.y, 0);
	}
}

void Bitmap::setTarget() const {
	al_set_target_bitmap(bitmap);
}

Position const& Bitmap::getPosition() const {
	return position;
}

Size const& Bitmap::getOriginalSize() const {
	return original;
}

Size const& Bitmap::getScaledSize() const {
	return scaled;
}

bool Bitmap::isPositionInBitmapPosition(Position const& other) const {
	bool isX = getPosition().x < other.x && other.x < (getPosition().x + scaled.width);
	bool isY = getPosition().y < other.y && other.y < (getPosition().y + scaled.height);

	return (isX && isY);
}
