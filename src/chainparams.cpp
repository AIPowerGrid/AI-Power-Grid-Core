// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2021 The Raven Core developers
// Copyright (c) 2022-2023 AIPG developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Bloomberg 10/30/23 Biden Signs Sweeping Order Regulating Artificial Intelligence";
    const CScript genesisOutputScript = CScript() << ParseHex("04f529c0007624ffa8c565cf9fbbcf406701b2a279a3ef06232069429b3c8c9fe8cac1b4062b418cdd4e4e2ea72ddbdf935a8f30fc3ca04d1844f6963332df8581") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
}


/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 100000;  // changed after community vote to 100000 for accelerated halvening in 2024
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled 	= true;
        consensus.powLimit 		= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit 	= uint256S("0000000fffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
	    consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (HIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1653004800; // Friday, 20 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1653264000; // Monday, 23 May 2022 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;
	
	    consensus.BIP34LockedIn = 6048; // Locked_in at height 6048


        // The best chain should have at least this much work
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // New blockchain, no work done yet

        // By default assume that the signatures in ancestors of this block are valid. Block# 0
        consensus.defaultAssumeValid = uint256S("0x000000fe8c99a7aacc5aff074278a8378e625c0d02e4894db8f09bab185f4eb6"); // Genesis block

        pchMessageStart[0] = 0x41; // A
        pchMessageStart[1] = 0x49; // I
        pchMessageStart[2] = 0x34; // 4
        pchMessageStart[3] = 0x45; // E
        nDefaultPort = 8865;
        nPruneAfterHeight = 100000;
		
	    uint32_t nGenesisTime = 1688352006; // October 30, 2023, at 00:00:00 UTC	

	    genesis = CreateGenesisBlock(nGenesisTime, 22801899, 0x1e00ffff, 4, 5000 * COIN);        
    
        consensus.hashGenesisBlock = genesis.GetX16RHash(); // Get the x16r hash	
        
        // debug
        // printf("Debug: Genesis block hash: %s\n", consensus.hashGenesisBlock.ToString().c_str()); // Print for debug

        assert(consensus.hashGenesisBlock == uint256S("0x000000fe8c99a7aacc5aff074278a8378e625c0d02e4894db8f09bab185f4eb6"));
        assert(genesis.hashMerkleRoot == uint256S("e04a78dcf0ad3d5c7f1ac4460c4c04bc333e677d52371b7453b5b09603b41d54"));

        // vSeeds.emplace_back("tobenamed.com", false); // New dnsseeder
        vSeeds.emplace_back("us-seed1.aipowergrid.io", false); 
        vSeeds.emplace_back("us-seed2.aipowergrid.io", false); 
        vSeeds.emplace_back("us-seed3.aipowergrid.io", false);
        vSeeds.emplace_back("jp-seed1.aipowergrid.io", false); 
        vSeeds.emplace_back("au-seed1.aipowergrid.io", false);
        vSeeds.emplace_back("eu-seed1.aipowergrid.io", false);
        vSeeds.emplace_back("in-seed1.aipowergrid.io", false);



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);  // 'A' prefix
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);  // 'A' prefix
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        // AIPG BIP44 cointype in mainnet is '2686'
        nExtCoinType = 2686;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

		checkpointData = (CCheckpointData) {
            {
            	{
            	    {0, uint256S("0x000000fe8c99a7aacc5aff074278a8378e625c0d02e4894db8f09bab185f4eb6")},
                    {1000, uint256S("0x0000000896d9bff8ff18634e4a6371c746f910a188b7e27912a7f99bf46b7619")},
                    {5000, uint256S("0x000000000001de284a9c92a2e1ac6e27318eda12d40af4cde7cef76d1938383a")},
                    {10000, uint256S("0x00000000000012a7e53f095089df469faee1c88374d34faff345cf63344e9f44")},
                    {17500, uint256S("0x0000000000003b97704bb221c3d891ba0a180170a883bcf673a6027ec7d3f256")},
                    {25000, uint256S("0x000000000000244c4b9141badcc9ea3793a616fde2f71117f691f5594497f601")},
                    {32500, uint256S("0x00000000000044067d88c8e8d31ba7484f42a54ce69b8dd96e1aaf0c18741bf1")},
                    {40000, uint256S("0x0000000000004d631d9a7e09ebd68dda413a0a38c4c7f9f0ec5d89016632aaf1")},
                    {50000, uint256S("0x0000000000001db9dc268fc6ad716468f8431031af3eac52f0f2dd877247bc01")},
                    {62500, uint256S("0x0000000000004b6d4a5ea2ff4cd8466098ad767b4a117b0cd32435afe8be6314")},
            	}
            }
        };


        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Points chain from rpc: getchaintxstats 50000
        	1705864305, // * UNIX timestamp of last known number of transactions
            103435,      // * total number of transactions between genesis and that timestamp
            0.03 // * estimated number of transactions per second after that timestamp
        };

        /** AIPG Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 50 * COIN;
        nReissueAssetBurnAmount = 10 * COIN;
        nIssueSubAssetBurnAmount = 10 * COIN;
        nIssueUniqueAssetBurnAmount = 0.5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 10 * COIN;
        nIssueQualifierAssetBurnAmount = 100 * COIN;
        nIssueSubQualifierAssetBurnAmount = 10 * COIN;
        nIssueRestrictedAssetBurnAmount = 150 * COIN;
        nAddNullQualifierTagBurnAmount = 0.01 * COIN;
		
        // 5% of 500 AIPG to operations wallet
	    nCommunityAutonomousAmount = 5;
        // Operations wallet placeholder

        // Burn Addresses
	    strIssueAssetBurnAddress = "AIissueAssetXXXXXXXXXXXXXXXXXhhZGt";
        strReissueAssetBurnAddress = "AIReissueAssetXXXXXXXXXXXXXXVEFAWu";
        strIssueSubAssetBurnAddress = "AIissueSubAssetXXXXXXXXXXXXXWcwhwL";
        strIssueUniqueAssetBurnAddress = "AIissueUniqueAssetXXXXXXXXXXWEAe58";
        strIssueMsgChannelAssetBurnAddress = "AIissueMsgChanneLAssetXXXXXXSjHvAY";
        strIssueQualifierAssetBurnAddress = "AIissueQuaLifierXXXXXXXXXXXXUgEDbC";
        strIssueSubQualifierAssetBurnAddress = "AIissueSubQuaLifierXXXXXXXXXVTzvv5";
        strIssueRestrictedAssetBurnAddress = "AIissueRestrictedXXXXXXXXXXXXzJZ1q";
        strAddNullQualifierTagBurnAddress = "AIaddTagBurnXXXXXXXXXXXXXXXXZQm5ya";

        
        //Global Burn Address
        strGlobalBurnAddress = "AIBurnXXXXXXXXXXXXXXXXXXXXXXWUo9FV";

        // AIPG Operations Fund
        strCommunityAutonomousAddress = "Ab8KBCTTJgy7XnsPsHbnwRMJD4MFjG12hU";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 1; // Asset activated block height
        nMessagingActivationBlock = 1; // Messaging activated block height
        nRestrictedActivationBlock = 1; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1688764800;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
    }
};

/**
 * Testnet (v7)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 100000;  //~2 months
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled 	= true;
        consensus.powLimit 	= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit 	= uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
	    consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (HIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714; // Approx 85% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1658055600; // Sunday 17 July 2022 12:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1659178800; // Saturday, 30 July 2022 11:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; // Approx 70% of 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000000f798386703ae778eeaf8a2f426dc2715eb8989b4226cddc1681b567760");


        pchMessageStart[0] = 0x41; // A
        pchMessageStart[1] = 0x49; // I
        pchMessageStart[2] = 0x34; // 4
        pchMessageStart[3] = 0x54; // T
        nDefaultPort = 18865;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1688350555;  // October 30, 2023
                   // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
           /////////////////////////////////////////////////////////////////
/*
        arith_uint256 test;
        bool fNegative;
        bool fOverflow;
        test.SetCompact(0x1e00ffff, &fNegative, &fOverflow);
        std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        int genesisNonce = 0;
        uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        for (int i=0;i<40000000;i++) {
            genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e00ffff, 4, 5000 * COIN);
            genesis.hashPrevBlock = TempHashHolding;
			// Depending on when the timestamp is on the genesis block. You will need to use GetX16RHash or GetX16RV2Hash. Replace GetHash() with these below
            consensus.hashGenesisBlock = genesis.GetX16RHash();

            arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
            if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
                BestBlockHash = consensus.hashGenesisBlock;
                std::cout << "CHOOSE: consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: BestBlockHash.GetHex(): " << BestBlockHash.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: genesis.GetX16RHash().GetHex(): " << genesis.GetX16RHash().GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
            }

            //TempHashHolding = consensus.hashGenesisBlock;

            if (BestBlockHashArith < test) {
                genesisNonce = i - 1;
                break;
            }
            std::cout << "	 consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";

        std::cout << "BestBlockHash.GetHex() to 0x" << BestBlockHash.GetHex() << std::endl;
        std::cout << "genesis.GetX16RHash().GetHex() to 0x" << genesis.GetX16RHash().GetHex() << std::endl;
        std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;

        std::cout << "\n";
        std::cout << "\n";
        int totalHits = 0;
        double totalTime = 0.0;

        for(int x = 0; x < 16; x++) {
            totalHits += algoHashHits[x];
            totalTime += algoHashTotal[x];
            std::cout << "hash algo " << x << " hits " << algoHashHits[x] << " total " << algoHashTotal[x] << " avg " << algoHashTotal[x]/algoHashHits[x] << std::endl;
        }

        std::cout << "Totals: hash algo " <<  " hits " << totalHits << " total " << totalTime << " avg " << totalTime/totalHits << std::endl;

        genesis.hashPrevBlock = TempHashHolding;

        return;           
        /////////////////////////////////////////////////////////////////
           // end of genesis block creation
*/
        genesis = CreateGenesisBlock(nGenesisTime, 18991761, 0x1e00ffff, 4, 5000 *  COIN);
        consensus.hashGenesisBlock = genesis.GetX16RV2Hash();
        //Test MerkleRoot and GenesisBlock
        assert(consensus.hashGenesisBlock == uint256S("0x000000f798386703ae778eeaf8a2f426dc2715eb8989b4226cddc1681b567760"));
        assert(genesis.hashMerkleRoot == uint256S("e04a78dcf0ad3d5c7f1ac4460c4c04bc333e677d52371b7453b5b09603b41d54"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.emplace_back("seed1-testnet.aipowergrid.io", false);
        vSeeds.emplace_back("seed2-testnet.aipowergrid.io", false);
        vSeeds.emplace_back("seed3-testnet.aipowergrid.io", false);
        vSeeds.emplace_back("seed4-testnet.aipowergrid.io", false);

	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);  // 'A' prefix
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);  // 'A' prefix
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // AIPG BIP44 cointype in testnet
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the AIPG chain
            // Stats as of 00000023b66f46d74890287a7b1157dd780c7c5fdda2b561eb96684d2b39d62e window size 43200
            0, // * UNIX timestamp of last known number of transactions
            0,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.0        // * estimated number of transactions per second after that timestamp
        };

        /** AIPG Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 50 * COIN;
        nReissueAssetBurnAmount = 10 * COIN;
        nIssueSubAssetBurnAmount = 10 * COIN;
        nIssueUniqueAssetBurnAmount = 0.5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 10 * COIN;
        nIssueQualifierAssetBurnAmount = 100 * COIN;
        nIssueSubQualifierAssetBurnAmount = 10 * COIN;
        nIssueRestrictedAssetBurnAmount = 150 * COIN;
        nAddNullQualifierTagBurnAmount = 0.01 * COIN;
		
	    // 5% of 500 AIPG to operations fund
	    nCommunityAutonomousAmount = 5;

        // Burn Addresses
	    strIssueAssetBurnAddress = "n1issueAssetXXXXXXXXXXXXXXXXWdnemQ";
        strReissueAssetBurnAddress = "n1ReissueAssetXXXXXXXXXXXXXXWG9NLd";
        strIssueSubAssetBurnAddress = "n1issueSubAssetXXXXXXXXXXXXXbNiH6v";
        strIssueUniqueAssetBurnAddress = "n1issueUniqueAssetXXXXXXXXXXS4695i";
        strIssueMsgChannelAssetBurnAddress = "n1issueMsgChanneLAssetXXXXXXT2PBdD";
        strIssueQualifierAssetBurnAddress = "n1issueQuaLifierXXXXXXXXXXXXUysLTj";
        strIssueSubQualifierAssetBurnAddress = "n1issueSubQuaLifierXXXXXXXXXYffPLh";
        strIssueRestrictedAssetBurnAddress = "n1issueRestrictedXXXXXXXXXXXXZVT9V";
        strAddNullQualifierTagBurnAddress = "n1addTagBurnXXXXXXXXXXXXXXXXX5oLMH";

        // Donation Address
        strCommunityAutonomousAddress = "AcYHNBj8C6nCFSpu1ANsJxturWp31W32cd";

	    // Global Burn Address
        strGlobalBurnAddress = "n1BurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 1; // Asset activated block height
        nMessagingActivationBlock = 1; // Messaging activated block height
        nRestrictedActivationBlock = 1; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1688764800; // Thu Nov 10 2023 00:00:00 UTC
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** AIPG End **/
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (HIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0; // GMT: Sun Mar 3, 2019 5:00:00 PM
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 999999999999ULL; // UTC: Wed Dec 25 2019 07:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000001a53f7f3d9f8be5f0cdfeddd641bee2c6c7001a9cdfdbb6f72ca66aed5");

        pchMessageStart[0] = 0x41; // A
        pchMessageStart[1] = 0x49; // I 
        pchMessageStart[2] = 0x34; // 4 
        pchMessageStart[3] = 0x52; // R 
        nDefaultPort = 18550;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1688340000;

                   // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
           /////////////////////////////////////////////////////////////////
/*
        arith_uint256 test;
        bool fNegative;
        bool fOverflow;
        test.SetCompact(0x1e00ffff, &fNegative, &fOverflow);
        std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        int genesisNonce = 0;
        uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        for (int i=0;i<40000000;i++) {
            genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e00ffff, 4, 500 * COIN);
            genesis.hashPrevBlock = TempHashHolding;
			// Depending on when the timestamp is on the genesis block. You will need to use GetX16RHash or GetX16RV2Hash. Replace GetHash() with these below
            consensus.hashGenesisBlock = genesis.GetX16RHash();

            arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
            if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
                BestBlockHash = consensus.hashGenesisBlock;
                std::cout << "CHOOSE: consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: BestBlockHash.GetHex(): " << BestBlockHash.GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: genesis.GetX16RHash().GetHex(): " << genesis.GetX16RHash().GetHex() << " Nonce: " << i << " nGenesisTime: " << nGenesisTime << "\n";
                std::cout << "CHOOSE: PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
            }

            //TempHashHolding = consensus.hashGenesisBlock;

            if (BestBlockHashArith < test) {
                genesisNonce = i - 1;
                break;
            }
            std::cout << "	 consensus.hashGenesisBlock.GetHex(): " << consensus.hashGenesisBlock.GetHex() << " Nonce: " << i << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";

        std::cout << "BestBlockHash.GetHex() to 0x" << BestBlockHash.GetHex() << std::endl;
        std::cout << "genesis.GetX16RHash().GetHex() to 0x" << genesis.GetX16RHash().GetHex() << std::endl;
        std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;

        std::cout << "\n";
        std::cout << "\n";
        int totalHits = 0;
        double totalTime = 0.0;

        for(int x = 0; x < 16; x++) {
            totalHits += algoHashHits[x];
            totalTime += algoHashTotal[x];
            std::cout << "hash algo " << x << " hits " << algoHashHits[x] << " total " << algoHashTotal[x] << " avg " << algoHashTotal[x]/algoHashHits[x] << std::endl;
        }

        std::cout << "Totals: hash algo " <<  " hits " << totalHits << " total " << totalTime << " avg " << totalTime/totalHits << std::endl;

        genesis.hashPrevBlock = TempHashHolding;

        return;           
        /////////////////////////////////////////////////////////////////
           // end of genesis block creation
*/
        genesis = CreateGenesisBlock(nGenesisTime, 1925563, 0x1e00ffff, 4, 500 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x0000001a53f7f3d9f8be5f0cdfeddd641bee2c6c7001a9cdfdbb6f72ca66aed5"));
        assert(genesis.hashMerkleRoot == uint256S("e04a78dcf0ad3d5c7f1ac4460c4c04bc333e677d52371b7453b5b09603b41d54"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
		
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // AIPG BIP44 cointype in regtest
        nExtCoinType = 1;

        /** AIPG Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 50 * COIN;
        nReissueAssetBurnAmount = 10 * COIN;
        nIssueSubAssetBurnAmount = 10 * COIN;
        nIssueUniqueAssetBurnAmount = 0.5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 10 * COIN;
        nIssueQualifierAssetBurnAmount = 100 * COIN;
        nIssueSubQualifierAssetBurnAmount = 10 * COIN;
        nIssueRestrictedAssetBurnAmount = 150 * COIN;
        nAddNullQualifierTagBurnAmount = 0.01 * COIN;
		
	//5% of 500 COIN to Opertions Fund
	nCommunityAutonomousAmount = 5;

        // Burn Addresses
	strIssueAssetBurnAddress = "n1issueAssetXXXXXXXXXXXXXXXXWdnemQ";
        strReissueAssetBurnAddress = "n1ReissueAssetXXXXXXXXXXXXXXWG9NLd";
        strIssueSubAssetBurnAddress = "n1issueSubAssetXXXXXXXXXXXXXbNiH6v";
        strIssueUniqueAssetBurnAddress = "n1issueUniqueAssetXXXXXXXXXXS4695i";
        strIssueMsgChannelAssetBurnAddress = "n1issueMsgChanneLAssetXXXXXXT2PBdD";
        strIssueQualifierAssetBurnAddress = "n1issueQuaLifierXXXXXXXXXXXXUysLTj";
        strIssueSubQualifierAssetBurnAddress = "n1issueSubQuaLifierXXXXXXXXXYffPLh";
        strIssueRestrictedAssetBurnAddress = "n1issueRestrictedXXXXXXXXXXXXZVT9V";
        strAddNullQualifierTagBurnAddress = "n1addTagBurnXXXXXXXXXXXXXXXXX5oLMH";
		
	// Global Burn Address
        strGlobalBurnAddress = "n1BurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 0; // Asset activated block height
        nMessagingActivationBlock = 0; // Messaging activated block height
        nRestrictedActivationBlock = 0; // Restricted activated block height

        // TODO, we need to figure out what to do with this for regtest. This effects the unit tests
        // For now we can use a timestamp very far away
        // If you are looking to test the kawpow hashing function in regtest. You will need to change this number
        nKAAAWWWPOWActivationTime = 3582830167;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** AIPG End **/
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
    SelectBaseParams(network);
    if (fForceBlockNetwork) {
        bNetwork.SetNetwork(network);
    }
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
