#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 14

// Name of the plugin.
#define PLUGIN_NAME "TiFiBank"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    ADD_LIQUIDITY_ETH,
    REMOVE_LIQUIDITY_ETH,
    LUCKY_BAG_AND_STAKE_DEPOSIT,
    STAKE_WITHDRAW,
    LUCKY_BAG_WITHDRAW,
    LUCKY_BAG_ENTER,
    APPROVE,
    LOAN_DEPOSIT,
    LOAN_WITHDRAW,
    LOAN_BORROW,
    LOAN_REPAY_BY_SHARE,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    MIN_AMOUNT_RECEIVED = 0,
    TOKEN_RECEIVED,
    BENEFICIARY,
    PATH_OFFSET,
    PATH_LENGTH,
    UNEXPECTED_PARAMETER,
    AMOUNT_SENT,
    TOKEN_SENT,
} parameter;

extern const uint32_t TIFI_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For display.
    uint8_t amount_received[INT256_LENGTH];
    uint8_t beneficiary[ADDRESS_LENGTH];
    uint8_t token_received[ADDRESS_LENGTH];
    uint8_t token_sent[ADDRESS_LENGTH];
    char ticker[MAX_TICKER_LEN];
    char ticker2[MAX_TICKER_LEN];
    uint8_t decimals;
    uint8_t decimals2;
    uint8_t token_found;
    uint8_t token_found2;
    uint8_t amount_sent[INT256_LENGTH];

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);