#ifdef __CINT__

// turns off dictionary generation for all
#pragma link off all class;
#pragma link off all function;
#pragma link off all global;
#pragma link off all typedef;

// link to nested scope
#pragma link C++ nestedclass;
#pragma link C++ defined_in "PDGData.h";
#pragma link C++ defined_in "urqmd_converter.h";
#pragma link C++ defined_in "particle_codes.h";
#pragma link C++ defined_in "pid.h";
#pragma link C++ defined_in "vertex_generator.h";
#pragma link C++ defined_in "tx_maker.h";


#endif
