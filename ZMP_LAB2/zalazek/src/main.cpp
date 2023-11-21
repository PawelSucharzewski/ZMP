#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include "../inc/AbstractInterp4Command.hh"
#include "../inc/AbstractMobileObj.hh"
#include "../inc/LibInterface.hh"
#include "../inc/Set4LibInterfaces.hh"
#include <cstdio>
#include <vector>
#define LINE_SIZE 500
#include <list>

using namespace std;


bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{

  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;

  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

  if (pProc==NULL) return false;

  while (fgets(Line,LINE_SIZE,pProc)) {
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


int main(int argc, char**argv)
{
Set4LibInterfaces set;
vector<string> plugins = {"libInterp4Move.so", "libInterp4Pause.so","libInterp4Rotate.so", "libInterp4Set.so"};
set.init(plugins);

istringstream command_stream;

ExecPreprocesor("cmd.cmd", command_stream );

set.ExecCmd(command_stream,NULL,0);
set.ExecCmd(command_stream,NULL,0);

return 0;
} 