#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

#include <sys/time.h>


#include <size.h>
#include <toggle.h>
#include <geauxdock.h>
#include <util_print.h>



using namespace std;



// arg = 1      print title
// arg = 2      print content
// arg = 3      print all

void
PrintStepTrack (const ReplicaMC *rep, const int arg)
{

  char names[11][30] = {
    "step",
    "lig_conf",
    "prt_conf",
    "temp_idx",
    "total",
    "movevector"
  };

  int a = arg & 0x1;
  int b = (arg >> 1) & 0x1;

  if (a == 1) {
    for (int i = 0; i < 11; ++i)
      printf (",%s", names[i]);
    printf ("\n");
  }

  if (b == 1) {
    printf (",%d", rep->step);
    printf (",%d", rep->idx_prt);
    printf (",%d", rep->idx_lig);
    printf (",%d", rep->idx_tmp);
    printf (",%f", rep->energy[MAXWEI - 1]);
    for (int i = 0; i < 6; i++)
      printf (",%f", rep->movematrix[i]);
    printf ("\n");
  }
}


void
PrintTrack (Record * record, int r, int iter_begin, int iter_end, int arg)
{
  // print title
  PrintStepTrack (NULL, 1);

  for (int s = iter_begin; s <= iter_end; ++s) {
    const ReplicaMC *rep = &record[r].replica[s];
    PrintStepTrack (rep, arg);
  }
}






void
PrintCsv (const float* energy, const int idx_rep, const int step, const int arg)
{
  char names[MAXWEI][8] = {
    "vdw", // 0
    "ele", // 1
    "pmf", // 2
    "psp", // 3
    "hdb", // 4
    "hpc", // 5
    "kde", // 6
    "lhm", // 7
    "dst", // 8
    "total" // 9
  };

  int a = arg & 0x1;
  int b = (arg >> 1) & 0x1;

  if (a == 1) {
    printf ("rep step");
    for (int i = 0; i < MAXWEI; ++i)
      printf (" %s", names[i]);
    printf ("\n");
  }

  if (b == 1) {
    printf ("%3d %d", idx_rep,  step);
    for (int i = 0; i < MAXWEI; ++i)
      // printf (" %+14.10f"  energy[i]);
      printf (" %.4f",  energy[i]);
    printf ("\n");
  }
}





void
PrintMoveVector (const float m[6], const int step)
{
  printf ("\t  %3d\t\t\t", step);
  for (int i = 0; i < 6; ++i) {
    printf (" %+f\t", m[i]);
  }
  printf ("\n");
}



void
PrintMoveRecord (const Record * record, const int steps_per_dump, const int r,
		 const int iter_begin, const int iter_end, const int arg)
{
  for (int s = iter_begin; s <= iter_end; ++s) {
    const ReplicaMC *rep = &record[r].replica[s];
    PrintMoveVector (rep->movematrix, rep->step);
  }

}


// arg = 1      print title
// arg = 2      print content
// arg = 3      print all

void
PrintRecord (const Record * record, int steps_per_dump, int r, int iter_begin, int iter_end, int arg)
{
  // print title
  //PrintCsv (NULL, 0, 0, 1);

  for (int s = iter_begin; s <= iter_end; ++s) {
    const ReplicaMC *rep = &record[r].replica[s];
    PrintCsv (rep->energy, r, rep->step, arg);
  }

}





void
PrintRepRecord (const Record * record, const int steps_per_dump, const int rep_begin,
		const int rep_end, const int iter_begin, const int iter_end, const int arg)
{
  printf ("\treplicas\n");

  printf ("step|\t");

  for (int r = rep_begin; r <= rep_end; ++r)
    printf ("%2d\t", r);
  putchar ('\n');

  printf ("----+");

  for (int r = rep_begin; r <= rep_end; ++r)
    printf ("--------");
  putchar ('\n');

  for (int s = iter_begin; s <= iter_end; ++s) {
    printf ("%3d |\t", s);

    for (int r = rep_begin; r <= rep_end; ++r) {
      const ReplicaMC *myrep = &record[r].replica[s];
      //printf ("%2d ", myrep->idx_prt);
      //printf ("%2d ", myrep->idx_tmp);
      //printf ("%2d ", myrep->idx_lig);

      printf ("%2d ", myrep->idx_rep);

      printf ("\t");
    }
    putchar ('\n');
  }

}





// print all temperature replicas of the same lig & prt
void
PrintRepRecord2 (Record * record, ComplexSize complexsize,
		 int steps_per_dump, int idx_prt, int idx_lig,
		 int iter_begin, int iter_end, int arg)
{
  printf ("temperature replicas with lig %d prt %d\n", idx_lig, idx_prt);

  printf ("MC step |\t");

  for (int t = 0; t < complexsize.n_tmp; ++t)
    printf ("%2d\t", t);
  putchar ('\n');

  printf ("--------+----");

  for (int t = 0; t < complexsize.n_tmp; ++t)
    printf ("--------");
  putchar ('\n');

  for (int s = iter_begin; s <= iter_end; ++s) {
    printf ("%5d   |\t", s);

    for (int t = 0; t < complexsize.n_tmp; ++t) {
      const int r =
	complexsize.n_tmp * complexsize.n_lig * idx_prt + complexsize.n_lig * t + idx_lig;
      const ReplicaMC *myrep = &record[r].replica[s];
      //printf ("%2d ", myrep->idx_prt);
      printf ("%2d ", myrep->idx_tmp);
      //printf ("%2d ", myrep->idx_lig);
      //printf ("%2d ", myrep->idx_rep);

      printf ("\t");
    }
    putchar ('\n');
  }
}






