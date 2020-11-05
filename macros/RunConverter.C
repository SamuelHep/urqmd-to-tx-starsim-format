
void RunConverter()
{
  
  gSystem->Load("../bin/UrqmdConverter.so");
  UrqmdConverter( "../data/urqmd.list", "../out_data/" );

}
