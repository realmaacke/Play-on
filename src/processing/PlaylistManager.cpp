#include "processing/PlaylistManager.hpp"
#include "Content.hpp"
#include <cstdio>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>
#include <rapidjson/filewritestream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

std::string PlaylistManager::parse_data(const std::string &line) {
    std::string parsedLine;

    if (line.find("") != std::string::npos) {
        // line contains, i.e. first line
    }

    return parsedLine;
}

void PlaylistManager::retrive_data() {
    std::ifstream playlist_file("./data/playlist.m3u");

    if (!playlist_file.is_open()) {
        std::cout << "File is not good" << std::endl;
    }
    std::string line;

    while (std::getline(playlist_file, line)) {
        this->parse_data(line);
    }

    std::vector<RawContent> data = {
        {"Test1", "location", "test-group", "google.com"},
        {"Test2", "location", "test-group", "google.com"},
        {"Test3", "location", "test-group", "google.com"},
        {"Test4", "location", "test-group", "google.com"},
        {"Test5", "location", "test-group", "google.com"}};

    result = data;
    data_dispatcher.emit();
}