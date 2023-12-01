#ifndef KLIENT_HH
#define KLIENT_HH

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "Configuration.hh"
#include "Reader.hh"
#include "Sender.hh"
#include "Set4LibInterfaces.hh"
#include "AbstractInterp4Command.hh"


using namespace std;



// /*!
//  * \brief Wysyła napis do poprzez gniazdo sieciowe.
//  *
//  * Wysyła napis do poprzez gniazdo sieciowe.
//  * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
//  *                        ma zostać wysłany napis w sensie języka C.
//  * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
//  *                    gniazdo sieciowe.
//  */
// int Send(int Sk2Server, const char *sMesg);

// /*!
//  * \brief Ilość stanów każdego z obiektów.
//  *
//  * Ilość stanów każdego z obiektów.
//  * Podział na kolejne stany obiektów wykorzystywany jest
//  * do animacji ruchu obiektów.
//  */
// #define STATES_NUMBER   8

// extern const char* Cmds4Obj1[STATES_NUMBER];
// extern const char* Cmds4Obj2[STATES_NUMBER];
// extern const char* Cmds4Obj3[STATES_NUMBER];

// /*!
//  * \brief Ta klasa trochę udaję klasę MobileObj, która jest w zadaniu.
//  *
//  */
// class GeomObject {
//   /*!
//    * \brief Identyfikuje aktualny stan obiektu.
//    *
//    * Identyfikuje aktualny stan obiektu. Indeks ten pozwala
//    * na wybór z tablicy \link GeomObject::_Cmd4StatDesc _Cmd4StatDesc\endlink
//    * odpowiedniego polecenia dla serwera, które reprezentuje aktualne
//    * położenie i orientację obiektu.
//    */
//    int _StateIdx = 0;
//   /*!
//    * \brief Zestaw sekwencji poleceń symulujących ruch obiektu.
//    *
//    * Zestaw sekwencji poleceń symulujących ruch obiektu.
//    * Każde polecenie odpowiada kolejnym stanom obiektu.
//    */
//    const char** _Cmd4StatDesc = nullptr;
  
//  public:

//   /*!
//    * \brief Ustawia zestaw poleceń odpowiadających kolejnym stanom
//    *        obiektu.
//    */
//   void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }
//   /*!
//    * \brief Udostępnia kolejny zestaw poleceń umożliwiających
//    *        zespołu obiektu.
//    *
//    * Udostępnia kolejny zestaw poleceń umożliwiających
//    * zespołu obiektu. Ta metoda "udaje" metodę, która w oryginalnym
//    * rozwiązaniu powinna wygenerować odpowiednie polecenie na podstawie
//    * przechowywanej informacji o położeniu i orientacji obiektu.
//    */
//   const char* GetStateDesc() const
//   {
//     return _Cmd4StatDesc[_StateIdx];
//   }
//   /*!
//    * \brief Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
//    *
//    *  Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
//    *  Ta metoda "udaje" metodę, która w oryginalnym rozwiązaniu
//    *  jest odpowiedzialna za zmianę stanu obiektu, tzn. zmianę jego
//    *  położenia lub orientacji.
//    */
//   bool IncStateIndex() {
//     if (_StateIdx >= STATES_NUMBER-1) return false;
//     ++_StateIdx;
//     return true;
//   }
// };





// /*!
//  * \brief Namiastka sceny z prostą kolekcją trzech wizualizowanych obiektów.
//  */
// // class Scene: public AccessControl {
// //   public:
// //     Scene(): _Container4Objects(3)
// //     {
// //       _Container4Objects[0].SetCmds(Cmds4Obj1);
// //       _Container4Objects[1].SetCmds(Cmds4Obj2);
// //       _Container4Objects[2].SetCmds(Cmds4Obj3);
// //     }
  
// //   /*!
// //    * \brief Prosta kolekcja obiektów sceny
// //    */
// //    std::vector<GeomObject>   _Container4Objects;
// // };



// /*!
//  * \brief Funkcja jest treścią wątku komunikacyjnego
//  * 
//  * Funkcja jest treścią wątku komunikacyjnego.
//  * \param[in] rSender - odpowiada za śledenie zmian na scenie 
//  *                      i przesyłanie do serwera graficznego
//  *                      aktualnego stanu sceny, gdy uległ on zmianie.
//  */
// void Fun_CommunicationThread(Sender  *pSender);


// /*!
//  * Otwiera połączenie sieciowe
//  * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
//  *                        realizowana komunikacja sieciowa.
//  */
// bool OpenConnection(int &rSocket);



// /*!
//  * \brief Przykład wykonywania pojedynczej operacji z animacją.
//  *
//  * Przykład wykonywania pojedynczej operacji z animacją.
//  * \param[in] pObj - wskaźnik na obiekt, dla którego ma być wykonana dana operacja
//  *                   zmiany jego stanu.
//  * \param[in] pAccCtrl - wskaźnik na obiekt, poprzez który przekazywana jest informacja
//  *                   o zmianie na scenie, zaś w trakcie dokonywania zmianay
//  *                   zamykany jest dostęp do całej sceny.
//  * \retval true - Jeśli dokonan zosała zmiana stanu wszystkich obiektów.
//  * \retval false - w przypadku przeciwnym.
//  */
// bool ChangeState(Scene &Scn); //GeomObject *pObj, AccessControl  *pAccCtrl)

int klient();


#endif