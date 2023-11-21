#include "Set4LibInterfaces.hh"
using namespace std;
bool Set4LibInterfaces::init(std::vector<std::string> plugins)
{
	for(vector<string>::iterator it = plugins.begin();
		it!=plugins.end();++it)
	{
 shared_ptr<LibInterface> _libtmp = make_shared<LibInterface>();
	  if(!_libtmp->init(*it))
		{
	    cerr << "!!! Brak biblioteki: "<<*it << endl;
	    return 0;
		}

	  libSet.insert(make_pair(_libtmp->_CmdName(),_libtmp));
	}

		std::map<std::string,std::shared_ptr<LibInterface>>::iterator jt;

	return 1;
}

bool Set4LibInterfaces::ExecCmd(std::istream &commands, AbstractMobileObj  *pMobObj,  int  Socket)
{
	string key;
	shared_ptr<LibInterface> lib;
 while(commands >> key)
    {
        map<string, shared_ptr<LibInterface>>::iterator it = libSet.find(key);

        if(it == libSet.end())
        {
            cout << "!!! Nie znaleziono polecenia: " << key << endl;
            return 0;
        }


        lib = it->second;

        cmd = lib->_pCreateCmd();

        cmd->ReadParams(commands);

        cout<< "Wykonuje: " << cmd->GetCmdName() << endl;
        cout<< "Skladnia: " << endl;
        cmd->PrintSyntax();

		cmd->PrintCmd();

		delete(cmd);
	}

	return 1;
}
