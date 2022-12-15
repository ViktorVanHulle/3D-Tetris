# executable file creation
add_executable(
	Blockout
	Main.cpp
	Window.cpp
	Game.cpp
	GameRenderer.cpp
	Tunnel.cpp
	Shaders.cpp
	Block.cpp
	TextureLoader.cpp
	"Main.h" "Window.h" "Game.h" "GameRenderer.h" "Tunnel.h"
 "Shaders.h" "Block.h" "Color.h" "TextureLoader.h")

target_link_libraries(${PROJECT_NAME} PRIVATE TCLAP)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/resources/cube_texture.png
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/cube_texture.png
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/resources/floor_texture.png 
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/floor_texture.png
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${PROJECT_NAME} PRIVATE TEXTURE_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/")
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)