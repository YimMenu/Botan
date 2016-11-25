/*
 * Extended Hash-Based Signatures Tests
 *
 * (C) 2014,2015 Jack Lloyd
 * (C) 2016 Matthias Gierlings
 **/

#include "tests.h"

#if defined(BOTAN_HAS_XMSS)
    #include <botan/xmss.h>
    #include "test_pubkey.h"
#endif

namespace Botan_Tests {

namespace {

#if defined(BOTAN_HAS_XMSS)

class XMSS_Signature_Tests : public PK_Signature_Generation_Test
   {
   public:
      XMSS_Signature_Tests() : PK_Signature_Generation_Test(
         "XMSS",
         "pubkey/xmss_sig.vec",
         {"Params", "Msg", "PrivateKey", "Signature"},
         {})
         {}

      std::string default_padding(const VarMap& vars) const override
         {
         return get_req_str(vars, "Params");
         }

      std::unique_ptr<Botan::Private_Key> load_private_key(const VarMap& vars) override
         {
         const std::vector<byte> raw_key = get_req_bin(vars, "PrivateKey");
         const Botan::secure_vector<byte> sec_key(raw_key.begin(), raw_key.end());

         std::unique_ptr<Botan::Private_Key> key(new Botan::XMSS_PrivateKey(sec_key));
         return key;
         }
   };

class XMSS_Signature_Verify_Tests : public PK_Signature_Verification_Test
   {
   public:
      XMSS_Signature_Verify_Tests() : PK_Signature_Verification_Test(
         "XMSS",
         "pubkey/xmss_verify.vec",
         {"Params", "Msg", "PublicKey", "Signature"},
         {})
         {}

      std::string default_padding(const VarMap& vars) const override
         {
         return get_req_str(vars, "Params");
         }

      std::unique_ptr<Botan::Public_Key> load_public_key(const VarMap& vars) override
         {
	     const std::vector<byte> raw_key = get_req_bin(vars, "PublicKey");
		 const Botan::secure_vector<byte> sec_key(raw_key.begin(), raw_key.end());

		 std::unique_ptr<Botan::Public_Key> key(new Botan::XMSS_PublicKey(sec_key));
         return key;
         }
   };

BOTAN_REGISTER_TEST("xmss_sign", XMSS_Signature_Tests);
BOTAN_REGISTER_TEST("xmss_verify", XMSS_Signature_Verify_Tests);

#endif

}

}
