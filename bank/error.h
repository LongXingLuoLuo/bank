#pragma once
#include<stdexcept>
#include<string>
using namespace std;
// 时间读取格式错误
class DateReadFormat:
    public runtime_error
{
public:
    DateReadFormat(string str);
};

// 账户取钱错误
class WithdrawOver:
    virtual public runtime_error {
public:
    WithdrawOver();
};

// 存储账户取钱超过余额错误
class AccountWithdrawOverBalance :
    virtual public WithdrawOver
{
public:
    AccountWithdrawOverBalance();
};

// 信用账户取钱超过余额错误
class AccountWithdrawOverCredit :
    virtual public WithdrawOver
{
public:
    AccountWithdrawOverCredit();
};
