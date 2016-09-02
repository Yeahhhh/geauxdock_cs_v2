#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <size.h>

#include <mpi.h>

using namespace std;

MPI_Datatype MPI_MSG;



void
Dock (char *recv_msg, char * name, const int id)
{
  //printf("%-20s \t\t\t\t\t client %02d\n", name, id);
  printf("%-20s \t\t\t\t\t client %02d: %s\n", name, id, recv_msg);
}



// assuming the server rank is 0
void client(int argc, char **argv)
{
    int id;
    MPI_Comm_rank (MPI_COMM_WORLD, &id);


    char *recv_msg = new char[MAXINPUTSTRINGLENG];

    int send_msg = id;
    const int dst = 0; // server rank is 0
    MPI_Status status;
    const int mytag = 0;

    while (1) {
        MPI_Send (&send_msg, 1, MPI_INT, dst, mytag, MPI_COMM_WORLD);
        printf ("%-20s \t\t\t\t\t client %02d request\n", argv[0], id);
        MPI_Recv (recv_msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD, &status);

        if (strcmp(recv_msg, "FINISH_SIGNAL") != 0) { // if not "FINISH_SIGNAL"
            printf ("%s start docking\n", argv[0]);
            //Dock (recv_msg, argv[0], id);
        }
        else { // if received "FINIASH_SIGNAL"
            printf ("%-20s \t\t\t\t\t\t\t\t\t\t client %02d retired\n", argv[0], id);
            break;
        }
    }

    delete[]recv_msg;
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


    if (id != 0)
        client (argc, argv); // client ID must not be 0; otherwise the messsage ID will be wrong
    else
        printf ("client is assigned with a wrong MPI rank\n");


    return 0;
}



