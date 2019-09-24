#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "allegro" for configuration "Release"
set_property(TARGET allegro APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(allegro PROPERTIES
	IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/allegro.lib"
	IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/allegro-5.2.dll"
  )

foreach(al_module ${allegro_MODULES})
	set_property(TARGET allegro::${al_module} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
	set_target_properties(allegro::${al_module} PROPERTIES
		IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/allegro_${al_module}.lib"
		IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/allegro_${al_module}.dll"
	)
endforeach()

list(APPEND _IMPORT_CHECK_TARGETS allegro )
list(APPEND allegro "${_IMPORT_PREFIX}/lib/allegro.lib" "${_IMPORT_PREFIX}/bin/allegro-5.2.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
