#include "header.h"

#ifndef ASSETSLOADER_H
#define ASSETSLOADER_H
#pragma once

using std::string;

class AssetsLoader
{
private:
    string assetName;

public:
    AssetsLoader(const char *name);

    ~AssetsLoader();

    string getPath();
};

#endif