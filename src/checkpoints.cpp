// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
    (	0,      uint256("0x0000c898f80438a996c99c35d363fa4871f82e852182708510da05b402986123") )
    (	1,      uint256("0x000099e3d930cfea1dcbbcef8dfd3aa1bff982522c5b8f31c4b71cb6c60a0629") )
    (	2,      uint256("0x0000227b5eabd8ec067a0ce7f02bc6fa680ea0909ce328b380251f99e2d845ba") )
    (	3,      uint256("0x00007d1646e4a0c6fe6425270740ed488222f37994f98ec84e87c53cdf43b4a9") )	
    (	1000,   uint256("0xaaa2d803f5d1598ae7c3e106030c307e2119348824826ae5366d96d95cdee49f") )		
    (	19002,  uint256("0x00004efbee6ba2c02362255d73c3c2aed3d98e0d072f54001a1be2dfaecbc714") )
    (	50000,  uint256("0x49f189c331a60e959e472175fe5ad93b2cca6333eee30ccdca027b0aadaf5386") )	
    (	100000, uint256("0x4c5c1f7ba6bd0d0015377ea86b5aa3f44cda4cf342048f068ae95df3d728457a") )
    (	200000, uint256("0x9396adf6b16197933dbf792b44691656a11022cab0f4bced93e1c6f73616430b") )	
    (	250000, uint256("0xdb46ff9bd4b3f12d696bf0e150c944a414346b4f551f15b74165f8f956f07681") )		
    (	277501, uint256("0x2224098650d50e928a8f4cec5142351ef958ba8d7a55a92977c01c7e300d3647") )
    (	277777, uint256("0xf8d7b54c8a1edb4a89edb7558e699e127ee2a1e813cb568dc27f96fb31680eb7") )	
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
