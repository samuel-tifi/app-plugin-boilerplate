#include "tifi_bank_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;

    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);
    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->version, "Swap", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->version, "Swap", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            strlcpy(msg->version, "Swap", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case ADD_LIQUIDITY_ETH:
            strlcpy(msg->version, "Add Liquidity", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case REMOVE_LIQUIDITY_ETH:
            strlcpy(msg->version, "Remove Liquidity", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LUCKY_BAG_AND_STAKE_DEPOSIT:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case STAKE_WITHDRAW:
            strlcpy(msg->version, "Unstake", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LUCKY_BAG_WITHDRAW:
            strlcpy(msg->version, "Lucky Bags", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LUCKY_BAG_ENTER:
            strlcpy(msg->version, "Lucky Bags", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case APPROVE:
            strlcpy(msg->version, "Approve", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LOAN_DEPOSIT:
            strlcpy(msg->version, "Loan", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LOAN_WITHDRAW:
            strlcpy(msg->version, "Loan", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LOAN_BORROW:
            strlcpy(msg->version, "Loan", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case LOAN_REPAY_BY_SHARE:
            strlcpy(msg->version, "Loan", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}