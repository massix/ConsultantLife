#include <core/TileMap.h>
#include <allegro5/allegro.h>
#include <core/Bitmap.h>
#include <json11.hpp>
#include <sstream>
#include <fstream>

using namespace cl::core;

TileMap::TileMap(std::string const& fileName) : 
	fileName(fileName),
	structure(nullptr),
	map(nullptr)
{

}

TileMap::~TileMap() {
	if (map != nullptr) {
		delete map;
	}

	if (structure != nullptr) {
		delete structure;
	}
}

void TileMap::load() {
	std::stringstream content;
	std::string error;

	std::ifstream i(fileName);
	content << i.rdbuf();
	i.close();

	structure = new json11::Json(json11::Json::parse(content.str(), error));
	for (auto const& layer : (*structure)["layers"].array_items()) {
		layers.push_back(Layer(&layer));
	}

	for (auto const& tileset : (*structure)["tilesets"].array_items()) {
		tileSets.push_back(TileSet(&tileset));
	}
}

void TileMap::createMap() {
	map = new Bitmap(getWidth() * getTileWidth(), getHeight() * getTileHeight());

	Bitmap oldTarget(al_get_target_bitmap());

	// !! Do not delete the bitmap object (we would destroy the main screen otherwise!)
	oldTarget.setOwner(false);

	// Draw each layer
	for (auto const& layer : getLayers()) {
		Bitmap l(layer.getWidth() * getTileWidth(), layer.getHeight() * getTileHeight());
		l.setTarget();

		uint32_t x = 0;
		uint32_t y = 0;
		for (auto const& d : layer.getData()) {
			auto const& tileSet = getTileSets().front();
			auto* b = tileSet.getBitmapAt(d);
			al_draw_bitmap(b, x * getTileWidth(), y * getTileHeight(), 0);

			if (++x >= layer.getWidth()) {
				x = 0;
				y++;
			}
		}

		map->setTarget();
		l.draw(Position{ 0, 0 });
	}

	oldTarget.setTarget();
}

ALLEGRO_BITMAP* TileMap::getMap() const {
	return map->getRaw();
}

uint32_t TileMap::getHeight() const {
	return (*structure)["height"].number_value();
}

uint32_t TileMap::getWidth() const {
	return (*structure)["width"].number_value();
}

uint32_t TileMap::getTileHeight() const {
	return (*structure)["tileheight"].number_value();
}

uint32_t TileMap::getTileWidth() const {
	return (*structure)["tilewidth"].number_value();
}

bool TileMap::isInfinite() const {
	return (*structure)["infinite"].bool_value();
}

Layers const& TileMap::getLayers() const {
	return layers;
}

void TileMap::draw(Position const& position) const {
	map->draw(position);
}

TileSets const& TileMap::getTileSets() const {
	return tileSets;
}

Layer::Layer(json11::Json const* structure) : structure(structure) {
	name = (*structure)["name"].string_value();
	for (auto d : (*structure)["data"].array_items()) {
		data.push_back(d.number_value());
	}
}

Data const& Layer::getData() const {
	return data;
}

uint32_t Layer::getHeight() const {
	return (*structure)["height"].number_value();
}

uint32_t Layer::getWidth() const {
	return (*structure)["width"].number_value();
}

uint32_t Layer::getX() const {
	return (*structure)["x"].number_value();
}

uint32_t Layer::getY() const {
	return (*structure)["y"].number_value();
}

uint8_t Layer::getId() const {
	return (*structure)["id"].number_value();
}

bool Layer::isVisible() const {
	return (*structure)["visible"].bool_value();
}

std::string const& Layer::getName() const {
	return name;
}

TileSet::TileSet(json11::Json const* structure) : structure(structure), map(nullptr) {
	imageFile = (*structure)["image"].string_value();
	map = al_load_bitmap(imageFile.c_str());
}

TileSet::~TileSet() {
	if (map != nullptr) {
		// FIXME: somehow this doesn't work, I might have messed up something..
		//al_destroy_bitmap(map);
		//map = nullptr;
	}
}

std::string const& TileSet::getImageFile() const {
	return imageFile;
}

uint32_t TileSet::getFirstGid() const {
	return (*structure)["firstgid"].number_value();
}

uint32_t TileSet::getTilesCount() const {
	return (*structure)["tilecount"].number_value();
}

uint32_t TileSet::getTileHeight() const {
	return (*structure)["tileheight"].number_value();
}

uint32_t TileSet::getTileWidth() const {
	return (*structure)["tilewidth"].number_value();
}

uint32_t TileSet::getColumns() const {
	return (*structure)["columns"].number_value();
}

uint32_t TileSet::getSpacing() const {
	return (*structure)["spacing"].number_value();
}

ALLEGRO_BITMAP* TileSet::getBitmapAt(uint32_t position) const {
	
	if (Cache.find(position) != Cache.end()) {
		return Cache.find(position)->second;
	}
	
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	ALLEGRO_BITMAP* tmp = al_create_bitmap(getTileWidth(), getTileHeight());
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t realPosition = position - getFirstGid();

	x = (realPosition % getColumns());
	y = realPosition / getColumns();

	// Draw into the new bitmap
	al_set_target_bitmap(tmp);
	al_draw_bitmap_region(map, x * getTileWidth() + (x * getSpacing()), y * getTileHeight() + (y * getSpacing()), getTileWidth(), getTileHeight(), 0, 0, 0);

	// Store in cache
	Cache[position] = tmp;

	// Restore old target
	al_set_target_bitmap(old);

	return tmp;
}
