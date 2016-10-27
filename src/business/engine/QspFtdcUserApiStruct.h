/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QspFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(Qsp_FTDCSTRUCT_H)
#define Qsp_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QspFtdcUserApiDataType.h"

///系统用户登录请求
struct CQspFtdcReqUserLoginField
{
	///交易日
	TQspFtdcDateType	TradingDay;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///密码
	TQspFtdcPasswordType	Password;
	///用户端产品信息
	TQspFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TQspFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TQspFtdcProtocolInfoType	ProtocolInfo;
	///IP地址
	TQspFtdcIPAddressType	IPAddress;
	///Mac地址
	TQspFtdcMacAddressType	MacAddress;
	///数据中心代码
	TQspFtdcDataCenterIDType	DataCenterID;
	///动态密码
	TQspFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TQspFtdcIPAddressType	ClientIPAddress;
};

///系统用户登录应答
struct CQspFtdcRspUserLoginField
{
	///交易日
	TQspFtdcDateType	TradingDay;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
	///登录成功时间
	TQspFtdcTimeType	LoginTime;
	///用户最大本地报单号
	TQspFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TQspFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TQspFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TQspFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TQspFtdcSequenceNoType	UserFlowSize;
};

///用户登出请求
struct CQspFtdcReqUserLogoutField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
};

///用户登出请求
struct CQspFtdcRspUserLogoutField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
};

///强制用户退出
struct CQspFtdcForceUserExitField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
};

///用户口令修改
struct CQspFtdcUserPasswordUpdateField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
	///旧密码
	TQspFtdcPasswordType	OldPassword;
	///新密码
	TQspFtdcPasswordType	NewPassword;
};

///输入报单
struct CQspFtdcInputOrderField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQspFtdcDateType	GTDDate;
	///成交量类型
	TQspFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQspFtdcVolumeType	MinVolume;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///强平原因
	TQspFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQspFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQspFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQspFtdcCustomType	UserCustom;
};

///报单操作
struct CQspFtdcOrderActionField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///本次撤单操作的本地编号
	TQspFtdcUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	TQspFtdcActionFlagType	ActionFlag;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///数量变化
	TQspFtdcVolumeType	VolumeChange;
};

///内存表导出
struct CQspFtdcMemDbField
{
	///内存表名
	TQspFtdcMemTableNameType	MemTableName;
};

///响应信息
struct CQspFtdcRspInfoField
{
	///错误代码
	TQspFtdcErrorIDType	ErrorID;
	///错误信息
	TQspFtdcErrorMsgType	ErrorMsg;
};

///报单查询
struct CQspFtdcQryOrderField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///成交查询
struct CQspFtdcQryTradeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///成交编号
	TQspFtdcTradeIDType	TradeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///合约查询
struct CQspFtdcQryInstrumentField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///产品代码
	TQspFtdcProductIDType	ProductID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///合约查询应答
struct CQspFtdcRspInstrumentField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///品种代码
	TQspFtdcProductIDType	ProductID;
	///品种名称
	TQspFtdcProductNameType	ProductName;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQspFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQspFtdcYearType	DeliveryYear;
	///交割月
	TQspFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TQspFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TQspFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TQspFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TQspFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TQspFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TQspFtdcPriceTickType	PriceTick;
	///币种
	TQspFtdcCurrencyType	Currency;
	///多头限仓
	TQspFtdcVolumeType	LongPosLimit;
	///空头限仓
	TQspFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TQspFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TQspFtdcPriceType	UpperLimitPrice;
	///昨结算
	TQspFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TQspFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TQspFtdcDateType	CreateDate;
	///上市日
	TQspFtdcDateType	OpenDate;
	///到期日
	TQspFtdcDateType	ExpireDate;
	///开始交割日
	TQspFtdcDateType	StartDelivDate;
	///最后交割日
	TQspFtdcDateType	EndDelivDate;
	///挂牌基准价
	TQspFtdcPriceType	BasisPrice;
	///当前是否交易
	TQspFtdcBoolType	IsTrading;
	///基础商品代码
	TQspFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TQspFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TQspFtdcPositionTypeType	PositionType;
	///执行价
	TQspFtdcPriceType	StrikePrice;
	///期权类型
	TQspFtdcOptionsTypeType	OptionsType;
	///汇率
	TQspFtdcRatioType	ExchangeRate;
	///产品类型
	TQspFtdcProductClassType	ProductClass;
	///连接类型
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
};

///合约状态
struct CQspFtdcInstrumentStatusField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///品种代码
	TQspFtdcProductIDType	ProductID;
	///品种名称
	TQspFtdcProductNameType	ProductName;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQspFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQspFtdcYearType	DeliveryYear;
	///交割月
	TQspFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TQspFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TQspFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TQspFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TQspFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TQspFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TQspFtdcPriceTickType	PriceTick;
	///币种
	TQspFtdcCurrencyType	Currency;
	///多头限仓
	TQspFtdcVolumeType	LongPosLimit;
	///空头限仓
	TQspFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TQspFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TQspFtdcPriceType	UpperLimitPrice;
	///昨结算
	TQspFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TQspFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TQspFtdcDateType	CreateDate;
	///上市日
	TQspFtdcDateType	OpenDate;
	///到期日
	TQspFtdcDateType	ExpireDate;
	///开始交割日
	TQspFtdcDateType	StartDelivDate;
	///最后交割日
	TQspFtdcDateType	EndDelivDate;
	///挂牌基准价
	TQspFtdcPriceType	BasisPrice;
	///当前是否交易
	TQspFtdcBoolType	IsTrading;
	///基础商品代码
	TQspFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TQspFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TQspFtdcPositionTypeType	PositionType;
	///执行价
	TQspFtdcPriceType	StrikePrice;
	///期权类型
	TQspFtdcOptionsTypeType	OptionsType;
	///汇率
	TQspFtdcRatioType	ExchangeRate;
	///产品类型
	TQspFtdcProductClassType	ProductClass;
	///连接类型
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
};

