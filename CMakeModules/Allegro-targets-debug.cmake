#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "allegro" for configuration "Debug"
set_property(TARGET allegro APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(allegro PROPERTIES
	IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/allegro-debug.lib"
	IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/allegro-debug-5.2.dll"
  )

foreach(al_module ${allegro_MODULES})
	set_property(TARGET allegro::${al_module} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_target_properties(allegro::${al_module} PROPERTIES
		IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/allegro_${al_module}-debug.lib"
		IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/allegro_${al_module}-debug-5.2.dll"
	)
endforeach()

list(APPEND _IMPORT_CHECK_TARGETS allegro )
list(APPEND _IMPORT_CHECK_FILES_FOR_allegro 
	"${_IMPORT_PREFIX}/debug/lib/allegro-debug.lib" 
	"${_IMPORT_PREFIX}/debug/bin/allegro-debug-5.2.dll"
)

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
