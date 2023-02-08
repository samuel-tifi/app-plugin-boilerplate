#include "tifi_bank_plugin.h"

static int find_selector(uint32_t selector, const uint32_t *selectors, size_t n, selector_t *out) {
    for (selector_t i = 0; i < n; i++) {
        if (selector == selectors[i]) {
            *out = i;
            return 0;
        }
    }
    return -1;
}

void handle_init_contract(void *parameters) {
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    memset(context, 0, sizeof(*context));

    uint32_t selector = U4BE(msg->selector, 0);
    if (find_selector(selector, TIFI_SELECTORS, NUM_SELECTORS, &context->selectorIndex)) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = AMOUNT_SENT;
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = AMOUNT_SENT;
            break;
        case ADD_LIQUIDITY_ETH:
            context->next_param = TOKEN_SENT;
            break;
        case REMOVE_LIQUIDITY_ETH:
            context->next_param = TOKEN_SENT;
            break;
        case LUCKY_BAG_AND_STAKE_DEPOSIT:
            context->next_param = AMOUNT_SENT;
            break;
        case STAKE_WITHDRAW:
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case LUCKY_BAG_WITHDRAW:
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case LUCKY_BAG_ENTER:
            context->next_param = AMOUNT_SENT;
            break;
        case APPROVE:
            context->next_param = TOKEN_SENT;
            break;
        case LOAN_DEPOSIT:
            context->next_param = TOKEN_SENT;
            break;
        case LOAN_WITHDRAW:
            context->next_param = TOKEN_RECEIVED;
            break;
        case LOAN_BORROW:
            context->next_param = TOKEN_RECEIVED;
            break;
        case LOAN_REPAY_BY_SHARE:
            context->next_param = TOKEN_SENT;
            break;
        // Keep this
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
