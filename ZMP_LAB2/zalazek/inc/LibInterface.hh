#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

class LibInterface{
private:
    void *_LibHandler;
    std::string _CmdName;
    AbstractInterp4Command *(*_pCreateCmd)(void);

public:
    ~LibInterface();
    bool init(std::string libraryName);
    AbstractInterp4Command *CreateCmd();
};
#endif
