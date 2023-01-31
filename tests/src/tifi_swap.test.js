import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

// EDIT THIS: Replace with your contract address
const contractAddr = "0xc8595392b8ca616a226dce8f69d9e0c7d4c81fe4";
// EDIT THIS: Replace `boilerplate` with your plugin name
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



// Test from constructed transaction
// EDIT THIS: build your own test
nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Swap', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    // Constants used to create the transaction
    // EDIT THIS: Remove what you don't need
    const amountOutMin = parseUnits("28471151959593036279", 'wei');
    const WBNB = "0xbb4CdB9CBd36B01bD1cBaEBF2De08d9173bc095c";
    const TIFI = "0x17E65E6b9B166Fb8e7c59432F0db126711246BC0";
    const path = [WBNB, TIFI];
    const deadline = Number(1632843280);
    // We set beneficiary to the default address of the emulator, so it maches sender address
    const beneficiary = SPECULOS_ADDRESS;

    // EDIT THIS: adapt the signature to your method
    // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
    // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
    const { data } = await contract.populateTransaction.swapExactETHForTokensSupportingFeeOnTransferTokens(amountOutMin, path, beneficiary, deadline);

    // Get the generic transaction template
    let unsignedTx = genericTx;
    // Modify `to` to make it interact with the contract
    unsignedTx.to = contractAddr;
    // Modify the attached data
    unsignedTx.data = data;
    // EDIT THIS: get rid of this if you don't wish to modify the `value` field.
    // Modify the number of ETH sent
    unsignedTx.value = parseEther("0.1");

    // Create serializedTx and remove the "0x" prefix
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx
    );

    const right_clicks = model.letter === 'S' ? 9 : 7;

    // Wait for the application to actually load and parse the transaction
    console.log('Waiting for the screen')
    await waitForAppScreen(sim);
    console.log('screen ready')
    // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
    // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_swap', [right_clicks, 0]);

    await tx;
  }));
});

