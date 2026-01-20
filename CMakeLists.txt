cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME "hello_setup")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		src/main.cpp
)
