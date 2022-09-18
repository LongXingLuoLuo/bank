#pragma once
#include<stdexcept>
#include<string>
using namespace std;
// ʱ���ȡ��ʽ����
class DateReadFormat:
    public runtime_error
{
public:
    DateReadFormat(string str);
};

// �˻�ȡǮ����
class WithdrawOver:
    virtual public runtime_error {
public:
    WithdrawOver();
};

// �洢�˻�ȡǮ����������
class AccountWithdrawOverBalance :
    virtual public WithdrawOver
{
public:
    AccountWithdrawOverBalance();
};

// �����˻�ȡǮ����������
class AccountWithdrawOverCredit :
    virtual public WithdrawOver
{
public:
    AccountWithdrawOverCredit();
};
