#include "../inc/LibInterface.hh"

using namespace std;
bool LibInterface::init(std::string lib_name)
{

  	void *pFun;
  	_LibHandler = dlopen(lib_name.c_str(),RTLD_LAZY);
	if(_LibHandler == NULL)
		{
		    cerr << "!!! Brak biblioteki:" <<lib_name << endl;
   			return 0;
		}
			cout << "Znaleziono bibliotekę:"<<lib_name<<endl;

	pFun = dlsym(_LibHandler,"CreateCmd");
	if(pFun == NULL)
		{
    		cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
   			return 0;
		}
  	_pCreateCmd= reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
	pFun=NULL;

	pFun = dlsym(_LibHandler,"GetCmdName");
	if(pFun == NULL)
		{
    		cerr << "!!! Nie znaleziono funkcji GetCmdName" << endl;
   			return 0;
		}
  	_pGetCmdName= reinterpret_cast<const char* (*)(void)>(pFun);
	pFun=NULL;
	return 1;
}


std::string LibInterface::_CmdName()
{
 	return _pGetCmdName();
}

