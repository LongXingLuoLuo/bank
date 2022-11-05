#pragma once
#include<stdexcept>
#include<string>
#include"account.h"
using namespace std;
// ʱ���ȡ��ʽ����
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
protected:
    Account* account;
};

// �˻�ȡǮ����
class AccountWithdrawOverException:
    virtual public AccountException {
public:
    AccountWithdrawOverException(Account* account);
};

// �����ʽ����
class CommandFormatException :virtual public runtime_error {
public:
    CommandFormatException(string cmd);
};

// �Ҳ����ļ�
class FileNotExistException : virtual public runtime_error {
public:
    FileNotExistException(string path);
};