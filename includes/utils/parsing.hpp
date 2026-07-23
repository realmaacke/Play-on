#include <string>

inline std::string get_attribute(
    const std::string &line, const std::string &key) {
    auto pos = line.find(key + "=\"");

    if (pos == std::string::npos)
        return {};

    pos += key.size() + 2;

    auto end = line.find('"', pos);

    if (end == std::string::npos)
        return {};

    return line.substr(pos, end - pos);
}

inline bool get_episode_info(
    const std::string &text, int &season, int &episode) {

    for (size_t i = 0; i + 3 < text.size(); i++) {
        if ((text[i] == 'S' || text[i] == 's') && std::isdigit(text[i + 1])) {
            size_t pos = i + 1;

            int s = 0;
            while (pos < text.size() && std::isdigit(text[pos])) {
                s = s * 10 + (text[pos] - '0');
                pos++;
            }

            while (pos < text.size() && std::isspace(text[pos]))
                pos++;

            if (pos < text.size() && (text[pos] == 'E' || text[pos] == 'e')) {
                int e = 0;
                bool found = false;

                pos++;

                while (pos < text.size() && std::isdigit(text[pos])) {
                    found = true;
                    e = e * 10 + (text[pos] - '0');
                    pos++;
                }

                if (found) {
                    season = s;
                    episode = e;
                    return true;
                }
            }
        }
    }

    return false;
}