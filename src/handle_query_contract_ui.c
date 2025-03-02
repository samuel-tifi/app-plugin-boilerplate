#include "tifi_bank_plugin.h"

static void set_screen0(ethQueryContractUI_t *msg, const context_t *context) {
    uint8_t decimals = context->decimals;
    const char *ticker = context->ticker;
    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    if (!context->token_found) {
        decimals = WEI_TO_ETHER;
        ticker = msg->network_ticker;
    }

    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "Send", msg->titleLength);
            amountToString(eth_amount,
                           eth_amount_size,
                           WEI_TO_ETHER,
                           "BNB ",
                           msg->msg,
                           msg->msgLength);
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "Send", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "Send", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case ADD_LIQUIDITY_ETH:
            strlcpy(msg->title, "Add Liquidity", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case REMOVE_LIQUIDITY_ETH:
            strlcpy(msg->title, "Remove Liquidity", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case LUCKY_BAG_AND_STAKE_DEPOSIT:
            strlcpy(msg->title, "Deposit", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           WEI_TO_ETHER,
                           "TIFI ",
                           msg->msg,
                           msg->msgLength);
            break;
        case STAKE_WITHDRAW:
            strlcpy(msg->title, "Unstake", msg->titleLength);
            amountToString(context->amount_received,
                           sizeof(context->amount_received),
                           WEI_TO_ETHER,
                           "TIFI ",
                           msg->msg,
                           msg->msgLength);
            break;
        case LUCKY_BAG_WITHDRAW:
            strlcpy(msg->title, "Withdraw", msg->titleLength);
            amountToString(context->amount_received,
                           sizeof(context->amount_received),
                           WEI_TO_ETHER,
                           "TIFI ",
                           msg->msg,
                           msg->msgLength);
            break;
        case LUCKY_BAG_ENTER:
            strlcpy(msg->title, "Bet with", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           WEI_TO_ETHER,
                           "TIFI ",
                           msg->msg,
                           msg->msgLength);
            break;
        case APPROVE:
            strlcpy(msg->title, "Approve", msg->titleLength);
            msg->msg[0] = '0';
            msg->msg[1] = 'x';
            uint64_t chainid = 0;
            getEthAddressStringFromBinary(
                context->token_sent,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                msg->pluginSharedRW->sha3,
                chainid);
            break;
        case LOAN_DEPOSIT:
            strlcpy(msg->title, "Loan Deposit", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case LOAN_WITHDRAW:
            strlcpy(msg->title, "Loan Withdraw", msg->titleLength);
            amountToString(context->amount_received,
                           sizeof(context->amount_received),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case LOAN_BORROW:
            strlcpy(msg->title, "Loan Borrow", msg->titleLength);
            amountToString(context->amount_received,
                           sizeof(context->amount_received),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
        case LOAN_REPAY_BY_SHARE:
            strlcpy(msg->title, "Loan Repay", msg->titleLength);
            amountToString(context->amount_sent,
                           sizeof(context->amount_sent),
                           decimals,
                           ticker,
                           msg->msg,
                           msg->msgLength);
            break;
    }
}

static void set_screen1(ethQueryContractUI_t *msg, const context_t *context) {
    const char *ticker2 = context->ticker2;
    const char *ticker = context->ticker;
    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    // If the token look up failed, use the default network ticker along with the default decimals.
    if (!context->token_found2) {
        ticker2 = msg->network_ticker;
    }

    if (!context->token_found) {
        ticker = msg->network_ticker;
    }

    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "For", msg->titleLength);
            strlcpy(msg->msg, ticker, msg->msgLength);
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "For", msg->titleLength);
            strlcpy(msg->msg, ticker2, msg->msgLength);
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->title, "For", msg->titleLength);
            strlcpy(msg->msg, "BNB ", msg->msgLength);
            break;
        case ADD_LIQUIDITY_ETH:
            strlcpy(msg->title, "With", msg->titleLength);
            amountToString(eth_amount,
                           eth_amount_size,
                           WEI_TO_ETHER,
                           "BNB ",
                           msg->msg,
                           msg->msgLength);
            break;
    }
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (msg->screenIndex) {
        case 0:
            set_screen0(msg, context);
            break;
        case 1:
            set_screen1(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
