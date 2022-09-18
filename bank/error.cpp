#include "error.h"
DateReadFormat::DateReadFormat(string str)
	:runtime_error(str+": 时间格式错误")
{

}
WithdrawOver::WithdrawOver() 
	:runtime_error("账户取钱错误")
{

}

AccountWithdrawOverBalance::AccountWithdrawOverBalance()
	:WithdrawOver(),runtime_error("储蓄账户取钱超过余额")
{

}
AccountWithdrawOverCredit::AccountWithdrawOverCredit()
	:WithdrawOver(), runtime_error("信用账户取钱超过信用额度")
{

}