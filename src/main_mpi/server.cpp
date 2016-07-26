#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>

#include <size.h>

#include <mpi.h>

using namespace std;

MPI_Datatype MPI_MSG;


// assuming the MPI rank of server is 0
void distribute(vector<string> & lines)
{
    int id, nprocs;
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    MPI_Request req[nprocs];
    MPI_Status st[nprocs];
    MPI_Status status;


    // dispatch jobs on requests
    const int n = lines.size() - 1; // number of input data
    for (int i = 0; i < n; i++) {
        string input = lines[i + 1];
        const char *msg = input.c_str();

        int dst;
        const int mytag = 0;
        MPI_Recv (&dst, 1, MPI_INT, MPI_ANY_SOURCE, mytag, MPI_COMM_WORLD, &status);
        MPI_Isend (msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD, &req[i]);
        printf ("server sent msg %03d to client %02d\n", i, dst);
    }
    for (int i = 1; i < nprocs; i++) { // wait for all clients
        MPI_Wait (&req[i], &st[i]);
    }



    // send finish signal
    const char *msg = "FINISH_SIGNAL";
    for (int i = 1; i < nprocs; i++) {
        int dst;
        const int mytag = 0;
        MPI_Recv (&dst, 1, MPI_INT, MPI_ANY_SOURCE, mytag, MPI_COMM_WORLD, &status);
        MPI_Isend (msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD, &req[i]);
        printf ("server kill client %02d\n", dst);
    }
    for (int i = 1; i < nprocs; i++) { // wait for all clients
        MPI_Wait (&req[i], &st[i]);
    }

}






void load(const string fnpath)
{
    ifstream ifn(fnpath.c_str());
    if (!ifn.is_open()) {
        cout << "Failed to open " << fnpath << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    vector<string> lines;

    while (getline(ifn, line)) {
        //cout << line << endl;
        lines.push_back(line);
    }

    ifn.close();

    const int nlines = lines.size();  // number of lines
    if (nlines < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }


    distribute(lines);
}


void server(int argc, char **argv)
{
    if (argc == 1) {
        load("a2.csv");
    }
    else if (argc == 2) {
        load(argv[1]);
    }
    else {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}


int
main (int argc, char **argv)
{
    int id, nprocs;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    if (nprocs < 2) {
        printf ("nprocs < 2. exit\n");
        exit (-1);
    }


    MPI_Type_contiguous (sizeof(char) * MAXINPUTSTRINGLENG, MPI_BYTE, &MPI_MSG);
    MPI_Type_commit (&MPI_MSG);


    if (id == 0)
        server (argc, argv); // server ID must be 0; otherwise the messsage ID will be wrong
    else
        printf ("server is assigned with a wrong MPI rank\n");


    return 0;
}




