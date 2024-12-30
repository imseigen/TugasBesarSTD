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

void addJalan(HalteGraph &G, adrHalteVertex asal, adrHalteVertex tujuanHalte, int jarakHalte)
{
    adrJalan newJalan;

    if (tujuanHalte == nullptr)
    {
        cout << "Halte tujuan tidak ada\n";
    }
    else 
    {
        if (asal->firstEdge == nullptr)
        {
            createJalan(tujuanHalte, jarakHalte, newJalan);
            asal->firstEdge = newJalan;
        }
        else
        {
            adrJalan tempJalan = asal->firstEdge;
            while (tempJalan->nextEdge != nullptr)
            {
                if (tempJalan->tujuanHalte == tujuanHalte) 
                {
                    cout << "Tujuan halte sudah ada\n";
                    return;
                }
                tempJalan = tempJalan->nextEdge;
            }
            if (tempJalan->tujuanHalte == tujuanHalte) 
            {
                cout << "Tujuan halte sudah ada\n";
                return;
            }
            createJalan(tujuanHalte, jarakHalte, newJalan);
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
                adrHalteVertex jalan = searchHalte(G, input_jalan);

                if (jalan != nullptr)
                {
                    cout << "Masukkan jarak halte ('0' untuk keluar): ";
                    cin >> jarak;
                    
                    addJalan(G, halte, jalan, jarak);

                    addJalan(G, jalan, halte, jarak);
                    
                    cout << "\nMasukkan halte tujuan ('0' untuk keluar): ";
                    cin >> input_jalan;
                    jalan = searchHalte(G, input_jalan);
                }
                else
                {
                    cout << "Halte tujuan tidak ada\n";
                }
            }
        }
        else
        {
            cout << "\nHalte tidak ada\n";
        }

        cout << "\nMasukkan nama halte ('0' untuk keluar): ";
        cin >> input_halte;
    }
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

void beamJalan(beamList &L, HalteGraph G, string beamID, string tujuan)
{
    adrBeam b = searchBeam(L, beamID);

    if (b == nullptr)
    {
        cout << "Beam tidak ditemukan\n";
    }
    else 
    {
        adrHalteVertex v = searchHalte(G, tujuan);


    }

    /*adrBeam b = L.firstBeam;
    while (b != nullptr)
    {
        if (b->location != nullptr && b->location->firstEdge != nullptr)
        {
            cout << "Beam " << b->idBeam << " berjalan dari " << b->location->halteID << " ke " << b->location->firstEdge->tujuanHalte->halteID << endl;
            b->location = G.firstHalte;  // Update ke halte berikutnya
        }
        b = b->nextBeam;
    }*/
}

void beamRecharge(beamList &L, string idBeam)
{
    adrBeam b = searchBeam(L, idBeam);

    if (b != nullptr)
    {
        for (int i = 0; i < 10; i++)
        {
            b->historyJalan[i] = nullptr;
        }

        cout << "Beam " << idBeam << " di-recharge." << endl;
    }
    else
    {
        cout << "Beam dengan ID " << idBeam << " tidak ditemukan." << endl;
    }
}


void printHalteGraph(HalteGraph G, beamList L)
{
    adrHalteVertex v = G.firstHalte;
    adrBeam b;
    adrJalan e;

    while (v != nullptr)
    {
        e = v->firstEdge;
        b = L.firstBeam;

        cout << "Halte " << v->halteID;
        while (e != nullptr)
        {
            cout << " |-- " << e->jarakHalte << " m --> Halte " << e->tujuanHalte->halteID << "|";
            e = e->nextEdge;
        }
        cout << endl;

        cout << "Beam di halte: ";
        
        while (b != nullptr)
        {
            if (b->location == v)
            {
                cout << "| " << b->idBeam << " |";
            }
            b = b->nextBeam;
        }
        cout << endl;

        v = v->nextHalte;
    }
}

    // Stack
    void createStack (Stack &S)
    {
        S.Top = nullptr;
    }

    bool isEmpty (Stack S)
    {
        return S.Top == nullptr;
    }

    void push (Stack &S, adrHalteVertex x)
    {
        if (isEmpty(S)) 
        {
            S.Top = x;
        } else {
            x->nextHalte = S.Top;
            S.Top = x;
        }
    }

    adrHalteVertex pop (Stack &S)
    {
        adrHalteVertex x = S.Top;

        if (x->nextHalte == nullptr)
        {
            S.Top = nullptr;
        } 
        else 
        {
            S.Top = x->nextHalte;
        }

        return x;
    }

    void printInfo (Stack S)
    {
        Stack q = S;
        adrHalteVertex x;

        while (!isEmpty(S))
        {
            x = pop(S);
            cout << x->halteID << " ";
        }
        
        S.Top = q.Top;
        cout << endl;
    }