///投资者资金查询
struct CQspFtdcQryInvestorAccountField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///投资者资金应答
struct CQspFtdcRspInvestorAccountField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQspFtdcAccountIDType	AccountID;
	///上次结算准备金
	TQspFtdcMoneyType	PreBalance;
	///上日可用资金
	TQspFtdcMoneyType	PreAvailable;
	///入金金额
	TQspFtdcMoneyType	Deposit;
	///出金金额
	TQspFtdcMoneyType	Withdraw;
	///占用保证金
	TQspFtdcMoneyType	Margin;
	///期权权利金收支
	TQspFtdcMoneyType	Premium;
	///手续费
	TQspFtdcMoneyType	Fee;
	///冻结的保证金
	TQspFtdcMoneyType	FrozenMargin;
	///冻结权利金
	TQspFtdcMoneyType	FrozenPremium;
	///冻结手续费
	TQspFtdcMoneyType	FrozenFee;
	///平仓盈亏
	TQspFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TQspFtdcMoneyType	PositionProfit;
	///可用资金
	TQspFtdcMoneyType	Available;
	///结算准备金
	TQspFtdcMoneyType	Balance;
	///多头占用保证金
	TQspFtdcMoneyType	LongMargin;
	///空头占用保证金
	TQspFtdcMoneyType	ShortMargin;
	///多头冻结的保证金
	TQspFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TQspFtdcMoneyType	ShortFrozenMargin;
	///动态权益
	TQspFtdcMoneyType	DynamicRights;
	///风险度
	TQspFtdcMoneyType	Risk;
	///其他费用
	TQspFtdcMoneyType	OtherFee;
	///质押金额
	TQspFtdcMoneyType	Mortgage;
	///币种
	TQspFtdcCurrencyIDType	Currency;
};

///可用投资者查询
struct CQspFtdcQryUserInvestorField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
};

///可用投资者
struct CQspFtdcRspUserInvestorField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///交易编码查询
struct CQspFtdcQryTradingCodeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
};

///交易编码查询
struct CQspFtdcRspTradingCodeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQspFtdcAccountIDType	AccountID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///会员编号
	TQspFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQspFtdcClientIDType	ClientID;
	///客户代码权限
	TQspFtdcTradingRightType	ClientRight;
	///客户类型
	TQspFtdcClientTypeType	ClientType;
	///客户保值类型
	TQspFtdcClientHedgeFlagType	ClientHedgeFlag;
	///是否活跃
	TQspFtdcIsActiveType	IsActive;
};

///交易所查询请求
struct CQspFtdcQryExchangeField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
};

///交易所查询应答
struct CQspFtdcRspExchangeField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TQspFtdcExchangeNameType	ExchangeName;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
};

///投资者持仓查询请求
struct CQspFtdcQryInvestorPositionField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///投资者持仓查询应答
struct CQspFtdcRspInvestorPositionField
{
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///客户代码
	TQspFtdcClientIDType	ClientID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///占用保证金
	TQspFtdcMoneyType	UsedMargin;
	///今持仓量
	TQspFtdcVolumeType	Position;
	///今日持仓成本
	TQspFtdcPriceType	PositionCost;
	///昨持仓量
	TQspFtdcVolumeType	YdPosition;
	///昨日持仓成本
	TQspFtdcMoneyType	YdPositionCost;
	///冻结的保证金
	TQspFtdcMoneyType	FrozenMargin;
	///开仓冻结持仓
	TQspFtdcVolumeType	FrozenPosition;
	///平仓冻结持仓
	TQspFtdcVolumeType	FrozenClosing;
	///冻结的权利金
	TQspFtdcMoneyType	FrozenPremium;
	///最后一笔成交编号
	TQspFtdcTradeIDType	LastTradeID;
	///最后一笔本地报单编号
	TQspFtdcOrderLocalIDType	LastOrderLocalID;
	///币种
	TQspFtdcCurrencyIDType	Currency;
};

///用户查询
struct CQspFtdcQryUserField
{
	///交易用户代码
	TQspFtdcUserIDType	StartUserID;
	///交易用户代码
	TQspFtdcUserIDType	EndUserID;
};

///用户
struct CQspFtdcUserField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///用户登录密码
	TQspFtdcPasswordType	Password;
	///是否活跃
	TQspFtdcIsActiveType	IsActive;
	///用户名称
	TQspFtdcUserNameType	UserName;
	///用户类型
	TQspFtdcUserTypeType	UserType;
	///营业部
	TQspFtdcDepartmentType	Department;
	///授权功能集
	TQspFtdcGrantFuncSetType	GrantFuncSet;
	///修改用户编号
	TQspFtdcUserIDType	SetUserID;
	///操作日期
	TQspFtdcDateType	CommandDate;
	///操作时间
	TQspFtdcTimeType	CommandTime;
};

///投资者手续费率查询
struct CQspFtdcQryInvestorFeeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///投资者手续费率
struct CQspFtdcInvestorFeeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///开仓手续费按比例
	TQspFtdcRatioType	OpenFeeRate;
	///开仓手续费按手数
	TQspFtdcRatioType	OpenFeeAmt;
	///平仓手续费按比例
	TQspFtdcRatioType	OffsetFeeRate;
	///平仓手续费按手数
	TQspFtdcRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	TQspFtdcRatioType	OTFeeRate;
	///平今仓手续费按手数
	TQspFtdcRatioType	OTFeeAmt;
};

///投资者保证金率查询
struct CQspFtdcQryInvestorMarginField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///投资者保证金率
struct CQspFtdcInvestorMarginField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///多头占用保证金按比例
	TQspFtdcRatioType	LongMarginRate;
	///多头保证金按手数
	TQspFtdcRatioType	LongMarginAmt;
	///空头占用保证金按比例
	TQspFtdcRatioType	ShortMarginRate;
	///空头保证金按手数
	TQspFtdcRatioType	ShortMarginAmt;
};

///成交
struct CQspFtdcTradeField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
	///会员编号
	TQspFtdcParticipantIDType	ParticipantID;
	///下单席位号
	TQspFtdcSeatIDType	SeatID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///用户编号
	TQspFtdcUserIDType	UserID;
	///成交编号
	TQspFtdcTradeIDType	TradeID;
	///报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///委托价格
	TQspFtdcPriceType	LimitPrice;
	///成交价格
	TQspFtdcPriceType	TradePrice;
	///成交数量
	TQspFtdcVolumeType	TradeVolume;
	///成交时间
	TQspFtdcTimeType	TradeTime;
	///清算会员编号
	TQspFtdcParticipantIDType	ClearingPartID;
	///系统报单编号
	TQspFtdcSequenceNoType	CombOrderSysID;
	///策略类型
	TQspFtdcPlotTypeType	PlotType;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///手续费
	TQspFtdcMoneyType	Fee;
};

