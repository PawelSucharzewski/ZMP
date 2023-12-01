#ifndef READER_HH
#define READER_HH

#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Configuration.hh"
#include "xmlinterp.hh"

#define LINE_SIZE 500

class Reader
{
private:
    std::string cmdFileName;

public:
    Reader(){};
    bool init(std::string cmdFile);
    
    // Wywołuje preprocesor C++
    // Odczytuje i przekazuje dane ze strumienia do istringstream
    // Wartość zwracana informuje o sukcesie operacji
    bool execPreprocesor(std::istringstream &IStrm4Cmds);

    // Inicjalizacja i ustawienie parsera XML
    // Parsowanie pliku XML i obsługa błędów
    // Zwraca true, jeśli parsowanie zakończone sukcesem
    bool ReadFile(const char *sFileName, Configuration &rConfig);
};

#endif