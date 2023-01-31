#include "tifi_bank_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;
    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            msg->numScreens = 2;
            msg->tokenLookup1 = context->token_received;
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            msg->numScreens = 2;
            msg->tokenLookup1 = context->token_sent;
            msg->tokenLookup2 = context->token_received;
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            msg->numScreens = 2;
            msg->tokenLookup1 = context->token_sent;
            break;
        case ADD_LIQUIDITY_ETH:
            msg->numScreens = 2;
            msg->tokenLookup1 = context->token_sent;
            break;
        case REMOVE_LIQUIDITY_ETH:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_sent;
            break;
        case LUCKY_BAG_AND_STAKE_DEPOSIT:
            msg->numScreens = 1;
            break;
        case STAKE_WITHDRAW:
            msg->numScreens = 1;
            break;
        case LUCKY_BAG_WITHDRAW:
            msg->numScreens = 1;
            break;
        case LUCKY_BAG_ENTER:
            msg->numScreens = 1;
            break;
        case APPROVE:
            msg->numScreens = 1;
            break;
        case LOAN_DEPOSIT:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_sent;
            break;
        case LOAN_WITHDRAW:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_received;
            break;
        case LOAN_BORROW:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_received;
            break;
        case LOAN_REPAY_BY_SHARE:
            msg->numScreens = 1;
            msg->tokenLookup1 = context->token_sent;
            break;
        default:
            msg->numScreens = 0;
            break;
    }

    // EDIT THIS: set `tokenLookup1` (and maybe `tokenLookup2`) to point to
    // token addresses you will info for (such as decimals, ticker...).

    msg->result = ETH_PLUGIN_RESULT_OK;
}
