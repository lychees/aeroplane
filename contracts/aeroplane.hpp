/**
 *  @dev deaso
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
//#include "../eosio.token/eosio.token.hpp"
#include <cmath>
#include <string>

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

        void newgame(const uint64_t roundid, const uint64_t[] players);
        void prepare(const uint64_t roundid);
        void step(const uint64_t roundid, const uint64_t step_index, const string player);
        void endgame(const uint64_t roundid, const uint64_t[] winners);
        void refreshround(const uint64_t roundid);

    private:

        void random6(const checksum256& hash);
        void startgame(const uint64_t roundid);

        struct player {
            uint64_t playerid;
            account_name name;
            checksum256 seed;

            uint64_t primary_key() const { return playerid; }
            EOSLIB_SERIALIZE(player, (playerid)(name)(seed))
        };
        typedef eosio::multi_index<N(player), player> player_index;
        player_index players;

        struct round {
            uint64_t roundid;
            uint64_t[] players;
            uint64_t[] poses;
            uint64_t step_index;
            uint64_t[] winners;
            bool is_end;
            uint64_t primary_key() const { return roundid; }
            EOSLIB_SERIALIZE(round, (roundid)(players)(poses)(step_index)(winners)(is_end))
        };
        typedef eosio::multi_index<N(round), round> rounds;

};
