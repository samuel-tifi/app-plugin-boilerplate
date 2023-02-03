import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

// EDIT THIS: Replace with your contract address
const contractAddr = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
// EDIT THIS: Replace `boilerplate` with your plugin name
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Approve', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    // Constants used to create the transaction
    // EDIT THIS: Remove what you don't need
    const amountSent = parseUnits("1000000000000000000000082442268486024", 'wei');
    const approving_contract_addr = '0x0aeff3d761f6706295f3828c87cce29c9418a93b'
    // We set beneficiary to the default address of the emulator, so it maches sender address
    const beneficiary = SPECULOS_ADDRESS;

    // EDIT THIS: adapt the signature to your method
    // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
    // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
    const { data } = await contract.populateTransaction.approve(approving_contract_addr, amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_approve', [right_clicks, 0]);

    await tx;
  }));
});
