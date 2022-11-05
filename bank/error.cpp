#include "error.h"
// ʱ���ȡ��ʽ����
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": ʱ���ʽ����")
{

}
string DateReadFormat::toString()const
{
	return what();
}
// �˻�����
AccountException::AccountException(Account* account)
	:account(account),runtime_error(account->getId() + "�˻�����")
{

}
string AccountException::toString() const
{
	return account->getId() + this->what();
}
// ȡǮ����
AccountWithdrawOverException::AccountWithdrawOverException(Account* account)
	:AccountException(account),runtime_error(account->getId()+"�˻�ȡǮ����")
{

}
// �����ʽ����
CommandFormatException::CommandFormatException(string cmd)
	:runtime_error(cmd + "�����ʽ����")
{

}

// �ļ�����
FileNotExistException::FileNotExistException(string path)
	:runtime_error("�޷����ļ�:" + path)
{

}