#include "error.h"
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": ʱ���ʽ����")
{

}
WithdrawOver::WithdrawOver() 
	:runtime_error("�˻�ȡǮ����")
{

}

AccountWithdrawOverBalance::AccountWithdrawOverBalance()
	:WithdrawOver(),runtime_error("�����˻�ȡǮ�������")
{

}
AccountWithdrawOverCredit::AccountWithdrawOverCredit()
	:WithdrawOver(), runtime_error("�����˻�ȡǮ�������ö��")
{

}