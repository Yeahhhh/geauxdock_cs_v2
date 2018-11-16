
/*
==============================================================================================
     __________________ ____ ___              .___             __      _________   _____
    /  _____/\______   \    |   \           __| _/____   ____ |  | __ /   _____/  /     \
   /   \  ___ |     ___/    |   /  ______  / __ |/  _ \_/ ___\|  |/ / \_____  \  /  \ /  \
   \    \_\  \|    |   |    |  /  /_____/ / /_/ (  <_> )  \___|    <  /        \/    Y    \
    \______  /|____|   |______/           \____ |\____/ \___  >__|_ \/_______  /\____|__  /
           \/                                  \/           \/     \/        \/         \/

      GPU-accelerated hybrid-resolution ligand docking using ReplicaMC Exchange Monte Carlo

==============================================================================================
*/


#ifndef __SIZE_H_
#define __SIZE_H_


#define MAX_STR_LENG 256



#define NAMEMAX 64
/* max lig aton name */

#define MAXPRO 2048
/* protein residues */

#define MAXLIG 64
/* ligand heavy atoms */

#define MAX_CONF_PRT  20
/* protein confs */

#define MAX_CONF_LIG 64
/* ligand confs */

#define MAXLIG_NUM 200
/* MAX ligand in one ligand .sdf file */

//#define MAX_TMP 1024
#define MAX_TMP 32
//#define MAX_TMP 1
/* number of temperature replicas */

//#define MAX_REP 16384
//#define MAX_REP 4096
//#define MAX_REP 2048
#define MAX_REP 1024
/* max replicas */

#define  MAXSWP 2000
/* max swapping pairs */

#define  MAXLIB 100
/* library cmps */

#define  MAXSDF  500
/* sdf length */

#define MAXTP1 31 // using 32 does not help imporoving performance
/* point types */

#define MAXTP2 24
/* atom types */

#define MAXTP3 50
/* point types (for ele) */

#define MAXTP4 20
/* residue types */

#define MAXFP1 1024
/* smiles */

#define  MAXFP2 168
/* maccs */

// MAXWEI must be less than 16 (can be extended to 32), see CUDA reduction code "e_s"
#define  MAXWEI 10
/* energy terms */

#define MAXKDE 10240
/* kde points */

#define MAX_MCS_ROW 1024
/* position restraints */

#define MAX_MCS_COL MAXLIG
/* mcs fields, number of field in a mcs */


#define INITTEMP 10000.0f
/* temperature in the first replica */


#define PI 3.1415926535f

/* value used for return statement in data.cpp for missing atoms */
#define BADKDE 50

// maximum string length for file names
#define MAXSTRINGLENG 256

// maximum input string length
#define MAXINPUTSTRINGLENG 2048

// if mcs equal to 123456789.0f, it is invalid
#define MCS_INVALID_COORD 0.01234f

// if mcs equal to 728492, it is invalid
#define CMCC_INVALID_VAL 10000.0f

// boltzman constant
#define BOLTZMANN_CONST 1.0f

// monte carlo steps
#define STEPS_PER_DUMP 100

// signal the MPI client to terminate
#define FINISH_SIGNAL 0XFFFFFF

// a small number, so that " / 0 + SMALL_NUMBER" is a legal expression
#define SMALL_NUMBER 0.0f








// column number of input/output CSV file
#define CSVTAG_MAGIC                     0
#define CSVTAG_DATA_ID                   1
#define CSVTAG_PRT_ID                    2
#define CSVTAG_PRT                       3
#define CSVTAG_LIG_ID                    4
#define CSVTAG_LIG                       5
#define CSVTAG_FF                        6
#define CSVTAG_WEIGHT                    7
#define CSVTAG_ENEPARA                   8
#define CSVTAG_NORA                      9
#define CSVTAG_NORB                     10
#define CSVTAG_NTEMP                    11
#define CSVTAG_TEMP_HIGH                12
#define CSVTAG_TEMP_LOW                 13
#define CSVTAG_TRAS_SCALE               14
#define CSVTAG_ROT_SCALE                15
#define CSVTAG_N_DUMP                   16
#define CSVTAG_STEPS_TOTAL              18
#define CSVTAG_SZ_N_PRT                 20
#define CSVTAG_SZ_N_LIG                 21
#define CSVTAG_SZ_N_TMP                 22
#define CSVTAG_SZ_N_REP                 23
#define CSVTAG_SZ_PRT_NPOINT            24
#define CSVTAG_SZ_LIG_NATOM             25
#define CSVTAG_SZ_KDE_NPOINT            26
#define CSVTAG_SZ_MCS_NROW              27

// performance metrics, real/estimated time on CPU/MIC/GPU
#define CSVTAG_TIME_RL_CPU              30
#define CSVTAG_TIME_EST_CPU             31
#define CSVTAG_TIME_RL_MIC              32
#define CSVTAG_TIME_EST_MIC             33
#define CSVTAG_TIME_RL_GPU              34
#define CSVTAG_TIME_EST_GPU             35
#define CSVTAG_LAST_TAG                 56



#endif