void
PrintLigand0 (const Ligand0 * lig0)
{
    const int lig_natom = lig0->lig_natom;
    for (int i = 0; i < lig_natom; ++i) {
        printf("Ligand0: %02d: x %8.4f, y %8.4f, z %8.4f, t %2d, c %8.4f, n %2d\n",
            i,
            lig0->coord_orig.x[i],
            lig0->coord_orig.y[i],
            lig0->coord_orig.z[i],
            lig0->t[i],
            lig0->c[i],
            lig0->n[i]
            );
    }
    printf ("Ligand0 center: %+10.6f\t%+10.6f\t%+10.6f\n",
        lig0->coord_orig.center[0],
        lig0->coord_orig.center[1],
        lig0->coord_orig.center[2]
        );
}






/*
   void
   PrintProtein (const Protein * prt)
   {
   printf ("prt_npoint:\t\t%d\n", prt->prt_npoint);

   printf ("x \t\ty \t\tz \t\t t \t c \t d \tindex\n");
   printf ("-----------------------------------------------\n");
   const int prt_npoint = prt->prt_npoint;
   for (int i = 0; i < prt_npoint; ++i) {
   printf ("%+10.6f\t", prt->x[i]);
   printf ("%+10.6f\t", prt->y[i]);
   printf ("%+10.6f\t", prt->z[i]);
   printf ("%2d\t", prt->t[i]);
   printf ("%2d\t", prt->c[i]);
   printf ("%4d\n", i);
   }

   }
   */


/*
   void
   PrintDataSize (const ParaH ph)
   {
   float lig_sz = sizeof (Ligand) / 1024;
   float prt_sz = sizeof (Protein) / 1024;
   float psp_sz = sizeof (Psp) / 1024;
   float kde_sz = sizeof (Kde) / 1024;
   float mcs_sz = sizeof (Mcs) / 1024;
   float enepara_sz = sizeof (EnePara) / 1024;

   printf ("lig \t\tprt \t\tpsp \t\tkde \t\tmcs \t\tenepara\n");
   printf ("%f \t%f \t%f \t%f \t%f \t%f\t\t",
   lig_sz, prt_sz, psp_sz, kde_sz, mcs_sz, enepara_sz);
   printf ("KB per struct\n");


   printf ("%f \t%f \t%f \t%f \t%f \t%f\t\t",
   lig_sz * ph.complexsize->n_lig,
   prt_sz * ph.complexsize->n_prt,
   psp_sz,
   kde_sz,
   mcs_sz * ph.complexsize->mcs_nrow,
   enepara_sz);
   printf ("KB total\n");
   }
   */






void
PrintResult (const Complex * complex, const Record *record)
{

#if 1

// print the initial status of the system
// print the initial status of the reference intput data "1a07C"

std::string s;
std::string::size_type pos;

s = complex->prt_file;
pos = s.find("1a07C");
if (pos == std::string::npos) { // sub-string not found
    goto next1;
}

s = complex->lig_file;
pos = s.find("1a07C");
if (pos == std::string::npos) { // sub-string not found
    goto next1;
}


printf ("  0 0 0.6434 -0.0367 -0.2079 -0.1845 0.8521 -0.8880 0.0523 0.1744 -1.0000 0.7735 Ref Result\n"); 
PrintRecord (record, complex->mcpara.steps_per_dump, 0, 0, 0, 2);


next1:

#endif







#if 0
// print all records
for (int r = 0; r <= complex->size.n_rep; ++r) {        // replica loop
    const int next_entry = record[r].next_entry;
    PrintRecord (record, complex->mcpara.steps_per_dump, r, 0, next_entry - 1, 2);
}
#endif






#if 1

// print all records

FILE *fp;
char output_file[100];
struct timeval t;
gettimeofday(&t, NULL);
double mytime_second = (double)t.tv_sec + (double)t.tv_usec * 1e-6;
sprintf(output_file, "out_%.6f.txt", mytime_second);


fp = fopen(output_file, "w");

fprintf(fp, "prt input file: %s, \t%3d conformations\n", complex->prt_file, complex->size.n_prt);
fprintf(fp, "lig input file: %s, \t%3d conformations\n", complex->lig_file, complex->size.n_lig);
fprintf(fp, "\n");


for (int r = 0; r <= complex->size.n_rep; ++r) {        // replica loop
    const ReplicaMC *rep = &complex->replica[r];


    fprintf(fp, "replica, %3d\n", r);
    fprintf(fp, "    prt index,  %2d\n", rep->idx_prt);
    fprintf(fp, "   temp index, %2d, minus beta, %f\n",
        rep->idx_tmp,
        complex->temp[rep->idx_tmp].minus_beta
        );
    fprintf(fp, "    lig index,  %2d \n", rep->idx_lig);

    const int next_entry = record[r].next_entry;


    if (next_entry != 0) {
        fprintf(fp, "    accepted moves in format ");
        fprintf(fp, "\"accepted step, mc move step, translation x y z, rotation x y z, energy\"\n");
    }
    else {
        fprintf(fp, "    all moves are rejected\n");
    }

    for (int s = 0; s < next_entry; s++) { // step of record
        const ReplicaMC *rep = &record[r].replica[s];
        fprintf(fp, "%5d, %5d, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f, %8.4f\n",
            s,                      // accepted step
            rep->step,              // mc move step
            rep->movematrix[0],
            rep->movematrix[1],
            rep->movematrix[2],
            rep->movematrix[3],
            rep->movematrix[4],
            rep->movematrix[5],
            rep->energy[9]          // total energy
            );
    }

    fprintf(fp, "\n");

}

fclose(fp);

printf("results are saved in %s\n", output_file);
#endif










// old code, bad !!!!!!!!!!!
#if 0
#if IS_H4DUMP == 1
char myoutputfile[MAXSTRINGLENG];
sprintf(myoutputfile, "%s/%s_%04d.h5", ph.mcpara->outputdir, ph.mcpara->outputfile, 0);
Record *record;
record = (Record *) malloc (ph.record_sz);
ReadRecord (record, ph.complexsize->n_rep, myoutputfile);

const int myreplica = 0;
const int iter_begin = 0;
//const int iter_end = minimal_int (steps_per_dump, 1) - 1;
const int iter_end = 0;
const int arg = 2;

PrintRecord (record, steps_per_dump, myreplica, iter_begin, iter_end, arg);
//PrintMoveRecord (record, steps_per_dump, myreplica, iter_begin, iter_end, arg);

free (record);
#endif
#endif

}



















