// Auto-generated file. Do not edit!
//   Template: src/f32-vtanh/avx-expm1minus.c.in
//   Generator: tools/xngen
//
// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/microparams.h>
#include <xnnpack/vunary.h>

void xnn_f32_vtanh_ukernel__avx_expm1minus_rr1_p6h5_nr1_x80(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_tanh_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const __m256 vsign_mask = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.sign_mask);
  const __m256 vsat_cutoff = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.sat_cutoff);
  const __m256 vlog2e = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.log2e);
  const __m256 vmagic_bias = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.magic_bias);
  const __m256 vminus_ln2 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.minus_ln2);
  const __m256 vc6 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.c6);
  const __m256 vc5 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.c5);
  const __m256 vc4 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.c4);
  const __m256 vc3 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.c3);
  const __m256 vc2 = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.c2);
  const __m256 vtwo = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.two);
  const __m256 vminus_one = _mm256_load_ps(params->avx_expm1minus_rr1_p6h5.minus_one);

  for (; batch >= 80 * sizeof(float); batch -= 80 * sizeof(float)) {
    const __m256 vx0 = _mm256_loadu_ps(input);
    const __m256 vx1 = _mm256_loadu_ps(input + 8);
    const __m256 vx2 = _mm256_loadu_ps(input + 16);
    const __m256 vx3 = _mm256_loadu_ps(input + 24);
    const __m256 vx4 = _mm256_loadu_ps(input + 32);
    const __m256 vx5 = _mm256_loadu_ps(input + 40);
    const __m256 vx6 = _mm256_loadu_ps(input + 48);
    const __m256 vx7 = _mm256_loadu_ps(input + 56);
    const __m256 vx8 = _mm256_loadu_ps(input + 64);
    const __m256 vx9 = _mm256_loadu_ps(input + 72);
    input += 80;

    const __m256 vz0 = _mm256_or_ps(vx0, vsign_mask);
    const __m256 vz1 = _mm256_or_ps(vx1, vsign_mask);
    const __m256 vz2 = _mm256_or_ps(vx2, vsign_mask);
    const __m256 vz3 = _mm256_or_ps(vx3, vsign_mask);
    const __m256 vz4 = _mm256_or_ps(vx4, vsign_mask);
    const __m256 vz5 = _mm256_or_ps(vx5, vsign_mask);
    const __m256 vz6 = _mm256_or_ps(vx6, vsign_mask);
    const __m256 vz7 = _mm256_or_ps(vx7, vsign_mask);
    const __m256 vz8 = _mm256_or_ps(vx8, vsign_mask);
    const __m256 vz9 = _mm256_or_ps(vx9, vsign_mask);

    const __m256 vinvsignx0 = _mm256_xor_ps(vx0, vz0);
    const __m256 vm0 = _mm256_cmp_ps(vz0, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx1 = _mm256_xor_ps(vx1, vz1);
    const __m256 vm1 = _mm256_cmp_ps(vz1, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx2 = _mm256_xor_ps(vx2, vz2);
    const __m256 vm2 = _mm256_cmp_ps(vz2, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx3 = _mm256_xor_ps(vx3, vz3);
    const __m256 vm3 = _mm256_cmp_ps(vz3, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx4 = _mm256_xor_ps(vx4, vz4);
    const __m256 vm4 = _mm256_cmp_ps(vz4, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx5 = _mm256_xor_ps(vx5, vz5);
    const __m256 vm5 = _mm256_cmp_ps(vz5, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx6 = _mm256_xor_ps(vx6, vz6);
    const __m256 vm6 = _mm256_cmp_ps(vz6, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx7 = _mm256_xor_ps(vx7, vz7);
    const __m256 vm7 = _mm256_cmp_ps(vz7, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx8 = _mm256_xor_ps(vx8, vz8);
    const __m256 vm8 = _mm256_cmp_ps(vz8, vsat_cutoff, _CMP_LE_OS);
    const __m256 vinvsignx9 = _mm256_xor_ps(vx9, vz9);
    const __m256 vm9 = _mm256_cmp_ps(vz9, vsat_cutoff, _CMP_LE_OS);

    __m256 vn0 = _mm256_add_ps(_mm256_mul_ps(vz0, vlog2e), vmagic_bias);
    __m256 vn1 = _mm256_add_ps(_mm256_mul_ps(vz1, vlog2e), vmagic_bias);
    __m256 vn2 = _mm256_add_ps(_mm256_mul_ps(vz2, vlog2e), vmagic_bias);
    __m256 vn3 = _mm256_add_ps(_mm256_mul_ps(vz3, vlog2e), vmagic_bias);
    __m256 vn4 = _mm256_add_ps(_mm256_mul_ps(vz4, vlog2e), vmagic_bias);
    __m256 vn5 = _mm256_add_ps(_mm256_mul_ps(vz5, vlog2e), vmagic_bias);
    __m256 vn6 = _mm256_add_ps(_mm256_mul_ps(vz6, vlog2e), vmagic_bias);
    __m256 vn7 = _mm256_add_ps(_mm256_mul_ps(vz7, vlog2e), vmagic_bias);
    __m256 vn8 = _mm256_add_ps(_mm256_mul_ps(vz8, vlog2e), vmagic_bias);
    __m256 vn9 = _mm256_add_ps(_mm256_mul_ps(vz9, vlog2e), vmagic_bias);

    const __m128 vn0_hi = _mm256_extractf128_ps(vn0, 1);
    const __m128 vn1_hi = _mm256_extractf128_ps(vn1, 1);
    const __m128 vn2_hi = _mm256_extractf128_ps(vn2, 1);
    const __m128 vn3_hi = _mm256_extractf128_ps(vn3, 1);
    const __m128 vn4_hi = _mm256_extractf128_ps(vn4, 1);
    const __m128 vn5_hi = _mm256_extractf128_ps(vn5, 1);
    const __m128 vn6_hi = _mm256_extractf128_ps(vn6, 1);
    const __m128 vn7_hi = _mm256_extractf128_ps(vn7, 1);
    const __m128 vn8_hi = _mm256_extractf128_ps(vn8, 1);
    const __m128 vn9_hi = _mm256_extractf128_ps(vn9, 1);

    __m256 vs0 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn0)), 23)));
    const __m128 vs0_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn0_hi), 23));
    __m256 vs1 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn1)), 23)));
    const __m128 vs1_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn1_hi), 23));
    __m256 vs2 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn2)), 23)));
    const __m128 vs2_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn2_hi), 23));
    __m256 vs3 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn3)), 23)));
    const __m128 vs3_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn3_hi), 23));
    __m256 vs4 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn4)), 23)));
    const __m128 vs4_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn4_hi), 23));
    __m256 vs5 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn5)), 23)));
    const __m128 vs5_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn5_hi), 23));
    __m256 vs6 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn6)), 23)));
    const __m128 vs6_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn6_hi), 23));
    __m256 vs7 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn7)), 23)));
    const __m128 vs7_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn7_hi), 23));
    __m256 vs8 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn8)), 23)));
    const __m128 vs8_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn8_hi), 23));
    __m256 vs9 = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn9)), 23)));
    const __m128 vs9_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn9_hi), 23));

    vs0 = _mm256_insertf128_ps(vs0, vs0_hi, 1);
    vs1 = _mm256_insertf128_ps(vs1, vs1_hi, 1);
    vs2 = _mm256_insertf128_ps(vs2, vs2_hi, 1);
    vs3 = _mm256_insertf128_ps(vs3, vs3_hi, 1);
    vs4 = _mm256_insertf128_ps(vs4, vs4_hi, 1);
    vs5 = _mm256_insertf128_ps(vs5, vs5_hi, 1);
    vs6 = _mm256_insertf128_ps(vs6, vs6_hi, 1);
    vs7 = _mm256_insertf128_ps(vs7, vs7_hi, 1);
    vs8 = _mm256_insertf128_ps(vs8, vs8_hi, 1);
    vs9 = _mm256_insertf128_ps(vs9, vs9_hi, 1);

    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);
    vn2 = _mm256_sub_ps(vn2, vmagic_bias);
    vn3 = _mm256_sub_ps(vn3, vmagic_bias);
    vn4 = _mm256_sub_ps(vn4, vmagic_bias);
    vn5 = _mm256_sub_ps(vn5, vmagic_bias);
    vn6 = _mm256_sub_ps(vn6, vmagic_bias);
    vn7 = _mm256_sub_ps(vn7, vmagic_bias);
    vn8 = _mm256_sub_ps(vn8, vmagic_bias);
    vn9 = _mm256_sub_ps(vn9, vmagic_bias);

    const __m256 vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2), vz0);
    const __m256 vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2), vz1);
    const __m256 vt2 = _mm256_add_ps(_mm256_mul_ps(vn2, vminus_ln2), vz2);
    const __m256 vt3 = _mm256_add_ps(_mm256_mul_ps(vn3, vminus_ln2), vz3);
    const __m256 vt4 = _mm256_add_ps(_mm256_mul_ps(vn4, vminus_ln2), vz4);
    const __m256 vt5 = _mm256_add_ps(_mm256_mul_ps(vn5, vminus_ln2), vz5);
    const __m256 vt6 = _mm256_add_ps(_mm256_mul_ps(vn6, vminus_ln2), vz6);
    const __m256 vt7 = _mm256_add_ps(_mm256_mul_ps(vn7, vminus_ln2), vz7);
    const __m256 vt8 = _mm256_add_ps(_mm256_mul_ps(vn8, vminus_ln2), vz8);
    const __m256 vt9 = _mm256_add_ps(_mm256_mul_ps(vn9, vminus_ln2), vz9);

    __m256 vp0 = _mm256_add_ps(_mm256_mul_ps(vc6, vt0), vc5);
    __m256 vp1 = _mm256_add_ps(_mm256_mul_ps(vc6, vt1), vc5);
    __m256 vp2 = _mm256_add_ps(_mm256_mul_ps(vc6, vt2), vc5);
    __m256 vp3 = _mm256_add_ps(_mm256_mul_ps(vc6, vt3), vc5);
    __m256 vp4 = _mm256_add_ps(_mm256_mul_ps(vc6, vt4), vc5);
    __m256 vp5 = _mm256_add_ps(_mm256_mul_ps(vc6, vt5), vc5);
    __m256 vp6 = _mm256_add_ps(_mm256_mul_ps(vc6, vt6), vc5);
    __m256 vp7 = _mm256_add_ps(_mm256_mul_ps(vc6, vt7), vc5);
    __m256 vp8 = _mm256_add_ps(_mm256_mul_ps(vc6, vt8), vc5);
    __m256 vp9 = _mm256_add_ps(_mm256_mul_ps(vc6, vt9), vc5);
    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc4);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc4);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc4);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc4);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc4);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc4);
    vp6 = _mm256_add_ps(_mm256_mul_ps(vp6, vt6), vc4);
    vp7 = _mm256_add_ps(_mm256_mul_ps(vp7, vt7), vc4);
    vp8 = _mm256_add_ps(_mm256_mul_ps(vp8, vt8), vc4);
    vp9 = _mm256_add_ps(_mm256_mul_ps(vp9, vt9), vc4);
    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc3);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc3);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc3);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc3);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc3);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc3);
    vp6 = _mm256_add_ps(_mm256_mul_ps(vp6, vt6), vc3);
    vp7 = _mm256_add_ps(_mm256_mul_ps(vp7, vt7), vc3);
    vp8 = _mm256_add_ps(_mm256_mul_ps(vp8, vt8), vc3);
    vp9 = _mm256_add_ps(_mm256_mul_ps(vp9, vt9), vc3);
    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc2);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc2);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc2);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc2);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc2);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc2);
    vp6 = _mm256_add_ps(_mm256_mul_ps(vp6, vt6), vc2);
    vp7 = _mm256_add_ps(_mm256_mul_ps(vp7, vt7), vc2);
    vp8 = _mm256_add_ps(_mm256_mul_ps(vp8, vt8), vc2);
    vp9 = _mm256_add_ps(_mm256_mul_ps(vp9, vt9), vc2);
    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vtwo);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vtwo);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vtwo);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vtwo);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vtwo);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vtwo);
    vp6 = _mm256_add_ps(_mm256_mul_ps(vp6, vt6), vtwo);
    vp7 = _mm256_add_ps(_mm256_mul_ps(vp7, vt7), vtwo);
    vp8 = _mm256_add_ps(_mm256_mul_ps(vp8, vt8), vtwo);
    vp9 = _mm256_add_ps(_mm256_mul_ps(vp9, vt9), vtwo);

    const __m256 vts0 = _mm256_mul_ps(vt0, vs0);
    const __m256 vsmo0 = _mm256_add_ps(vs0, vminus_one);
    const __m256 vts1 = _mm256_mul_ps(vt1, vs1);
    const __m256 vsmo1 = _mm256_add_ps(vs1, vminus_one);
    const __m256 vts2 = _mm256_mul_ps(vt2, vs2);
    const __m256 vsmo2 = _mm256_add_ps(vs2, vminus_one);
    const __m256 vts3 = _mm256_mul_ps(vt3, vs3);
    const __m256 vsmo3 = _mm256_add_ps(vs3, vminus_one);
    const __m256 vts4 = _mm256_mul_ps(vt4, vs4);
    const __m256 vsmo4 = _mm256_add_ps(vs4, vminus_one);
    const __m256 vts5 = _mm256_mul_ps(vt5, vs5);
    const __m256 vsmo5 = _mm256_add_ps(vs5, vminus_one);
    const __m256 vts6 = _mm256_mul_ps(vt6, vs6);
    const __m256 vsmo6 = _mm256_add_ps(vs6, vminus_one);
    const __m256 vts7 = _mm256_mul_ps(vt7, vs7);
    const __m256 vsmo7 = _mm256_add_ps(vs7, vminus_one);
    const __m256 vts8 = _mm256_mul_ps(vt8, vs8);
    const __m256 vsmo8 = _mm256_add_ps(vs8, vminus_one);
    const __m256 vts9 = _mm256_mul_ps(vt9, vs9);
    const __m256 vsmo9 = _mm256_add_ps(vs9, vminus_one);

    const __m256 vemo0 = _mm256_add_ps(_mm256_mul_ps(vp0, vts0), vsmo0);
    const __m256 vemo1 = _mm256_add_ps(_mm256_mul_ps(vp1, vts1), vsmo1);
    const __m256 vemo2 = _mm256_add_ps(_mm256_mul_ps(vp2, vts2), vsmo2);
    const __m256 vemo3 = _mm256_add_ps(_mm256_mul_ps(vp3, vts3), vsmo3);
    const __m256 vemo4 = _mm256_add_ps(_mm256_mul_ps(vp4, vts4), vsmo4);
    const __m256 vemo5 = _mm256_add_ps(_mm256_mul_ps(vp5, vts5), vsmo5);
    const __m256 vemo6 = _mm256_add_ps(_mm256_mul_ps(vp6, vts6), vsmo6);
    const __m256 vemo7 = _mm256_add_ps(_mm256_mul_ps(vp7, vts7), vsmo7);
    const __m256 vemo8 = _mm256_add_ps(_mm256_mul_ps(vp8, vts8), vsmo8);
    const __m256 vemo9 = _mm256_add_ps(_mm256_mul_ps(vp9, vts9), vsmo9);

    const __m256 vepo0 = _mm256_add_ps(vemo0, vtwo);
    const __m256 vepo1 = _mm256_add_ps(vemo1, vtwo);
    const __m256 vepo2 = _mm256_add_ps(vemo2, vtwo);
    const __m256 vepo3 = _mm256_add_ps(vemo3, vtwo);
    const __m256 vepo4 = _mm256_add_ps(vemo4, vtwo);
    const __m256 vepo5 = _mm256_add_ps(vemo5, vtwo);
    const __m256 vepo6 = _mm256_add_ps(vemo6, vtwo);
    const __m256 vepo7 = _mm256_add_ps(vemo7, vtwo);
    const __m256 vepo8 = _mm256_add_ps(vemo8, vtwo);
    const __m256 vepo9 = _mm256_add_ps(vemo9, vtwo);
    __m256 vrepo0 = _mm256_rcp_ps(vepo0);
    __m256 vrepo1 = _mm256_rcp_ps(vepo1);
    __m256 vrepo2 = _mm256_rcp_ps(vepo2);
    __m256 vrepo3 = _mm256_rcp_ps(vepo3);
    __m256 vrepo4 = _mm256_rcp_ps(vepo4);
    __m256 vrepo5 = _mm256_rcp_ps(vepo5);
    __m256 vrepo6 = _mm256_rcp_ps(vepo6);
    __m256 vrepo7 = _mm256_rcp_ps(vepo7);
    __m256 vrepo8 = _mm256_rcp_ps(vepo8);
    __m256 vrepo9 = _mm256_rcp_ps(vepo9);
    vrepo0 = _mm256_mul_ps(vrepo0, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo0, vepo0)));
    vrepo1 = _mm256_mul_ps(vrepo1, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo1, vepo1)));
    vrepo2 = _mm256_mul_ps(vrepo2, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo2, vepo2)));
    vrepo3 = _mm256_mul_ps(vrepo3, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo3, vepo3)));
    vrepo4 = _mm256_mul_ps(vrepo4, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo4, vepo4)));
    vrepo5 = _mm256_mul_ps(vrepo5, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo5, vepo5)));
    vrepo6 = _mm256_mul_ps(vrepo6, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo6, vepo6)));
    vrepo7 = _mm256_mul_ps(vrepo7, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo7, vepo7)));
    vrepo8 = _mm256_mul_ps(vrepo8, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo8, vepo8)));
    vrepo9 = _mm256_mul_ps(vrepo9, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo9, vepo9)));

    __m256 vy0 = _mm256_mul_ps(vemo0, vrepo0);
    __m256 vy1 = _mm256_mul_ps(vemo1, vrepo1);
    __m256 vy2 = _mm256_mul_ps(vemo2, vrepo2);
    __m256 vy3 = _mm256_mul_ps(vemo3, vrepo3);
    __m256 vy4 = _mm256_mul_ps(vemo4, vrepo4);
    __m256 vy5 = _mm256_mul_ps(vemo5, vrepo5);
    __m256 vy6 = _mm256_mul_ps(vemo6, vrepo6);
    __m256 vy7 = _mm256_mul_ps(vemo7, vrepo7);
    __m256 vy8 = _mm256_mul_ps(vemo8, vrepo8);
    __m256 vy9 = _mm256_mul_ps(vemo9, vrepo9);


    vy0 = _mm256_blendv_ps(vy0, vminus_one, vm0);
    vy1 = _mm256_blendv_ps(vy1, vminus_one, vm1);
    vy2 = _mm256_blendv_ps(vy2, vminus_one, vm2);
    vy3 = _mm256_blendv_ps(vy3, vminus_one, vm3);
    vy4 = _mm256_blendv_ps(vy4, vminus_one, vm4);
    vy5 = _mm256_blendv_ps(vy5, vminus_one, vm5);
    vy6 = _mm256_blendv_ps(vy6, vminus_one, vm6);
    vy7 = _mm256_blendv_ps(vy7, vminus_one, vm7);
    vy8 = _mm256_blendv_ps(vy8, vminus_one, vm8);
    vy9 = _mm256_blendv_ps(vy9, vminus_one, vm9);
    vy0 = _mm256_xor_ps(vy0, vinvsignx0);
    vy1 = _mm256_xor_ps(vy1, vinvsignx1);
    vy2 = _mm256_xor_ps(vy2, vinvsignx2);
    vy3 = _mm256_xor_ps(vy3, vinvsignx3);
    vy4 = _mm256_xor_ps(vy4, vinvsignx4);
    vy5 = _mm256_xor_ps(vy5, vinvsignx5);
    vy6 = _mm256_xor_ps(vy6, vinvsignx6);
    vy7 = _mm256_xor_ps(vy7, vinvsignx7);
    vy8 = _mm256_xor_ps(vy8, vinvsignx8);
    vy9 = _mm256_xor_ps(vy9, vinvsignx9);

    _mm256_storeu_ps(output, vy0);
    _mm256_storeu_ps(output + 8, vy1);
    _mm256_storeu_ps(output + 16, vy2);
    _mm256_storeu_ps(output + 24, vy3);
    _mm256_storeu_ps(output + 32, vy4);
    _mm256_storeu_ps(output + 40, vy5);
    _mm256_storeu_ps(output + 48, vy6);
    _mm256_storeu_ps(output + 56, vy7);
    _mm256_storeu_ps(output + 64, vy8);
    _mm256_storeu_ps(output + 72, vy9);
    output += 80;
  }
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const __m256 vx = _mm256_loadu_ps(input);
    input += 8;

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    const __m256 vinvsignx = _mm256_xor_ps(vx, vz);
    const __m256 vm = _mm256_cmp_ps(vz, vsat_cutoff, _CMP_LE_OS);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);

    const __m128 vn_hi = _mm256_extractf128_ps(vn, 1);
    __m256 vs = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn)), 23)));
    const __m128 vs_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn_hi), 23));
    vs = _mm256_insertf128_ps(vs, vs_hi, 1);

    vn = _mm256_sub_ps(vn, vmagic_bias);

    const __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2), vz);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc6, vt), vc5);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vtwo);

    const __m256 vts = _mm256_mul_ps(vt, vs);
    const __m256 vsmo = _mm256_add_ps(vs, vminus_one);
    const __m256 vemo = _mm256_add_ps(_mm256_mul_ps(vp, vts), vsmo);

    const __m256 vepo = _mm256_add_ps(vemo, vtwo);
    __m256 vrepo = _mm256_rcp_ps(vepo);
    vrepo = _mm256_mul_ps(vrepo, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo, vepo)));

    __m256 vy = _mm256_mul_ps(vemo, vrepo);


    vy = _mm256_blendv_ps(vy, vminus_one, vm);
    vy = _mm256_xor_ps(vy, vinvsignx);

    _mm256_storeu_ps(output, vy);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &params->avx_expm1minus_rr1_p6h5.mask_table[7] - batch));

    const __m256 vx = _mm256_maskload_ps(input, vmask);

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    const __m256 vinvsignx = _mm256_xor_ps(vx, vz);
    const __m256 vm = _mm256_cmp_ps(vz, vsat_cutoff, _CMP_LE_OS);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);

    const __m128 vn_hi = _mm256_extractf128_ps(vn, 1);
    __m256 vs = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn)), 23)));
    const __m128 vs_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn_hi), 23));
    vs = _mm256_insertf128_ps(vs, vs_hi, 1);

    vn = _mm256_sub_ps(vn, vmagic_bias);

    const __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2), vz);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc6, vt), vc5);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vtwo);

    const __m256 vts = _mm256_mul_ps(vt, vs);
    const __m256 vsmo = _mm256_add_ps(vs, vminus_one);
    const __m256 vemo = _mm256_add_ps(_mm256_mul_ps(vp, vts), vsmo);

    const __m256 vepo = _mm256_add_ps(vemo, vtwo);
    __m256 vrepo = _mm256_rcp_ps(vepo);
    vrepo = _mm256_mul_ps(vrepo, _mm256_sub_ps(vtwo, _mm256_mul_ps(vrepo, vepo)));

    __m256 vy = _mm256_mul_ps(vemo, vrepo);


    vy = _mm256_blendv_ps(vy, vminus_one, vm);
    vy = _mm256_xor_ps(vy, vinvsignx);

    __m128 vy_lo = _mm256_castps256_ps128(vy);
    if (batch & (4 * sizeof(float))) {
      _mm_storeu_ps(output, vy_lo);
      vy_lo = _mm256_extractf128_ps(vy, 1);
      output += 4;
    }
    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vy_lo);
      vy_lo = _mm_movehl_ps(vy_lo, vy_lo);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vy_lo);
    }
  }
}
