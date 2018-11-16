
#if 1
const float mcpersec =
ch->mcpara.steps_total * ch->size.n_rep / e[4].Span();
printf ("mc kernel time\t\t\t%8.3f s\n", e[4].Span());
printf ("time per MC sweep per replica\t%8.3f * 1e-6 s\n", 1e6 / mcpersec);
printf ("MC sweeps per second\t\t%8.3f\n", mcpersec);
printf ("speedup over 1023.5\t\t%8.3f X\n", mcpersec / 1023.5);
/*
putchar ('\n');
printf ("kernel:\n");
printf ("kernel wall time\t\t%8.3f\n", e[10].Span ());
printf ("alloc host\t\t\t%8.3f\n", e[0].Span ());
printf ("H2Dcpy\t\t\t\t%8.3f\n", e[1].Span ());
printf ("init 1\t\t\t\t%8.3f\n", e[2].Span ());
printf ("init 2\t\t\t\t%8.3f\n", e[3].Span ());
printf ("monte carlo\t\t\t%8.3f\n", e[4].Span ());
printf ("\n");
*/
#endif





#if 0
printf ("Benchmark,\t\t");
printf ("%s,", ch->lig_file);
printf ("%s,", ch->prt_file);
printf ("%d,", ch->mcpara.steps_total);
printf ("%d,", ch->mcpara.steps_total);
printf ("%d,", ch->mcpara.steps_per_dump);
printf ("%d,", ch->size.n_lig);
printf ("%d,", ch->size.n_prt);
printf ("%d,", ch->size.n_tmp);
printf ("%d,", ch->size.n_rep);
printf ("%d,", ch->size.lig_natom);
printf ("%d,", ch->size.prt_npoint);
printf ("%d,", ch->size.kde_npoint);
printf ("%d,", ch->size.mcs_nrow);
printf ("%.3f", e[4].Span()); // seconds
printf ("\n");
#endif





#if IS_PAPI == 1
printf ("Benchmark_papi,\t\t");
printf ("%s,", ch->lig_file);
printf ("%s,", ch->prt_file);
printf ("%d,", ch->mcpara.steps_total);
printf ("%d,", ch->mcpara.steps_per_dump);
printf ("%d,", ch->size.n_lig);
printf ("%d,", ch->size.n_prt);
printf ("%d,", ch->size.n_tmp);
printf ("%d,", ch->size.n_rep);
printf ("%d,", ch->size.lig_natom);
printf ("%d,", ch->size.prt_npoint);
printf ("%d,", ch->size.kde_npoint);
printf ("%d,", ch->size.mcs_nrow);
printf ("%.3f,", e[4].Span()); // seconds
for (int i = 0; i < m0.papi_event_n; ++i)
printf ("%.3f,", (float) m0.papi_event_val[i] / 1000000.0f);
printf ("\n");
#endif


