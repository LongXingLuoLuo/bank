#include "error.h"
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": ʱ���ʽ����")
{

}
string DateReadFormat::toString()const
{
	return what();
}
AccountException::AccountException(Account* account)
	:account(account),runtime_error("�˻�����")
{

}
string AccountException::toString() const
{
	return account->getId() + this->what();
}
AccountWithdrawOverException::AccountWithdrawOverException(Account* account)
	:AccountException(account),runtime_error("�˻�ȡǮ����")
{

}
CommandFormatException::CommandFormatException(string cmd)
	:runtime_error(cmd + "�����ʽ����")
{

}