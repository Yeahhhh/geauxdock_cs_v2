#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>

#include <size.h>

#include <mpi.h>


#include <yeah/cpp/text_io.hpp>

using namespace std;

MPI_Datatype MPI_MSG;


void distribute(vector<string> & lines)
{
    int id, nprocs;
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    MPI_Status status;


    // dispatch jobs on requests
    const int n = lines.size() - 1; // number of input data
    printf ("number of jobs: %d\n", n);


    for (int i = 0; i < n; i++) {
        string input = lines[i + 1];
        const char *msg = input.c_str();

        int dst;
        const int mytag = 0;
        MPI_Recv (&dst, 1, MPI_INT, MPI_ANY_SOURCE, mytag, MPI_COMM_WORLD, &status);
        MPI_Send (msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD);
        printf ("server sent msg %03d to client %02d\n", i, dst);
    }



    // send finish signal
    const char *msg = "FINISH_SIGNAL";
    for (int i = 1; i < nprocs; i++) {
        int dst;
        const int mytag = 0;
        MPI_Recv (&dst, 1, MPI_INT, MPI_ANY_SOURCE, mytag, MPI_COMM_WORLD, &status);
        MPI_Send (msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD);
        printf ("server kill client %02d\n", dst);
    }
    printf ("server quit\n");

}




void server(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "a3.csv";
    }
    if (argc == 2) {
        fn = argv[1];
    }
    if (argc > 2) {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> lines;
    yeah::load_fn_to_vecstr(fn, lines);
    distribute(lines);
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




