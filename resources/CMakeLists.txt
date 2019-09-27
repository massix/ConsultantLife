file(GLOB resources_FONTS "*.ttf")
file(GLOB resources_IMAGES "*.png")
file(GLOB resources_JSONS "*.json")

foreach(font ${resources_FONTS})
	get_filename_component(font_NAME ${font} NAME)
	message(STATUS "Copying ${font_NAME}")
	configure_file(
		"${font}"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/${font_NAME}"
		COPYONLY
	)
endforeach(font)

foreach(image ${resources_IMAGES})
	get_filename_component(image_NAME ${image} NAME)
	message(STATUS "Copying ${image_NAME}")
	configure_file(
		"${image}"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/${image_NAME}"
		COPYONLY
	)
endforeach(image)

foreach(json ${resources_JSONS})
	get_filename_component(json_NAME ${json} NAME)
	message(STATUS "Copying ${json_NAME}")
	configure_file(
		"${json}"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/${json_NAME}"
		COPYONLY
	)
endforeach(json)
