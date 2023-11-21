#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH
#include "AbstractInterp4Command.hh"
#include <string.h>
#include <dlfcn.h>
#include <iostream>

class LibInterface {
	public:
		~LibInterface(){};
		LibInterface(){};
		bool init(std::string lib_name);

		std::string _CmdName();

		void* _LibHandler;
		const char *(*_pGetCmdName)(void);
		AbstractInterp4Command *(*_pCreateCmd)(void);
		AbstractInterp4Command *(*_pPrintCmd)(void);//mobileObj zamienić na scene kiedyś tam
		AbstractInterp4Command *(*_pReadParams)(std::istream&);


};

#endif
