add_library(model SHARED Consultant.cpp)

include(DeclareNewSharedLibrary)
declare_new_shared_library(model)

find_package(sqlite3 CONFIG REQUIRED)
target_link_libraries(model sqlite3)