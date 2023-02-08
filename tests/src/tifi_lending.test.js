import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

const contractAddr = "0x8a6f7834a9d60090668f5db33fec353a7fb4704b";
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lending Deposit', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("1000000000000000000000082442", 'wei');
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.deposit(TIFI, amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_deposit', [right_clicks, 0]);

    await tx;
  }));
});

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lending Borrow', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("4000000000000000000", 'wei');
    const BUSD = "0xe9e7CEA3DedcA5984780Bafc599bD69ADd087D56";
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.borrow(BUSD, amountSent);

    console.log(data)
    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;
    console.log(unsignedTx)
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
    console.log(serializedTx)
    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 5 : 5;

    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_borrow', [right_clicks, 0]);

    await tx;
  }));
});

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lending Repay', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("3989992592826844060", 'wei');
    const BUSD = "0xe9e7CEA3DedcA5984780Bafc599bD69ADd087D56";
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.repayByShare(BUSD, amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_repay', [right_clicks, 0]);

    await tx;
  }));
});

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lending Withdraw', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("999541943318922664662268406", 'wei');
    const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.withdraw(TIFI, amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_withdraw', [right_clicks, 0]);

    await tx;
  }));
});