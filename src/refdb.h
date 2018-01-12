// Copyright (c) 2017 The Merit Foundation developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MERIT_REFDB_H
#define MERIT_REFDB_H

#include "dbwrapper.h"
#include "amount.h"
#include "serialize.h"
#include "primitives/referral.h"
#include "primitives/transaction.h"
#include "pog/wrs.h"

#include <boost/optional.hpp>
#include <vector>

namespace referral
{
using Address = uint160;
using MaybeReferral = boost::optional<Referral>;
using MaybeAddress = boost::optional<Address>;
using ChildAddresses = std::vector<Address>;
using Addresses = std::vector<Address>;
using MaybeWeightedKey = boost::optional<pog::WeightedKey>;
using LotteryEntrant = std::tuple<pog::WeightedKey, char, Address>;
using MaybeLotteryEntrant = boost::optional<LotteryEntrant>;
using AddressPair = std::pair<char, Address>;
using MaybeAddressPair = boost::optional<AddressPair>;


struct AddressANV
{
    char address_type;
    Address address;
    CAmount anv;
};

using AddressANVs = std::vector<AddressANV>;
using MaybeAddressANV = boost::optional<AddressANV>;

/**
 * These are the replaced samples in the lottery.
 */
struct LotteryUndo
{
    pog::WeightedKey replaced_key;
    char replaced_address_type;
    Address replaced_address;
    Address replaced_with;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(replaced_key);
        READWRITE(replaced_address_type);
        READWRITE(replaced_address);
        READWRITE(replaced_with);
    }
};

using LotteryUndos = std::vector<LotteryUndo>;

class ReferralsViewDB
{
protected:
    mutable CDBWrapper m_db;
public:
    explicit ReferralsViewDB(
            size_t cache_size,
            bool memory = false,
            bool wipe = false,
            const std::string& name = "referrals");

    MaybeReferral GetReferral(const Address&) const;
    MaybeReferral GetReferral(const uint256&) const;
    MaybeAddressPair GetParentAddress(const Address&) const;
    MaybeAddress GetAddressByPubKey(const CPubKey&) const;
    ChildAddresses GetChildren(const Address&) const;

    bool UpdateANV(char address_type, const Address&, CAmount);
    MaybeAddressANV GetANV(const Address&) const;
    AddressANVs GetAllANVs() const;
    bool OrderReferrals(referral::ReferralRefs& refs);

    bool InsertReferral(const Referral&, bool allow_no_parent = false);
    bool RemoveReferral(const Referral&);
    bool ConfirmReferral(const Referral&, const CTransaction&);

    bool Exists(const Address&) const;
    bool IsConfirmed(const Address&) const;
    bool RemoveReferralConfirmation(const Address&);

    AddressANVs GetAllRewardableANVs() const;

    bool AddAddressToLottery(
            int height,
            uint256,
            char address_type,
            MaybeAddress,
            const uint64_t max_reservoir_size,
            LotteryUndos&);

    bool UndoLotteryEntrant(
            const LotteryUndo&,
            const uint64_t max_reservoir_size);

private:
    uint64_t GetLotteryHeapSize() const;
    MaybeLotteryEntrant GetMinLotteryEntrant() const;
    bool FindLotteryPos(const Address& address, uint64_t& pos) const;

    bool InsertLotteryEntrant(
            const pog::WeightedKey& key,
            char address_type,
            const Address& address,
            const uint64_t max_reservoir_size);

    bool PopMinFromLotteryHeap();
    bool RemoveFromLottery(const Address&);
    bool RemoveFromLottery(uint64_t pos);
};

} // namespace referral

#endif
