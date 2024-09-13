#include <pmmintrin.h>
#include <xmmintrin.h>
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

#include <math.h>
#include <stdint.h>
#include "vec.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


available_isa _AVAILABLE_ISA;



/* get cpu intrinsics for different cpus */

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
available_isa get_cpu_intrinsics() {
  ruapu_init();
  available_isa get_isa;
  get_isa.mmx = ruapu_supports("mmx");
  get_isa.sse = ruapu_supports("sse");
  get_isa.sse2 = ruapu_supports("sse2");
  get_isa.sse3 = ruapu_supports("sse3");
  get_isa.ssse3 = ruapu_supports("ssse3");
  get_isa.sse41 = ruapu_supports("sse41");
  get_isa.sse42 = ruapu_supports("sse42");
  get_isa.sse4a = ruapu_supports("sse4a");
  get_isa.xop = ruapu_supports("xop");
  get_isa.avx = ruapu_supports("avx");
  get_isa.f16c = ruapu_supports("f16c");
  get_isa.fma = ruapu_supports("fma");
  get_isa.avx2 = ruapu_supports("avx2");
  get_isa.avx512f = ruapu_supports("avx512f");
  get_isa.avx512bw = ruapu_supports("avx512bw");
  get_isa.avx512cd = ruapu_supports("avx512cd");
  get_isa.avx512dq = ruapu_supports("avx512dq");
  get_isa.avx512vl = ruapu_supports("avx512vl");
  get_isa.avx512vnni = ruapu_supports("avx512vnni");
  get_isa.avx512bf16 = ruapu_supports("avx512bf16");
  get_isa.avx512ifma = ruapu_supports("avx512ifma");
  get_isa.avx512vbmi = ruapu_supports("avx512vbmi");
  get_isa.avx512vbmi2 = ruapu_supports("avx512vbmi2");
  get_isa.avx512fp16 = ruapu_supports("avx512fp16");
  get_isa.avx512er = ruapu_supports("avx512er");
  get_isa.avx5124fmaps = ruapu_supports("avx5124fmaps");
  get_isa.avx5124vnniw = ruapu_supports("avx5124vnniw");
  get_isa.avxvnni = ruapu_supports("avxvnni");
  get_isa.avxvniint8 = ruapu_supports("avxvniint8");
  get_isa.avxvnniint16 = ruapu_supports("avxvnniint16");
  get_isa.avxifma = ruapu_supports("avxifma");
  get_isa.amxfp16 = ruapu_supports("amxfp16");
  get_isa.amxbf16 = ruapu_supports("amxbf16");
  get_isa.amxint8 = ruapu_supports("amxint8");
  get_isa.amxtile = ruapu_supports("amxtile");
  get_isa.bmi1 = ruapu_supports("bmi1");
  get_isa.bmi2 = ruapu_supports("bmi2");
  get_isa.gfni = ruapu_supports("gfni");
  get_isa.aesni = ruapu_supports("aesni");
  get_isa.vaes = ruapu_supports("vaes");
  get_isa.sha = ruapu_supports("sha");
  get_isa.rdrand = ruapu_supports("rdrand");
  get_isa.rdseed = ruapu_supports("rdseed");
  get_isa.tsx = ruapu_supports("tsx");
  return get_isa;
}

