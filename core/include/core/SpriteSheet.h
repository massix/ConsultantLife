#pragma once
#include <string>
#include <vector>
#include <core_export.h>

extern "C" {
	struct ALLEGRO_BITMAP;
}

namespace json11 {
	class Json;
}

namespace cl {
	namespace core {
		struct Position;

		/* Holder of an Animation, composed of different frames */
		class CORE_EXPORT Animation final {
		public:
			Animation(std::string const& name, uint8_t const frames, uint8_t const index) :
				name(name),
				frames(frames),
				index(index) {};
			virtual ~Animation();
			std::string const& getName() const;
			uint8_t const getFrames() const;
			uint8_t const getIndex() const;
		private:
			std::string const name;
			uint8_t const frames;
			uint8_t const index;
		};

		/* Parameters as found in the JSON reference file for the SpriteSheet */
		class CORE_EXPORT Parameters final {
		public:

			/* Builder class for parameters.. */
			class Builder final {
			public:
				Builder() : instance(new Parameters()) {}
				Builder& withNature(std::string const&);
				Builder& withXStart(uint32_t);
				Builder& withYStart(uint32_t);
				Builder& withXDistance(uint32_t);
				Builder& withYDistance(uint32_t);
				Builder& withPadding(uint32_t);
				Builder& withSplit(std::string const&);
				Builder& addAnimation(Animation const&);
				Parameters* build();
			private:
				Parameters* instance;
			};

		private:
			Parameters() : xStart(0), yStart(0), xDistance(0), yDistance(0), padding(0) {};
			Parameters(Parameters const&) = delete;
			Parameters& operator=(Parameters const&) = delete;

			std::string nature;
			uint32_t xStart;
			uint32_t yStart;
			uint32_t xDistance;
			uint32_t yDistance;
			uint32_t padding;
			std::string split;
			std::vector<Animation> animations;

		public:
			std::string const& getNature() const;
			uint32_t const getXStart() const;
			uint32_t const getYStart() const;
			uint32_t const getXDistance() const;
			uint32_t const getYDistance() const;
			std::string const& getSplit() const;
			std::vector<Animation> const& getAnimations() const;
		};

		/* Holder of a SpriteSheet */
		class CORE_EXPORT SpriteSheet {
		public:
			SpriteSheet(std::string const& fileName);
			virtual ~SpriteSheet();

			void load();
			std::string const& getName() const;
			std::string const& getSpriteSheetFilename() const;
			std::string const& getDescription() const;
			std::string const& getFormat() const;
			Parameters const* getParameters() const;
			Animation const& getAnimation(std::string const&);
			void drawFrame(std::string const& animationName, uint8_t frame, Position const& position);

		private:
			std::string jsonFilename;
			json11::Json* json;
			Parameters* parameters;
			ALLEGRO_BITMAP* bitmap;
		};
	}
}