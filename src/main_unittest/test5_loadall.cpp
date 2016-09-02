#include <string>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <frontend.h>


using namespace std;



int main(int argc, char **argv)
{
    Loader loader;


    string input1 =
        "magicnumber_a4a6b25c,0,1a07C,/worka/work/yfang11/geauxdock_cs_v2/data/astex/proteins/1a07C.pdb,1a07C1,/worka/work/yfang11/geauxdock_cs_v2/data/astex/ligands/1a07C1.sdf,/worka/work/yfang11/geauxdock_cs_v2/data/astex/ligands/1a07C1-0.8.ff,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08ff_opt,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/paras,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08_nor_a,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08_nor_b,1,0.044,0.036,0.02,0.08,1,0,1000,0,11,51,1,561,344,34,454,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
    //string input2 = input1;


    loader.load(input1);
    loader.check();
    loader.print_sz();

    loader.load(input1);
    loader.check();
    loader.print_sz();
    loader.check();

#if 1
    vector<string> tokens = loader.get_tokens();
    for (unsigned int i = 0; i < tokens.size() - 1; ++i)
        cout << tokens[i] << ",";
    cout << tokens[tokens.size() - 1];
#endif


    cout << endl;

    printf("done\n");
    return 0;
}

