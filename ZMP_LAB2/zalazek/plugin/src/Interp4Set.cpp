#include <iostream>
#include <vector>
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
Interp4Set::Interp4Set(): _X_Value(0), _Y_Value(0), _Z_Value(0), _Name(""), _OX_Angle(0), _OY_Angle(0), _OZ_Angle(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name << " " << _X_Value << " " << _Y_Value << " " << _Z_Value << " " << _OX_Angle << " " << _OY_Angle << " " << _OZ_Angle <<endl;
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
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  std::vector<std::string> arguments;
    std::string argument;
    while (Strm_CmdsList >> argument) { 
      arguments.push_back(argument);
    }
  
  _Name = arguments[0];
  _X_Value = std::stod(arguments[1]);
  _Y_Value = std::stod(arguments[2]);
  _Z_Value = std::stod(arguments[3]);
  _OX_Angle = std::stod(arguments[4]);
  _OY_Angle = std::stod(arguments[5]);
  _OZ_Angle = std::stod(arguments[6]);
  return true;
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
  cout << "   Set  NazwaObiektu  WspX  WspY WspZ katOX katOY katOZ" << endl;
}


// wczytać program przez preprocesor (popen)