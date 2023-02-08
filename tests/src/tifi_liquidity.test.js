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
  test('[Nano ' + model.letter + '] TiFi Add Liquidity ETH', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountTokenDesired = parseUnits("4869280000000000000000848244", 'wei');
    const amountTokenMin = parseUnits("4869280000000000000000848244", 'wei');
    const amountETHMin = parseUnits("4869280000000000000000848244", 'wei');
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const deadline = Number(1632843280);
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.addLiquidityETH(TIFI, amountTokenDesired, amountTokenMin, amountETHMin, beneficiary, deadline);

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;
    unsignedTx.value = parseEther("0.2");

    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 8 : 6;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_add_liquidity_eth', [right_clicks, 0]);

    await tx;
  }));
});


nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Remove Liquidity ETH', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const liquidityAmount = parseUnits("21550000000000000000008", 'wei');
    const amountTokenMin = parseUnits("21550000000000000000008", 'wei');
    const amountETHMin = parseUnits("21550000000000000000008", 'wei');
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const deadline = Number(1632843280);
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.removeLiquidityETH(TIFI, liquidityAmount, amountTokenMin, amountETHMin, beneficiary, deadline);

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;

    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 7 : 5;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_remove_liquidity_eth', [right_clicks, 0]);

    await tx;
  }));
});
