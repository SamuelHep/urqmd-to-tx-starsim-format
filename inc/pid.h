#ifndef PID_H_
#define PID_H_

#include "TObject.h"

class Pid : public TObject {

 public:
  Pid(){ id[0] = -999; id[1] = -999; id[2] = -999;};
  Pid(int pdg,int geant, int urqmd){ id[0] = pdg; id[1] = geant; id[2] = urqmd; };
  int operator [] ( int i ) { if ( i < 0 || i > 2 ) return -999; return id[i]; };

 private:
  int id[3];

  ClassDef(Pid,1);

};

#endif
