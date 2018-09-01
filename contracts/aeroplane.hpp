/**
 *  @dev minakokojima
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
//#include "../eosio.token/eosio.token.hpp"
#include <cmath>
#include <string>

#define EOS_SYMBOL S(4, EOS)
#define HPY_SYMBOL S(4, HPY)
#define TOKEN_CONTRACT N(eosio.token)

typedef double real_type;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::contract;
using eosio::permission_level;
using eosio::action;

class aeroplane : public tradeableToken {
    public:
        aeroplane(account_name self) :
        offers(_self, _self) {}

        void newgame(const checksum256& hash);
        void random6(const checksum256& hash);
        void step(const string player);
        void endgame(const string player) ;

    private:
        // @abi table offer i64
        struct player {
            uint64_t playerid;
            account_name name;
            checksum256 seed;

            uint64_t primary_key() const { return playerid; }
            EOSLIB_SERIALIZE(player, (playerid)(name)(seed))
        };
        typedef eosio::multi_index<N(player), player> player_index;
        player_index players;

        // @abi table result i64
        struct round {
            uint64_t roundid;
            uint64_t[] players;
            uint64_t[] poses;
            uint64_t[] step_index;
            bool is_end;
            uint64_t primary_key() const { return roundid; }
            EOSLIB_SERIALIZE(round, (roundid)(players)(poses)(step_index)(is_end))
        };
        typedef eosio::multi_index<N(round), round> rounds;

};
