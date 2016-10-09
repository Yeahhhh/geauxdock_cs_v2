#include <iostream>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <size.h>
#include <frontend.h>

#include <mpi.h>

#if TARGET_DEVICE == TARGET_CPU || TARGET_DEVICE == TARGET_MIC
#include <backend_cpu_mic.h>
#elif TARGET_DEVICE == TARGET_GPU
#include <backend_gpu.h>
#endif

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>
#include <yeah/measuring/counting/timer.hpp>


using namespace std;

MPI_Datatype MPI_MSG;



/*
   void
   Dock (char *recv_msg, char * name, const int id)
   {
//printf("%-20s \t\t\t\t\t client %02d\n", name, id);
}
*/



void client(int argc, char **argv)
{
    int id;
    MPI_Comm_rank (MPI_COMM_WORLD, &id);


    char *recv_msg = new char[MAXINPUTSTRINGLENG];

    int send_msg = id;
    const int dst = 0; // server rank is 0
    MPI_Status status;
    const int mytag = 0;


    vector<string> tokens;
    Loader loader; // frontend
    Docker docker; // backend
    yeah::measuring::counting::Timer t;

    char pname[1024];
    char ofn[1024];
    int pname_len;
    MPI_Get_processor_name(pname, &pname_len);

    while (1) {
        MPI_Send (&send_msg, 1, MPI_INT, dst, mytag, MPI_COMM_WORLD);
        printf ("%-20s \t\t\t\t\t client %02d request\n", argv[0], id);
        MPI_Recv (recv_msg, 1, MPI_MSG, dst, mytag, MPI_COMM_WORLD, &status);

        if (strcmp(recv_msg, "FINISH_SIGNAL") != 0) { // if not "FINISH_SIGNAL"
            printf ("%s start docking\n", argv[0]);
            printf("hostname: %s", pname);
            //Dock (recv_msg, argv[0], id);


            string line = recv_msg;
            loader.load(line);
            loader.check();
            loader.build_complex(docker.complex);

            t.Reset();
            t.Start();
            docker.run();
            t.Stop();
            t.Print();

            tokens = loader.get_tokens();
#if TARGET_DEVICE == TARGET_CPU
            tokens[CSVTAG_TIME_RL_CPU] = num2string(t.ts);
            sprintf(ofn, "a5.cpu3.%s.csv", pname);
#endif
#if TARGET_DEVICE == TARGET_MIC
            tokens[CSVTAG_TIME_RL_MIC] = num2string(t.ts);
            sprintf(ofn, "a5.mic3.%s.csv", pname);
#endif
#if TARGET_DEVICE == TARGET_GPU
            tokens[CSVTAG_TIME_RL_GPU] = num2string(t.ts);
            sprintf(ofn, "a5.gpu3.%s.csv", pname);
#endif

            std::string str = yeah::sprint_tokens_csv(tokens);
            vector<string> strs;
            strs.push_back(str);
            yeah::save_vecstr_to_fn_append(ofn, strs);
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



