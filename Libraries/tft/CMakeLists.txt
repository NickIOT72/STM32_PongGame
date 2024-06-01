cmake_minimum_required(VERSION 3.22)

project( tft LANGUAGES CXX)

add_library( ${PROJECT_NAME} INTERFACE)
enable_language(C ASM)

target_compile_definitions(${PROJECT_NAME} INTERFACE 
	USE_HAL_DRIVER 
	STM32F446xx
  $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories( ${PROJECT_NAME} INTERFACE
  ${PROJECT_SOURCE_DIR}
)

target_sources(  ${PROJECT_NAME} INTERFACE
  ${PROJECT_SOURCE_DIR}/tft.c
  ${PROJECT_SOURCE_DIR}/fonts.c
)
