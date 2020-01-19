cmake_minimum_required(VERSION 3.8)

project(multiplayer)

add_executable(out src/main.cpp)
target_compile_features(out PRIVATE cxx_std_17)