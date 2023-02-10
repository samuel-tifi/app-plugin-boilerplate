import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits } from "ethers/lib/utils";

const contractAddr = "0x17e65e6b9b166fb8e7c59432f0db126711246bc0";
const pluginName = "tifibank";
const testNetwork = "bsc";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);



nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] TiFi Approve', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    const amountSent = parseUnits("1000000000000000000000082442268486024", 'wei');
    const approving_contract_addr = '0x0aeff3d761f6706295f3828c87cce29c9418a93b'
    const beneficiary = SPECULOS_ADDRESS;

    const { data } = await contract.populateTransaction.approve(approving_contract_addr, amountSent);

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
    await sim.navigateAndCompareSnapshots('.', model.name + '_tifi_approve', [right_clicks, 0]);

    await tx;
  }));
});
