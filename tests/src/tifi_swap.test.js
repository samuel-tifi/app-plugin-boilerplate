import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

const contractAddr = "0xc8595392b8ca616a226dce8f69d9e0c7d4c81fe4";
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Swap', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountOutMin = parseUnits("28471151959593036279", 'wei');
    const WBNB = "0xbb4cdb9cbd36b01bd1cbaebf2de08d9173bc095c";
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const path = [WBNB, TIFI];
    const deadline = Number(1632843280);
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.swapExactETHForTokensSupportingFeeOnTransferTokens(amountOutMin, path, beneficiary, deadline);

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;
    unsignedTx.value = parseEther("0.1");

    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 6 : 6;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_swap', [right_clicks, 0]);

    await tx;
  }));
});

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Swap from tokens to tokens', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountOutMin = parseUnits("28471151959593036279", 'wei');
    const amountIn = parseUnits("1031332642000000000048862488", 'wei');
    const WBNB = "0xbb4cdb9cbd36b01bd1cbaebf2de08d9173bc095c";
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const BUSD = "0xe9e7CEA3DedcA5984780Bafc599bD69ADd087D56";
    const path = [TIFI, WBNB, BUSD];
    const deadline = Number(1632843280);
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.swapExactTokensForTokensSupportingFeeOnTransferTokens(amountIn, amountOutMin, path, beneficiary, deadline);

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;

    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 8 : 6;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_swap_from_tokens', [right_clicks, 0]);

    await tx;
  }));
});


nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Swap from tokens to BNB', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountOutMin = parseUnits("28471151959593036279", 'wei');
    const amountIn = parseUnits("1031332642000000000048862488", 'wei');
    const WBNB = "0xbb4cdb9cbd36b01bd1cbaebf2de08d9173bc095c";
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const path = [TIFI, WBNB];
    const deadline = Number(1632843280);
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.swapExactTokensForETHSupportingFeeOnTransferTokens(amountIn, amountOutMin, path, beneficiary, deadline);

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 8 : 6;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_swap_to_bnb', [right_clicks, 0]);

    await tx;
  }));
});
