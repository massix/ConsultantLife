#pragma once

#include <core_export.h>
#include <string>
#include <vector>

extern "C" {
	struct ALLEGRO_BITMAP;
}

namespace json11 {
	class Json;
}

namespace cl {
	namespace core {
		typedef std::vector<uint16_t> Data;

		class CORE_EXPORT Layer {
		public:
			Layer(json11::Json const* structure);
			Data const& getData() const;
			uint32_t getHeight() const;
			uint32_t getWidth() const;
			uint32_t getX() const;
			uint32_t getY() const;
			uint8_t getId() const;
			bool isVisible() const;
			std::string const& getName() const;
		private:
			Data data;
			std::string name;
			json11::Json const* structure;
		};

		typedef std::vector<Layer> Layers;

		class CORE_EXPORT TileSet {
		public:
			TileSet(json11::Json const* structure);
			std::string const& getImageFile() const;

		private:
			std::string imageFile;
			json11::Json const* structure;
		};

		typedef std::vector<TileSet> TileSets;

		class CORE_EXPORT TileMap {
		public:
			TileMap(std::string const& fileName);
			virtual ~TileMap();
			void load();
			uint32_t getHeight() const;
			uint32_t getWidth() const;
			uint32_t getTileHeight() const;
			uint32_t getTileWidth() const;
			bool isInfinite() const;
			Layers const& getLayers() const;
			TileSets const& getTileSets() const;


		private:
			ALLEGRO_BITMAP* map;
			std::string const fileName;
			json11::Json* structure;
			Layers layers;
			TileSets tileSets;

		};
	}
}