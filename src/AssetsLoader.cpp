#include "AssetsLoader.hpp"

AssetsLoader::AssetsLoader(const char *name)
{
    assetName.assign(name);
}

AssetsLoader::~AssetsLoader()
{
}

string AssetsLoader::getPath()
{
    string prefix;
#ifdef WIN32
    prefix.assign("../../assets/");
#else
    prefix.assign("../assets/");
#endif
    return prefix.append(assetName);
}