#include "klient.hh"


/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 1
 * i obrazujących jego ruch.
//  */
// const char *Cmds4Obj1[STATES_NUMBER] = {
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,23)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,26)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,29)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,32)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,35)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,38)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,41)\n",
//     "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,44)\n"};

// /*!
//  * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 2
//  * i obrazujących jego ruch.
//  */
// const char *Cmds4Obj2[STATES_NUMBER] = {
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-48,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-45,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-42,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-39,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-36,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-33,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-30,0)\n",
//     "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-27,0)\n"};

// /*!
//  * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 3
//  * i obrazujących jego ruch.
//  */
// const char *Cmds4Obj3[STATES_NUMBER] = {
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-48,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-51,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-54,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-57,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-60,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-63,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-66,0)\n",
//     "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-69,0)\n"};

// /*!
//  * \brief Wysyła napis do poprzez gniazdo sieciowe.
//  *
//  * Wysyła napis do poprzez gniazdo sieciowe.
//  * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które
//  *                        ma zostać wysłany napis w sensie języka C.
//  * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
//  *                    gniazdo sieciowe.
//  */
// int Send(int Sk2Server, const char *sMesg)
// {
//   ssize_t IlWyslanych;
//   ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

//   while ((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0)
//   {
//     IlDoWyslania -= IlWyslanych;
//     sMesg += IlWyslanych;
//   }
//   if (IlWyslanych < 0)
//   {
//     cerr << "*** Blad przeslania napisu." << endl;
//   }
//   return 0;
// }

// /*!
//  * \brief Funkcja jest treścią wątku komunikacyjnego
//  *
//  * Funkcja jest treścią wątku komunikacyjnego.
//  * \param[in] rSender - odpowiada za śledenie zmian na scenie
//  *                      i przesyłanie do serwera graficznego
//  *                      aktualnego stanu sceny, gdy uległ on zmianie.
//  */
// void Fun_CommunicationThread(Sender *pSender)
// {
//   pSender->Watching_and_Sending();
// }

// /*!
//  * Otwiera połączenie sieciowe
//  * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
//  *                        realizowana komunikacja sieciowa.
//  */
// bool OpenConnection(int &rSocket)
// {
//   struct sockaddr_in DaneAdSerw;

//   bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

//   DaneAdSerw.sin_family = AF_INET;
//   DaneAdSerw.sin_addr.s_addr = inet_addr("127.1");
//   DaneAdSerw.sin_port = htons(PORT);

//   rSocket = socket(AF_INET, SOCK_STREAM, 0);

//   if (rSocket < 0)
//   {
//     cerr << "*** Blad otwarcia gniazda." << endl;
//     return false;
//   }

//   if (connect(rSocket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
//   {
//     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
//     return false;
//   }
//   return true;
// }

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
// bool ChangeState(Scene &Scn) // GeomObject *pObj, AccessControl  *pAccCtrl)
// {
//   bool Changed;

//   while (true)
//   {
//     Scn.LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
//                       // modyfikacje na obiekcie.
//     for (GeomObject &rObj : Scn._Container4Objects)
//     {
//       if (!(Changed = rObj.IncStateIndex()))
//       {
//         Scn.UnlockAccess();
//         return false;
//       }
//     }
//     Scn.MarkChange();
//     Scn.UnlockAccess();
//     usleep(3);
//   }
//   return true;
// }

int klient()
{
  // Inicjalizacja obiektów i zmiennych
  Configuration Config; // nazwy bibliotek i konfiguracje obiektów 
  Reader reader; //czytanie xml
  Set4LibInterfaces lib_handler; //zarządzanie bibliotekami - mapa bibliotek i ich interfejsy
  AbstractInterp4Command *command; //abstrakcyjny wskaźnik na aktualnie wykorzystywaną funkcję z biblioteki
  std::istringstream stream;
  std::vector<std::thread> threads; //wątki
  
  // Inicjalizacja czytnika komend
  reader.init("config/commands.cmd");

  // Wczytanie pliku konfiguracyjnego
  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  // Inicjalizacja sceny i wysyłanie
  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  // Inicjalizacja interfejsów bibliotek dynamicznych
  lib_handler.init(Config.libs);

  // Wątek do obserwacji i wysyłania danych
  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);
  
  std::string key;

  // Wczytywanie poleceń z pliku
  reader.execPreprocesor(stream);
  while (stream >> key)
  {
    // Wykonanie komendy zgodnie z interfejsem
    command = lib_handler.execute(key);

    // Obsługa komend równoległych

    if (lib_handler.isParallel() && command != nullptr)
    {
      command->ReadParams(stream);
      threads.push_back(std::thread(&AbstractInterp4Command::ExecCmd, command, &scene));
    }
    // Czekanie na zakończenie wątków, jeśli komendy nie są równoległe
    else if (!lib_handler.isParallel())
    {
      for (int i = 0; i < threads.size(); ++i)
      {
        if (threads[i].joinable())
          threads[i].join();
      }
      threads.clear();
    }
  }

  // Zakończenie pracy i czekanie na zakończenie wątków
  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  for (int i = 0; i < threads.size(); ++i)
  {
    if (threads[i].joinable())
      threads[i].join();
  }
  Thread4Sending.join();

  return 0;
}
