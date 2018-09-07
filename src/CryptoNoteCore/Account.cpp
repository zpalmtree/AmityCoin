// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "Account.h"
#include "CryptoNoteSerialization.h"

namespace CryptoNote {
//-----------------------------------------------------------------
AccountBase::AccountBase() {
  setNull();
}
//-----------------------------------------------------------------
void AccountBase::setNull() {
  m_keys = AccountKeys();
}
//-----------------------------------------------------------------
void AccountBase::generate() {
  Crypto::generate_keys(m_keys.address.spendPublicKey, m_keys.spendSecretKey);
  Crypto::generate_keys(m_keys.address.viewPublicKey, m_keys.viewSecretKey);
  m_creation_timestamp = time(NULL);
}
//----------------------------------------------------------------- 
Crypto::SecretKey AccountBase::generate_key(const Crypto::SecretKey& recovery_key, bool recover, bool two_random)
{
  Crypto::SecretKey first = generate_m_keys(m_keys.address.spendPublicKey, m_keys.spendSecretKey, recovery_key, recover);

  // rng for generating second set of keys is hash of first rng.  means only one set of electrum-style words needed for recovery
  Crypto::SecretKey second;
  keccak((uint8_t *)&first, sizeof(Crypto::SecretKey), (uint8_t *)&second, sizeof(Crypto::SecretKey));

  generate_m_keys(m_keys.address.viewPublicKey, m_keys.viewSecretKey, second, two_random ? false : true);
 
  struct tm timestamp;
  timestamp.tm_year = 2018 - 1900;  // year 2018
  timestamp.tm_mon = 1 - 1;  // month Jan'
  timestamp.tm_mday = 1;  // 1 of Jan' 2018
  timestamp.tm_hour = 0;
  timestamp.tm_min = 0;
  timestamp.tm_sec = 0;

  if (recover)
  {
    m_creation_timestamp = mktime(&timestamp);
  }
    else
  {
    m_creation_timestamp = time(NULL);
  }
  return first;
}

//-----------------------------------------------------------------
const AccountKeys &AccountBase::getAccountKeys() const {
  return m_keys;
}

void AccountBase::setAccountKeys(const AccountKeys &keys) {
  m_keys = keys;
}
//-----------------------------------------------------------------

void AccountBase::serialize(ISerializer &s) {
  s(m_keys, "m_keys");
  s(m_creation_timestamp, "m_creation_timestamp");
}
}
