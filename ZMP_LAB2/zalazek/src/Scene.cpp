#include "Scene.hh"

Scene::Scene(Configuration &config)
{

  for (int i = 0; i < config._ObjectsConfig.size(); i++)
  {
    MobileObj tmp;
    tmp.SetName(config._ObjectsConfig[i].name.c_str());
    tmp.SetAng_Roll_deg(config._ObjectsConfig[i].rot[0]);
    tmp.SetAng_Pitch_deg(config._ObjectsConfig[i].rot[1]);
    tmp.SetAng_Yaw_deg(config._ObjectsConfig[i].rot[2]);
    tmp.SetPosition_m(config._ObjectsConfig[i].shift);
    tmp.setRgb(config._ObjectsConfig[i].rgb);
    tmp.setScale(config._ObjectsConfig[i].scale);
    tmp.setTranslation(config._ObjectsConfig[i].trans);

    AddMobileObj(&tmp);
    std::cout << "dodano obiekt " << tmp.GetName() << std::endl;
  }
}


void Scene::AddMobileObj(MobileObj *pMobObj)
{
  _Container4Objects.insert(std::make_pair(pMobObj->GetName(), *pMobObj));
}
