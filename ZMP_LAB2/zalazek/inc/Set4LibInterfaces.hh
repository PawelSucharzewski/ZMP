#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include <LibInterface.hh>


class Set4LibInterfaces
{
	private:
		std::map<std::string,std::shared_ptr<LibInterface>> libSet;
		AbstractInterp4Command* cmd;
	public:

  	bool init(std::vector<std::string> plugins);
	bool ExecCmd(std::istream &commands, AbstractMobileObj  *pMobObj,  int  Socket);

};
