#include "TString.h"
#include <fstream>
#include <iostream>
#include "TVector3.h"
#include "tx_maker.h"
#include "particle_codes.h"

using std::cout;
using std::endl;

ClassImp( TxMaker ) 

//Set All counters to 0
TxMaker::TxMaker(TString out_tx_directory, TString tx_prefix, int nevents_per_file)
{
  event_counter_=0;
  track_counter_=0;
  file_counter_=0;
  nevents_per_file_ = nevents_per_file;
  out_dir_ = out_tx_directory;
  tx_prefix_ = tx_prefix;
  outFile_ = NULL;
  particle_codes = new ParticleCodes();
  //  particle_codes->PrintAll(); //Make sure particle codes are correct
}

//Used privately to reset OutFile_ if event_counter_ > nevents_per_file_
ofstream * TxMaker::GetOutFile()
{
  if ( event_counter_ == 0 )
    {
      outFile_ = new ofstream( TString::Format("%s/%s_%i.tx",out_dir_.Data(),tx_prefix_.Data(),file_counter_) );
      file_counter_++;
      return outFile_;
      
    }
  else if ( event_counter_ >= nevents_per_file_ )
    {
      outFile_->close();
      event_counter_ =0; //Reset Counter
      return GetOutFile();
    }
  return outFile_;
}

//SetEvent pass a vertex and the multiplicity. Resets the track counter
void TxMaker::SetEvent( TVector3 vertex, int mult )
{
  ofstream *outFile = GetOutFile();
  *outFile << TString::Format("EVENT: %d %d %d\n", event_counter_, mult, 1); event_counter_++;
  *outFile << TString::Format("VERTEX: %g %g %g %g %d %d %d %d\n",vertex.X(), vertex.Y(), vertex.Z(), 0.0, 1, 0, 0, mult);
  track_counter_=0; //Reset track counter
}

//Call after SetEvent to fill track.
void TxMaker::SetTrack( int pdg_pid, float px, float py, float pz )
{
  //Make sure the geant/urqmd pid is valid
  int geant_pid = particle_codes->Pdg_to_Geant(pdg_pid);
  int urqmd_pid = particle_codes->Pdg_to_Urqmd(pdg_pid);
  //   cout << "PDG=" << pdg_pid << " GEANT=" << geant_pid << " URQMD=" << urqmd_pid << endl;
  if ( geant_pid == -999 || urqmd_pid == -999 ) return;

  *outFile_ << TString::Format("TRACK: %d %g %g %g %d %d %d %d\n", geant_pid, px, py, pz, track_counter_, 1, 0, urqmd_pid);
  track_counter_++;
}


