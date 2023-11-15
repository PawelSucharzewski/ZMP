#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <vector>
#include "AbstractInterp4Command.hh"

#define LINE_SIZE 1000
using namespace std;


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

void printCmdValuesAndSyntax(AbstractInterp4Command *_cmdPtr){
  cout << endl;
  cout << _cmdPtr->GetCmdName() << endl;
  cout << endl;
  _cmdPtr->PrintSyntax();
  cout << endl;
  _cmdPtr->PrintCmd();
  cout << endl;
}


void ReadStreamLineByLine(std::istringstream& inputStream,vector<AbstractInterp4Command*> cmdPtr) {
    std::string line;

    while (std::getline(inputStream, line)) {
        std::istringstream lineStream(line);
        std::string functionName;
        lineStream >> functionName;
        if(functionName == "Move"){
          cmdPtr[0]->ReadParams(lineStream);
          printCmdValuesAndSyntax(cmdPtr[0]);
          cout << "Wywołano Move" << endl;
        }
        else if(functionName == "Set"){
          cmdPtr[1]->ReadParams(lineStream);
          printCmdValuesAndSyntax(cmdPtr[1]);
          cout << "Wywołano Set" << endl;
        }
        else if(functionName == "Pause"){
          cmdPtr[3]->ReadParams(lineStream);
          printCmdValuesAndSyntax(cmdPtr[3]);
          cout << "Wywołano Pause" << endl;
        }
        else if(functionName == "Rotate"){
          cmdPtr[2]->ReadParams(lineStream);
          printCmdValuesAndSyntax(cmdPtr[2]);
          cout << "Wywołano Rotate" << endl;
        }
    }
}

int main()
{
  vector<AbstractInterp4Command*> cmdPtr;
  LibInterface MoveLibInterface;
  if (!MoveLibInterface.Init("libInterp4Move.so")) {
    return 1;
  }

  MoveLibInterface._cmdHnd = MoveLibInterface.CreateCmd();
  cmdPtr.push_back(MoveLibInterface._cmdHnd);
  printCmdValuesAndSyntax(MoveLibInterface._cmdHnd);

  LibInterface SetLibInterface;
  if (!SetLibInterface.Init("libInterp4Set.so")) {
    return 1;
  }

  SetLibInterface._cmdHnd = SetLibInterface.CreateCmd();
  cmdPtr.push_back(SetLibInterface._cmdHnd);
  printCmdValuesAndSyntax(SetLibInterface._cmdHnd);

  LibInterface RotateLibInterface;

  if (!RotateLibInterface.Init("libInterp4Rotate.so")) {
    return 1;
  }

  RotateLibInterface._cmdHnd = RotateLibInterface.CreateCmd();
  cmdPtr.push_back(RotateLibInterface._cmdHnd);
  printCmdValuesAndSyntax(RotateLibInterface._cmdHnd);

  LibInterface PauseLibInterface;

  if (!PauseLibInterface.Init("libInterp4Pause.so")) {
    return 1;
  }

  PauseLibInterface._cmdHnd = PauseLibInterface.CreateCmd();
  printCmdValuesAndSyntax(PauseLibInterface._cmdHnd);
  cmdPtr.push_back(PauseLibInterface._cmdHnd);

  istringstream cmds;
  ExecPreprocesor("cmd.cmd",cmds);
  ReadStreamLineByLine(cmds,cmdPtr);

  
}

