/*
 * This uses veriations of the clhash algorithm for Veros Coin, licensed
 * with the Apache-2.0 open source license.
 * 
 * Copyright (c) 2018 Michael Toutonghi
 * Distributed under the Apache 2.0 software license, available in the original form for clhash
 * here: https://github.com/lemire/clhash/commit/934da700a2a54d8202929a826e2763831bd43cf7#diff-9879d6db96fd29134fc802214163b95a
 * 
 * CLHash is a very fast hashing function that uses the
 * carry-less multiplication and SSE instructions.
 *
 * Original CLHash code (C) 2017, 2018 Daniel Lemire and Owen Kaser
 * Faster 64-bit universal hashing
 * using carry-less multiplications, Journal of Cryptographic Engineering (to appear)
 *
 * Best used on recent x64 processors (Haswell or better).
 *
 **/

#ifndef INCLUDE_VEROS_CLHASH_H
#define INCLUDE_VEROS_CLHASH_H


//#include <intrin.h>

#ifndef _WIN32
#include <cpuid.h>
#else
#include <intrin.h>
#endif // !WIN32


#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
//#include <boost/thread.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)

	typedef unsigned char u_char;

typedef unsigned char u_char;

#endif
#include "haraka.h"
#include "haraka_portable.h"
enum {
    // Veros Key size must include the equivalent size of a Haraka key
    // after the first part.
    // Any excess over a power of 2 will not get mutated, and any excess over
    // power of 2 + Haraka sized key will not be used
	VEROSKEYSIZE = 1024 * 8 + (40 * 16),
	VEROSHHASH_SOLUTION_VERSION = 1
};



extern int __cpuverosoptimized;

inline bool IsCPUVerosOptimized()
{

#ifndef _WIN32
	unsigned int eax, ebx, ecx, edx;

	if (!__get_cpuid(1, &eax, &ebx, &ecx, &edx))
	{
		return false;
	}
	return ((ecx & (bit_AVX | bit_AES)) == (bit_AVX | bit_AES));
#else

	// https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/cpuid.h
#define bit_AVX		(1 << 28)
#define bit_AES		(1 << 25)
	// https://insufficientlycomplicated.wordpress.com/2011/11/07/detecting-intel-advanced-vector-extensions-avx-in-visual-studio/
	// bool cpuAVXSuport = cpuInfo[2] & (1 << 28) || false;

	int cpuInfo[4];
	__cpuid(cpuInfo, 1);
	return ((cpuInfo[2] & (bit_AVX | bit_AES)) == (bit_AVX | bit_AES));

#endif


    if (__cpuverosoptimized & 0x80)
    {
#ifdef _WIN32
        #define bit_AVX		(1 << 28)
        #define bit_AES		(1 << 25)
        #define bit_PCLMUL  (1 << 1)
        // https://insufficientlycomplicated.wordpress.com/2011/11/07/detecting-intel-advanced-vector-extensions-avx-in-visual-studio/
        // bool cpuAVXSuport = cpuInfo[2] & (1 << 28) || false;

        int cpuInfo[4];
		__cpuid(cpuInfo, 1);
        __cpuverosoptimized = ((cpuInfo[2] & (bit_AVX | bit_AES | bit_PCLMUL)) == (bit_AVX | bit_AES | bit_PCLMUL));
#else
        unsigned int eax,ebx,ecx,edx;

        if (!__get_cpuid(1,&eax,&ebx,&ecx,&edx))
        {
            __cpuverosoptimized = false;
        }
        else
        {
            __cpuverosoptimized = ((ecx & (bit_AVX | bit_AES | bit_PCLMUL)) == (bit_AVX | bit_AES | bit_PCLMUL));
        }
#endif //WIN32
    }
    return __cpuverosoptimized;

};

inline void ForceCPUVerosOptimized(bool trueorfalse)
{
    __cpuverosoptimized = trueorfalse;
};

uint64_t verosclhashv2_1(void * random, const unsigned char buf[64], uint64_t keyMask, uint32_t *fixrand, uint32_t *fixrandex,
	u128 *g_prand, u128 *g_prandex);
uint64_t verosclhashv2_2(void * random, const unsigned char buf[64], uint64_t keyMask, uint32_t *fixrand, uint32_t *fixrandex,
	u128 *g_prand, u128 *g_prandex);
uint64_t verosclhash_port(void * random, const unsigned char buf[64], uint64_t keyMask, uint32_t *fixrand, uint32_t *fixrandex,
	u128 *g_prand, u128 *g_prandex);

void *alloc_aligned_buffer(uint64_t bufSize);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus

#include <vector>
#include <string>

// special high speed hasher for VerosHash 2.0

#endif // #ifdef __cplusplus

#endif // INCLUDE_VEROS_CLHASH_H
