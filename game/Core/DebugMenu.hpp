#pragma once


#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <raylib.h>


class DebugMenu {
private:
    std::map<int, std::function<std::string()>> entries;

    // Private constructor for singleton
    DebugMenu() {}

public:
    // Delete copy constructor and assignment operator to prevent duplication
    DebugMenu(const DebugMenu&) = delete;
    DebugMenu& operator=(const DebugMenu&) = delete;

    static DebugMenu& getInstance() {
        static DebugMenu instance; // Singleton instance
        return instance;
    }

    void setEntry(int position, const std::function<std::string()>& entry) {
        entries[position] = entry;
    }

    void render() const {
        int step = 20;
        for (const auto& [position, entry] : entries) {
            int y = position * step;
            DrawText(entry().c_str(), 0, y, 20, BLACK);
        }
    }

    void clear() {
        entries.clear();
    }
};