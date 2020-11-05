#ifndef TX_MAKER_
#define TX_MAKER_

#include "TObject.h"
#include <fstream>
#include "TVector3.h"
#include "TString.h"
#include "particle_codes.h"

class TxMaker : public TObject {

 public:
  
  TxMaker();
  TxMaker(TString out_tx_directory, TString tx_prefix, int nevents_per_file);
  ~TxMaker(){};
  
  void SetEvent( TVector3 vertex, int mult );
  void SetTrack( int pdg_pid, float px, float py, float pz );

 private:

  ofstream * GetOutFile();  
  
  int event_counter_;
  int track_counter_;;
  int file_counter_;
  int nevents_per_file_;
  TString out_dir_;
  TString tx_prefix_;
  ofstream * outFile_;
  ParticleCodes * particle_codes;

  ClassDef( TxMaker, 1 ) ;


};


#endif
