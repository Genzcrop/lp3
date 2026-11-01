// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract BankAccount {

    // Store balance of each customer
    mapping(address => uint256) private balances;

    // 1. Deposit money
    function deposit() public payable {
        require(msg.value > 0, "Amount must be positive");

        balances[msg.sender] += msg.value;
    }

    // 2. Withdraw money
    function withdraw(uint256 amount) public {
        require(amount > 0, "Invalid amount");

        require(
            balances[msg.sender] >= amount,
            "Insufficient balance"
        );

        balances[msg.sender] -= amount;

        (bool success, ) = payable(msg.sender).call{value: amount}("");

        require(success, "Transfer failed");
    }

    // 3. Show balance
    function showBalance() public view returns (uint256) {
        return balances[msg.sender];
    }
}