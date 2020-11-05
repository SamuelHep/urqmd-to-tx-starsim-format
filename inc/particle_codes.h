#ifndef PARTICLE_CODES_H_
#define PARTICLE_CODES_H_

#include "TObject.h"
#include <vector>
#include "pid.h"

class ParticleCodes : public TObject {

 public:
  
  ParticleCodes();
  ~ParticleCodes();

  //Conversion Calls ( if conversion is not known, return value is -999 )
  int Pdg_to_Geant(const int pid);
  int Pdg_to_Urqmd(const int pid);
  int Urqmd_to_Geant(const int pid);
  int Urqmd_to_Pdg(const int pid);
  int Geant_to_Urqmd(const int pid);
  int Geant_to_Pdg(const int pid);
  void PrintAll();

 private:

  std::vector< Pid > pid_vector_;
  const int kBadVal = -999;

  const int kPdg = 0;
  const int kGeant = 1;
  const int kUrqmd = 2;


  int ElementX_to_Y(const int pid, const int i,const int j);

  ClassDef( ParticleCodes, 1 );


};

#endif
