#pragma once

#include "Content.hpp"
#include "glibmm/dispatcher.h"
#include <future>
#include <string>
#include <vector>

class PlaylistManager {

  public:
    PlaylistManager() {}
    std::string parse_data(const std::string &line);

    void retrive_data();

    Glib::Dispatcher data_dispatcher;
    std::vector<RawContent> result;

  private:
    std::string playlist_path; // This will change in future.
};