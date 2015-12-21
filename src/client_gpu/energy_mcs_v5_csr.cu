// sparse matrix in CSR format



float elhm = 0.0f;
int i = threadIdx.x;



int elhm2 = ncol[...];


__shared__ float elhm1s[1024];

//for (int i = threadIdx.x; i < npoint; i += blockDim.x) { // blockDim.x

if (i < npoint) {
  const int l = mcsm->idx_col[i];
  const float dx = lig_x2[l] - mcsm->x[i]; // do not use __LDG
  const float dy = lig_y2[l] - mcsm->y[i];
  const float dz = lig_z2[l] - mcsm->z[i];
  elhm1s[i] = dx * dx + dy * dy + dz * dz;
}


__syncthreads ();
if (i < nrow) {
  float elhm1 = 0.0f;
  for (int j = 0; j < mcsm->ncol[i]; ++j) {
    elhm1 += elhm1s[mcsm->row_ptr + j];
  }
  elhm += mcs_tcc[m] * sqrtf (elhm1 / (float) elhm2);
 }



BlockReduceSum_1_d_2 (elhm);
if (threadIdx.x == 0)
  e_s[7] = logf (elhm / mcs_nrow);


