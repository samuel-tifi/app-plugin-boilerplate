/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "os.h"
#include "cx.h"

#include "tifi_bank_plugin.h"

static const uint32_t SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR =
    0xb6f9de95;
static const uint32_t SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR =
    0x5c11d795;
static const uint32_t SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR =
    0x791ac947;
static const uint32_t ADD_LIQUIDITY_ETH_SELECTOR = 0xf305d719;
static const uint32_t REMOVE_LIQUIDITY_ETH_SELECTOR = 0x02751cec;
static const uint32_t LUCKY_BAG_AND_STAKE_DEPOSIT_SELECTOR = 0xb6b55f25;
static const uint32_t STAKE_WITHDRAW_SELECTOR = 0x441a3e70;
static const uint32_t LUCKY_BAG_WITHDRAW_SELECTOR = 0x2e1a7d4d;
static const uint32_t LUCKY_BAG_ENTER_SELECTOR = 0xa59f3e0c;
static const uint32_t APPROVE_SELECTOR = 0x095ea7b3;
static const uint32_t LOAN_DEPOSIT_SELECTOR = 0x47e7ef24;
static const uint32_t LOAN_WITHDRAW_SELECTOR = 0xf3fef3a3;
static const uint32_t LOAN_BORROW_SELECTOR = 0x4b8a3529;
static const uint32_t LOAN_REPAY_BY_SHARE_SELECTOR = 0xa4bae008;

const uint32_t TIFI_SELECTORS[NUM_SELECTORS] = {
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    ADD_LIQUIDITY_ETH_SELECTOR,
    REMOVE_LIQUIDITY_ETH_SELECTOR,
    LUCKY_BAG_AND_STAKE_DEPOSIT_SELECTOR,
    STAKE_WITHDRAW_SELECTOR,
    LUCKY_BAG_WITHDRAW_SELECTOR,
    LUCKY_BAG_ENTER_SELECTOR,
    APPROVE_SELECTOR,
    LOAN_DEPOSIT_SELECTOR,
    LOAN_WITHDRAW_SELECTOR,
    LOAN_BORROW_SELECTOR,
    LOAN_REPAY_BY_SHARE_SELECTOR,
};

void dispatch_plugin_calls(int message, void *parameters) {
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_INFO:
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

void handle_query_ui_exception(unsigned int *args) {
    switch (args[0]) {
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            ((ethQueryContractUI_t *) args[1])->result = ETH_PLUGIN_RESULT_ERROR;
            break;
        default:
            break;
    }
}

void call_app_ethereum() {
    unsigned int libcall_params[3];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    os_lib_call((unsigned int *) &libcall_params);
}

__attribute__((section(".boot"))) int main(int arg0) {
    __asm volatile("cpsie i");

    os_boot();

    BEGIN_TRY {
        TRY {
            check_api_level(CX_COMPAT_APILEVEL);

            if (!arg0) {
                call_app_ethereum();
                return 0;
            } else {
                const unsigned int *args = (const unsigned int *) arg0;

                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    dispatch_plugin_calls(args[0], (void *) args[1]);
                }
            }
        }
        CATCH_OTHER(e) {
            switch (e) {
                case 0x6502:
                case EXCEPTION_OVERFLOW:
                    handle_query_ui_exception((unsigned int *) arg0);
                    break;
                default:
                    break;
            }
            PRINTF("Exception 0x%x caught\n", e);
        }
        FINALLY {
            os_lib_end();
        }
    }
    END_TRY;

    return 0;
}
