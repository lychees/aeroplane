#include <eosiolib/crypto.h>
#include "aeroplane.hpp"

#include <cstdio>

 // @abi action
void aeroplane::newgame(const account_name msgsender, const uint64_t roundid, const string[] players) {
    //require_auth( msgsender );
    auto round = rounds.find(roundid);
    eosio_assert(round == round.end(), "round already created" ); 

    //init accounts.
    account_name accounts[players.length] = {};
    for(int i=0;i<players.length;i++){
        accounts[i] = eosio::chain::string_to_name(players[i]);
    }

    //init etc arrays.
    bool prepareds[players.length] = {};
    for(int i=0;i<players.length;i++){ prepareds[i] = false; }

    bool poses[players.length] = {};//pos:1001 = [1,1]; 121312 = [121,312]
    for(int i=0;i<players.length;i++){ poses[i] = 0; }

    bool winners[players.length] = {};
    for(int i=0;i<players.length;i++){ winners[i] = 0; }

    //insert.
    round.emplace(_self, [&](auto &round) {
        round.roundid = roundid;
        round.accounts = accounts;
        round.prepareds = prepareds;
        round.poses = poses;
        round.step_index = 0;
        round.winners = winners;
        round.is_started = false;
        round.is_ended = false;
    });
}

 // @abi action
void aeroplane::prepare(const account_name msgsender, const uint64_t roundid) {
    auto round = rounds.find(roundid);
    eosio_assert( round != round.end(), "no round" );
    eosio_assert( round.is_started != true, "is started" );
    for(int i=0;i<round.prepareds.length;i++){
        if (round.accounts[i] == msgsender){
            break;
        }
        eosio_assert(i == round.accounts.length - 1, "no player" ); 
    }
    round.emplace(_self, [&](auto &round) {
        for(int i=0;i<round.accounts.length;i++){
            if (round.accounts[i] == msgsender){
                round.prepareds[i] = true;
                break;
            }
        }
    });
    for(int i=0;i<round.prepareds.length;i++){
        if (round.prepared[i] == false){
            break;
        }
        if(i == round.accounts.length - 1) startgame(msgsender, roundid);
    }
}

 // @abi action
void aeroplane::step(const account_name msgsender, 
                    const uint64_t roundid, 
                    const uint64_t step_index) {
    auto round = rounds.find(roundid);
    eosio_assert( round != round.end(), "no round" );
    eosio_assert( round.is_started, "not started" );
    // judge action player
    auto step_index = round.step_index;
    uint64_t index = step_index % round.prepareds.length;
    eosio_assert( round.account[index] == msgsender, "wrong player" );

    uint64_t random6 = random6();

    // do something..
    refreshround(msgsender, roundid);

    if (random6 == 6) round.winners.push(index);

    if(round.winners.length == round.prepareds.length){
        endgame(msgsender, roundid);
        return;
    } 
    // calculate next player;
    for (int i=0;i<round.players.length;i++){ // == while(true)
        index = index + 1 % round.prepareds.length;
        step_index = step_index + 1;
        for(int i=0;i<round.winners.length;i++){
            if(index == round.winners[i]) continue;
        }
        round.emplace(_self, [&](auto &round) {
            round.step_index = step_index;
        });
        break;
    }
}

 // @abi action
void aeroplane::endgame(const account_name msgsender, const uint64_t roundid) {
    auto round = rounds.find(roundid);
    eosio_assert( round != round.end(), "no round" );
    eosio_assert( round.is_started, "not started" );
    round.emplace(_self, [&](auto &round) {
        round.is_ended = true;
    });
    // solve winner rewards..
}

 // @abi action
void aeroplane::refreshround(const account_name msgsender, const uint64_t roundid){
    // do something..
}

 // @abi action
void aeroplane::random6(){
    //return random 1-6..
    return 6;
}

 // @abi action
void aeroplane::startgame(const account_name msgsender, const uint64_t roundid){
    //refresh map..

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