void
PrintComplexInfo (const Complex * c)
{

    printf ("===============================================================\n");
    printf ("Inputs\n");
    printf ("===============================================================\n");
    printf ("ligand file\t\t\t%s\n", c->lig_file);
    printf ("protein file\t\t\t%s\n", c->prt_file);
    printf ("lhm file\t\t\t%s\n", c->lhm_file);
    printf ("enepara file\t\t\t%s\n", c->enepara_file);
    printf ("weight file\t\t\t%s\n", c->weight_file);

    /*
       printf ("ligand conformations\t\t%d\n", c->size.n_lig);
       printf ("prt conformations\t\t%d\n", c->size.n_prt);
       printf ("temperatures\t\t\t%d\n", c->size.n_tmp);
       printf ("replica ensembles\t\t%d\n", c->size.n_rep);

       printf ("size_lig\t\t\t%d\n", c->size.lig_natom);
       printf ("size_prt\t\t\t%d\n", c->size.prt_npoint);
       printf ("size_pnk\t\t\t%d\n", c->size.kde_npoint);
       printf ("size_mcs\t\t\t%d\n", c->size.mcs_nrow);
       */
    printf ("===============================================================\n");

}




void
PrintSummary (const Complex * c)
{
    putchar ('\n');

    PrintComplexInfo (c);

    printf ("===============================================================\n");
    printf ("Outputs\n");
    printf ("===============================================================\n");
    printf ("output directory\t\t%s\n", c->mcpara.outputdir);
    printf ("out file (HDF5)\t\t\t%s/%s_XXXX.h5\n", c->mcpara.outputdir, c->mcpara.outputfile);

    printf ("steps_per_dump\t\t\t%d\n", c->mcpara.steps_per_dump);

    printf ("===============================================================\n");
    printf ("Memory Sizes\n");
    const float sz_prt = (float) sizeof (Protein) * MAX_CONF_PRT / 1024 / 1024;
    const float sz1 = (float) sizeof (Complex) / 1024 / 1024;
    const float sz2 = (float) sizeof (Record) * MAX_REP / 1024 / 1024;
    const float sz3 = (float) sizeof (Record) * c->size.n_rep / 1024 / 1024;
    printf ("size of protein\t\t\t\t\t%.3f MB\n", sz_prt);
    printf ("size of each complex\t\t\t\t%.3f MB\n", sz1);
    printf ("record size (memory allocation):\t\t%.3f MB\n", sz2);
    printf ("record size (memory size of each dump file):\t%.3f MB\n", sz3);
    printf ("===============================================================\n");


    printf ("Monte Carlo parameters\n");
    printf ("===============================================================\n");
    printf ("steps_total\t\t\t%d\n", c->mcpara.steps_total);
    printf ("steps_per_dump\t\t\t%d\n", c->mcpara.steps_per_dump);


    printf ("translational scale\t\t");
    for (int i = 0; i < 3; ++i)
        printf ("%.8f ", c->mcpara.move_scale[i]);
    printf ("\n");

    printf ("rotational scale\t\t");
    for (int i = 3; i < 6; ++i)
        printf ("%.8f ", c->mcpara.move_scale[i]);
    printf ("\n");

    printf ("===============================================================\n");

}


