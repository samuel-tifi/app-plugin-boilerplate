#include "tifi_bank_plugin.h"

// EDIT THIS: Remove this function and write your own handlers!
// SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS
static void handle_swap_exact_eth_for_tokens_supporting_fee_on_transfer_tokens(
    ethPluginProvideParameter_t *msg,
    context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case MIN_AMOUNT_RECEIVED:  // amountOutMin
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = PATH_OFFSET;
            break;
        case PATH_OFFSET:  // path
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // to
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATH_LENGTH;
            context->go_to_offset = true;
            break;
        case PATH_LENGTH:
            context->offset = msg->parameterOffset - SELECTOR_SIZE + PARAMETER_LENGTH * 2;
            context->go_to_offset = true;
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // path[1] -> contract address of token received
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_exact_tokens_for_tokens_supporting_fee_on_transfer_tokens(
    ethPluginProvideParameter_t *msg,
    context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case MIN_AMOUNT_RECEIVED:  // amountOutMin
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = PATH_OFFSET;
            break;
        case PATH_OFFSET:  // path
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // to
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATH_LENGTH;
            context->go_to_offset = true;
            break;
        case PATH_LENGTH:
            context->offset = msg->parameterOffset - SELECTOR_SIZE +
                              PARAMETER_LENGTH * U2BE(msg->parameter, PARAMETER_LENGTH - 1);
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->go_to_offset = true;
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // path[1] -> contract address of token received
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_exact_tokens_for_eth_supporting_fee_on_transfer_tokens(
    ethPluginProvideParameter_t *msg,
    context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case MIN_AMOUNT_RECEIVED:  // amountOutMin
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = PATH_OFFSET;
            break;
        case PATH_OFFSET:  // path
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // to
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATH_LENGTH;
            context->go_to_offset = true;
            break;
        case PATH_LENGTH:
            context->offset = msg->parameterOffset - SELECTOR_SIZE +
                              PARAMETER_LENGTH * U2BE(msg->parameter, PARAMETER_LENGTH - 1);
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->go_to_offset = true;
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_add_liquidity_eth(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_SENT:  // amountSent
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_remove_liquidity_eth(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_SENT:  // amountSent
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_lucky_bag_and_stake_deposit(ethPluginProvideParameter_t *msg,
                                               context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stake_withdraw(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case MIN_AMOUNT_RECEIVED:  // amountSent
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_lucky_bag_withdraw(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case MIN_AMOUNT_RECEIVED:  // amountSent
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_lucky_bag_enter(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_approve(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_SENT:  // amountSent
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_loan_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_SENT:  // amountSent
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_loan_borrow(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_RECEIVED:  // amountSent
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            context->next_param = AMOUNT_SENT;
            break;
        case MIN_AMOUNT_RECEIVED:  // amountSent
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_loan_withdraw(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_RECEIVED:  // amountSent
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            context->next_param = AMOUNT_SENT;
            break;
        case MIN_AMOUNT_RECEIVED:  // amountSent
            copy_parameter(context->amount_received,
                           msg->parameter,
                           sizeof(context->amount_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_loan_repay_by_share(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    switch (context->next_param) {
        case TOKEN_SENT:  // amountSent
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // amountSent
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // EDIT THIS: adapt the cases and the names of the functions.
    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            handle_swap_exact_eth_for_tokens_supporting_fee_on_transfer_tokens(msg, context);
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            handle_swap_exact_tokens_for_tokens_supporting_fee_on_transfer_tokens(msg, context);
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            handle_swap_exact_tokens_for_eth_supporting_fee_on_transfer_tokens(msg, context);
            break;
        case ADD_LIQUIDITY_ETH:
            handle_add_liquidity_eth(msg, context);
            break;
        case REMOVE_LIQUIDITY_ETH:
            handle_remove_liquidity_eth(msg, context);
            break;
        case LUCKY_BAG_AND_STAKE_DEPOSIT:
            handle_lucky_bag_and_stake_deposit(msg, context);
            break;
        case STAKE_WITHDRAW:
            handle_stake_withdraw(msg, context);
            break;
        case LUCKY_BAG_WITHDRAW:
            handle_lucky_bag_withdraw(msg, context);
            break;
        case LUCKY_BAG_ENTER:
            handle_lucky_bag_enter(msg, context);
            break;
        case APPROVE:
            handle_approve(msg, context);
            break;
        case LOAN_DEPOSIT:
            handle_loan_deposit(msg, context);
            break;
        case LOAN_WITHDRAW:
            handle_loan_withdraw(msg, context);
            break;
        case LOAN_BORROW:
            handle_loan_borrow(msg, context);
            break;
        case LOAN_REPAY_BY_SHARE:
            handle_loan_repay_by_share(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}