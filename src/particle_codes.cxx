#include "particle_codes.h"
#include <iostream>
#include <vector>
#include <iomanip>

using std::setw;
using std::cout;
using std::endl;

ClassImp(ParticleCodes);

ParticleCodes::ParticleCodes()
{
  
  //UrQMD Codes may be incorrect, but I really only care about pdg to geant
  
  pid_vector_.push_back( Pid( 22, 1, 100 ) );//gamma
  pid_vector_.push_back(Pid( -11, 2, kBadVal) );//postitron
  pid_vector_.push_back(Pid( 11, 3, kBadVal) );//electron
  pid_vector_.push_back(Pid( 12, 4, kBadVal) );//neutrino
  pid_vector_.push_back(Pid( -13, 5, kBadVal) );//mu+
  pid_vector_.push_back(Pid( 13, 6, kBadVal) );//mu-
  pid_vector_.push_back(Pid( 111, 7, 101) );//pi0
  pid_vector_.push_back(Pid( 211, 8, 101) );//pi+
  pid_vector_.push_back(Pid( -211, 9, 101) );//pi-
  pid_vector_.push_back(Pid( 130, 10, 106) );//K0 long
  pid_vector_.push_back(Pid( 321, 11, 106) );//K+
  pid_vector_.push_back(Pid( -321, 12, -106) );//K-
  pid_vector_.push_back(Pid( 2112, 13, 1) );//neutron
  pid_vector_.push_back(Pid( 2212, 14, 1) );//proton
  pid_vector_.push_back(Pid( -2212, 15, -1) );//antiproton
  pid_vector_.push_back(Pid( 310, 16, 106) );//K0 short
  pid_vector_.push_back(Pid( 221, 17, 102) );//eta
  pid_vector_.push_back(Pid( 3122, 18, 27) );//lambda
  pid_vector_.push_back(Pid( 3222, 19, 40) );//sigma+
  pid_vector_.push_back(Pid( 3212, 20, 40) );//sigma0
  pid_vector_.push_back(Pid( 3112, 21, 40) );//sigma-
  pid_vector_.push_back(Pid( 3322, 22, 49) );//xi0
  pid_vector_.push_back(Pid( 3112, 23, 49) );//xi-
  pid_vector_.push_back(Pid( 3334, 24, 55) );//omega
  pid_vector_.push_back(Pid( -2112, 25, -1) );//antineutron
  pid_vector_.push_back(Pid( -3122, 26, -27) );//antilambda
  pid_vector_.push_back(Pid( -3222, 27, -20) );//antisigma-
  pid_vector_.push_back(Pid( -3212, 28, -20) );//antisigma0
  pid_vector_.push_back(Pid( -3112, 29, -20) );//antisigma+
  pid_vector_.push_back(Pid( -3322, 30, -49) );//antixi0
  pid_vector_.push_back(Pid( -3112, 31, -49) );//antixi+
  pid_vector_.push_back(Pid( -3334, 32, -55) );//antiomega+
  pid_vector_.push_back(Pid( -15, 33, kBadVal) );//tau+
  pid_vector_.push_back(Pid( 15, 34, kBadVal) );//tau-
  pid_vector_.push_back(Pid( 411, 35, kBadVal) );//D+
  pid_vector_.push_back(Pid( -411, 36, kBadVal) );//D-
  pid_vector_.push_back(Pid( 421, 37, kBadVal) );//D0
  
  pid_vector_.push_back(Pid( kBadVal, 45, kBadVal) );//deuteron
  pid_vector_.push_back(Pid( kBadVal, 46, kBadVal) );//tritium
  pid_vector_.push_back(Pid( kBadVal, 47, kBadVal) );//alpha

}

ParticleCodes::~ParticleCodes(){}

//General Conversion 
int ParticleCodes::ElementX_to_Y(const int pid, const int i,const int j)
{  
  for ( auto pid_triple : pid_vector_ ){
    if ( (pid_triple[i]) == pid ) return pid_triple[j]; 
  } 
  return kBadVal;

}

//Specific Conversions
int ParticleCodes::Pdg_to_Geant(const int pid) { return ElementX_to_Y(pid, kPdg , kGeant ); }; 
int ParticleCodes::Pdg_to_Urqmd(const int pid) { return ElementX_to_Y(pid, kPdg , kUrqmd ); }; 
int ParticleCodes::Urqmd_to_Geant(const int pid) { return ElementX_to_Y(pid, kUrqmd , kGeant ); }; 
int ParticleCodes::Urqmd_to_Pdg(const int pid) { return ElementX_to_Y(pid, kUrqmd , kPdg ); }; 
int ParticleCodes::Geant_to_Urqmd(const int pid) { return ElementX_to_Y(pid, kGeant , kUrqmd ); }; 
int ParticleCodes::Geant_to_Pdg(const int pid) { return ElementX_to_Y(pid, kGeant , kPdg ); }; 

void ParticleCodes::PrintAll()
{
  cout << setw(10) << "PDG" << setw(10) << "GEANT" << setw(10) << "URQMD" << endl;
 for ( auto pid_triple : pid_vector_ ){
   cout << setw(10) << pid_triple[0] << setw(10) << pid_triple[1] << setw(10) << pid_triple[2] << endl;
  } 
}
