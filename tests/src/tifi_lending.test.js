import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

// EDIT THIS: Replace with your contract address
const contractAddr = "0x8a6f7834a9d60090668f5db33fec353a7fb4704b";
// EDIT THIS: Replace `boilerplate` with your plugin name
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



// nano_models.forEach(function (model) {
//   test('[Nano ' + model.letter + '] TiFi Lending Deposit', zemu(model, async (sim, eth) => {
//     const contract = new ethers.Contract(contractAddr, abi);

//     // Constants used to create the transaction
//     // EDIT THIS: Remove what you don't need
//     const amountSent = parseUnits("1000000000000000000000082442", 'wei');
//     const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
//     // We set beneficiary to the default address of the emulator, so it maches sender address
//     const beneficiary = SPECULOS_ADDRESS;

//     // EDIT THIS: adapt the signature to your method
//     // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
//     // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
//     const { data } = await contract.populateTransaction.deposit(TIFI, amountSent);

//     // Get the generic transaction template
//     let unsignedTx = genericTx;
//     // Modify `to` to make it interact with the contract
//     unsignedTx.to = contractAddr;
//     // Modify the attached data
//     unsignedTx.data = data;

//     // Create serializedTx and remove the "0x" prefix
//     const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

//     const tx = eth.signTransaction(
//       "44'/60'/0'/0",
//       serializedTx
//     );

//     const right_clicks = model.letter === 'S' ? 7 : 5;

//     // Wait for the application to actually load and parse the transaction
//     await waitForAppScreen(sim);
//     // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
//     // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
//     await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_deposit', [right_clicks, 0]);

//     await tx;
//   }));
// });

nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Lending Borrow', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    // Constants used to create the transaction
    // EDIT THIS: Remove what you don't need
    const amountSent = parseUnits("4000000000000000000", 'wei');
    const BUSD = "0xe9e7CEA3DedcA5984780Bafc599bD69ADd087D56";
    // We set beneficiary to the default address of the emulator, so it maches sender address
    const beneficiary = SPECULOS_ADDRESS;

    // EDIT THIS: adapt the signature to your method
    // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
    // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
    const { data } = await contract.populateTransaction.borrow(BUSD, amountSent);

    // Get the generic transaction template
    let unsignedTx = genericTx;
    // Modify `to` to make it interact with the contract
    unsignedTx.to = contractAddr;
    // Modify the attached data
    unsignedTx.data = data;

    // Create serializedTx and remove the "0x" prefix
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 7 : 5;

    // Wait for the application to actually load and parse the transaction
    await waitForAppScreen(sim);
    // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
    // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_borrow', [right_clicks, 0]);

    await tx;
  }));
});

// nano_models.forEach(function (model) {
//   test('[Nano ' + model.letter + '] TiFi Lending Repay', zemu(model, async (sim, eth) => {
//     const contract = new ethers.Contract(contractAddr, abi);

//     // Constants used to create the transaction
//     // EDIT THIS: Remove what you don't need
//     const amountSent = parseUnits("3989992592826844060", 'wei');
//     const BUSD = "0xe9e7CEA3DedcA5984780Bafc599bD69ADd087D56";
//     // We set beneficiary to the default address of the emulator, so it maches sender address
//     const beneficiary = SPECULOS_ADDRESS;

//     // EDIT THIS: adapt the signature to your method
//     // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
//     // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
//     const { data } = await contract.populateTransaction.repayByShare(BUSD, amountSent);

//     // Get the generic transaction template
//     let unsignedTx = genericTx;
//     // Modify `to` to make it interact with the contract
//     unsignedTx.to = contractAddr;
//     // Modify the attached data
//     unsignedTx.data = data;

//     // Create serializedTx and remove the "0x" prefix
//     const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

//     const tx = eth.signTransaction(
//       "44'/60'/0'/0",
//       serializedTx
//     );

//     const right_clicks = model.letter === 'S' ? 7 : 5;

//     // Wait for the application to actually load and parse the transaction
//     await waitForAppScreen(sim);
//     // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
//     // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
//     await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_repay', [right_clicks, 0]);

//     await tx;
//   }));
// });

// nano_models.forEach(function (model) {
//   test('[Nano ' + model.letter + '] TiFi Lending Withdraw', zemu(model, async (sim, eth) => {
//     const contract = new ethers.Contract(contractAddr, abi);

//     // Constants used to create the transaction
//     // EDIT THIS: Remove what you don't need
//     const amountSent = parseUnits("999541943318922664662268406", 'wei');
//     const TIFI = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
//     // We set beneficiary to the default address of the emulator, so it maches sender address
//     const beneficiary = SPECULOS_ADDRESS;

//     // EDIT THIS: adapt the signature to your method
//     // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
//     // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
//     const { data } = await contract.populateTransaction.withdraw(TIFI, amountSent);

//     // Get the generic transaction template
//     let unsignedTx = genericTx;
//     // Modify `to` to make it interact with the contract
//     unsignedTx.to = contractAddr;
//     // Modify the attached data
//     unsignedTx.data = data;

//     // Create serializedTx and remove the "0x" prefix
//     const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

//     const tx = eth.signTransaction(
//       "44'/60'/0'/0",
//       serializedTx
//     );

//     const right_clicks = model.letter === 'S' ? 7 : 5;

//     // Wait for the application to actually load and parse the transaction
//     await waitForAppScreen(sim);
//     // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
//     // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
//     await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_lending_withdraw', [right_clicks, 0]);

//     await tx;
//   }));
// });