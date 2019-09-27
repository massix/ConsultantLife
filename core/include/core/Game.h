#pragma once

#include <core_export.h>
#include <string>
#include <exception>

namespace cl {
	namespace core {
		class CORE_EXPORT Game {
		public:
			Game(std::string const&);
			~Game();
			bool init();
			void mainLoop();
			std::string const& getName() const;

		private:
			Game(Game const&) = delete;
			Game& operator=(Game const&) = delete;
			std::string gameName;
		};
	}
}
