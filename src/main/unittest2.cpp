#include <string>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <frontend.h>
#include <backend_gpu.h>


using namespace std;


int main(int argc, char **argv)
{
    string input1 =
"magicnumber_a4a6b25c,0,1a07C,/home/yfang11/work2/geauxdock_cs_v2/data/astex/proteins/1a07C.pdb,1a07C1,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a07C1.sdf,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a07C1-0.8.ff,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08ff_opt,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/paras,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_a,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_b,1,0.044,0.036,0.02,0.08,1,0,100,0,11,51,1,561,344,34,454,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

    Loader loader;
    Docker docker;

    loader.load(input1);
    loader.check();

#if 1
    vector<string> tokens = loader.get_tokens();
    for (unsigned int i = 0; i < tokens.size() - 1; ++i)
        cout << tokens[i] << ",";
    cout << tokens[tokens.size() - 1];
#endif
    cout << endl;


    //Complex complex;
    //loader.build_complex(&complex);
    loader.build_complex(docker.complex);
    docker.run();

    return 0;
}

