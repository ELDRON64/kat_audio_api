#pragma once
#include <filesystem>

#define root_path std::filesystem::current_path()
#define audio_libs_path root_path"/audio_libs"

int setup ( ) {
    std::filesystem::create_directory(audio_libs_path);
}