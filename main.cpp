#include <iostream>
#include "graph.h"

using namespace std;

int menu ()
{
    int input;

    cout << "\n========== MENU ==========\n";
    cout << "1. Tambah halte" << endl;
    cout << "2. Tambah jalan" << endl;
    cout << "3. Print Halte & Beam" << endl;
    cout << "4. Tambah beam" << endl;
    cout << "5. Kendarai beam" << endl;
    cout << "6. Recharge beam" << endl;
    cout << "0. Keluar" << endl;
    cout << "===========================\n";
    cout << "Input anda: ";
    cin >> input;
    cout << "---------------------------\n";

    return input;
}

int main()
{
    HalteGraph G;
    beamList L;
    initHalteGraph(G);
    initBeamList(L);
    
    string beamID, tujuan;

    int input = menu();

    while (input != 0)
    {
        switch (input)
        {
        case 1:
            buildHalteGraph(G);
            break;

        case 2:
            buildJalan(G);
            break;

        case 3:
            printHalteGraph(G, L);
            break;

        case 4:
            buildBeam(L, G);
            break;

        case 5:
            cout << "Id beam yang dipakai: ";
            cin >> beamID;
            cout << "Halte tujuan: ";
            cin >> tujuan;

            beamJalan(L, G, beamID, tujuan);
            break;

        case 6:
            cout << "Id beam yang ingin di recharge: ";
            cin >> beamID;
            beamRecharge(L, beamID);
            break;

        default:
            cout << "Input salah";
            break;
        }

        input = menu();
    }

    /*
    Stack S;
    createStack(S);
    elmStack* p = createElmStack(G.firstHalte);
    push(S, p);
    printInfo(S);
    p = createElmStack(G.firstHalte->nextHalte);
    push(S, p);
    printInfo(S);
    p = pop(S);
    printInfo(S);
    */

    return 0;
}
