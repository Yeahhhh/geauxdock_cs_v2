
#if 0
/* load the ligand raw conf
 * the ligand effective total conf is less than the raw, since some small rmsd excluded */
void
loadLigConf(LigandFile * lig_file)
{
    // ifstream
    std::string llib3 = lig_file->molid;
    list < string > l1_sdf;
    list < string >::iterator i1_sdf;
    string line1;
    ifstream iff(lig_file->path.c_str());

    if (!iff.is_open()) {
        cout << "cannot open ligand conf file" << endl;
        cout << "Cannot open " << lig_file->path << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(iff, line1))
        l1_sdf.push_back(line1);

    iff.close();

    string llib1[MAXSDF];	// contains each line the .sdf file
    int llib2 = 0;

    // load the raw total conf, lig_natom, lnb, ligand name
    for (i1_sdf = l1_sdf.begin(); i1_sdf != l1_sdf.end(); i1_sdf++) {
        llib1[llib2++] = (*i1_sdf);
        if ((*i1_sdf) == "$$$$") {
            if (llib2 > 10) {
                lig_file->lig_natom = atoi(llib1[3].substr(0, 3).c_str());
                lig_file->lnb = atoi(llib1[3].substr(3, 3).c_str());
                for (int i1 = 4 + lig_file->lig_natom + lig_file->lnb; i1 < llib2 - 1; i1++) {
                    if (llib1[i1].find(llib3) != string::npos)
                        lig_file->id = llib1[i1 + 1];
                    else if (llib1[i1].find("ENSEMBLE_TOTAL") != string::npos)
                        lig_file->raw_conf = atoi(llib1[i1 + 1].c_str());
                }
            }
        }
    }

    // DEBUG_2_("llib2: ", llib2);
    llib2 = 0;

}
#endif
