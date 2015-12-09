#!/usr/bin/env python

import os
import sys
import socket
import re
#import subprocess32    # a more robust replacement of  os.system ()

BIN = ''
OUTPUT_DIR = ''
OUTPUT_DIR_BASE = './out'
NT_LOW = 1
NT_HI = 1
NT_STEP = 1
ITER_LOW = 0
ITER_HI = 0


def Run2 (cmd, dir):
  for i in range (ITER_LOW, ITER_HI):
      ii = str (i).zfill (2)
      file =  dir + '/' + ii
      cmd2 = cmd
      cmd2 += ' | tee ' + file + '.txt'
      cmd3 = 'grep "\<Benchmark\>" ' + file + '.txt > ' + file + '_bench.csv'
      cmd4 = 'grep "\<Benchmark_papi\>" ' + file + '.txt > ' + file + '_benchpapi.csv'

      #print cmd2
      #print cmd3
      #print cmd4
      os.system (cmd2)
      os.system (cmd3)
      os.system (cmd4)



def Run1 (bin, output_dir2):
    for nt in range (NT_LOW, NT_HI + 1, NT_STEP):
        cmd = bin
        cmd = cmd + ' -nt ' + str (nt)

#        cmd = cmd + ' -ll ../data/astex/ligands/ligs.txt'
        cmd = cmd + ' -ll ../data/astex/ligands/list.txt'
# ligand conf == 1:
#	cmd = cmd + ' -ll ../data/astex/ligands/ligs_5cppA1.txt'

#        cmd = cmd + ' -lp ../data/astex/proteins/prts-1.txt'
        cmd = cmd + ' -lp ../data/astex/proteins/prts-11.txt'

        dir = output_dir2 + '_nt' + str (nt)
        #print dir
        os.mkdir (dir)

        Run2 (cmd, dir)



if __name__ == '__main__':
    bin = sys.argv[1]
    NT_LOW = sys.argv[2]
    NT_HI = sys.argv[3]
    NT_STEP = sys.argv[4]
    ITER_LOW = sys.argv[5]
    ITER_HI = sys.argv[6]
    NT_LOW = int (NT_LOW)
    NT_HI = int (NT_HI)
    NT_STEP = int (NT_STEP)
    ITER_LOW = int (ITER_LOW)
    ITER_HI = int (ITER_HI)



    hostname = socket.gethostname ()
    hostname = re.sub ("\d+$", "", hostname)
    binname = os.path.basename (bin)
    #output_dir2 = os.path.join (OUTPUT_DIR_BASE, hostname + '_' + binname)
    output_dir2 = OUTPUT_DIR_BASE + '_' + hostname + '_' + binname

    Run1 (bin, output_dir2)




# export OMP_PROC_BIND=true
# export MIC_OMP_PROC_BIND=true
# export MIC_KMP_AFFINITY=SCATTER


# for bin in ./bin/smic_100/gpuk20*; do echo $bin; done

# benchmark kernel components
# for bin in ./bin/smic_100/cpu*; do ./batch_cs.py $bin 2 2 1 1 8; done
# for bin in ./bin/smic_100/gpuk20*; do ./batch_cs.py $bin 28 28 1 1 8; done
# for bin in ./bin/smic_100/cpu*; do ./batch_cs.py $bin 40 40 1 1 8; done
# for bin in ./bin/smic_100/mic*; do ./batch_cs.py $bin 240 240 1 1 8; done
# for bin in ./bin/lasphi_100/gpu980*; do ./batch_cs.py $bin 64 64 1 1 8; done
# for bin in ./bin/ece_100/gpu780_*; do ./batch_cs.py $bin 24 24 1 1 8; done


# production runs
# ./batch_cs.py ./bin/production_run_1000/smic_cpu 1 1 1 1 8
# ./batch_cs.py ./bin/production_run_1000/smic_gpuk20 1 1 1 1 8
# ./batch_cs.py ./bin/production_run_1000/smic_mic 1 1 1 1 8
# ./batch_cs.py ./bin/production_run_1000/ece_gpu780 1 1 1 1 8
# ./batch_cs.py ./bin/production_run_1000/ece_gpu780x2 1 1 1 1 8
# ./batch_cs.py ./bin/production_run_1000/lasphi_gpu980 1 1 1 1 8

# reps
# ./batch_cs.py ./bin/smic_100/cpu_branch_full 1 100 1 1 8
# ./batch_cs.py ./bin/smic_100/gpuk20_branch_full 1 70 1 1 8
# ./batch_cs.py ./bin/smic_100/mic_branch_full 1 960 1 1 8

