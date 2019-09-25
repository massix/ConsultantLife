file(GLOB core_SOURCES "src/*.cpp")
add_library(core SHARED ${core_SOURCES})

include(DeclareNewSharedLibrary)
declare_new_shared_library(core)

find_package(allegro CONFIG REQUIRED)
target_link_libraries(core allegro allegro::dialog allegro::image)