///报单
struct CQspFtdcOrderField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQspFtdcDateType	GTDDate;
	///成交量类型
	TQspFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQspFtdcVolumeType	MinVolume;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///强平原因
	TQspFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQspFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQspFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQspFtdcCustomType	UserCustom;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
	///会员编号
	TQspFtdcParticipantIDType	ParticipantID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///下单席位号
	TQspFtdcSeatIDType	SeatID;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///本地报单编号
	TQspFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TQspFtdcOrderSourceType	OrderSource;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TQspFtdcTimeType	CancelTime;
	///撤单用户编号
	TQspFtdcUserIDType	CancelUserID;
	///今成交数量
	TQspFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQspFtdcVolumeType	VolumeRemain;
	///策略类型
	TQspFtdcPlotTypeType	PlotType;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///手续费
	TQspFtdcMoneyType	Fee;
};

///数据流回退
struct CQspFtdcFlowMessageCancelField
{
	///序列系列号
	TQspFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TQspFtdcDateType	TradingDay;
	///数据中心代码
	TQspFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TQspFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TQspFtdcSequenceNoType	EndSequenceNo;
};

///信息分发
struct CQspFtdcDisseminationField
{
	///序列系列号
	TQspFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TQspFtdcSequenceNoType	SequenceNo;
};

///出入金结果
struct CQspFtdcInvestorAccountDepositResField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQspFtdcAccountIDType	AccountID;
	///资金流水号
	TQspFtdcAccountSeqNoType	AccountSeqNo;
	///金额
	TQspFtdcMoneyType	Amount;
	///出入金方向
	TQspFtdcAccountDirectionType	AmountDirection;
	///可用资金
	TQspFtdcMoneyType	Available;
	///结算准备金
	TQspFtdcMoneyType	Balance;
};

///行情基础属性
struct CQspFtdcMarketDataBaseField
{
	///交易日
	TQspFtdcDateType	TradingDay;
	///结算组代码
	TQspFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQspFtdcSettlementIDType	SettlementID;
	///昨结算
	TQspFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQspFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQspFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQspFtdcRatioType	PreDelta;
};

