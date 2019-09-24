add_library(core SHARED Game.cpp Bitmap.cpp)

include(DeclareNewSharedLibrary)
declare_new_shared_library(core)

find_package(allegro CONFIG REQUIRED)
target_link_libraries(core allegro allegro::dialog allegro::image)
