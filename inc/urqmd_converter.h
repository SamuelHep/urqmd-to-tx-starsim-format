#ifndef URQMD_CONVERTER_H_
#define URQMD_CONVERTER_H_

#include "TChain.h"
#include "TString.h"

void UrqmdConverter(TString file_list_name, TString out_tx_directory, TString tx_prefix = "3p0GeV_urqmd");
TChain * LoadChainFromFileList( TString file_list_name );

#endif