void print_available_isa() {
    printf("hbvec available ISAs\n");
    printf("====================\n");
    available_isa isa = _AVAILABLE_ISA;
    printf("MMX: %d\n", isa.mmx);
    printf("SSE: %d\n", isa.sse);
    printf("SSE2: %d\n", isa.sse2);
    printf("SSE3: %d\n", isa.sse3);
    printf("SSSE3: %d\n", isa.ssse3);
    printf("SSE4.1: %d\n", isa.sse41);
    printf("SSE4.2: %d\n", isa.sse42);
    printf("SSE4a: %d\n", isa.sse4a);
    printf("XOP: %d\n", isa.xop);
    printf("AVX: %d\n", isa.avx);
    printf("F16C: %d\n", isa.f16c);
    printf("FMA: %d\n", isa.fma);
    printf("AVX2: %d\n", isa.avx2);
    printf("AVX-512F: %d\n", isa.avx512f);
    printf("AVX-512BW: %d\n", isa.avx512bw);
    printf("AVX-512CD: %d\n", isa.avx512cd);
    printf("AVX-512DQ: %d\n", isa.avx512dq);
    printf("AVX-512VL: %d\n", isa.avx512vl);
    printf("AVX-512VNNI: %d\n", isa.avx512vnni);
    printf("AVX-512BF16: %d\n", isa.avx512bf16);
    printf("AVX-512IFMA: %d\n", isa.avx512ifma);
    printf("AVX-512VBMI: %d\n", isa.avx512vbmi);
    printf("AVX-512VBMI2: %d\n", isa.avx512vbmi2);
    printf("AVX-512FP16: %d\n", isa.avx512fp16);
    printf("AVX-512ER: %d\n", isa.avx512er);
    printf("AVX-5124FMAPS: %d\n", isa.avx5124fmaps);
    printf("AVX-5124VNNIW: %d\n", isa.avx5124vnniw);
    printf("AVX-VNNI: %d\n", isa.avxvnni);
    printf("AVX-VNI-INT8: %d\n", isa.avxvniint8);
    printf("AVX-VNI-INT16: %d\n", isa.avxvnniint16);
    printf("AVX-IFMA: %d\n", isa.avxifma);
    printf("AMX-FP16: %d\n", isa.amxfp16);
    printf("AMX-BF16: %d\n", isa.amxbf16);
    printf("AMX-INT8: %d\n", isa.amxint8);
    printf("AMX-TILE: %d\n", isa.amxtile);
    printf("BMI1: %d\n", isa.bmi1);
    printf("BMI2: %d\n", isa.bmi2);
    printf("GFNI: %d\n", isa.gfni);
    printf("AES-NI: %d\n", isa.aesni);
    printf("VAES: %d\n", isa.vaes);
    printf("SHA: %d\n", isa.sha);
    printf("RDRAND: %d\n", isa.rdrand);
    printf("RDSEED: %d\n", isa.rdseed);
    printf("TSX: %d\n", isa.tsx);
    printf("====================\n");
}

/// TODO: write print for ARM devices
#elif __arch64__ || defined(_M_ARM64)
const available_isa get_cpu_intrinsics() {
  ruapu_init();
  available_isa get_arm_isa;
  get_arm_isa.neon = ruapu_supports("neon");
  get_arm_isa.vfpv4 = ruapu_supports("vfpv4");
  get_arm_isa.lse = ruapu_supports("lse");
  get_arm_isa.cpuid = ruapu_supports("cpuid");
  get_arm_isa.asimdrdm = ruapu_supports("asimdrdm");
  get_arm_isa.asimdhp = ruapu_supports("asimdhp");
  get_arm_isa.asimddp = ruapu_supports("asimddp");
  get_arm_isa.asimdfhm = ruapu_supports("asimdfhm");
  get_arm_isa.bf16 = ruapu_supports("bf16");
  get_arm_isa.i8mm = ruapu_supports("i8mm");
  get_arm_isa.frint = ruapu_supports("frint");
  get_arm_isa.jscvt = ruapu_supports("jscvt");
  get_arm_isa.fcma = ruapu_supports("fcma");
  get_arm_isa.mte = ruapu_supports("mte");
  get_arm_isa.mte2 = ruapu_supports("mte2");
  get_arm_isa.sve = ruapu_supports("sve");
  get_arm_isa.sve2 = ruapu_supports("sve2");
  get_arm_isa.svebf16 = ruapu_supports("svebf16");
  get_arm_isa.svei8mm = ruapu_supports("svei8mm");
  get_arm_isa.svef32mm = ruapu_supports("svef32mm");
  get_arm_isa.svef64mm = ruapu_supports("svef64mm");
  get_arm_isa.sme = ruapu_supports("sme");
  get_arm_isa.smef16f16 = ruapu_supports("smef16f16");
  get_arm_isa.smef64f64 = ruapu_supports("smef64f64");
  get_arm_isa.pmull = ruapu_supports("pmull");
  get_arm_isa.crc32 = ruapu_supports("crc32");
  get_arm_isa.aes = ruapu_supports("aes");
  get_arm_isa.sha1 = ruapu_supports("sha1");
  get_arm_isa.sha2 = ruapu_supports("sha2");
  get_arm_isa.sha3 = ruapu_supports("sha3");
  get_arm_isa.sha512 = ruapu_supports("sha512");
  get_arm_isa.sm3 = ruapu_supports("sm3");
  get_arm_isa.sm4 = ruapu_supports("sm4");
  get_arm_isa.svepmull = ruapu_supports("svepmull");
  get_arm_isa.svebitperm = ruapu_supports("svebitperm");
  get_arm_isa.svaes = ruapu_supports("svaes");
  get_arm_isa.svesha3 = ruapu_supports("svesha3");
  get_arm_isa.svesm4 = ruapu_supports("svesm4");
  get_arm_isa.amx = ruapu_supports("amx");
  return get_isa;
}

