#include "TH1D.h"
#include "TFile.h"
#include "TChain.h"
#include "TMath.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <fstream>
#include "tx_maker.h"
#include "urqmd_converter.h"
#include "PDGData.h"
#include "vertex_generator.h"

void UrqmdConverter(TString file_list_name, TString out_tx_directory, TString tx_prefix)
{
  
  TRandom3 * rand = new TRandom3(0);
  PDGData pdg;
  TxMaker tx_maker( out_tx_directory , tx_prefix, 100 );
  VertexGenerator vertex_generator(123);

  //Check the boost with simple out hists
  TFile * ofile = new TFile("urqmd_converter_hists.root","recreate");
  TH1D * h_pz  = new TH1D("h_pz","",200,-10,10);
  TH1D * h_eta = new TH1D("h_eta","",200,-10,10);
  TH1D * h_eta_boost = new TH1D("h_eta_boost","",200,-10,10);
  TH1D * h_rap = new TH1D("h_rap","",200,-10,10);
  TH1D * h_rap_boost = new TH1D("h_rap_boost","",200,-10,10);
  TH1D * h_rad = new TH1D("h_rad","",50,-1.0*TMath::Pi(),TMath::Pi());
  TH1D * h_rad_spin = new TH1D("h_rad_spin","",50,-1.0*TMath::Pi(),TMath::Pi());


  //Beam Kinematics
  double beam_rapidity = 2.097/2.0; //3GeV Beam Rapidity
  double gamma = TMath::CosH(beam_rapidity);
  double beta = TMath::TanH(beam_rapidity);
  double gamma_beta = TMath::SinH(beam_rapidity); 

  //Setup the chain
  TChain * chain = LoadChainFromFileList( file_list_name );

  float px_array[10000];
  float py_array[10000];
  float pz_array[10000];
  int  pid[10000];
  int npart=0;
  int mult=0;
  
  //Set UrQMD Values
  chain->SetBranchAddress("Npart", &npart );
  chain->SetBranchAddress("mul", &mult );
  chain->SetBranchAddress("pid", pid );
  chain->SetBranchAddress("px" , px_array );
  chain->SetBranchAddress("py" , py_array );
  chain->SetBranchAddress("pz" , pz_array );
  
  for ( int i_entry=0; i_entry < chain->GetEntries(); i_entry++ )
    {
      chain->GetEntry( i_entry );

      tx_maker.SetEvent( vertex_generator.GenerateVertex() , mult);
      
      for ( int i_track=0; i_track< mult; i_track++ )
	{
	  //Get Kinematic Variables
	  float mass = pdg[ abs(pid[i_track]) ].m0;
	  float px = px_array[i_track];
	  float py = py_array[i_track];
	  float pz = pz_array[i_track];
	  float p = sqrt(px*px + py*py + pz*pz);
	  float E = sqrt(px*px + py*py + pz*pz + mass*mass);

	  //Boost
	  float E_boost = gamma*E - gamma_beta*pz;
	  float pz_boost = gamma*pz - gamma_beta*E;
	  float p_boost = sqrt( px*px + py*py + pz_boost*pz_boost );

	  float eta = 0.5*TMath::Log( ( p + pz ) / ( p - pz ) );
	  float eta_boost = 0.5*TMath::Log( ( p_boost + pz_boost ) / ( p_boost - pz_boost ) );

	  float rap  = 0.5*TMath::Log( ( E + pz ) / ( E - pz ) );
	  float rap_boost  = 0.5*TMath::Log( ( E_boost + pz_boost ) / ( E_boost - pz_boost ) );

	  //Random Spin px and py
	  float pt = sqrt( px*px + py*py );
	  float angle = TMath::ATan2( py, px );
	  float random_angle = rand->Uniform(-1.0*TMath::Pi(),TMath::Pi());
	  float px_spin = pt*TMath::Cos(random_angle);
	  float py_spin = pt*TMath::Sin(random_angle);

	  h_rad->Fill(angle);
	  h_rad_spin->Fill(random_angle);

	  h_pz->Fill( pz_boost );

	  h_eta->Fill( eta );
	  h_eta_boost->Fill( eta_boost );

	  h_rap->Fill( rap );
	  h_rap_boost->Fill( rap_boost );

	  tx_maker.SetTrack( pid[i_track] , px , py , pz_boost );

	}

    }

  ofile->cd();
  h_pz->Write();
  h_eta->Write();
  h_eta_boost->Write();
  h_rap->Write();
  h_rap_boost->Write();
  h_rad->Write();
  h_rad_spin->Write();

}


TChain * LoadChainFromFileList( TString file_list_name )
{
 TChain * chain = new TChain("urqmd");

  ifstream  file_list( file_list_name );
  if ( ! file_list.is_open() ){
    fputs("ERROR::File is not open",stderr);
    exit( EXIT_FAILURE );
  }

  std::string file_name;
  while ( file_list.good() ){
    getline(file_list,file_name);
    if ( file_name.length() != 0 && file_name.find(".root") != std::string::npos){
      chain->Add(file_name.c_str());
    }
  }
 
  return chain;

}
