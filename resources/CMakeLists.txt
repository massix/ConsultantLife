file(GLOB resources_FONTS "*.ttf")
foreach(font ${resources_FONTS})
	get_filename_component(FONT_name ${font} NAME)
	configure_file(
		"${font}"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/${FONT_name}"
		COPYONLY
	)
endforeach(font)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/BossWalking_01.png" 
	"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/BossWalking_01.png"
	COPYONLY
)