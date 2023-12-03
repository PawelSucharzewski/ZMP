#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

// #include "LibInterface.hh"

#include "MobileObjConfig.hh"

using namespace std;

class Configuration {
  public:
    std::vector<MobileObjConfig>_ObjectsConfig;
    std::vector<std::string> libs;
};

#endif
