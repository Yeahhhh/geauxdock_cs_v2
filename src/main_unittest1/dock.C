#define CATCH_CONFIG_MAIN

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstdio>


#include <size.h>
#include <dock.h>
#include <util.h>
#include <util_optimize.h>
#include <util_print.h>
#include <toggle.h>
#include <load.h>

#include "catch.hpp"

TEST_CASE( "Load", "[ligand]" )
{
  Ligand0 *lig0 = new Ligand0[300];

  LigandFile *lig_file = new LigandFile;
  lig_file->molid = "MOLID";
  lig_file->path = "../../test/ZINC00062388.sdf";

  loadLigand (lig_file, lig0);

  delete[]lig0;
}
