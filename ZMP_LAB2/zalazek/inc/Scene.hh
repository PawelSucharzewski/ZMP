#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <string>
#include "AccessControl.hh"
#include "Configuration.hh"
#include "MobileObj.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Scene
 *
 *  Zawiera definicję klasy Scene.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

/*!
 * \brief Definiuje interfejs klasy modelującej scenę roboczą.
 *
 * Definiuje interfejs klasy modelującej scenę roboczą,
 * która zawiera kolekcję obiektów mobilnych.
 */
class Scene : public AccessControl
{
private:
    /*!
     * \brief Prosta kolekcja obiektów sceny
     */
    std::map<std::string, MobileObj> _Container4Objects;

public:
    Scene(Configuration &config);
    /*!
     * \brief Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
     *
     *  Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
     *  \param[in] sName - pełna kwalifikowana nazwa obiektu.
     *  \return Jeśli obiekt zostanie znaleziony, to zwracany jest wskaźnik
     *          na niego. W przypadku przeciwnym zwracany jest wskaźnik \p nullptr.
     */
    MobileObj *FindMobileObj(const char *sName)
    {
        MobileObj *pointer_to_object = NULL;
        std::map<std::string, MobileObj>::iterator iterator = _Container4Objects.find(sName);
        if (iterator == _Container4Objects.end())
        {
            std::cout << "FindMobileObj: Nie znaleziono wtyczki dla polecenia: " << sName << std::endl;
        }
        pointer_to_object = &(iterator->second);
        return pointer_to_object;
    }
    /*!
     * \brief Dodaje do sceny nowy obiekt.
     *
     *  Dodaje do sceny nowy obiekt. Obiekt ten musi mieć poprawnie
     *  skonstruowaną pełną kwalifikowaną nazwę.
     *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
     */
    void AddMobileObj(MobileObj *pMobObj);
    std::map<std::string, MobileObj> getMobileObjects() { return _Container4Objects; }
};

#endif
