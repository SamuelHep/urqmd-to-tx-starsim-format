
#include "TRandom3.h"
#include "TVector3.h"
#include "vertex_generator.h"

ClassImp(VertexGenerator);

VertexGenerator::VertexGenerator(int seed)
{

  random3 = new TRandom3(seed);
  
  //STAR FXT LOCATION
  vx_ = 0.0;
  vy_ = -2.0;
  vz_min_ = 200.65;
  vz_max_ = 200.75;

}


TVector3 VertexGenerator::GenerateVertex()
{
  vz_ = random3->Uniform(vz_min_,vz_max_);
  return TVector3(vz_,vy_,vz_);
}
