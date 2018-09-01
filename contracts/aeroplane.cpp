#include <eosiolib/crypto.h>
#include "aeroplane.hpp"

#include <cstdio>

 // @abi action
void aeroplane::newgame(const uint64_t roundid, const uint64_t[] players) {

}

 // @abi action
void aeroplane::prepare(const uint64_t roundid) {
    
}

 // @abi action
void aeroplane::step(const uint64_t roundid, const uint64_t step_index, const string player) {
    
}

 // @abi action
void aeroplane::endgame(const uint64_t roundid, const uint64_t[] winners) {
    
}

 // @abi action
void aeroplane::refreshround(const uint64_t roundid){

}

 // @abi action
void aeroplane::random6(const checksum256& hash){

}

 // @abi action
void aeroplane::startgame(const uint64_t roundid){

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
MY_EOSIO_ABI(aeroplane, (newgame)(prepare)(step)(endgame)(refresh))

// generate .abi file
// EOSIO_ABI(happyeosslot, (transfer)(init)(sell)(reveal)(test))
