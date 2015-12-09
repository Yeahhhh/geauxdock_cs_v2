
// parse matrix
// no performance difference
// result is wrong



float elhm = 0.0f;
ty = threadIdx.x / bdx_mcs;
tx = threadIdx.x % bdx_mcs;


//Mcs *mcs_ = &complex->mcs[0];

// lhm loop, ~11
// unrolling outer loop does not help
//#pragma unroll 4
for (int j = 0; j < mcs_nrow; j += bdy_mcs) { // y loop
  float elhm1 = 0.0f;
  int elhm2 = 0;

  {
    const int m = j + ty;
    if (m < mcs_nrow) {
      // lig loop, ~30

      for (int i = tx; i < mcs_i2max[m]; i += bdx_mcs) { // x loop
        const int l = mcs[m].i2[i];
        const float dx = lig_x2[l] - mcs[m].x[i]; // do not use __LDG
        const float dy = lig_y2[l] - mcs[m].y[i];
        const float dz = lig_z2[l] - mcs[m].z[i];
        elhm1 += dx * dx + dy * dy + dz * dz;
        elhm2++;
      } // lig loop
    } // if (m < mcs_nrow)
  }

  BlockReduceSum_2D_2_d_2 (bdy_mcs, bdx_mcs, elhm1, elhm2);

  if (threadIdx.x < bdy_mcs) {
    const int m = j + threadIdx.x;
    if (m < mcs_nrow && elhm2 != 0)
      elhm += mcs_tcc[m] * sqrtf (elhm1 / (float) elhm2);
  }


 } // lhm loop

WarpReduceSum_1_d_2 (elhm);
if (threadIdx.x == 0)
  e_s[7] = logf (elhm / mcs_nrow);


