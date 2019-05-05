// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xdc;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 10882;
        nRPCPort = 10883;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "03/06/2018 Madcoin Re-Launch";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1527996089, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1527996089;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 108741;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000c898f80438a996c99c35d363fa4871f82e852182708510da05b402986123"));
        assert(genesis.hashMerkleRoot == uint256("0xee78a0d998c272965e3c94a581504abb98b481de5ee1fdf1bf21a5427f4f3d35"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,203);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
		
        vSeeds.push_back(CDNSSeedData("seed1.madcoin.io", "seed1.madcoin.io"));
        vSeeds.push_back(CDNSSeedData("seed2.madcoin.io", "seed2.madcoin.io"));
      
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "Mq19GqFvajRrEdDHYRKGYjTsQfpV5jyipF";
        nLastPOWBlock = 24000;
        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xdc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("048deba713a5deaa1f4050f95143bc20c153f2acd731ee7ebc7f5f3887541a96ceb64271b9eab7ba2d2008c081498b0426f42922870ab7b773e2e82ca49fe542d3");
        nDefaultPort = 110882;
        nRPCPort = 110883;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 1518415703; 
        genesis.nNonce = 108741;
   
        assert(hashGenesisBlock == uint256("0x0000c898f80438a996c99c35d363fa4871f82e852182708510da05b402986123"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,75);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,203);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
