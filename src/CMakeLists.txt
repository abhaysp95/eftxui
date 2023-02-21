set(TARGET eftxui)


function(example name)
	add_executable(${TARGET}_${name} ${name}.cpp)
	target_include_directories(${TARGET}_${name} PRIVATE ..)
	target_link_libraries(${TARGET}_${name} PUBLIC

		PRIVATE ftxui::screen
		PRIVATE ftxui::dom
		PRIVATE ftxui::component
	)

	install(TARGETS ${TARGET}_${name} RUNTIME DESTINATION bin)

endfunction(example)

example(starter)
example(screen_basic)
example(dom_basic)
example(paragraph_basic)
example(graph_basic)
example(color_info_palette256)
example(color_truecolor_hsv)
example(color_truecolor_rgb)
example(color_gallery_basic)
example(layout_hbox_vbox_basic)
example(layout_gridbox_basic)
example(layout_flexbox_basic)
example(table_basic)

# add_executable(${TARGET} starter.cpp)

# target_include_directories(${TARGET} PRIVATE ..)

# # target_link_libraries(${TARGET} PRIVATE ftxui)

# target_link_libraries(${TARGET}
#   PRIVATE ftxui::screen
#   PRIVATE ftxui::dom
#   # PRIVATE ftxui::component # Not needed for this example.
# )

