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
    
    string beamID;

    // int input = menu();

    // while (input != 0)
    // {
    //     switch (input)
    //     {
    //     case 1:
    //         buildHalteGraph(G);
    //         break;

    //     case 2:
    //         buildJalan(G);
    //         break;

    //     case 3:
    //         printHalteGraph(G, L);
    //         break;

    //     case 4:
    //         buildBeam(L, G);
    //         break;

    //     case 5:
    //         break;

    //     case 6:
    //         cout << "Id beam yang ingin di recharge: ";
    //         cin >> beamID;
    //         beamRecharge(L, beamID);
    //         break;

    //     default:
    //         cout << "Input salah";
    //         break;
    //     }

    //     input = menu();
    // }

    // buildHalteGraph(G);
    // buildJalan(G);
    // printHalteGraph(G);

    // insertBeam(L, G, "Beam 1", G.firstHalte);
    // insertBeam(L, G, "Beam 2", G.firstHalte);
    // insertBeam(L, G, "Beam 3", G.firstHalte);

    // beamJalan(L, G);
    // beamRecharge(L, "Beam 1");
    // beamRecharge(L, "Beam 2");
    // beamRecharge(L, "Beam 3");

    Stack S;
    createStack(S);
    buildHalteGraph(G);
    printHalteGraph(G,L);
    cout << endl;

    adrHalteVertex x = G.firstHalte;
    push(S, x);
    printInfo(S);
    cout << endl;

    adrHalteVertex y = pop(S);
    printHalteGraph(G, L);
    printInfo(S);

    return 0;
}
