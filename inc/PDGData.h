#ifndef ___PDGDATA_HEAD_PROTECT__KNE9VO
#define ___PDGDATA_HEAD_PROTECT__KNE9VO
#include <iostream>
#include <map>

struct ParticleDataEntry {
    int pid;
    int spin;
    int charge;
    int col;
    float m0;
};

struct PDGData {
    PDGData();
    ParticleDataEntry pdat[500];
    std::map<int, ParticleDataEntry*> pdt;
    typedef std::map<int, ParticleDataEntry*>::iterator pit;
    pit pdtend;
    ParticleDataEntry operator [](int pid) {
        pit it = pdt.find(pid);
        if (it == pdtend) return *(pdt[0]);
        return *(it->second);
    }
};

#endif
