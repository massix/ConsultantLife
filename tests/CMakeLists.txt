file(GLOB core_TESTS "src/core/*.cpp")

find_package(GTest CONFIG REQUIRED)

add_executable(coreTests ${core_TESTS})
target_compile_definitions(coreTests PUBLIC "RESOURCES_DIRECTORY=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources\"")
target_link_libraries(coreTests GTest::gtest GTest::gtest_main core)

add_test(AllTestsInCore "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/coreTests")
