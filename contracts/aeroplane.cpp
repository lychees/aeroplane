#include <eosiolib/crypto.h>
#include ".hpp"

#include <cstdio>

 // @abi action
void happyeosslot::newgame(const checksum256 &hash) {

}

 // @abi action
void happyeosslot::random6(const checksum256 &hash) {
    
}

 // @abi action
void happyeosslot::step(const string player) {
    
}

 // @abi action
void happyeosslot::endgame(const string player) {
    
}


#define MY_EOSIO_ABI(TYPE, MEMBERS)                                                                                  \
    extern "C"                                                                                                       \
    {                                                                                                                \
        void apply(uint64_t receiver, uint64_t code, uint64_t action)                                                \
        {                                                                                                            \
                                                                                                                     \
            auto self = receiver;                                                                                    \
            if (action == N(onerror))                                                                                \
            {                                                                                                        \
                eosio_assert(code == N(eosio), "onerror action's are only valid from the \"eosio\" system account"); \
            }                                                                                                        \
            if (code == TOKEN_CONTRACT && action == N(transfer)) {                                                   \
                action = N(onTransfer);                                                                              \
            }                                                                                                        \
            if ((code == TOKEN_CONTRACT && action == N(onTransfer)) || code == self && action != N(onTransfer)) {                               \
                TYPE thiscontract(self);                                                                             \
                switch (action)                                                                                      \
                {                                                                                                    \
                    EOSIO_API(TYPE, MEMBERS)                                                                         \
                }                                                                                                     \
            }                                                                                                        \
        }                                                                                                            \
    }
// generate .wasm and .wast file
MY_EOSIO_ABI(happyeosslot, (onTransfer)(transfer)(init)(sell)(reveal)(test))

// generate .abi file
// EOSIO_ABI(happyeosslot, (transfer)(init)(sell)(reveal)(test))
