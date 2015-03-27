// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_CONSENSUS_PARAMS_H

#include "arith_uint256.h"
#include "uint256.h"

namespace Consensus {
/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Used to check majorities for block version upgrade */
    int nMajorityEnforceBlockUpgrade;
    int nMajorityRejectBlockOutdated;
    int nMajorityWindow;
    /** Proof of work parameters */
    arith_uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    int64_t nMinDifficultySince;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }
    /** Auxpow parameters */
    int32_t nAuxpowChainId;
    int nAuxpowStartHeight;
    bool fStrictChainId;
    int nLegacyBlocksBefore; // -1 for "always allow"

    /**
     * Check whether or not minimum difficulty blocks are allowed
     * with the given time stamp.
     * @param nBlockTime Time of the block with minimum difficulty.
     * @return True if it is allowed to have minimum difficulty.
     */
    bool AllowMinDifficultyBlocks(int64_t nBlockTime) const
    {
        if (!fPowAllowMinDifficultyBlocks)
            return false;
        return nBlockTime > nMinDifficultySince;
    }

    /**
     * Check whether or not to allow legacy blocks at the given height.
     * @param nHeight Height of the block to check.
     * @return True if it is allowed to have a legacy version.
     */
    bool AllowLegacyBlocks(unsigned nHeight) const
    {
        if (nLegacyBlocksBefore < 0)
            return true;
        return static_cast<int> (nHeight) < nLegacyBlocksBefore;
    }
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_CONSENSUS_PARAMS_H