#include <core/TileMap.h>
#include <allegro5/allegro.h>
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
	if (structure != nullptr)
		delete structure;
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

TileSet::TileSet(json11::Json const* structure) : structure(structure) {
	imageFile = (*structure)["image"].string_value();
}

std::string const& TileSet::getImageFile() const {
	return imageFile;
}
