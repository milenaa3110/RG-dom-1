#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

inline string load_shader_source(const char *filePath) {
    const ifstream file(filePath, ios::in | ios::binary);
    if (!file) {
        cerr << "Failed to open shader file: " << filePath << endl;
        return "";
    }
    ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

#endif
