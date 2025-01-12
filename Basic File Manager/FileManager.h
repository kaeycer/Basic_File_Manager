#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = filesystem;

class FileManager {
public:
    FileManager();
    void changeDirectory(const string& strDestPath);
    void listContents();
    void createDirectory(const string& strName);
    void copyFile(const string& strSource, const string& strDestination);
    void viewFiles();
    void moveFiles(const string& strSource, const string& strDestination);
    void runApplication();
    void inputEdgeCase();

    // Accessors and Getters
    fs::path getPath() const;

private:
    fs::path _currentPath;
    vector<string> vecCommand;
};

#endif // FILEMANAGER_H
