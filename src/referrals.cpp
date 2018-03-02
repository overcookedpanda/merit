// Copyright (c) 2017-2018 The Merit Foundation developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "referrals.h"

#include <utility>

namespace referral
{
ReferralsViewCache::ReferralsViewCache(ReferralsViewDB* db) : m_db{db}
{
    assert(db);
};

MaybeReferral ReferralsViewCache::GetReferral(const Address& address) const
{
    {
        LOCK(m_cs_cache);
        auto it = referrals_index.find(address);
        if (it != referrals_index.end()) {
            return *it;
        }
    }

    if (auto ref = m_db->GetReferral(address)) {
        InsertReferralIntoCache(*ref);
        return ref;
    }

    return {};
}

bool ReferralsViewCache::Exists(const uint256& hash) const
{
    {
        LOCK(m_cs_cache);
        if (referrals_index.get<by_hash>().count(hash) > 0) {
            return true;
        }
    }

    if (auto ref = m_db->GetReferral(hash)) {
        InsertReferralIntoCache(*ref);
        return true;
    }

    return false;
}

bool ReferralsViewCache::Exists(const Address& address) const
{
    {
        LOCK(m_cs_cache);
        if (referrals_index.count(address) > 0) {
            return true;
        }
    }
    if (auto ref = m_db->GetReferral(address)) {
        InsertReferralIntoCache(*ref);
        return true;
    }
    return false;
}

bool ReferralsViewCache::Exists(const std::string& alias) const
{
    if (alias.size() == 0) {
        return false;
    }

    {
        LOCK(m_cs_cache);
        if (referrals_index.get<by_alias>().count(alias) > 0) {
            return true;
        }
    }
    if (auto ref = m_db->GetReferral(alias)) {
        InsertReferralIntoCache(*ref);
        return true;
    }
    return false;
}

void ReferralsViewCache::InsertReferralIntoCache(const Referral& ref) const
{
    LOCK(m_cs_cache);
    assert(ref.alias.size() == 0 || referrals_index.get<by_alias>().count(ref.alias) == 0);

    referrals_index.insert(ref);
}

bool ReferralsViewCache::RemoveReferral(const Referral& ref) const
{
    referrals_index.erase(ref.GetAddress());
    return m_db->RemoveReferral(ref);
}

bool ReferralsViewCache::IsConfirmed(const Address& address) const
{
    assert(m_db);
    //TODO: Have an in memory cache. For now just passthrough.
    return m_db->IsConfirmed(address);
}

}
