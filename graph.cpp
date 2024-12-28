#include "graph.h"

void createHalteVertex(string halteID, adrHalteVertex &v)
{
    v = new halteVertex();
    v->halteID = halteID;
    v->nextHalte = nullptr;
    v->firstEdge = nullptr;
}

void createJalan(string tujuanHalteID, int jarakHalte, adrJalan &e)
{
    e = new jalan();
    e->tujuanHalteID = tujuanHalteID;
    e->jarakHalte = jarakHalte;
    e->nextEdge = nullptr;
}

void initHalteGraph(HalteGraph &G)
{
    G.firstHalte = nullptr;
}

void addHalteVertex(HalteGraph &G, string halteID)
{
    adrHalteVertex newHalte;
    createHalteVertex(halteID, newHalte);

    if (G.firstHalte == nullptr) // Jika G.firstHalte kosong
    {
        G.firstHalte = newHalte;
    }
    else
    {
        adrHalteVertex v = G.firstHalte;
        while (v->nextHalte != nullptr)
        {
            v = v->nextHalte;
        }
        v->nextHalte = newHalte;
    }
}

void addJalan(HalteGraph &G, string asalHalteID, string tujuanHalteID, int jarakHalte)
{
    adrHalteVertex asal = G.firstHalte;
    while (asal != nullptr && asal->halteID != asalHalteID)
    {
        asal = asal->nextHalte;
    }

    if (asal != nullptr)
    {
        adrJalan newJalan;
        createJalan(tujuanHalteID, jarakHalte, newJalan);

        if (asal->firstEdge == nullptr)
        {
            asal->firstEdge = newJalan;
        }
        else
        {
            adrJalan tempJalan = asal->firstEdge;
            while (tempJalan->nextEdge != nullptr)
            {
                tempJalan = tempJalan->nextEdge;
            }
            tempJalan->nextEdge = newJalan;
        }
    }
}

void buildHalteGraph(HalteGraph &G)
{
    string input;
    cout << "Masukkan nama halte ('0' untuk keluar): ";
    cin >> input;
    while (input != "0")
    {
        addHalteVertex(G, input);
        cout << "Masukkan nama halte ('0' untuk keluar): ";
        cin >> input;
    }
}

void printHalteGraph(HalteGraph G)
{
    adrHalteVertex v = G.firstHalte;
    while (v != nullptr)
    {
        cout << "Halte ID: " << v->halteID << endl;
        adrJalan e = v->firstEdge;
        while (e != nullptr)
        {
            cout << "  Tujuan: " << e->tujuanHalteID << ", Jarak: " << e->jarakHalte << endl;
            e = e->nextEdge;
        }
        v = v->nextHalte;
    }
}

int hitungTotalJarak(HalteGraph G, beamList L, string idBeam)
{
    adrBeam b = L.firstBeam;
    while (b != nullptr && b->idBeam != idBeam)
    {
        b = b->nextBeam;
    }

    if (b == nullptr) return 0; // Beam tidak ditemukan

    int totalJarak = 0;
    adrJalan jalan = b->location->firstEdge;
    while (jalan != nullptr)
    {
        totalJarak += jalan->jarakHalte;
        jalan = jalan->nextEdge;
    }
    return totalJarak;
}

void createBeam(string idBeam, halteVertex* location, adrBeam &b)
{
    b = new beam;
    b->idBeam = idBeam;
    b->location = location;
    b->nextBeam = nullptr;
}

void initBeamList(beamList &L)
{
    L.firstBeam = nullptr;
}

void insertBeam(beamList &L, HalteGraph &G, string idBeam, halteVertex* location)
{
    adrBeam newBeam;
    createBeam(idBeam, location, newBeam);

    if (L.firstBeam == nullptr)
    {
        L.firstBeam = newBeam;
    }
    else
    {
        adrBeam b = L.firstBeam;
        while (b->nextBeam != nullptr)
        {
            b = b->nextBeam;
        }
        b->nextBeam = newBeam;
    }
}

void beamJalan(beamList &L, HalteGraph &G)
{
    adrBeam b = L.firstBeam;
    while (b != nullptr)
    {
        if (b->location != nullptr && b->location->firstEdge != nullptr)
        {
            cout << "Beam " << b->idBeam << " berjalan dari " << b->location->halteID << " ke " << b->location->firstEdge->tujuanHalteID << endl;
            b->location = G.firstHalte;  // Update ke halte berikutnya
        }
        b = b->nextBeam;
    }
}

void beamRecharge(beamList &L, string idBeam)
{
    adrBeam b = L.firstBeam;
    while (b != nullptr && b->idBeam != idBeam)
    {
        b = b->nextBeam;
    }

    if (b != nullptr)
    {
        cout << "Beam " << idBeam << " di-recharge." << endl;
    }
    else
    {
        cout << "Beam dengan ID " << idBeam << " tidak ditemukan." << endl;
    }
}
