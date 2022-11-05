#include "error.h"
// 时间读取格式错误
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": 时间格式错误")
{

}
string DateReadFormat::toString()const
{
	return what();
}
// 账户错误
AccountException::AccountException(Account* account)
	:account(account),runtime_error(account->getId() + "账户错误")
{

}
string AccountException::toString() const
{
	return account->getId() + this->what();
}
// 取钱错误
AccountWithdrawOverException::AccountWithdrawOverException(Account* account)
	:AccountException(account),runtime_error(account->getId()+"账户取钱错误")
{

}
// 命令格式错误
CommandFormatException::CommandFormatException(string cmd)
	:runtime_error(cmd + "命令格式错误")
{

}

// 文件错误
FileNotExistException::FileNotExistException(string path)
	:runtime_error("无法打开文件:" + path)
{

}