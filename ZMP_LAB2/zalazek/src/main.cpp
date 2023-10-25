#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

using namespace std;

class LibInterface{
    void *_pLibHnd = nullptr;
    AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
  public:
  ~LibInterface() {if(_pLibHnd) dlclose(_pLibHnd);};
  bool Init(const char *sFileName);
  AbstractInterp4Command *CreateCmd() { assert(_pCreateCmd); return _pCreateCmd();}
};

bool LibInterface::Init(const char *sFileName){
  _pLibHnd = dlopen(sFileName,RTLD_LAZY);
  if (!_pLibHnd) {
    cerr << "!!! Brak biblioteki: " << sFileName << endl;
    return false;
  }
  void *pFun =dlsym(_pLibHnd,"CreateCmd");
   if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
  return true;
}


int main()
{
  LibInterface MoveLibInterface;

  if (!MoveLibInterface.Init("libInterp4Move.so")) {
    return 1;
  }


  AbstractInterp4Command *pCmd = MoveLibInterface.CreateCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  LibInterface SetLibInterface;

  if (!SetLibInterface.Init("libInterp4Set.so")) {
    return 1;
  }

    pCmd = SetLibInterface.CreateCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  LibInterface RotateLibInterface;

  if (!RotateLibInterface.Init("libInterp4Rotate.so")) {
    return 1;
  }

    pCmd = RotateLibInterface.CreateCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  LibInterface PauseLibInterface;

  if (!PauseLibInterface.Init("libInterp4Pause.so")) {
    return 1;
  }

    pCmd = PauseLibInterface.CreateCmd();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;
  
}

