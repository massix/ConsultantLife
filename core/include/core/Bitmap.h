#pragma once

#include <core_export.h>
#include <string>
#include <core/PositionSize.h>

extern "C" {
	struct ALLEGRO_BITMAP;
}

namespace cl {
	namespace core {
		class CORE_EXPORT Bitmap {
		public:
			Bitmap(std::string const& filename);
			virtual ~Bitmap();

			ALLEGRO_BITMAP* getRaw();
			void scale(uint32_t newWidth, uint32_t newHeight);
			void scaleWithFactor(float factor);
			void setPosition(Position const& position);
			void draw(Position const& newPosition);
			Position const & getPosition() const;
			Size const& getOriginalSize() const;
			Size const& getScaledSize() const;

			bool isPositionInBitmapPosition(Position const& other) const;

		private:
			Bitmap() = delete;

			std::string filename;

			Position position;
			Size original;
			Size scaled;

			ALLEGRO_BITMAP* bitmap;
		};
	}
}