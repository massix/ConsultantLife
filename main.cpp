#include <core/Game.h>
#include <model/Consultant.h>
#include <string>
#include <iostream>

using namespace cl;

int main(int argc, char *argv[]) {
	test();
	core::Game g(std::string("LETAN"));
	if (g.init()) {
		g.mainLoop();
	}

	return 0;
}
