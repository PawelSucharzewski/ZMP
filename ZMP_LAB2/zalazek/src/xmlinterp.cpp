#include <xercesc/util/PlatformUtils.hpp>
#include "xmlinterp.hh"
#include "MobileObjConfig.hh"
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>



using namespace std;


/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 */
XMLInterp4Config::XMLInterp4Config(Configuration &rConfig)
{
  conf = &rConfig;
}


/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument()
{
  cout << "*** Rozpoczecie przetwarzania dokumentu XML." << endl;
}


/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument()
{
  cout << "=== Koniec przetwarzania dokumentu XML." << endl;
}





/*!
 * Analizuje atrybuty elementu XML \p "Lib" i odpowiednio je interpretuje.
 * \param[in] rAttrs - atrybuty elementu XML \p "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes &rAttrs) {
  if (rAttrs.getLength() != 1) {
    cerr << "Zla ilosc atrybutow dla \"Lib\"" << endl;
    exit(1);
  }

  char *sParamName = xercesc::XMLString::transcode(rAttrs.getQName(0));

  if (strcmp(sParamName, "Name")) {
    cerr << "Zla nazwa atrybutu dla Lib" << endl;
    exit(1);
  }

  XMLSize_t Size = 0;
  char *sLibName = xercesc::XMLString::transcode(rAttrs.getValue(Size));

  cout << "  Nazwa biblioteki: " << sLibName << endl;


  this->conf->libs.push_back(sLibName);

  xercesc::XMLString::release(&sParamName);
  xercesc::XMLString::release(&sLibName);
}


/*!
 * Analizuje atrybuty. Sprawdza czy ich nazwy są poprawne. Jeśli tak,
 * to pobiera wartości atrybutów (w postaci napisów) i przekazuje ...
 * \param[in] rAttrs - atrybuty elementu XML \p "Cube".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes  &rAttrs)
{
  int attributes_number = rAttrs.getLength();
  
  std::vector<std::vector<std::string>> sValue(6,
                                               std::vector<std::string>(2, ""));

  if (attributes_number < 1) {
    cerr << "Zla ilosc atrybutow dla \"Cube\"" << endl;
    exit(1);
  }

  /*
   *  Tutaj pobierane sa nazwy pierwszego i drugiego atrybuty.
   *  Sprawdzamy, czy na pewno jest to Name i Value.
   */

  for (int i = 0; i < attributes_number; i++) {
    std::string attribute = xercesc::XMLString::transcode(rAttrs.getQName(i));
    if (attribute == "Name") {
      sValue[0][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[0][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    } else if (attribute == "Shift") {

      sValue[1][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[1][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    } else if (attribute == "Scale") {
      sValue[2][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[2][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    } else if (attribute == "RotXYZ_deg") {
      sValue[3][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[3][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    } else if (attribute == "Trans_m") {
      sValue[4][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[4][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    } else if (attribute == "RGB") {
      sValue[5][0] = xercesc::XMLString::transcode(rAttrs.getQName(i));
      sValue[5][1] = xercesc::XMLString::transcode(rAttrs.getValue(i));
    }
  }



 
  cout << " Atrybuty:" << endl;


  for (int i = 0; i < 6; i++) {
    cout << "     " << sValue[i][0] << " = \"" << sValue[i][1] << "\"" << endl;
  }

  
  istringstream IStrm;
  Vector3D tmp;
  MobileObjConfig object_config;

  object_config.name = sValue[0][1];

  for (int i = 1; i < 6; i++) {
    IStrm.str(sValue[i][1]);
    IStrm >> tmp[0] >> tmp[1] >> tmp[2];
    switch (i) {
    case 1:
      object_config.shift = tmp;
  
      break;
    case 2:
      object_config.scale = tmp;
      
      break;
    case 3:
      object_config.rot = tmp;
     
      break;
    case 4:
      object_config.trans = tmp;
   
      break;
    case 5:
      object_config.rgb = tmp;
    
      break;

    default:
      break;
    }
    cout << " Czytanie wartosci OK!!!" << endl;
    if (i > 0) {
      cout << sValue[i][0] << "     " << tmp[0] << "  " << tmp[1] << "  "
           << tmp[2] << endl;
    }
    IStrm.clear();
  }
  conf->_ObjectsConfig.push_back(object_config);
}







/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] rElemName - nazwa elementu XML.
 * \param[in] rAttrs - atrybuty napotkanego elementu XML.
 */
void XMLInterp4Config::WhenStartElement( const std::string           &rElemName,
		                         const xercesc::Attributes   &rAttrs
                                       )
{
  if (rElemName == "Lib") {
    ProcessLibAttrs(rAttrs);   return;   
  }

  if (rElemName == "Cube") {
    ProcessCubeAttrs(rAttrs);  return;
  }
}




/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *  \param[in] rAttrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLInterp4Config::startElement(  const   XMLCh* const            pURI,
                                      const   XMLCh* const            pLocalName,
                                      const   XMLCh* const            pQName,
				      const   xercesc::Attributes&    rAttrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  cout << "+++ Poczatek elementu: "<< sElemName << endl;

  WhenStartElement(sElemName, rAttrs);

  xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Lib Name="Rotate">
     </Lib>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika:
 * \verbatim</Lib>\endverbatim
 * Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Lib".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *                      
 */
void XMLInterp4Config::endElement(  const   XMLCh* const    pURI,
                                    const   XMLCh* const    pLocalName,
                                    const   XMLCh* const    pQName
                                 )
{
   char* sURI =  xercesc::XMLString::transcode(pURI);
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   char* sQName =  xercesc::XMLString::transcode(pQName);
   cout << "   URI: " << sURI << endl;
   cout << " QName: " << sQName << endl;
   cout << "----- Koniec elementu: "<< sElemName << endl;

   xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException&  rException)
{
   char* sMessage = xercesc::XMLString::transcode(rException.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(rException.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << rException.getLineNumber() << endl
        << " Kolumna: " << rException.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] rException - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLInterp4Config::error(const xercesc::SAXParseException&  rException)
{
  cerr << "Blad ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}


/*!
 * Metoda wywołana jest w przypadku błędów, które nie są fatalne
 * i mogą być traktowane jako ostrzeżenia.
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException&  rException)  
{
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}
