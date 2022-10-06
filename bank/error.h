#pragma once
#include<stdexcept>
#include<string>
#include"account.h"
using namespace std;
// 时间读取格式错误
class DateReadFormat:
    public runtime_error
{
public:
    DateReadFormat(string str);
    virtual string toString() const;
};
class AccountException :virtual public runtime_error {
public:
    AccountException(Account* account);
    virtual string toString() const;
private:
    Account* account;
};
// 账户取钱错误
class AccountWithdrawOverException:
    virtual public AccountException {
public:
    AccountWithdrawOverException(Account* account);
};
class CommandFormatException :virtual public runtime_error {
public:
    CommandFormatException(string cmd);
};