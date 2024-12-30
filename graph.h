#ifndef HALTE_GRAPH_H_INCLUDED
#define HALTE_GRAPH_H_INCLUDED
#include <iostream>
using namespace std;

//Graph untuk halte & jalan
struct jalan;
struct halteVertex;

typedef halteVertex* adrHalteVertex;
typedef jalan* adrJalan;

struct halteVertex
{
    string halteID;
    adrHalteVertex nextHalte;
    adrJalan firstEdge;
};

struct jalan
{
    adrHalteVertex tujuanHalte;
    int jarakHalte;
    adrJalan nextEdge;
};

struct HalteGraph
{
    adrHalteVertex firstHalte;
    int count = 0;
};

// Beam
typedef struct beam* adrBeam;

struct beam
{
    string idBeam; 
    int battery = 10;
    adrHalteVertex location;
    adrBeam nextBeam;
};

struct beamList
{
    adrBeam firstBeam;
};

// Stack
struct elmStack
{
    adrHalteVertex info;
    elmStack *next;
};

struct Stack
{
    elmStack *Top;
};


// Halte & Jalan
void createHalteVertex(string halteID, adrHalteVertex &v);
void createJalan(adrHalteVertex tujuan, int jarakHalte, adrJalan &e);
void initHalteGraph(HalteGraph &G);
void addHalteVertex(HalteGraph &G, string halteID);
adrHalteVertex searchHalte(HalteGraph G, string halteID);
adrJalan searchJalan(HalteGraph G, adrHalteVertex v, adrHalteVertex x);
void addJalan(HalteGraph &G, adrHalteVertex asal, adrHalteVertex tujuanHalte, int jarakHalte);
void buildHalteGraph(HalteGraph &G);
void buildJalan(HalteGraph &G);

void findRuteTerpendek(HalteGraph G, string startHalteID, string endHalteID);

// Beam
void createBeam (string idBeam, adrHalteVertex location, adrBeam &b);
void initBeamList (beamList &L);
adrBeam searchBeam (beamList L, string beamID);
void insertBeam (beamList &L, HalteGraph G, string beamID, adrHalteVertex location);
void buildBeam (beamList &L, HalteGraph G);
void beamJalan (beamList &L, HalteGraph G, string beamID, string tujuan);
void beamRecharge (beamList &L, string beamID);

void printHalteGraph(HalteGraph G, beamList L);

// Stack
void createStack (Stack &S);
elmStack* createElmStack (adrHalteVertex x);
bool isEmpty (Stack S);
void push (Stack &S, elmStack* x);
elmStack* pop (Stack &S);
void printInfo (Stack S);

#endif
