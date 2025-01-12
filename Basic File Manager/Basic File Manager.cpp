// Basic File Manager.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

#include "FileManager.h"
#include "iostream"
#include "filesystem"

using namespace std;
namespace fs = std::filesystem;

int main() {
    FileManager fmObj;
    fmObj.runApplication();

    return 0;
}