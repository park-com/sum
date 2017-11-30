// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include <iostream>

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;


#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xdf;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x94;
        pchMessageStart[3] = 0x2c;
        vAlertPubKey = ParseHex("04e6480b31b13352355cd4072def967e52d928130cb33eded45d995251e627b3ecbe6637cfab15dc7017fb4de258daebd89ed3adfb0a2867c1d723d039c4392e4a");
        nDefaultPort = 13800;
        nRPCPort = 13801;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        /*
        nNonce is: 61618576
        Hash is: 000001768b08da66b92dede0ea8e7dcb97424f93d7ac2ac59e7a6cf98f20615a
        Block is: CBlock(hash=000001768b08da66b92dede0ea8e7dcb97424f93d7ac2ac59e7a6cf98f20615a, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614, nTime=1445353519, nBits=1e0fffff, nNonce=61618576, vtx=1, vchBlockSig=)
          Coinbase(hash=2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614, nTime=1445353519, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a2e3230204f63742032303135204120426c6f6f6d626572672052756e3f204472756d73204172652042656174696e67)
            CTxOut(empty)
          vMerkleTree:  2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614
        */
        const char* pszTimestamp = "2017/11/30 Politics: Trump Shares Inflammatory Anti-Muslim Videos, and Britain’s Leader Condemns Them";
        const uint32_t genesisTimestamp = 1512017192;
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, genesisTimestamp, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = genesisTimestamp;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();

        //*****************************************************************************

        // "mine" the nonce
        if(false) {
           std::cout << "search mainnet genesis blocks" << std::endl;
           for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
               if (genesis.nNonce % 1000000 == 0)
                   std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
               hashGenesisBlock = genesis.GetHash();
               unsigned char *b = hashGenesisBlock.end() - 3;
               if (memcmp(b, "\x01\x00\x00", 3) == 0) {
                   std::cout << "nNonce is: " << genesis.nNonce << std::endl;
                   std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                   std::cout << "Block is: " << genesis.ToString() << std::endl;
                   abort();
                   break;
               }
           }
        }
        //*****************************************************************************

        genesis.nNonce = 3973393;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000001eec72fb1361d84715e1ac838efa37e718cb905574b7049a45bbf548b3d"));
        assert(genesis.hashMerkleRoot == uint256("0x3c46987bbe1bb7baab4aa5962c55245a8590a0576fedc37f6c0263dfd1b94d4a"));

        vSeeds.push_back(CDNSSeedData("soompay.net", "14.63.226.166"));
        vSeeds.push_back(CDNSSeedData("172.30.1.1", "172.30.1.7"));
        //vSeeds.push_back(CDNSSeedData("seed3.sumcoin.io", "seed3.sumcoin.io"));
        //vSeeds.push_back(CDNSSeedData("seed4.sumcoin.io", "seed4.sumcoin.io"));
        //vSeeds.push_back(CDNSSeedData("seed5.sumcoin.io", "seed5.sumcoin.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63); // appears as "S" in base58
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = LAST_POW_BLOCK;
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
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("046f791cd0652c59aea3f327e5d4fd816e32db1c9816a53a81ebff59c67bbabba4ca12204d1ea83d6795993e0398a6b435df1ff91a4ba7f93c6869dbd775789e0b");
        nDefaultPort = 23800;
        nRPCPort = 23801;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();

        //****************************************************************************
        // "mine" the nonce
        if(false) {
           std::cout << "search testnet genesis blocks" << std::endl;
           for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
               if (genesis.nNonce % 1000000 == 0)
                   std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
               hashGenesisBlock = genesis.GetHash();
               unsigned char *b = hashGenesisBlock.end() - 2;
               if (memcmp(b, "\x00\x00", 2) == 0) {
                   std::cout << "testnet nNonce is: " << genesis.nNonce << std::endl;
                   std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                   std::cout << "Block is: " << genesis.ToString() << std::endl;
                   abort();
                   break;
               }
           }
       }
       //*****************************************************************************


        genesis.nNonce = 11136;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00005111d99bb9ee94a026c9e961787357d4bdf618347c480dd62cabc91b5ab7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();;

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//a
/*
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xea;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xde;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1512017192;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //=====================================================================
        
        std::cout << "RegTest Block is: " << genesis.ToString() << std::endl;
        
        //=====================================================================
        assert(hashGenesisBlock == uint256(""));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;
*/
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
        //case CChainParams::REGTEST:
        //    pCurrentParams = &regTestParams;
        //    break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
