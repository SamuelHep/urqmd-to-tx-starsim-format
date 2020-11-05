#ifndef VERTEX_GENERATOR_
#define VERTEX_GENERATOR_

#include "TRandom3.h"
#include "TObject.h"
#include "TVector3.h"

class VertexGenerator : public TObject {

 public:
  
  VertexGenerator(int seed);
  ~VertexGenerator(){delete random3;}

  //Set Vertex Variables
  void SetBeamSpot(double vx, double vy){vx_ = vx; vy_ = vy; }; // XY BeamSpot
  void SetZRange(double vz_min, double vz_max){ vz_min_ = vz_min; vz_max_ = vz_max; };

  TVector3 GenerateVertex();

 private:

  double vx_;
  double vy_;
  double vz_;
  double vz_min_;
  double vz_max_;

  TRandom3 * random3;

  ClassDef( VertexGenerator, 1);

};

#endif 
