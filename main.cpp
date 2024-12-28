#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    HalteGraph G;
    beamList L;
    initHalteGraph(G);
    initBeamList(L);

    buildHalteGraph(G);
    printHalteGraph(G);

    insertBeam(L, G, "Beam 1", G.firstHalte);
    insertBeam(L, G, "Beam 2", G.firstHalte);
    insertBeam(L, G, "Beam 3", G.firstHalte);

    beamJalan(L, G);
    beamRecharge(L, "Beam 1");
    beamRecharge(L, "Beam 2");
    beamRecharge(L, "Beam 3");

    return 0;
}
