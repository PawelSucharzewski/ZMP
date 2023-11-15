#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <vector>
#include "AbstractInterp4Command.hh"

#define LINE_SIZE 1000
using namespace std;

vector<string> libs_names;

class LibInterface{
    void *_pLibHnd = nullptr;
    AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
  public:
  AbstractInterp4Command *_cmdHnd;
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

bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{
    string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    ostringstream OTmpStrm;

    Cmd4Preproc += NazwaPliku;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
    if (!pProc) return false;
    while (fgets(Line,LINE_SIZE,pProc)) 
    {
    OTmpStrm << Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

void ReadStreamLineByLine(std::istringstream& inputStream) {
    std::string line;
    while (std::getline(inputStream, line)) {
        std::cout << "Odczytano linię: " << line << std::endl;
    }
}

int main()
{
  libs_names.push_back("libInterp4Move.so");
  libs_names.push_back("libInterp4Set.so");
  libs_names.push_back("libInterp4Rotate.so");
  libs_names.push_back("libInterp4Pause.so");


  LibInterface MoveLibInterface;

  if (!MoveLibInterface.Init("libInterp4Move.so")) {
    return 1;
  }


  MoveLibInterface._cmdHnd = MoveLibInterface.CreateCmd();

  cout << endl;
  cout << MoveLibInterface._cmdHnd->GetCmdName() << endl;
  cout << endl;
  MoveLibInterface._cmdHnd->PrintSyntax();
  cout << endl;
  MoveLibInterface._cmdHnd->PrintCmd();
  cout << endl;
  
  delete MoveLibInterface._cmdHnd;

  LibInterface SetLibInterface;
  if (!SetLibInterface.Init("libInterp4Set.so")) {
    return 1;
  }

    SetLibInterface._cmdHnd = SetLibInterface.CreateCmd();

  cout << endl;
  cout << SetLibInterface._cmdHnd->GetCmdName() << endl;
  cout << endl; 
  SetLibInterface._cmdHnd->PrintSyntax();
  cout << endl;
  SetLibInterface._cmdHnd->PrintCmd();
  cout << endl;
  
  delete SetLibInterface._cmdHnd;

  LibInterface RotateLibInterface;

  if (!RotateLibInterface.Init("libInterp4Rotate.so")) {
    return 1;
  }

    RotateLibInterface._cmdHnd = RotateLibInterface.CreateCmd();

  cout << endl;
  cout << RotateLibInterface._cmdHnd->GetCmdName() << endl;
  cout << endl;
  RotateLibInterface._cmdHnd->PrintSyntax();
  cout << endl;
  RotateLibInterface._cmdHnd->PrintCmd();
  cout << endl;
  
  delete RotateLibInterface._cmdHnd;

  LibInterface PauseLibInterface;

  if (!PauseLibInterface.Init("libInterp4Pause.so")) {
    return 1;
  }

    PauseLibInterface._cmdHnd = PauseLibInterface.CreateCmd();

  cout << endl;
  cout << PauseLibInterface._cmdHnd->GetCmdName() << endl;
  cout << endl;
  PauseLibInterface._cmdHnd->PrintSyntax();
  cout << endl;
  PauseLibInterface._cmdHnd->PrintCmd();
  cout << endl;
  
  delete PauseLibInterface._cmdHnd;

  istringstream cmds;
  ExecPreprocesor("cmd.cmd",cmds);
  ReadStreamLineByLine(cmds);
  
}

