import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

const contractAddr = "0x90aa87478408c52a10139896f56ae0fcb641d238";
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lucky Bag Deposit', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("1000000000000000000000082442", 'wei');
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.deposit(amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lucky_bags_deposit', [right_clicks, 0]);

    await tx;
  }));
});

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lucky Bag Withdraw', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("45648823800000018426860644", 'wei');
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.withdraw(amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lucky_bags_withdraw', [right_clicks, 0]);

    await tx;
  }));
});
nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lucky Bag Enter', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("23016548000000000000040686", 'wei');
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.enter(amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lucky_bags_enter', [right_clicks, 0]);

    await tx;
  }));
});