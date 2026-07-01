#include "processing/PlaylistManager.hpp"
#include "Content.hpp"
#include <vector>

void PlaylistManager::parse_data() {}

void PlaylistManager::retrive_data() {

    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    std::vector<RawContent> data = {
        {"Test1", "location", "test-group", "google.com"},
        {"Test2", "location", "test-group", "google.com"},
        {"Test3", "location", "test-group", "google.com"},
        {"Test4", "location", "test-group", "google.com"},
        {"Test5", "location", "test-group", "google.com"}};

    result = data;
    data_dispatcher.emit();
}