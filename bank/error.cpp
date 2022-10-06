#include "error.h"
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": 时间格式错误")
{

}
string DateReadFormat::toString()const
{
	return what();
}
AccountException::AccountException(Account* account)
	:account(account),runtime_error("账户错误")
{

}
string AccountException::toString() const
{
	return account->getId() + this->what();
}
AccountWithdrawOverException::AccountWithdrawOverException(Account* account)
	:AccountException(account),runtime_error("账户取钱错误")
{

}
CommandFormatException::CommandFormatException(string cmd)
	:runtime_error(cmd + "命令格式错误")
{

}