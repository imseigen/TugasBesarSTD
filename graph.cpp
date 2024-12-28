#include "graph.h"

void createHalteVertex(string halteID, adrHalteVertex &v)
{
    v = new halteVertex();
    v->halteID = halteID;
    v->nextHalte = nullptr;
    v->firstEdge = nullptr;
}

void createJalan(adrHalteVertex tujuan, int jarakHalte, adrJalan &e)
{
    e = new jalan();
    e->tujuanHalte = tujuan;
    e->jarakHalte = jarakHalte;
    e->nextEdge = nullptr;
}

void initHalteGraph(HalteGraph &G)
{
    G.firstHalte = nullptr;
}

void addHalteVertex(HalteGraph &G, string halteID)
{
    adrHalteVertex newHalte = searchHalte(G, halteID);

    if (newHalte != nullptr)
    {
        cout << "Halte sudah ada\n";
    }
    else
    {
        createHalteVertex(halteID, newHalte);
        if (G.firstHalte == nullptr) 
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
        
        cout << "Halte berhasil ditambahkan\n";
    }

    
}

adrHalteVertex searchHalte(HalteGraph G, string halteID)
{
    adrHalteVertex v = G.firstHalte;

    while (v != nullptr && v->halteID != halteID)
    {
        v = v->nextHalte;
    }

    return v;
}

void addJalan(HalteGraph &G, adrHalteVertex asal, string tujuanHalteID, int jarakHalte)
{
    adrJalan newJalan;
    adrHalteVertex tujuan = searchHalte(G, tujuanHalteID);

    if (tujuan == nullptr)
    {
        cout << "Halte tujuan tidak ada\n";
    }
    else 
    {
        createJalan(tujuan, jarakHalte, newJalan);

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

        cout << "Jalan berhasil ditambahkan\n";
    }
}

void buildHalteGraph(HalteGraph &G)
{
    string input_halte;

    //Input halte
    cout << "Masukkan nama halte ('0' untuk keluar): ";
    cin >> input_halte;
    while (input_halte != "0")
    {
        addHalteVertex(G, input_halte);

        cout << "\nMasukkan nama halte ('0' untuk keluar): ";
        cin >> input_halte;
    }
}

void buildJalan(HalteGraph &G) 
{
    string input_halte, input_jalan;
    int jarak;
    
    cout << "Masukkan nama halte ('0' untuk keluar): ";
    cin >> input_halte;
    while (input_halte != "0")
    {
        adrHalteVertex halte = searchHalte(G, input_halte);

        if (halte != nullptr)
        {
            cout << "\nMasukkan halte tujuan ('0' untuk keluar): ";
            cin >> input_jalan;
            while (input_jalan != "0") 
            {
                cout << "Masukkan jarak halte ('0' untuk keluar): ";
                cin >> jarak;
                
                addJalan(G, halte, input_jalan, jarak);
                
                cout << "\nMasukkan halte tujuan ('0' untuk keluar): ";
                cin >> input_jalan;
            }
        }
        else
        {
            cout << "\nHalte tujuan tidak ada\n";
        }

        cout << "\nMasukkan nama halte ('0' untuk keluar): ";
        cin >> input_halte;
    }
}

void printHalteGraph(HalteGraph G, beamList L)
{
    adrHalteVertex v = G.firstHalte;
    adrJalan e;

    while (v != nullptr)
    {
        e = v->firstEdge;

        cout << "Halte " << v->halteID;
        while (e != nullptr)
        {
            cout << " |-- " << e->jarakHalte << " --> Halte " << e->tujuanHalte->halteID << "|";
            e = e->nextEdge;
        }
        cout << endl;
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

//Beam
void createBeam(string idBeam, adrHalteVertex location, adrBeam &b)
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

adrBeam searchBeam (beamList L, string beamID)
{
    adrBeam b = L.firstBeam;

    while (b != nullptr && b->idBeam != beamID)
    {
        b = b->nextBeam;
    }
    return b;
}

void insertBeam(beamList &L, HalteGraph G, string idBeam, adrHalteVertex location)
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

void buildBeam (beamList &L, HalteGraph G)
{
    string beamID, locationID;
    adrHalteVertex location;
    adrBeam newBeam;

    cout << "Masukkan id beam ('0' untuk keluar): ";
    cin >> beamID;

    while (beamID != "0")
    {
        newBeam = searchBeam(L, beamID);

        if (newBeam != nullptr)
        {
            cout << "Beam sudah ada\n";
        }
        else 
        {
            cout << "\nMasukan lokasi beam: ";
            cin >> locationID;
            location = searchHalte(G, locationID);

            insertBeam(L, G, beamID, location);
            cout << "\nBeam berhasil dimasukkan\n";
        }

        cout << "\nMasukkan id beam ('0' untuk keluar): ";
        cin >> beamID;
    }
}

void beamJalan(beamList &L, HalteGraph &G)
{
    adrBeam b = L.firstBeam;
    while (b != nullptr)
    {
        if (b->location != nullptr && b->location->firstEdge != nullptr)
        {
            cout << "Beam " << b->idBeam << " berjalan dari " << b->location->halteID << " ke " << b->location->firstEdge->tujuanHalte->halteID << endl;
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
