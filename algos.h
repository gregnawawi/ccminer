#ifndef ALGOS_H
#define ALGOS_H

#include <string.h>
#include "compat.h"

enum sha_algos {
	ALGO_BLAKECOIN = 0,
	ALGO_BLAKE,
	ALGO_BLAKE2S,
	ALGO_ALLIUM,
	ALGO_BMW,
	ALGO_BASTION,
	ALGO_C11,
	ALGO_CRYPTOLIGHT,
	ALGO_CRYPTONIGHT,
	ALGO_DEEP,
	ALGO_DECRED,
	ALGO_DMD_GR,
	ALGO_EQUIHASH,
	ALGO_FRESH,
	ALGO_FUGUE256,		/* Fugue256 */
	ALGO_GROESTL,
	ALGO_HEAVY,		/* Heavycoin hash */
	ALGO_HMQ1725,
	ALGO_HSR,
	ALGO_KECCAK,
	ALGO_KECCAKC,		/* refreshed Keccak with pool factor 256 */
	ALGO_JACKPOT,
	ALGO_JHA,
	ALGO_LBRY,
	ALGO_LUFFA,
	ALGO_LYRA2,
	ALGO_LYRA2v2,
	ALGO_LYRA2Z,
	ALGO_MJOLLNIR,		/* Hefty hash */
	ALGO_MYR_GR,
	ALGO_NEOSCRYPT,
	ALGO_NIST5,
	ALGO_PENTABLAKE,
	ALGO_PHI,
	ALGO_PHI2,
	ALGO_POLYTIMOS,
	ALGO_QUARK,
	ALGO_QUBIT,
	ALGO_SCRYPT,
	ALGO_SCRYPT_JANE,
	ALGO_SHA256D,
	ALGO_SHA256T,
	ALGO_SIA,
	ALGO_SIB,
	ALGO_SKEIN,
	ALGO_SKEIN2,
	ALGO_SKUNK,
	ALGO_SONOA,
	ALGO_S3,
	ALGO_TIMETRAVEL,
	ALGO_TRIBUS,
	ALGO_BITCORE,
	ALGO_X11EVO,
	ALGO_X11,
	ALGO_X12,
	ALGO_X13,
	ALGO_X14,
	ALGO_X15,
	ALGO_X16R,
	ALGO_X16S,
	ALGO_X17,
	ALGO_VANILLA,
	ALGO_VELTOR,
	ALGO_WHIRLCOIN,
	ALGO_WHIRLPOOL,
	ALGO_WHIRLPOOLX,
	ALGO_WILDKECCAK,
	ALGO_ZR5,
	ALGO_MONERO,
	ALGO_GRAFT,
	ALGO_STELLITE,
	ALGO_AUTO,
	ALGO_COUNT
};

extern volatile enum sha_algos opt_algo;

static const char *algo_names[] = {
	"veros"
	""
};

// string to int/enum
static inline int algo_to_int(char* arg)
{
	int i;

	for (i = 0; i < ALGO_COUNT; i++) {
		if (algo_names[i] && !strcasecmp(arg, algo_names[i])) {
			return i;
		}
	}

	return i;
}

static inline int get_cryptonight_algo(int fork)
{
	int algo = ALGO_COUNT;

	switch (fork) {
		case 8:
			algo = ALGO_GRAFT;
			break;

		case 7:
			algo = ALGO_MONERO;
			break;

		case 3:
			algo = ALGO_STELLITE;
			break;

		default:
			algo = ALGO_CRYPTONIGHT;
			break;
	}

	return algo;
}

#endif
