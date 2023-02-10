#include "tifi_bank_plugin.h"

// EDIT THIS: Adapt this function to your needs! Remember, the information for tokens are held in
// `msg->item1` and `msg->item2`. If those pointers are `NULL`, this means the ethereum app didn't
// find any info regarding the requested tokens!
void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    if (msg->item1) {
        context->decimals = msg->item1->token.decimals;
        strlcpy(context->ticker, (char *) msg->item1->token.ticker, sizeof(context->ticker));

        context->token_found = true;
    } else {
        context->token_found = false;

        context->decimals = 18;
        strlcpy(context->ticker, "???", sizeof(context->ticker));
    }

    if (msg->item2) {
        context->decimals2 = msg->item2->token.decimals;
        strlcpy(context->ticker2, (char *) msg->item2->token.ticker, sizeof(context->ticker2));

        context->token_found2 = true;
    } else {
        context->token_found2 = false;

        context->decimals2 = 18;
        strlcpy(context->ticker2, "???", sizeof(context->ticker2));
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}