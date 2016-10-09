#!/usr/bin/env python2

from __future__ import print_function
import glob
import os
import sys


def func_lig(lig_dir):
    ffs = sorted(glob.glob(lig_dir + '/*.ff'))
    sdfs = sorted(glob.glob(lig_dir + '/*.sdf'))
    sdf_ffs = zip(sdfs, ffs)

    strs = []
    for sdf_ff in sdf_ffs:
        sdf_path = os.path.abspath(sdf_ff[0])
        ff_path = os.path.abspath(sdf_ff[1])
        lig_id = os.path.basename(sdf_path).split ('.')[0]
        str = lig_id + ',' + sdf_path + ',' + ff_path
        strs.append(str)
    return strs



def func_prt(prt_fn):
    prt_path = os.path.abspath(prt_fn)
    prt_id = os.path.basename(prt_path).split ('.')[0]
    str = prt_id + ',' + prt_path
    return str


def func1 (argv):
    prt_fn = argv[1] #.strip().lstrip()
    lig_dir = argv[2]
    weight_fn = argv[3]
    enepara_fn = argv[4]
    nora_fn = argv[5]
    norb_fn = argv[6]
    n_temp = argv[7]
    temp_high = argv[8]
    temp_low = argv[9]
    tras_scale = argv[10]
    rot_scale = argv[11]
    n_dump = argv[12]


    #print(prt_fn, lig_dir)

    prt_str = func_prt(prt_fn)
    lig_strs = func_lig(lig_dir)
    weight_str = os.path.abspath(weight_fn)
    enepara_str = os.path.abspath(enepara_fn)
    nora_str = os.path.abspath(nora_fn)
    norb_str = os.path.abspath(norb_fn)

    tagi = 0
    print('magicnumber_a4a6b25c,', end = '')
    tagi += 1
    print('data_id,', end = '')
    tagi += 1
    print('prt_id,prt,', end = '')
    tagi += 2
    print('lig_id,lig,ff,', end = '')
    tagi += 2
    print('weight,enepara,nora,norb,', end = '')
    tagi += 4
    print('ntemp,temp_high,temp_low,tras_scale,rot_scale,n_dump,', end = '')
    tagi += 6

    tag_extra=40
    for j in range(1, tag_extra):
        print('tag%d' % (tagi + j), end = ',')
    print('tag%d' % (tagi + tag_extra))

    i = 0
    for lig_str in lig_strs:
        print('magicnumber_a4a6b25c', end = ',')
        print(i, end = ',')
        print(prt_str, end = ',')
        print(lig_str, end = ',')
        print(weight_str, end = ',')
        print(enepara_str, end = ',')
        print(nora_str, end = ',')
        print(norb_str, end = ',')
        print(n_temp, end = ',')
        print(temp_high, end = ',')
        print(temp_low, end = ',')
        print(tras_scale, end = ',')
        print(rot_scale, end = ',')
        print(n_dump, end = ',')
        for j in range(1, tag_extra):
            print('-2', end = ',')
        print('-2')
        i += 1


if __name__ == '__main__':

    #if len(sys.argv) != 11:
    #    print('Usage: %s ...' % sys.argv[0])

    func1(sys.argv)


