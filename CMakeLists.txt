cmake_minimum_required(VERSION 3.8)

project(multiplayer)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

if(MSVC)
	target_link_libraries(server PRIVATE wsock32 ws2_32)
	target_link_libraries(client PRIVATE wsock32 ws2_32)
else() 
	message(FATAL_ERROR "OS currently unsupported.")
endif()

target_compile_features(server PRIVATE cxx_std_17)
target_compile_features(client PRIVATE cxx_std_17)