///行情静态属性
struct CQspFtdcMarketDataStaticField
{
	///今开盘
	TQspFtdcPriceType	OpenPrice;
	///最高价
	TQspFtdcPriceType	HighestPrice;
	///最低价
	TQspFtdcPriceType	LowestPrice;
	///今收盘
	TQspFtdcPriceType	ClosePrice;
	///涨停板价
	TQspFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQspFtdcPriceType	LowerLimitPrice;
	///今结算
	TQspFtdcPriceType	SettlementPrice;
	///今虚实度
	TQspFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CQspFtdcMarketDataLastMatchField
{
	///最新价
	TQspFtdcPriceType	LastPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///成交金额
	TQspFtdcMoneyType	Turnover;
	///持仓量
	TQspFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CQspFtdcMarketDataBestPriceField
{
	///申买价一
	TQspFtdcPriceType	BidPrice1;
	///申买量一
	TQspFtdcVolumeType	BidVolume1;
	///申卖价一
	TQspFtdcPriceType	AskPrice1;
	///申卖量一
	TQspFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CQspFtdcMarketDataBid23Field
{
	///申买价二
	TQspFtdcPriceType	BidPrice2;
	///申买量二
	TQspFtdcVolumeType	BidVolume2;
	///申买价三
	TQspFtdcPriceType	BidPrice3;
	///申买量三
	TQspFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CQspFtdcMarketDataAsk23Field
{
	///申卖价二
	TQspFtdcPriceType	AskPrice2;
	///申卖量二
	TQspFtdcVolumeType	AskVolume2;
	///申卖价三
	TQspFtdcPriceType	AskPrice3;
	///申卖量三
	TQspFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CQspFtdcMarketDataBid45Field
{
	///申买价四
	TQspFtdcPriceType	BidPrice4;
	///申买量四
	TQspFtdcVolumeType	BidVolume4;
	///申买价五
	TQspFtdcPriceType	BidPrice5;
	///申买量五
	TQspFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CQspFtdcMarketDataAsk45Field
{
	///申卖价四
	TQspFtdcPriceType	AskPrice4;
	///申卖量四
	TQspFtdcVolumeType	AskVolume4;
	///申卖价五
	TQspFtdcPriceType	AskPrice5;
	///申卖量五
	TQspFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CQspFtdcMarketDataUpdateTimeField
{
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQspFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQspFtdcMillisecType	UpdateMillisec;
};

///深度行情
struct CQspFtdcDepthMarketDataField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///交易日
	TQspFtdcDateType	TradingDay;
	///结算组代码
	TQspFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQspFtdcSettlementIDType	SettlementID;
	///昨结算
	TQspFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQspFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQspFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQspFtdcRatioType	PreDelta;
	///今开盘
	TQspFtdcPriceType	OpenPrice;
	///最高价
	TQspFtdcPriceType	HighestPrice;
	///最低价
	TQspFtdcPriceType	LowestPrice;
	///今收盘
	TQspFtdcPriceType	ClosePrice;
	///涨停板价
	TQspFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQspFtdcPriceType	LowerLimitPrice;
	///今结算
	TQspFtdcPriceType	SettlementPrice;
	///今虚实度
	TQspFtdcRatioType	CurrDelta;
	///最新价
	TQspFtdcPriceType	LastPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///成交金额
	TQspFtdcMoneyType	Turnover;
	///持仓量
	TQspFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQspFtdcPriceType	BidPrice1;
	///申买量一
	TQspFtdcVolumeType	BidVolume1;
	///申卖价一
	TQspFtdcPriceType	AskPrice1;
	///申卖量一
	TQspFtdcVolumeType	AskVolume1;
	///申买价二
	TQspFtdcPriceType	BidPrice2;
	///申买量二
	TQspFtdcVolumeType	BidVolume2;
	///申买价三
	TQspFtdcPriceType	BidPrice3;
	///申买量三
	TQspFtdcVolumeType	BidVolume3;
	///申卖价二
	TQspFtdcPriceType	AskPrice2;
	///申卖量二
	TQspFtdcVolumeType	AskVolume2;
	///申卖价三
	TQspFtdcPriceType	AskPrice3;
	///申卖量三
	TQspFtdcVolumeType	AskVolume3;
	///申买价四
	TQspFtdcPriceType	BidPrice4;
	///申买量四
	TQspFtdcVolumeType	BidVolume4;
	///申买价五
	TQspFtdcPriceType	BidPrice5;
	///申买量五
	TQspFtdcVolumeType	BidVolume5;
	///申卖价四
	TQspFtdcPriceType	AskPrice4;
	///申卖量四
	TQspFtdcVolumeType	AskVolume4;
	///申卖价五
	TQspFtdcPriceType	AskPrice5;
	///申卖量五
	TQspFtdcVolumeType	AskVolume5;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQspFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQspFtdcMillisecType	UpdateMillisec;
};

///订阅合约的相关信息
struct CQspFtdcSpecificInstrumentField
{
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///套利合约
struct CQspFtdcCombInstrumentField
{
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///套利价格类别
	TQspFtdcCombPriceTypeType	priceType;
	///价格公式
	TQspFtdcformulaType	priceformula;
	///触发类型
	TQspFtdcOrderEnterTypeType	EnterType;
	///当前是否交易
	TQspFtdcBoolType	IsTrading;
	///默认下单数量
	TQspFtdcVolumeType	Volume;
	///最大下单数量
	TQspFtdcVolumeType	MaxVolume;
	///默认触发次数
	TQspFtdcVolumeType	TrigTimes;
	///最大触发次数
	TQspFtdcVolumeType	MaxTrigTimes;
	///腿数
	TQspFtdcVolumeType	LegNum;
	///交易所代码
	TQspFtdcExchangeIDType	Leg1ExchangeID;
	///腿一合约代码
	TQspFtdcInstrumentIDType	Leg1ID;
	///腿一买卖方向
	TQspFtdcDirectionType	Leg1Direction;
	///腿一乘数
	TQspFtdcVolumeMultipleType	Leg1Multiple;
	///腿一价比例
	TQspFtdcRatioType	Leg1PriceRatio;
	///腿一基差价
	TQspFtdcPriceType	Leg1BasisPrice;
	///腿一报入顺序
	TQspFtdcVolumeType	Leg1SeqNo;
	///交易所代码
	TQspFtdcExchangeIDType	Leg2ExchangeID;
	///腿二合约代码
	TQspFtdcInstrumentIDType	Leg2ID;
	///腿二买卖方向
	TQspFtdcDirectionType	Leg2Direction;
	///腿二乘数
	TQspFtdcVolumeMultipleType	Leg2Multiple;
	///腿二价比例
	TQspFtdcRatioType	Leg2PriceRatio;
	///腿二基差价
	TQspFtdcPriceType	Leg2BasisPrice;
	///腿二报入顺序
	TQspFtdcVolumeType	Leg2SeqNo;
	///交易所代码
	TQspFtdcExchangeIDType	Leg3ExchangeID;
	///腿三合约代码
	TQspFtdcInstrumentIDType	Leg3ID;
	///腿三买卖方向
	TQspFtdcDirectionType	Leg3Direction;
	///腿三乘数
	TQspFtdcVolumeMultipleType	Leg3Multiple;
	///腿三价比例
	TQspFtdcRatioType	Leg3PriceRatio;
	///腿三基差价
	TQspFtdcPriceType	Leg3BasisPrice;
	///腿三报入顺序
	TQspFtdcVolumeType	Leg3SeqNo;
	///腿四交易所代码
	TQspFtdcExchangeIDType	Leg4ExchangeID;
	///腿四合约代码
	TQspFtdcInstrumentIDType	Leg4ID;
	///腿四买卖方向
	TQspFtdcDirectionType	Leg4Direction;
	///腿四乘数
	TQspFtdcVolumeMultipleType	Leg4Multiple;
	///腿四价比例
	TQspFtdcRatioType	Leg4PriceRatio;
	///腿四基差价
	TQspFtdcPriceType	Leg4BasisPrice;
	///腿四报入顺序
	TQspFtdcVolumeType	Leg4SeqNo;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///操作标志
	TQspFtdcActionFlagType	ActionFlag;
	///开平循环组合平仓类型
	TQspFtdcOffsetTypeType	OffsetType;
	///腿一操作标志
	TQspFtdcCombLeg1ActionFlagType	Leg1ActionFlag;
	///投资者编号
	TQspFtdcInvestorIDType	Leg1InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg2InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg3InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg4InvestorID;
	///追单次数
	TQspFtdcVolumeType	Leg1Times;
	///追单次数
	TQspFtdcVolumeType	Leg2Times;
	///追单次数
	TQspFtdcVolumeType	Leg3Times;
	///追单次数
	TQspFtdcVolumeType	Leg4Times;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg4OpenDealType;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg1HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg2HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg3HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg4HedgeFlag;
};

///合约查询
struct CQspFtdcQryCombInstrumentField
{
	///合约代码
	TQspFtdcInstrumentIDType	CombInstrumentID;
};

///套利深度行情
struct CQspFtdcCombMarketDataField
{
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQspFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQspFtdcMillisecType	UpdateMillisec;
	///申买价一
	TQspFtdcPriceType	BidPrice1;
	///申买量一
	TQspFtdcVolumeType	BidVolume1;
	///申卖价一
	TQspFtdcPriceType	AskPrice1;
	///申卖量一
	TQspFtdcVolumeType	AskVolume1;
	///最新价
	TQspFtdcPriceType	LastPrice;
	///距收盘时间多少秒暂停操作
	TQspFtdcBoolType	Leg1Gap;
	///距收盘时间多少秒暂停操作
	TQspFtdcBoolType	Leg2Gap;
	///距收盘时间多少秒暂停操作
	TQspFtdcBoolType	Leg3Gap;
	///距收盘时间多少秒暂停操作
	TQspFtdcBoolType	Leg4Gap;
};

///输入报单
struct CQspFtdcCombInputOrderField
{
	///系统报单编号
	TQspFtdcSequenceNoType	CombOrderSysID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///止盈价格
	TQspFtdcPriceType	OffsetPrice;
	///止损价格
	TQspFtdcPriceType	StopPrice;
	///初始委托量
	TQspFtdcVolumeType	Volume;
	///报入量数量
	TQspFtdcVolumeType	SendInVolume;
	///开仓成交数量
	TQspFtdcVolumeType	OpenTradeVolume;
	///开仓成交是否整数
	TQspFtdcBoolType	IsOpenTradeWhole;
	///平仓成交数量
	TQspFtdcVolumeType	OffstTradeVolume;
	///委托触发次数
	TQspFtdcVolumeType	TrigTimes;
	///报单触发次数
	TQspFtdcVolumeType	OrderTimes;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///操作标志
	TQspFtdcActionFlagType	ActionFlag;
	///腿一操作标志
	TQspFtdcCombLeg1ActionFlagType	Leg1ActionFlag;
	///报单类型
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///套利循环类型
	TQspFtdcCombCycleTypeType	CycleType;
	///套利成交状态
	TQspFtdcTradeStatusType	TradeStatus;
	///当前报入腿号
	TQspFtdcVolumeType	PresentLegNo;
	///投资者编号
	TQspFtdcInvestorIDType	Leg1InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg2InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg3InvestorID;
	///投资者编号
	TQspFtdcInvestorIDType	Leg4InvestorID;
	///腿一基差价
	TQspFtdcPriceType	Leg1BasisPrice;
	///腿二基差价
	TQspFtdcPriceType	Leg2BasisPrice;
	///腿三基差价
	TQspFtdcPriceType	Leg3BasisPrice;
	///腿四基差价
	TQspFtdcPriceType	Leg4BasisPrice;
	///腿一报入顺序
	TQspFtdcVolumeType	Leg1SeqNo;
	///腿二报入顺序
	TQspFtdcVolumeType	Leg2SeqNo;
	///腿三报入顺序
	TQspFtdcVolumeType	Leg3SeqNo;
	///腿四报入顺序
	TQspFtdcVolumeType	Leg4SeqNo;
	///腿一乘数
	TQspFtdcVolumeMultipleType	Leg1Multiple;
	///腿二乘数
	TQspFtdcVolumeMultipleType	Leg2Multiple;
	///腿三乘数
	TQspFtdcVolumeMultipleType	Leg3Multiple;
	///腿四乘数
	TQspFtdcVolumeMultipleType	Leg4Multiple;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///开平循环组合平仓类型
	TQspFtdcOffsetTypeType	OffsetType;
	///错单已成交自动平仓
	TQspFtdcBoolType	IsErrorAutoOffset;
	///追单次数
	TQspFtdcVolumeType	Leg1Times;
	///追单次数
	TQspFtdcVolumeType	Leg2Times;
	///追单次数
	TQspFtdcVolumeType	Leg3Times;
	///追单次数
	TQspFtdcVolumeType	Leg4Times;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg4OpenDealType;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg1HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg2HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg3HedgeFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	Leg4HedgeFlag;
};

///套利成交
struct CQspFtdcCombTradeField
{
	///成交编号
	TQspFtdcTradeIDType	TradeID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
	///系统报单编号
	TQspFtdcSequenceNoType	CombOrderSysID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///委托价格
	TQspFtdcPriceType	LimitPrice;
	///成交价格
	TQspFtdcPriceType	TradePrice;
	///成交数量
	TQspFtdcVolumeType	TradeVolume;
	///成交时间
	TQspFtdcTimeType	TradeTime;
};

///套利分腿报单
struct CQspFtdcCombAPIInputOrderField
{
	///委托批次号
	TQspFtdcSequenceNoType	OrderBatchNO;
	///内存表变化类型
	TQspFtdcMemtableChangeTypeType	MemtableChangeType;
	///第几腿
	TQspFtdcVolumeType	LegNo;
	///委托顺序
	TQspFtdcVolumeType	LegSeqNo;
	///相同委托顺序数
	TQspFtdcVolumeType	SameLegSeqNo;
	///腿一操作标志
	TQspFtdcCombLeg1ActionFlagType	Leg1ActionFlag;
	///基差价
	TQspFtdcPriceType	LegBasisPrice;
	///腿乘数
	TQspFtdcVolumeMultipleType	LegMultiple;
	///腿买卖方向
	TQspFtdcDirectionType	LegDirection;
	///腿价比例
	TQspFtdcRatioType	LegPriceRatio;
	///是否套利最后一批
	TQspFtdcBoolType	IsLastLegSeqNo;
	///套利合约代码
	TQspFtdcInstrumentIDType	CombInstrumentID;
	///套利买卖方向
	TQspFtdcDirectionType	CombDirection;
	///委托价格
	TQspFtdcPriceType	CombLimitPrice;
	///套利价格类别
	TQspFtdcCombPriceTypeType	priceType;
	///成交金额
	TQspFtdcMoneyType	Amount;
	///报入数量
	TQspFtdcVolumeType	SendVolume;
	///第一腿报入时已成交量
	TQspFtdcVolumeType	FirstLegTradeVolume;
	///报入错误数量
	TQspFtdcVolumeType	ErrorVolume;
	///第一批次第一笔报单编号
	TQspFtdcOrderSysIDType	OrderSysID1;
	///第一批次第二笔报单编号
	TQspFtdcOrderSysIDType	OrderSysID2;
	///第一批次第三笔报单编号
	TQspFtdcOrderSysIDType	OrderSysID3;
	///开仓委托数量
	TQspFtdcVolumeType	LegOpenOrderVolume;
	///平仓委托数量
	TQspFtdcVolumeType	LegOffsetOrderVolume;
	///开仓成交数量
	TQspFtdcVolumeType	LegOpenTradeVolume;
	///平仓成交数量
	TQspFtdcVolumeType	LegOffsetTradeVolume;
	///成交编号
	TQspFtdcTradeIDType	TradeID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQspFtdcDateType	GTDDate;
	///成交量类型
	TQspFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQspFtdcVolumeType	MinVolume;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///强平原因
	TQspFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQspFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQspFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQspFtdcCustomType	UserCustom;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
	///会员编号
	TQspFtdcParticipantIDType	ParticipantID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///下单席位号
	TQspFtdcSeatIDType	SeatID;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///本地报单编号
	TQspFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TQspFtdcOrderSourceType	OrderSource;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TQspFtdcTimeType	CancelTime;
	///撤单用户编号
	TQspFtdcUserIDType	CancelUserID;
	///今成交数量
	TQspFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQspFtdcVolumeType	VolumeRemain;
	///策略类型
	TQspFtdcPlotTypeType	PlotType;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///手续费
	TQspFtdcMoneyType	Fee;
	///追单次数
	TQspFtdcVolumeType	Leg1Times;
	///追单次数
	TQspFtdcVolumeType	Leg2Times;
	///追单次数
	TQspFtdcVolumeType	Leg3Times;
	///追单次数
	TQspFtdcVolumeType	Leg4Times;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TQspFtdcOpenDealTypeType	Leg4OpenDealType;
};

///历史套利成交查询
struct CQspFtdcQryHisCombTradeField
{
	///开始交易日
	TQspFtdcTradingDayType	BeginTradingDay;
	///结束交易日
	TQspFtdcTradingDayType	EndTradingDay;
	///套利合约代码
	TQspFtdcInstrumentIDType	CombInstrumentID;
	///系统报单编号
	TQspFtdcSequenceNoType	CombOrderSysID;
	///成交编号
	TQspFtdcTradeIDType	TradeID;
};

///历史成交查询
struct CQspFtdcQryHisTradeField
{
	///开始交易日
	TQspFtdcTradingDayType	BeginTradingDay;
	///结束交易日
	TQspFtdcTradingDayType	EndTradingDay;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///成交编号
	TQspFtdcTradeIDType	TradeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
};

///套利消息通知
struct CQspFtdcCombNtyMessageField
{
	///套利合约代码
	TQspFtdcInstrumentIDType	CombInstrumentID;
	///系统报单编号
	TQspFtdcSequenceNoType	CombOrderSysID;
	///第几腿
	TQspFtdcVolumeType	LegNo;
	///委托顺序
	TQspFtdcVolumeType	LegSeqNo;
	///消息摘要
	TQspFtdcAbstractType	Abstract;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
};

///网格交易策略报单请求
struct CQspFtdcGridOrderField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQspFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///用户代码
	TQspFtdcUserIDType	UserID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQspFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQspFtdcPriceType	LimitPrice;
	///数量
	TQspFtdcVolumeType	Volume;
	///有效期类型
	TQspFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQspFtdcDateType	GTDDate;
	///成交量类型
	TQspFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQspFtdcVolumeType	MinVolume;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///强平原因
	TQspFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQspFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQspFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQspFtdcCustomType	UserCustom;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
	///会员编号
	TQspFtdcParticipantIDType	ParticipantID;
	///客户号
	TQspFtdcClientIDType	ClientID;
	///下单席位号
	TQspFtdcSeatIDType	SeatID;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///本地报单编号
	TQspFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TQspFtdcOrderSourceType	OrderSource;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TQspFtdcTimeType	CancelTime;
	///撤单用户编号
	TQspFtdcUserIDType	CancelUserID;
	///今成交数量
	TQspFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQspFtdcVolumeType	VolumeRemain;
	///策略类型
	TQspFtdcPlotTypeType	PlotType;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///手续费
	TQspFtdcMoneyType	Fee;
	///冻结手续费
	TQspFtdcMoneyType	FrozenFee;
	///冻结的保证金
	TQspFtdcMoneyType	FrozenMargin;
	///期权权利金收支
	TQspFtdcMoneyType	FrozenPremium;
	///资金帐号
	TQspFtdcAccountIDType	AccountID;
	///下单用户编号
	TQspFtdcUserIDType	OrderUserID;
	///交易类型
	TQspFtdcTradeTypeType	TradeType;
	///处理标志
	TQspFtdcDealFlagType	DealFlag;
	///委托批次号
	TQspFtdcSequenceNoType	OrderBatchNO;
	///第几腿
	TQspFtdcVolumeType	LegNo;
	///委托顺序
	TQspFtdcVolumeType	LegSeqNo;
	///相同委托顺序数
	TQspFtdcVolumeType	SameLegSeqNo;
	///是否套利最后一批
	TQspFtdcBoolType	IsLastLegSeqNo;
	///是否套利腿的最后一笔
	TQspFtdcBoolType	IsLastSameLegNo;
	///第一批次第一腿第几笔
	TQspFtdcVolumeType	LegSeqNo1LegNoNum;
	///腿一操作标志
	TQspFtdcCombLeg1ActionFlagType	Leg1ActionFlag;
	///基差价
	TQspFtdcPriceType	LegBasisPrice;
	///不再追单
	TQspFtdcBoolType	IsNoCancelOrder;
	///接收客户端时间
	TQspFtdcMillisecType	LocalInsertTime;
	///当前档
	TQspFtdcVolumeType	CurrPot;
	///当前档
	TQspFtdcVolumeType	LastPot;
	///成交状态
	TQspFtdcTradeStatusType	TradeStatus;
	///是否被平仓或撤单
	TQspFtdcBoolType	IsOffset;
	///被平掉的原订单编号
	TQspFtdcOrderSysIDType	OffsetSysID;
	///原购买价格
	TQspFtdcPriceType	OpenPrice;
	///成交价格
	TQspFtdcPriceType	TradePrice;
	///档位价格
	TQspFtdcPriceType	PotPrice;
	///止损状态
	TQspFtdcBoolType	IsStopLoss;
	///该订单是否可以被查找，默认查找
	TQspFtdcIsActiveType	IsActive;
	///报单时间
	TQspFtdcMillisecType	OrderTime;
	///备注
	TQspFtdcCustomType	Comment;
	///内存表变化类型
	TQspFtdcMemtableChangeTypeType	MemtableChangeType;
};

///连接管理
struct CQspFtdcAPILinkField
{
	///连接编号
	TQspFtdcFrontIDType	LinkID;
	///前台交易用户代码
	TQspFtdcUserIDType	UserID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///后台投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///密码
	TQspFtdcPasswordType	Password;
	///是否活跃
	TQspFtdcBoolType	IsActive;
	///环境编号
	TQspFtdcEnvNoType	EnvNo;
	///是否接收行情
	TQspFtdcBoolType	IsMrkActive;
	///是否只接收自选合约行情QuotCrtList 1=是
	TQspFtdcBoolType	IsRcvQuotList;
};

///各市场开闭市时间
struct CQspFtdcMarketTimeField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///开市时间
	TQspFtdcTimeType	OpenTime;
	///闭市时间
	TQspFtdcTimeType	CloseTime;
	///距离开市可以报单时间
	TQspFtdcTimeType	GapOpen;
	///距离闭市可以报盘时间
	TQspFtdcTimeType	GapClose;
};

///做多做空策略录入
struct CQspFtdcLongShortPlotInputField
{
	///多空策略类型
	TQspFtdcLongShortPlotTypeType	LongShortPlotType;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略报价,报入不能修改
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///点距：最小报价的数量
	TQspFtdcVolumeType	Range;
	///档数
	TQspFtdcVolumeType	Grade;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///启动时间
	TQspFtdcTimeType	StartTime;
	///停止时间
	TQspFtdcTimeType	EndTime;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///首笔报单促发方式：支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///最大报单数量
	TQspFtdcVolumeType	MaxQty;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///做多做空策略
struct CQspFtdcLongShortPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///多空策略类型
	TQspFtdcLongShortPlotTypeType	LongShortPlotType;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略报价,报入不能修改
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///点距：最小报价的数量
	TQspFtdcVolumeType	Range;
	///档数
	TQspFtdcVolumeType	Grade;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///启动时间
	TQspFtdcTimeType	StartTime;
	///停止时间
	TQspFtdcTimeType	EndTime;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///首笔报单促发方式：支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///最大报单数量
	TQspFtdcVolumeType	MaxQty;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///当前档
	TQspFtdcVolumeType	CurrPot;
	///上一档
	TQspFtdcVolumeType	PrePot;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///是否促发首次报单
	TQspFtdcBoolType	IsSendFirst;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///做多做空策略修改
struct CQspFtdcLongShortPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///档数
	TQspFtdcVolumeType	Grade;
	///止损价
	TQspFtdcPriceType	StopPrice;
	///启动时间
	TQspFtdcTimeType	StartTime;
	///停止时间
	TQspFtdcTimeType	EndTime;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///最大报单数量
	TQspFtdcVolumeType	MaxQty;
};

///做多做空策略查询请求
struct CQspFtdcQryLongShortPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///基础数据查询应答
struct CQspFtdcQueryBaseFinishField
{
	///客户端经纪公司编号
	TQspFtdcBrokerIDType	FrontBrokerID;
	///客户端前台交易用户代码
	TQspFtdcUserIDType	FrontUserID;
	///交易所经纪公司编号
	TQspFtdcBrokerIDType	BackBrokerID;
	///交易所前台交易用户代码
	TQspFtdcUserIDType	BackUserID;
	///密码
	TQspFtdcPasswordType	Password;
	///连接类型
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
	///交易或者行情
	TQspFtdcBoolType	TradeOrMarket;
	///前置编号
	TQspFtdcFrontIDType	FrontID;
	///会话编号
	TQspFtdcSessionIDType	SessionID;
	///交易日
	TQspFtdcTradingDayType	TradingDay;
};

///冰山订单输入请求
struct CQspFtdcIcebergPlotInputField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///实际最大报单数量
	TQspFtdcVolumeType	MaxQty;
	///实际最小报单数量
	TQspFtdcVolumeType	MinQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///冰山订单输入应答
struct CQspFtdcIcebergPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///实际最大报单数量
	TQspFtdcVolumeType	MaxQty;
	///实际最小报单数量
	TQspFtdcVolumeType	MinQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TQspFtdcBoolType	IsSendFirst;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///冰山订单策略修改
struct CQspFtdcIcebergPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///实际最大报单数量
	TQspFtdcVolumeType	MaxQty;
	///实际最小报单数量
	TQspFtdcVolumeType	MinQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///冰山订单查询请求
struct CQspFtdcQryIcebergPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///幽灵订单查询请求
struct CQspFtdcGhostPlotInputField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///触发报单价格
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///最小触发报单数量
	TQspFtdcVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///幽灵订单查询
struct CQspFtdcGhostPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///触发报单价格
	TQspFtdcPriceType	OrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///最小触发报单数量
	TQspFtdcVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TQspFtdcBoolType	IsSendFirst;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///幽灵订单策略修改
struct CQspFtdcGhostPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///支持限价和市价
	TQspFtdcOrderPriceTypeType	OrderPriceType;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///最小触发报单数量
	TQspFtdcVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///幽灵订单查询请求
struct CQspFtdcQryGhostPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///盯盘订单查询请求
struct CQspFtdcPegPlotInputField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///最大委托价
	TQspFtdcPriceType	MaxOrderPrice;
	///最小委托价
	TQspFtdcPriceType	MinOrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///盯盘订单查询
struct CQspFtdcPegPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///最大委托价
	TQspFtdcPriceType	MaxOrderPrice;
	///最小委托价
	TQspFtdcPriceType	MinOrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TQspFtdcBoolType	IsSendFirst;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///盯盘订单策略修改
struct CQspFtdcPegPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///最大委托价
	TQspFtdcPriceType	MaxOrderPrice;
	///最小委托价
	TQspFtdcPriceType	MinOrderPrice;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///盯盘订单查询请求
struct CQspFtdcQryPegPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///TWap订单查询请求
struct CQspFtdcTWapPlotInputField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///拆分次数
	TQspFtdcVolumeType	NumberOfWaves;
	///在拆单后数量不满足报单数量是否自动处理
	TQspFtdcBoolType	IsAutoWaves;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///参考委托价
	TQspFtdcPriceType	ReffPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///委托间隔时间
	TQspFtdcVolumeType	WaitDelay;
	///撤单确认时间
	TQspFtdcVolumeType	CancelDelay;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///TWap订单查询
struct CQspFtdcTWapPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///拆分次数
	TQspFtdcVolumeType	NumberOfWaves;
	///在拆单后数量不满足报单数量是否自动处理
	TQspFtdcBoolType	IsAutoWaves;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///参考委托价
	TQspFtdcPriceType	ReffPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///委托间隔时间
	TQspFtdcVolumeType	WaitDelay;
	///撤单确认时间
	TQspFtdcVolumeType	CancelDelay;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TQspFtdcBoolType	IsSendFirst;
	///最小报单数量
	TQspFtdcVolumeType	MinLimitOrderVolume;
	///最大报单数量
	TQspFtdcVolumeType	MaxLimitOrderVolume;
	///最新价
	TQspFtdcPriceType	LastPrice;
	///卖一价
	TQspFtdcPriceType	AskPrice;
	///买一价
	TQspFtdcPriceType	BidPrice;
	///上次报单时间
	TQspFtdcMillisecType	LastOrderTime;
	///上次撤单时间
	TQspFtdcMillisecType	LastCancelTime;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///TWap订单策略修改
struct CQspFtdcTWapPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///参考委托价
	TQspFtdcPriceType	ReffPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///委托间隔时间
	TQspFtdcVolumeType	WaitDelay;
	///撤单确认时间
	TQspFtdcVolumeType	CancelDelay;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///TWap订单查询请求
struct CQspFtdcQryTWapPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///MIT和Stop订单查询请求
struct CQspFtdcMITStopPlotInputField
{
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///最小触发量
	TQspFtdcVolumeType	MinTrigQty;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///触发委托价
	TQspFtdcPriceType	TrigPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///策略报单类型
	TQspFtdcMITStopTypeType	MITStopType;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
};

///MIT和Stop订单查询
struct CQspFtdcMITStopPlotField
{
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///插入日期
	TQspFtdcDateType	InsertDate;
	///插入时间
	TQspFtdcTimeType	InsertTime;
	///修改日期
	TQspFtdcDateType	ModifyDate;
	///修改时间
	TQspFtdcTimeType	ModifyTime;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///最小触发量
	TQspFtdcVolumeType	MinTrigQty;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///触发委托价
	TQspFtdcPriceType	TrigPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///策略报单类型
	TQspFtdcMITStopTypeType	MITStopType;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///报单状态
	TQspFtdcOrderStatusType	OrderStatus;
	///持仓成本
	TQspFtdcMoneyType	PositionCost;
	///买成交剩余量
	TQspFtdcVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TQspFtdcVolumeType	SellRemainVolume;
	///买冻结数量
	TQspFtdcVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TQspFtdcVolumeType	FrozenSellVolume;
	///是否达到触发价，达到触发价下次开始发单
	TQspFtdcBoolType	IsSendFirst;
	///最小报单数量
	TQspFtdcVolumeType	MinLimitOrderVolume;
	///最大报单数量
	TQspFtdcVolumeType	MaxLimitOrderVolume;
	///最新价
	TQspFtdcPriceType	LastPrice;
	///卖一价
	TQspFtdcPriceType	AskPrice;
	///买一价
	TQspFtdcPriceType	BidPrice;
	///浮动盈亏
	TQspFtdcMoneyType	FloatMoney;
};

///MIT和Stop订单策略修改
struct CQspFtdcMITStopPlotActionField
{
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQspFtdcDirectionType	Direction;
	///投机套保标志
	TQspFtdcHedgeFlagType	HedgeFlag;
	///开平标志
	TQspFtdcOffsetFlagType	OffsetFlag;
	///最小触发量
	TQspFtdcVolumeType	MinTrigQty;
	///盯盘类型
	TQspFtdcReffPriceTypeType	ReffPriceType;
	///触发委托价
	TQspFtdcPriceType	TrigPrice;
	///价差
	TQspFtdcPriceType	PriceDiff;
	///报单数量
	TQspFtdcVolumeType	Volume;
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///MIT和Stop订单查询请求
struct CQspFtdcQryMITStopPlotField
{
	///登录经纪公司编号
	TQspFtdcBrokerIDType	LogBrokerID;
	///登录用户代码
	TQspFtdcUserIDType	LogUserID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///策略执行状态
	TQspFtdcPlotStatusTypeType	Status;
	///投资者编号
	TQspFtdcInvestorIDType	InvestorID;
};

///订阅的行情列表
struct CQspFtdcSubMarketQuotoListField
{
	///连接编号
	TQspFtdcFrontIDType	LinkID;
	///连接类型,QDP,QDAM,CTP
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
	///交易所代码
	TQspFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQspFtdcInstrumentIDType	InstrumentID;
	///是否订阅
	TQspFtdcBoolType	IsActive;
};

///对应各环境连接管理器
struct CQspFtdcEnvManagerField
{
	///环境编号
	TQspFtdcEnvNoType	EnvNo;
	///环境名称
	TQspFtdcShortNameType	EnvName;
	///环境描述
	TQspFtdcLongNameType	EnvDesc;
	///连接类型
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
	///连接地址
	TQspFtdcTCPAddressType	TradeAddress;
	///连接地址
	TQspFtdcTCPAddressType	MarketAddress;
	///订阅主题号
	TQspFtdcTopicIDType	TopicID;
};

///连接管理
struct CQspFtdcAPIInnerLinkField
{
	///连接编号
	TQspFtdcFrontIDType	LinkID;
	///前台交易用户代码
	TQspFtdcUserIDType	UserID;
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///后台投资者编号
	TQspFtdcInvestorIDType	InvestorID;
	///密码
	TQspFtdcPasswordType	Password;
	///是否活跃
	TQspFtdcBoolType	IsActive;
	///环境编号
	TQspFtdcEnvNoType	EnvNo;
	///是否接收行情
	TQspFtdcBoolType	IsMrkActive;
	///是否只接收自选合约行情QuotCrtList 1=是
	TQspFtdcBoolType	IsRcvQuotList;
	///连接类型
	TQspFtdcAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TQspFtdcLinkTypeType	LinkType;
	///连接地址
	TQspFtdcTCPAddressType	TradeAddress;
	///连接地址
	TQspFtdcTCPAddressType	MarketAddress;
	///订阅主题号
	TQspFtdcTopicIDType	TopicID;
};

///策略消息通知
struct CQspFtdcPlotNtyMessageField
{
	///经纪公司编号
	TQspFtdcBrokerIDType	BrokerID;
	///策略执行编号
	TQspFtdcOrderLocalIDType	PlotID;
	///错误代码
	TQspFtdcErrorIDType	ErrorID;
	///消息摘要
	TQspFtdcAbstractType	Abstract;
};



#endif