#elif __arm__ || defined(_M_ARM)
const available_isa get_cpu_intrinsics() {
  ruapu_init();
  available_isa get_mips_isa;
  get_mips_isa.msa = ruapu_supports("msa");
  get_mips_isa.mmi = ruapu_supports("mmi");
  get_mips_isa.sx = ruapu_supports("sx");
  get_mips_isa.asx = ruapu_supports("asx");
  get_mips_isa.msa2 = ruapu_supports("msa2");
  get_mips_isa.crypto = ruapu_supports("crypto");
  return get_isa;
}
#endif


// Get ISA debug function 
void debug_vec() {
  _AVAILABLE_ISA = get_cpu_intrinsics();
  print_available_isa();
}



#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <immintrin.h> 
#include <xmmintrin.h>
#include <pmmintrin.h> // SSE3


Vec3 vec3_new(float x, float y, float z) {
    Vec3 v;
    v.data = _mm_set_ps(0.0f, z ,y ,x);
    return v;
}

void vec3_print(Vec3 v) {
    printf("x: %f y: %f z: %f\n", v.data[0], v.data[1], v.data[2]);
}

Vec3 vec3_from_float(float f) {
  Vec3 v;
  v.data = _mm_set1_ps(f);
  return v;
}

Vec3 vec3_negate(Vec3 v) {
  Vec3 v_neg;
  __m128 neg = _mm_set1_ps(-1.0f);
  v_neg.data = _mm_mul_ps(v.data, neg);
  return v_neg;
}

Vec3 vec3_from_int(int i) {
  Vec3 v = {.data=_mm_set1_ps((float) i)};
  return v;
}

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 add = {.data=_mm_add_ps(v1.data, v2.data)}; 
  return add;
}

Vec3 vec3_div(Vec3 v1, Vec3 v2) {
  Vec3 div = {.data=_mm_div_ps(v1.data, v2.data)};
  return div;
}

Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 mul = {.data=_mm_mul_ps(v1.data, v2.data)};
  return mul;
}

Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 sub = {.data=_mm_sub_ps(v1.data, v2.data)};
  return sub;
}

// sometimes slower than plain C?!
float vec3_dot(Vec3 v1, Vec3 v2)
{
  __m128 mul = _mm_mul_ps(v1.data, v2.data);
  __m128 sum = _mm_hadd_ps(mul, mul);
  sum = _mm_hadd_ps(sum, sum);
  float result;
  _mm_store_ss(&result, sum);
  return result;
}

Vec3 vec3_unit(Vec3 v) {
  float len = vec3_length(v);
  return vec3_div(vec3_from_float(len), v);
}

float vec3_length(Vec3 v) {
  float dot_v = vec3_dot(v, v);
  return sqrtf(dot_v);
}

float vec3x(Vec3 v) {
  return v.data[0];
}

float vec3y(Vec3 v) {
  return v.data[1];
}

float vec3z(Vec3 v) {
  return v.data[2];
}

#endif



