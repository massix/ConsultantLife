function(declare_new_shared_library lib_name)
	message(STATUS "Declaring new library ${lib_name}")
	include(GenerateExportHeader)
	generate_export_header(${lib_name})

	target_include_directories(${lib_name}
		PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
		PUBLIC "${CMAKE_CURRENT_BINARY_DIR}"
	)

	set_target_properties(${lib_name} PROPERTIES
		IMPORTED_IMPLIB "${CMAKE_CURRENT_BINARY_DIR}/${lib_name}.lib"
		IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/${lib_name}.dll"
	)
endfunction(declare_new_shared_library)