#include "Set4LibInterfaces.hh"

bool Set4LibInterfaces::init(std::vector<std::string> lib_vector)
{
    for (int i = 0; i < lib_vector.size(); i++)
    {
        std::shared_ptr<LibInterface> new_library = std::make_shared<LibInterface>();
    

        new_library->init("libs/" + lib_vector[i]);
        std::string command_name = lib_vector[i].substr(10, lib_vector[i].length() - 13);
        std::cout << command_name << std::endl;

        lib.insert(std::make_pair(command_name, new_library));
    }



    return 0;
}

AbstractInterp4Command *Set4LibInterfaces::execute(std::string key)
{
   
    std::shared_ptr<LibInterface> handle;
    AbstractInterp4Command *command = nullptr;

  
    if (key == "Begin_Parallel_Actions")
    {
        parallel = true;
    }
    else if (key == "End_Parallel_Actions")
    {
        parallel = false;
    }
    else
    {
        std::map<std::string, std::shared_ptr<LibInterface>>::iterator iterator = lib.find(key);
        if (iterator == lib.end())
        {
            std::cout << "Set4LibInterfaces: Nie znaleziono wtyczki dla polecenia: " << key << std::endl;
            return nullptr;
        }

        handle = iterator->second;
        command = handle->CreateCmd();
    }
  
    return command;
}
