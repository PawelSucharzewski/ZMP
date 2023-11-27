#include <iostream>
#include "Interp4Set.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _Name(""), _Wsp_x(0), _Wsp_y(0), _Wsp_z(0), _Angle_x(0), _Angle_y(0), _Angle_z(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name  << _Wsp_x << _Wsp_y << _Wsp_z << _Angle_x << _Angle_y << _Angle_z << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd(Scene *scene) const
{

  MobileObj *obj = scene->FindMobileObj(_Name.c_str());
  Vector3D new_position;

  new_position[0] = _Wsp_x;
  new_position[1] = _Wsp_y;
  new_position[2] = _Wsp_z;
  scene->LockAccess();
  

  obj->SetPosition_m(new_position);
  obj->SetAng_Roll_deg(_Angle_x);
  obj->SetAng_Pitch_deg(_Angle_y);
  obj->SetAng_Yaw_deg(_Angle_z);

  scene->MarkChange();
  scene->UnlockAccess();
  usleep(10000);

  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if (!(Strm_CmdsList >> _Name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Wsp_x))
  {
    std::cout << "Blad wczytywania wspolrzednej x" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Wsp_y))
  {
    std::cout << "Blad wczytywania wspolrzednej y" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Wsp_z))
  {
    std::cout << "Blad wczytywania wspolrzednej z" << std::endl;
    return 1;
  }

    if (!(Strm_CmdsList >> _Angle_x))
  {
    std::cout << "Blad wczytywania kata z" << std::endl;
    return 1;
  }

    if (!(Strm_CmdsList >> _Angle_y))
  {
    std::cout << "Blad wczytywania kata z" << std::endl;
    return 1;
  }

    if (!(Strm_CmdsList >> _Angle_z))
  {
    std::cout << "Blad wczytywania kata z" << std::endl;
    return 1;
  }
  return 0;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set nazwa_obiektu wsp_x wsp_y wsp_z kat_OX kat_OY kat_OZ" << endl;
}
