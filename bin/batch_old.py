#!/usr/bin/env python

import shlex
import os
import sys
import datetime
import socket
import re


OUTPUT_DIR_BASE = '/work/yfang11/dock/bench'
OUTPUT_DIR = ''
PARAS_DAT = '/work/yfang11/geauxdock_multibackend/data/parameters'
OPT_FILE = os.path.join (PARAS_DAT, '08ff_opt')
NOR_A_FILE = os.path.join (PARAS_DAT, '08_nor_a')
NOR_B_FILE = os.path.join (PARAS_DAT, '08_nor_b')
PARA_FILE = os.path.join (PARAS_DAT, 'paras')





def nameDir (basedir):
    hostname = socket.gethostname ()
    hostname = re.sub ("\d+$", "", hostname)
    timenow = datetime.datetime.now ().strftime("%y%m%d-%H%M%S")
    dir = os.path.join (basedir, hostname + '_' + timenow)
    return dir




def readList (file):
    return [line.rstrip('\n') for line in open(file)]



def runList (bin, prt_list, lig_list, n_tmp):
    for line1 in readList (prt_list):
        prt_id, prt_file = line1.split ()

        for line2 in readList (lig_list):
            lig_id, lig_file, ff_file = line2.split ()

            cmd = ''
            cmd += bin
            cmd += ' -p ' + prt_file
            cmd += ' -l ' + lig_file
            cmd += ' -s ' + ff_file
            cmd += ' -id ' + lig_id
            cmd += ' -opt ' + OPT_FILE
            cmd += ' -na ' + NOR_A_FILE
            cmd += ' -nb ' + NOR_B_FILE
            cmd += ' -para ' + PARA_FILE
            cmd += ' -floor_temp 0.044f'
            cmd += ' -ceiling_temp 0.036f'
            cmd += ' -nt ' + n_tmp

            #args = shlex.split(cmd)
            #print args

            outputfile = os.path.join (OUTPUT_DIR, prt_id + '-' + lig_id + '.txt')
            #print outputfile
            cmd += ' > ' + outputfile
            print cmd
	    #os.system (cmd)



if __name__ == '__main__':

    bin = sys.argv[1]
    prt_list = sys.argv[2]
    lig_list = sys.argv[3]
    n_tmp = sys.argv[4]

    OUTPUT_DIR = nameDir (OUTPUT_DIR_BASE)
#    os.mkdir (OUTPOUT_DIR)

    runList (bin, prt_list, lig_list, n_tmp)


