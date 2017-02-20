/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file UserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(STRUCT_H)
#define STRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UserApiDataType.h"

///系统用户登录请求
struct CReqUserLoginField
{
	///交易日
	TDateType	TradingDay;
	///交易用户代码
	TUserIDType	UserID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///密码
	TPasswordType	Password;
	///用户端产品信息
	TProductInfoType	UserProductInfo;
	///接口端产品信息
	TProductInfoType	InterfaceProductInfo;
	///协议信息
	TProtocolInfoType	ProtocolInfo;
	///IP地址
	TIPAddressType	IPAddress;
	///Mac地址
	TMacAddressType	MacAddress;
	///数据中心代码
	TDataCenterIDType	DataCenterID;
	///动态密码
	TPasswordType	OneTimePassword;
	///终端IP地址
	TIPAddressType	ClientIPAddress;
};

///系统用户登录应答
struct CRspUserLoginField
{
	///交易日
	TDateType	TradingDay;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
	///登录成功时间
	TTimeType	LoginTime;
	///用户最大本地报单号
	TUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TSequenceNoType	UserFlowSize;
};

///用户登出请求
struct CReqUserLogoutField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
};

///用户登出请求
struct CRspUserLogoutField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
};

///强制用户退出
struct CForceUserExitField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
};

///用户口令修改
struct CUserPasswordUpdateField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
	///旧密码
	TPasswordType	OldPassword;
	///新密码
	TPasswordType	NewPassword;
};

///输入报单
struct CInputOrderField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///系统报单编号
	TOrderSysIDType	OrderSysID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///用户代码
	TUserIDType	UserID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TDirectionType	Direction;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///价格
	TPriceType	LimitPrice;
	///数量
	TVolumeType	Volume;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///GTD日期
	TDateType	GTDDate;
	///成交量类型
	TVolumeConditionType	VolumeCondition;
	///最小成交量
	TVolumeType	MinVolume;
	///止损价
	TPriceType	StopPrice;
	///强平原因
	TForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TBoolType	IsAutoSuspend;
	///业务单元
	TBusinessUnitType	BusinessUnit;
	///用户自定义域
	TCustomType	UserCustom;
};

///报单操作
struct COrderActionField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///报单编号
	TOrderSysIDType	OrderSysID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///用户代码
	TUserIDType	UserID;
	///本次撤单操作的本地编号
	TUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	TUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	TActionFlagType	ActionFlag;
	///价格
	TPriceType	LimitPrice;
	///数量变化
	TVolumeType	VolumeChange;
};

///内存表导出
struct CMemDbField
{
	///内存表名
	TMemTableNameType	MemTableName;
};

///响应信息
struct CRspInfoField
{
	///错误代码
	TErrorIDType	ErrorID;
	///错误信息
	TErrorMsgType	ErrorMsg;
};

///报单查询
struct CQryOrderField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///报单编号
	TOrderSysIDType	OrderSysID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///成交查询
struct CQryTradeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///成交编号
	TTradeIDType	TradeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///合约查询
struct CQryInstrumentField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///产品代码
	TProductIDType	ProductID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///合约查询应答
struct CRspInstrumentField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///品种代码
	TProductIDType	ProductID;
	///品种名称
	TProductNameType	ProductName;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///合约名称
	TInstrumentNameType	InstrumentName;
	///交割年份
	TYearType	DeliveryYear;
	///交割月
	TMonthType	DeliveryMonth;
	///限价单最大下单量
	TVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TVolumeType	MinMarketOrderVolume;
	///数量乘数
	TVolumeMultipleType	VolumeMultiple;
	///报价单位
	TPriceTickType	PriceTick;
	///币种
	TCurrencyType	Currency;
	///多头限仓
	TVolumeType	LongPosLimit;
	///空头限仓
	TVolumeType	ShortPosLimit;
	///跌停板价
	TPriceType	LowerLimitPrice;
	///涨停板价
	TPriceType	UpperLimitPrice;
	///昨结算
	TPriceType	PreSettlementPrice;
	///合约交易状态
	TInstrumentStatusType	InstrumentStatus;
	///创建日
	TDateType	CreateDate;
	///上市日
	TDateType	OpenDate;
	///到期日
	TDateType	ExpireDate;
	///开始交割日
	TDateType	StartDelivDate;
	///最后交割日
	TDateType	EndDelivDate;
	///挂牌基准价
	TPriceType	BasisPrice;
	///当前是否交易
	TBoolType	IsTrading;
	///基础商品代码
	TInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TPositionTypeType	PositionType;
	///执行价
	TPriceType	StrikePrice;
	///期权类型
	TOptionsTypeType	OptionsType;
	///汇率
	TRatioType	ExchangeRate;
	///产品类型
	TProductClassType	ProductClass;
	///连接类型
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
};

///合约状态
struct CInstrumentStatusField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///品种代码
	TProductIDType	ProductID;
	///品种名称
	TProductNameType	ProductName;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///合约名称
	TInstrumentNameType	InstrumentName;
	///交割年份
	TYearType	DeliveryYear;
	///交割月
	TMonthType	DeliveryMonth;
	///限价单最大下单量
	TVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TVolumeType	MinMarketOrderVolume;
	///数量乘数
	TVolumeMultipleType	VolumeMultiple;
	///报价单位
	TPriceTickType	PriceTick;
	///币种
	TCurrencyType	Currency;
	///多头限仓
	TVolumeType	LongPosLimit;
	///空头限仓
	TVolumeType	ShortPosLimit;
	///跌停板价
	TPriceType	LowerLimitPrice;
	///涨停板价
	TPriceType	UpperLimitPrice;
	///昨结算
	TPriceType	PreSettlementPrice;
	///合约交易状态
	TInstrumentStatusType	InstrumentStatus;
	///创建日
	TDateType	CreateDate;
	///上市日
	TDateType	OpenDate;
	///到期日
	TDateType	ExpireDate;
	///开始交割日
	TDateType	StartDelivDate;
	///最后交割日
	TDateType	EndDelivDate;
	///挂牌基准价
	TPriceType	BasisPrice;
	///当前是否交易
	TBoolType	IsTrading;
	///基础商品代码
	TInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TPositionTypeType	PositionType;
	///执行价
	TPriceType	StrikePrice;
	///期权类型
	TOptionsTypeType	OptionsType;
	///汇率
	TRatioType	ExchangeRate;
	///产品类型
	TProductClassType	ProductClass;
	///连接类型
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
};

///投资者资金查询
struct CQryInvestorAccountField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///投资者资金应答
struct CRspInvestorAccountField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///资金帐号
	TAccountIDType	AccountID;
	///上次结算准备金
	TMoneyType	PreBalance;
	///上日可用资金
	TMoneyType	PreAvailable;
	///入金金额
	TMoneyType	Deposit;
	///出金金额
	TMoneyType	Withdraw;
	///占用保证金
	TMoneyType	Margin;
	///期权权利金收支
	TMoneyType	Premium;
	///手续费
	TMoneyType	Fee;
	///冻结的保证金
	TMoneyType	FrozenMargin;
	///冻结权利金
	TMoneyType	FrozenPremium;
	///冻结手续费
	TMoneyType	FrozenFee;
	///平仓盈亏
	TMoneyType	CloseProfit;
	///持仓盈亏
	TMoneyType	PositionProfit;
	///可用资金
	TMoneyType	Available;
	///结算准备金
	TMoneyType	Balance;
	///多头占用保证金
	TMoneyType	LongMargin;
	///空头占用保证金
	TMoneyType	ShortMargin;
	///多头冻结的保证金
	TMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TMoneyType	ShortFrozenMargin;
	///动态权益
	TMoneyType	DynamicRights;
	///风险度
	TMoneyType	Risk;
	///其他费用
	TMoneyType	OtherFee;
	///质押金额
	TMoneyType	Mortgage;
	///币种
	TCurrencyIDType	Currency;
};

///可用投资者查询
struct CQryUserInvestorField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
};

///可用投资者
struct CRspUserInvestorField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///交易编码查询
struct CQryTradingCodeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///交易所代码
	TExchangeIDType	ExchangeID;
};

///交易编码查询
struct CRspTradingCodeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///资金帐号
	TAccountIDType	AccountID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///会员编号
	TParticipantIDType	ParticipantID;
	///客户代码
	TClientIDType	ClientID;
	///客户代码权限
	TTradingRightType	ClientRight;
	///客户类型
	TClientTypeType	ClientType;
	///客户保值类型
	TClientHedgeFlagType	ClientHedgeFlag;
	///是否活跃
	TIsActiveType	IsActive;
};

///交易所查询请求
struct CQryExchangeField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
};

///交易所查询应答
struct CRspExchangeField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///交易所名称
	TExchangeNameType	ExchangeName;
	///交易日
	TTradingDayType	TradingDay;
};

///投资者持仓查询请求
struct CQryInvestorPositionField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///投资者持仓查询应答
struct CRspInvestorPositionField
{
	///投资者编号
	TInvestorIDType	InvestorID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///客户代码
	TClientIDType	ClientID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///占用保证金
	TMoneyType	UsedMargin;
	///今持仓量
	TVolumeType	Position;
	///今日持仓成本
	TPriceType	PositionCost;
	///昨持仓量
	TVolumeType	YdPosition;
	///昨日持仓成本
	TMoneyType	YdPositionCost;
	///冻结的保证金
	TMoneyType	FrozenMargin;
	///开仓冻结持仓
	TVolumeType	FrozenPosition;
	///平仓冻结持仓
	TVolumeType	FrozenClosing;
	///冻结的权利金
	TMoneyType	FrozenPremium;
	///最后一笔成交编号
	TTradeIDType	LastTradeID;
	///最后一笔本地报单编号
	TOrderLocalIDType	LastOrderLocalID;
	///币种
	TCurrencyIDType	Currency;
};

///用户查询
struct CQryUserField
{
	///交易用户代码
	TUserIDType	StartUserID;
	///交易用户代码
	TUserIDType	EndUserID;
};

///用户
struct CUserField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///用户登录密码
	TPasswordType	Password;
	///是否活跃
	TIsActiveType	IsActive;
	///用户名称
	TUserNameType	UserName;
	///用户类型
	TUserTypeType	UserType;
	///营业部
	TDepartmentType	Department;
	///授权功能集
	TGrantFuncSetType	GrantFuncSet;
	///修改用户编号
	TUserIDType	SetUserID;
	///操作日期
	TDateType	CommandDate;
	///操作时间
	TTimeType	CommandTime;
};

///投资者手续费率查询
struct CQryInvestorFeeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///投资者手续费率
struct CInvestorFeeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///客户号
	TClientIDType	ClientID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///开仓手续费按比例
	TRatioType	OpenFeeRate;
	///开仓手续费按手数
	TRatioType	OpenFeeAmt;
	///平仓手续费按比例
	TRatioType	OffsetFeeRate;
	///平仓手续费按手数
	TRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	TRatioType	OTFeeRate;
	///平今仓手续费按手数
	TRatioType	OTFeeAmt;
};

///投资者保证金率查询
struct CQryInvestorMarginField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///投资者保证金率
struct CInvestorMarginField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///客户号
	TClientIDType	ClientID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///多头占用保证金按比例
	TRatioType	LongMarginRate;
	///多头保证金按手数
	TRatioType	LongMarginAmt;
	///空头占用保证金按比例
	TRatioType	ShortMarginRate;
	///空头保证金按手数
	TRatioType	ShortMarginAmt;
};

///成交
struct CTradeField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///交易日
	TTradingDayType	TradingDay;
	///会员编号
	TParticipantIDType	ParticipantID;
	///下单席位号
	TSeatIDType	SeatID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///客户号
	TClientIDType	ClientID;
	///用户编号
	TUserIDType	UserID;
	///成交编号
	TTradeIDType	TradeID;
	///报单编号
	TOrderSysIDType	OrderSysID;
	///本地报单编号
	TUserOrderLocalIDType	UserOrderLocalID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///委托价格
	TPriceType	LimitPrice;
	///成交价格
	TPriceType	TradePrice;
	///成交数量
	TVolumeType	TradeVolume;
	///成交时间
	TTimeType	TradeTime;
	///清算会员编号
	TParticipantIDType	ClearingPartID;
	///系统报单编号
	TSequenceNoType	CombOrderSysID;
	///策略类型
	TPlotTypeType	PlotType;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///手续费
	TMoneyType	Fee;
};

///报单
struct COrderField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///系统报单编号
	TOrderSysIDType	OrderSysID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///用户代码
	TUserIDType	UserID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TDirectionType	Direction;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///价格
	TPriceType	LimitPrice;
	///数量
	TVolumeType	Volume;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///GTD日期
	TDateType	GTDDate;
	///成交量类型
	TVolumeConditionType	VolumeCondition;
	///最小成交量
	TVolumeType	MinVolume;
	///止损价
	TPriceType	StopPrice;
	///强平原因
	TForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TBoolType	IsAutoSuspend;
	///业务单元
	TBusinessUnitType	BusinessUnit;
	///用户自定义域
	TCustomType	UserCustom;
	///交易日
	TTradingDayType	TradingDay;
	///会员编号
	TParticipantIDType	ParticipantID;
	///客户号
	TClientIDType	ClientID;
	///下单席位号
	TSeatIDType	SeatID;
	///插入时间
	TTimeType	InsertTime;
	///本地报单编号
	TOrderLocalIDType	OrderLocalID;
	///报单来源
	TOrderSourceType	OrderSource;
	///报单状态
	TOrderStatusType	OrderStatus;
	///撤销时间
	TTimeType	CancelTime;
	///撤单用户编号
	TUserIDType	CancelUserID;
	///今成交数量
	TVolumeType	VolumeTraded;
	///剩余数量
	TVolumeType	VolumeRemain;
	///策略类型
	TPlotTypeType	PlotType;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///手续费
	TMoneyType	Fee;
};

///数据流回退
struct CFlowMessageCancelField
{
	///序列系列号
	TSequenceSeriesType	SequenceSeries;
	///交易日
	TDateType	TradingDay;
	///数据中心代码
	TDataCenterIDType	DataCenterID;
	///回退起始序列号
	TSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TSequenceNoType	EndSequenceNo;
};

///信息分发
struct CDisseminationField
{
	///序列系列号
	TSequenceSeriesType	SequenceSeries;
	///序列号
	TSequenceNoType	SequenceNo;
};

///出入金结果
struct CInvestorAccountDepositResField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///资金帐号
	TAccountIDType	AccountID;
	///资金流水号
	TAccountSeqNoType	AccountSeqNo;
	///金额
	TMoneyType	Amount;
	///出入金方向
	TAccountDirectionType	AmountDirection;
	///可用资金
	TMoneyType	Available;
	///结算准备金
	TMoneyType	Balance;
};

///行情基础属性
struct CMarketDataBaseField
{
	///交易日
	TDateType	TradingDay;
	///结算组代码
	TSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TSettlementIDType	SettlementID;
	///昨结算
	TPriceType	PreSettlementPrice;
	///昨收盘
	TPriceType	PreClosePrice;
	///昨持仓量
	TLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TRatioType	PreDelta;
};

///行情静态属性
struct CMarketDataStaticField
{
	///今开盘
	TPriceType	OpenPrice;
	///最高价
	TPriceType	HighestPrice;
	///最低价
	TPriceType	LowestPrice;
	///今收盘
	TPriceType	ClosePrice;
	///涨停板价
	TPriceType	UpperLimitPrice;
	///跌停板价
	TPriceType	LowerLimitPrice;
	///今结算
	TPriceType	SettlementPrice;
	///今虚实度
	TRatioType	CurrDelta;
};

///行情最新成交属性
struct CMarketDataLastMatchField
{
	///最新价
	TPriceType	LastPrice;
	///数量
	TVolumeType	Volume;
	///成交金额
	TMoneyType	Turnover;
	///持仓量
	TLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CMarketDataBestPriceField
{
	///申买价一
	TPriceType	BidPrice1;
	///申买量一
	TVolumeType	BidVolume1;
	///申卖价一
	TPriceType	AskPrice1;
	///申卖量一
	TVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CMarketDataBid23Field
{
	///申买价二
	TPriceType	BidPrice2;
	///申买量二
	TVolumeType	BidVolume2;
	///申买价三
	TPriceType	BidPrice3;
	///申买量三
	TVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CMarketDataAsk23Field
{
	///申卖价二
	TPriceType	AskPrice2;
	///申卖量二
	TVolumeType	AskVolume2;
	///申卖价三
	TPriceType	AskPrice3;
	///申卖量三
	TVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CMarketDataBid45Field
{
	///申买价四
	TPriceType	BidPrice4;
	///申买量四
	TVolumeType	BidVolume4;
	///申买价五
	TPriceType	BidPrice5;
	///申买量五
	TVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CMarketDataAsk45Field
{
	///申卖价四
	TPriceType	AskPrice4;
	///申卖量四
	TVolumeType	AskVolume4;
	///申卖价五
	TPriceType	AskPrice5;
	///申卖量五
	TVolumeType	AskVolume5;
};

///行情更新时间属性
struct CMarketDataUpdateTimeField
{
	///合约代码
	TInstrumentIDType	InstrumentID;
	///最后修改时间
	TTimeType	UpdateTime;
	///最后修改毫秒
	TMillisecType	UpdateMillisec;
};

///深度行情
struct CDepthMarketDataField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///交易日
	TDateType	TradingDay;
	///结算组代码
	TSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TSettlementIDType	SettlementID;
	///昨结算
	TPriceType	PreSettlementPrice;
	///昨收盘
	TPriceType	PreClosePrice;
	///昨持仓量
	TLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TRatioType	PreDelta;
	///今开盘
	TPriceType	OpenPrice;
	///最高价
	TPriceType	HighestPrice;
	///最低价
	TPriceType	LowestPrice;
	///今收盘
	TPriceType	ClosePrice;
	///涨停板价
	TPriceType	UpperLimitPrice;
	///跌停板价
	TPriceType	LowerLimitPrice;
	///今结算
	TPriceType	SettlementPrice;
	///今虚实度
	TRatioType	CurrDelta;
	///最新价
	TPriceType	LastPrice;
	///数量
	TVolumeType	Volume;
	///成交金额
	TMoneyType	Turnover;
	///持仓量
	TLargeVolumeType	OpenInterest;
	///申买价一
	TPriceType	BidPrice1;
	///申买量一
	TVolumeType	BidVolume1;
	///申卖价一
	TPriceType	AskPrice1;
	///申卖量一
	TVolumeType	AskVolume1;
	///申买价二
	TPriceType	BidPrice2;
	///申买量二
	TVolumeType	BidVolume2;
	///申买价三
	TPriceType	BidPrice3;
	///申买量三
	TVolumeType	BidVolume3;
	///申卖价二
	TPriceType	AskPrice2;
	///申卖量二
	TVolumeType	AskVolume2;
	///申卖价三
	TPriceType	AskPrice3;
	///申卖量三
	TVolumeType	AskVolume3;
	///申买价四
	TPriceType	BidPrice4;
	///申买量四
	TVolumeType	BidVolume4;
	///申买价五
	TPriceType	BidPrice5;
	///申买量五
	TVolumeType	BidVolume5;
	///申卖价四
	TPriceType	AskPrice4;
	///申卖量四
	TVolumeType	AskVolume4;
	///申卖价五
	TPriceType	AskPrice5;
	///申卖量五
	TVolumeType	AskVolume5;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///最后修改时间
	TTimeType	UpdateTime;
	///最后修改毫秒
	TMillisecType	UpdateMillisec;
};

///订阅合约的相关信息
struct CSpecificInstrumentField
{
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///套利合约
struct CCombInstrumentField
{
	///合约代码
	TInstrumentIDType	InstrumentID;
	///套利价格类别
	TCombPriceTypeType	priceType;
	///价格公式
	TformulaType	priceformula;
	///触发类型
	TOrderEnterTypeType	EnterType;
	///当前是否交易
	TBoolType	IsTrading;
	///默认下单数量
	TVolumeType	Volume;
	///最大下单数量
	TVolumeType	MaxVolume;
	///默认触发次数
	TVolumeType	TrigTimes;
	///最大触发次数
	TVolumeType	MaxTrigTimes;
	///腿数
	TVolumeType	LegNum;
	///交易所代码
	TExchangeIDType	Leg1ExchangeID;
	///腿一合约代码
	TInstrumentIDType	Leg1ID;
	///腿一买卖方向
	TDirectionType	Leg1Direction;
	///腿一乘数
	TVolumeMultipleType	Leg1Multiple;
	///腿一价比例
	TRatioType	Leg1PriceRatio;
	///腿一基差价
	TPriceType	Leg1BasisPrice;
	///腿一报入顺序
	TVolumeType	Leg1SeqNo;
	///交易所代码
	TExchangeIDType	Leg2ExchangeID;
	///腿二合约代码
	TInstrumentIDType	Leg2ID;
	///腿二买卖方向
	TDirectionType	Leg2Direction;
	///腿二乘数
	TVolumeMultipleType	Leg2Multiple;
	///腿二价比例
	TRatioType	Leg2PriceRatio;
	///腿二基差价
	TPriceType	Leg2BasisPrice;
	///腿二报入顺序
	TVolumeType	Leg2SeqNo;
	///交易所代码
	TExchangeIDType	Leg3ExchangeID;
	///腿三合约代码
	TInstrumentIDType	Leg3ID;
	///腿三买卖方向
	TDirectionType	Leg3Direction;
	///腿三乘数
	TVolumeMultipleType	Leg3Multiple;
	///腿三价比例
	TRatioType	Leg3PriceRatio;
	///腿三基差价
	TPriceType	Leg3BasisPrice;
	///腿三报入顺序
	TVolumeType	Leg3SeqNo;
	///腿四交易所代码
	TExchangeIDType	Leg4ExchangeID;
	///腿四合约代码
	TInstrumentIDType	Leg4ID;
	///腿四买卖方向
	TDirectionType	Leg4Direction;
	///腿四乘数
	TVolumeMultipleType	Leg4Multiple;
	///腿四价比例
	TRatioType	Leg4PriceRatio;
	///腿四基差价
	TPriceType	Leg4BasisPrice;
	///腿四报入顺序
	TVolumeType	Leg4SeqNo;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///操作标志
	TActionFlagType	ActionFlag;
	///开平循环组合平仓类型
	TOffsetTypeType	OffsetType;
	///腿一操作标志
	TCombLeg1ActionFlagType	Leg1ActionFlag;
	///投资者编号
	TInvestorIDType	Leg1InvestorID;
	///投资者编号
	TInvestorIDType	Leg2InvestorID;
	///投资者编号
	TInvestorIDType	Leg3InvestorID;
	///投资者编号
	TInvestorIDType	Leg4InvestorID;
	///追单次数
	TVolumeType	Leg1Times;
	///追单次数
	TVolumeType	Leg2Times;
	///追单次数
	TVolumeType	Leg3Times;
	///追单次数
	TVolumeType	Leg4Times;
	///开仓处理方式
	TOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg4OpenDealType;
	///投机套保标志
	THedgeFlagType	Leg1HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg2HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg3HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg4HedgeFlag;
};

///合约查询
struct CQryCombInstrumentField
{
	///合约代码
	TInstrumentIDType	CombInstrumentID;
};

///套利深度行情
struct CCombMarketDataField
{
	///合约代码
	TInstrumentIDType	InstrumentID;
	///最后修改时间
	TTimeType	UpdateTime;
	///最后修改毫秒
	TMillisecType	UpdateMillisec;
	///申买价一
	TPriceType	BidPrice1;
	///申买量一
	TVolumeType	BidVolume1;
	///申卖价一
	TPriceType	AskPrice1;
	///申卖量一
	TVolumeType	AskVolume1;
	///最新价
	TPriceType	LastPrice;
	///距收盘时间多少秒暂停操作
	TBoolType	Leg1Gap;
	///距收盘时间多少秒暂停操作
	TBoolType	Leg2Gap;
	///距收盘时间多少秒暂停操作
	TBoolType	Leg3Gap;
	///距收盘时间多少秒暂停操作
	TBoolType	Leg4Gap;
};

///输入报单
struct CCombInputOrderField
{
	///系统报单编号
	TSequenceNoType	CombOrderSysID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUserOrderLocalIDType	UserOrderLocalID;
	///买卖方向
	TDirectionType	Direction;
	///价格
	TPriceType	LimitPrice;
	///止盈价格
	TPriceType	OffsetPrice;
	///止损价格
	TPriceType	StopPrice;
	///初始委托量
	TVolumeType	Volume;
	///报入量数量
	TVolumeType	SendInVolume;
	///开仓成交数量
	TVolumeType	OpenTradeVolume;
	///开仓成交是否整数
	TBoolType	IsOpenTradeWhole;
	///平仓成交数量
	TVolumeType	OffstTradeVolume;
	///委托触发次数
	TVolumeType	TrigTimes;
	///报单触发次数
	TVolumeType	OrderTimes;
	///插入时间
	TTimeType	InsertTime;
	///报单状态
	TOrderStatusType	OrderStatus;
	///操作标志
	TActionFlagType	ActionFlag;
	///腿一操作标志
	TCombLeg1ActionFlagType	Leg1ActionFlag;
	///报单类型
	TOrderPriceTypeType	OrderPriceType;
	///套利循环类型
	TCombCycleTypeType	CycleType;
	///套利成交状态
	TTradeStatusType	TradeStatus;
	///当前报入腿号
	TVolumeType	PresentLegNo;
	///投资者编号
	TInvestorIDType	Leg1InvestorID;
	///投资者编号
	TInvestorIDType	Leg2InvestorID;
	///投资者编号
	TInvestorIDType	Leg3InvestorID;
	///投资者编号
	TInvestorIDType	Leg4InvestorID;
	///腿一基差价
	TPriceType	Leg1BasisPrice;
	///腿二基差价
	TPriceType	Leg2BasisPrice;
	///腿三基差价
	TPriceType	Leg3BasisPrice;
	///腿四基差价
	TPriceType	Leg4BasisPrice;
	///腿一报入顺序
	TVolumeType	Leg1SeqNo;
	///腿二报入顺序
	TVolumeType	Leg2SeqNo;
	///腿三报入顺序
	TVolumeType	Leg3SeqNo;
	///腿四报入顺序
	TVolumeType	Leg4SeqNo;
	///腿一乘数
	TVolumeMultipleType	Leg1Multiple;
	///腿二乘数
	TVolumeMultipleType	Leg2Multiple;
	///腿三乘数
	TVolumeMultipleType	Leg3Multiple;
	///腿四乘数
	TVolumeMultipleType	Leg4Multiple;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///开平循环组合平仓类型
	TOffsetTypeType	OffsetType;
	///错单已成交自动平仓
	TBoolType	IsErrorAutoOffset;
	///追单次数
	TVolumeType	Leg1Times;
	///追单次数
	TVolumeType	Leg2Times;
	///追单次数
	TVolumeType	Leg3Times;
	///追单次数
	TVolumeType	Leg4Times;
	///开仓处理方式
	TOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg4OpenDealType;
	///投机套保标志
	THedgeFlagType	Leg1HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg2HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg3HedgeFlag;
	///投机套保标志
	THedgeFlagType	Leg4HedgeFlag;
};

///套利成交
struct CCombTradeField
{
	///成交编号
	TTradeIDType	TradeID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///交易日
	TTradingDayType	TradingDay;
	///系统报单编号
	TSequenceNoType	CombOrderSysID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///买卖方向
	TDirectionType	Direction;
	///委托价格
	TPriceType	LimitPrice;
	///成交价格
	TPriceType	TradePrice;
	///成交数量
	TVolumeType	TradeVolume;
	///成交时间
	TTimeType	TradeTime;
};

///套利分腿报单
struct CCombAPIInputOrderField
{
	///委托批次号
	TSequenceNoType	OrderBatchNO;
	///内存表变化类型
	TMemtableChangeTypeType	MemtableChangeType;
	///第几腿
	TVolumeType	LegNo;
	///委托顺序
	TVolumeType	LegSeqNo;
	///相同委托顺序数
	TVolumeType	SameLegSeqNo;
	///腿一操作标志
	TCombLeg1ActionFlagType	Leg1ActionFlag;
	///基差价
	TPriceType	LegBasisPrice;
	///腿乘数
	TVolumeMultipleType	LegMultiple;
	///腿买卖方向
	TDirectionType	LegDirection;
	///腿价比例
	TRatioType	LegPriceRatio;
	///是否套利最后一批
	TBoolType	IsLastLegSeqNo;
	///套利合约代码
	TInstrumentIDType	CombInstrumentID;
	///套利买卖方向
	TDirectionType	CombDirection;
	///委托价格
	TPriceType	CombLimitPrice;
	///套利价格类别
	TCombPriceTypeType	priceType;
	///成交金额
	TMoneyType	Amount;
	///报入数量
	TVolumeType	SendVolume;
	///第一腿报入时已成交量
	TVolumeType	FirstLegTradeVolume;
	///报入错误数量
	TVolumeType	ErrorVolume;
	///第一批次第一笔报单编号
	TOrderSysIDType	OrderSysID1;
	///第一批次第二笔报单编号
	TOrderSysIDType	OrderSysID2;
	///第一批次第三笔报单编号
	TOrderSysIDType	OrderSysID3;
	///开仓委托数量
	TVolumeType	LegOpenOrderVolume;
	///平仓委托数量
	TVolumeType	LegOffsetOrderVolume;
	///开仓成交数量
	TVolumeType	LegOpenTradeVolume;
	///平仓成交数量
	TVolumeType	LegOffsetTradeVolume;
	///成交编号
	TTradeIDType	TradeID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///系统报单编号
	TOrderSysIDType	OrderSysID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///用户代码
	TUserIDType	UserID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TDirectionType	Direction;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///价格
	TPriceType	LimitPrice;
	///数量
	TVolumeType	Volume;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///GTD日期
	TDateType	GTDDate;
	///成交量类型
	TVolumeConditionType	VolumeCondition;
	///最小成交量
	TVolumeType	MinVolume;
	///止损价
	TPriceType	StopPrice;
	///强平原因
	TForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TBoolType	IsAutoSuspend;
	///业务单元
	TBusinessUnitType	BusinessUnit;
	///用户自定义域
	TCustomType	UserCustom;
	///交易日
	TTradingDayType	TradingDay;
	///会员编号
	TParticipantIDType	ParticipantID;
	///客户号
	TClientIDType	ClientID;
	///下单席位号
	TSeatIDType	SeatID;
	///插入时间
	TTimeType	InsertTime;
	///本地报单编号
	TOrderLocalIDType	OrderLocalID;
	///报单来源
	TOrderSourceType	OrderSource;
	///报单状态
	TOrderStatusType	OrderStatus;
	///撤销时间
	TTimeType	CancelTime;
	///撤单用户编号
	TUserIDType	CancelUserID;
	///今成交数量
	TVolumeType	VolumeTraded;
	///剩余数量
	TVolumeType	VolumeRemain;
	///策略类型
	TPlotTypeType	PlotType;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///手续费
	TMoneyType	Fee;
	///追单次数
	TVolumeType	Leg1Times;
	///追单次数
	TVolumeType	Leg2Times;
	///追单次数
	TVolumeType	Leg3Times;
	///追单次数
	TVolumeType	Leg4Times;
	///开仓处理方式
	TOpenDealTypeType	Leg1OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg2OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg3OpenDealType;
	///开仓处理方式
	TOpenDealTypeType	Leg4OpenDealType;
};

///历史套利成交查询
struct CQryHisCombTradeField
{
	///开始交易日
	TTradingDayType	BeginTradingDay;
	///结束交易日
	TTradingDayType	EndTradingDay;
	///套利合约代码
	TInstrumentIDType	CombInstrumentID;
	///系统报单编号
	TSequenceNoType	CombOrderSysID;
	///成交编号
	TTradeIDType	TradeID;
};

///历史成交查询
struct CQryHisTradeField
{
	///开始交易日
	TTradingDayType	BeginTradingDay;
	///结束交易日
	TTradingDayType	EndTradingDay;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///用户代码
	TUserIDType	UserID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///成交编号
	TTradeIDType	TradeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
};

///套利消息通知
struct CCombNtyMessageField
{
	///套利合约代码
	TInstrumentIDType	CombInstrumentID;
	///系统报单编号
	TSequenceNoType	CombOrderSysID;
	///第几腿
	TVolumeType	LegNo;
	///委托顺序
	TVolumeType	LegSeqNo;
	///消息摘要
	TAbstractType	Abstract;
	///经纪公司编号
	TBrokerIDType	BrokerID;
};

///网格交易策略报单请求
struct CGridOrderField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///系统报单编号
	TOrderSysIDType	OrderSysID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///用户代码
	TUserIDType	UserID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///用户本地报单号
	TUserOrderLocalIDType	UserOrderLocalID;
	///报单类型
	TOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TDirectionType	Direction;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///价格
	TPriceType	LimitPrice;
	///数量
	TVolumeType	Volume;
	///有效期类型
	TTimeConditionType	TimeCondition;
	///GTD日期
	TDateType	GTDDate;
	///成交量类型
	TVolumeConditionType	VolumeCondition;
	///最小成交量
	TVolumeType	MinVolume;
	///止损价
	TPriceType	StopPrice;
	///强平原因
	TForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TBoolType	IsAutoSuspend;
	///业务单元
	TBusinessUnitType	BusinessUnit;
	///用户自定义域
	TCustomType	UserCustom;
	///交易日
	TTradingDayType	TradingDay;
	///会员编号
	TParticipantIDType	ParticipantID;
	///客户号
	TClientIDType	ClientID;
	///下单席位号
	TSeatIDType	SeatID;
	///插入时间
	TTimeType	InsertTime;
	///本地报单编号
	TOrderLocalIDType	OrderLocalID;
	///报单来源
	TOrderSourceType	OrderSource;
	///报单状态
	TOrderStatusType	OrderStatus;
	///撤销时间
	TTimeType	CancelTime;
	///撤单用户编号
	TUserIDType	CancelUserID;
	///今成交数量
	TVolumeType	VolumeTraded;
	///剩余数量
	TVolumeType	VolumeRemain;
	///策略类型
	TPlotTypeType	PlotType;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///手续费
	TMoneyType	Fee;
	///冻结手续费
	TMoneyType	FrozenFee;
	///冻结的保证金
	TMoneyType	FrozenMargin;
	///期权权利金收支
	TMoneyType	FrozenPremium;
	///资金帐号
	TAccountIDType	AccountID;
	///下单用户编号
	TUserIDType	OrderUserID;
	///交易类型
	TTradeTypeType	TradeType;
	///处理标志
	TDealFlagType	DealFlag;
	///委托批次号
	TSequenceNoType	OrderBatchNO;
	///第几腿
	TVolumeType	LegNo;
	///委托顺序
	TVolumeType	LegSeqNo;
	///相同委托顺序数
	TVolumeType	SameLegSeqNo;
	///是否套利最后一批
	TBoolType	IsLastLegSeqNo;
	///是否套利腿的最后一笔
	TBoolType	IsLastSameLegNo;
	///第一批次第一腿第几笔
	TVolumeType	LegSeqNo1LegNoNum;
	///腿一操作标志
	TCombLeg1ActionFlagType	Leg1ActionFlag;
	///基差价
	TPriceType	LegBasisPrice;
	///不再追单
	TBoolType	IsNoCancelOrder;
	///接收客户端时间
	TMillisecType	LocalInsertTime;
	///当前档
	TVolumeType	CurrPot;
	///当前档
	TVolumeType	LastPot;
	///成交状态
	TTradeStatusType	TradeStatus;
	///是否被平仓或撤单
	TBoolType	IsOffset;
	///被平掉的原订单编号
	TOrderSysIDType	OffsetSysID;
	///原购买价格
	TPriceType	OpenPrice;
	///成交价格
	TPriceType	TradePrice;
	///档位价格
	TPriceType	PotPrice;
	///止损状态
	TBoolType	IsStopLoss;
	///该订单是否可以被查找，默认查找
	TIsActiveType	IsActive;
	///报单时间
	TMillisecType	OrderTime;
	///备注
	TCustomType	Comment;
	///内存表变化类型
	TMemtableChangeTypeType	MemtableChangeType;
};

///连接管理
struct CAPILinkField
{
	///连接编号
	TFrontIDType	LinkID;
	///前台交易用户代码
	TUserIDType	UserID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///后台投资者编号
	TInvestorIDType	InvestorID;
	///密码
	TPasswordType	Password;
	///是否活跃
	TBoolType	IsActive;
	///环境编号
	TEnvNoType	EnvNo;
	///是否接收行情
	TBoolType	IsMrkActive;
	///是否只接收自选合约行情QuotCrtList 1=是
	TBoolType	IsRcvQuotList;
};

///各市场开闭市时间
struct CMarketTimeField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///开市时间
	TTimeType	OpenTime;
	///闭市时间
	TTimeType	CloseTime;
	///距离开市可以报单时间
	TTimeType	GapOpen;
	///距离闭市可以报盘时间
	TTimeType	GapClose;
};

///做多做空策略录入
struct CLongShortPlotInputField
{
	///多空策略类型
	TLongShortPlotTypeType	LongShortPlotType;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略报价,报入不能修改
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///点距：最小报价的数量
	TVolumeType	Range;
	///档数
	TVolumeType	Grade;
	///止损价
	TPriceType	StopPrice;
	///启动时间
	TTimeType	StartTime;
	///停止时间
	TTimeType	EndTime;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///首笔报单促发方式：支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///投资者编号
	TInvestorIDType	InvestorID;
	///最大报单数量
	TVolumeType	MaxQty;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///做多做空策略
struct CLongShortPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///多空策略类型
	TLongShortPlotTypeType	LongShortPlotType;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略报价,报入不能修改
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///点距：最小报价的数量
	TVolumeType	Range;
	///档数
	TVolumeType	Grade;
	///止损价
	TPriceType	StopPrice;
	///启动时间
	TTimeType	StartTime;
	///停止时间
	TTimeType	EndTime;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///首笔报单促发方式：支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///投资者编号
	TInvestorIDType	InvestorID;
	///最大报单数量
	TVolumeType	MaxQty;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///当前档
	TVolumeType	CurrPot;
	///上一档
	TVolumeType	PrePot;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///是否促发首次报单
	TBoolType	IsSendFirst;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///做多做空策略修改
struct CLongShortPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///报单数量
	TVolumeType	Volume;
	///档数
	TVolumeType	Grade;
	///止损价
	TPriceType	StopPrice;
	///启动时间
	TTimeType	StartTime;
	///停止时间
	TTimeType	EndTime;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///最大报单数量
	TVolumeType	MaxQty;
};

///做多做空策略查询请求
struct CQryLongShortPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///基础数据查询应答
struct CQueryBaseFinishField
{
	///客户端经纪公司编号
	TBrokerIDType	FrontBrokerID;
	///客户端前台交易用户代码
	TUserIDType	FrontUserID;
	///交易所经纪公司编号
	TBrokerIDType	BackBrokerID;
	///交易所前台交易用户代码
	TUserIDType	BackUserID;
	///密码
	TPasswordType	Password;
	///连接类型
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
	///交易或者行情
	TBoolType	TradeOrMarket;
	///前置编号
	TFrontIDType	FrontID;
	///会话编号
	TSessionIDType	SessionID;
	///交易日
	TTradingDayType	TradingDay;
};

///冰山订单输入请求
struct CIcebergPlotInputField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///实际最大报单数量
	TVolumeType	MaxQty;
	///实际最小报单数量
	TVolumeType	MinQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///冰山订单输入应答
struct CIcebergPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///实际最大报单数量
	TVolumeType	MaxQty;
	///实际最小报单数量
	TVolumeType	MinQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TBoolType	IsSendFirst;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///冰山订单策略修改
struct CIcebergPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///策略报价,报入不能修改
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///实际最大报单数量
	TVolumeType	MaxQty;
	///实际最小报单数量
	TVolumeType	MinQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///冰山订单查询请求
struct CQryIcebergPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///幽灵订单查询请求
struct CGhostPlotInputField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///触发报单价格
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///最小触发报单数量
	TVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///幽灵订单查询
struct CGhostPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///触发报单价格
	TPriceType	OrderPrice;
	///报单数量
	TVolumeType	Volume;
	///最小触发报单数量
	TVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TBoolType	IsSendFirst;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///幽灵订单策略修改
struct CGhostPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///支持限价和市价
	TOrderPriceTypeType	OrderPriceType;
	///报单数量
	TVolumeType	Volume;
	///最小触发报单数量
	TVolumeType	MinTriggerQty;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///幽灵订单查询请求
struct CQryGhostPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///盯盘订单查询请求
struct CPegPlotInputField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///最大委托价
	TPriceType	MaxOrderPrice;
	///最小委托价
	TPriceType	MinOrderPrice;
	///报单数量
	TVolumeType	Volume;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///盯盘订单查询
struct CPegPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///最大委托价
	TPriceType	MaxOrderPrice;
	///最小委托价
	TPriceType	MinOrderPrice;
	///报单数量
	TVolumeType	Volume;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TBoolType	IsSendFirst;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///盯盘订单策略修改
struct CPegPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///最大委托价
	TPriceType	MaxOrderPrice;
	///最小委托价
	TPriceType	MinOrderPrice;
	///报单数量
	TVolumeType	Volume;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///盯盘订单查询请求
struct CQryPegPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///TWap订单查询请求
struct CTWapPlotInputField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///拆分次数
	TVolumeType	NumberOfWaves;
	///在拆单后数量不满足报单数量是否自动处理
	TBoolType	IsAutoWaves;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///参考委托价
	TPriceType	ReffPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///委托间隔时间
	TVolumeType	WaitDelay;
	///撤单确认时间
	TVolumeType	CancelDelay;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///TWap订单查询
struct CTWapPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///拆分次数
	TVolumeType	NumberOfWaves;
	///在拆单后数量不满足报单数量是否自动处理
	TBoolType	IsAutoWaves;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///参考委托价
	TPriceType	ReffPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///委托间隔时间
	TVolumeType	WaitDelay;
	///撤单确认时间
	TVolumeType	CancelDelay;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///成交后报单是否发送
	TBoolType	IsSendFirst;
	///最小报单数量
	TVolumeType	MinLimitOrderVolume;
	///最大报单数量
	TVolumeType	MaxLimitOrderVolume;
	///最新价
	TPriceType	LastPrice;
	///卖一价
	TPriceType	AskPrice;
	///买一价
	TPriceType	BidPrice;
	///上次报单时间
	TMillisecType	LastOrderTime;
	///上次撤单时间
	TMillisecType	LastCancelTime;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///TWap订单策略修改
struct CTWapPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///参考委托价
	TPriceType	ReffPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///委托间隔时间
	TVolumeType	WaitDelay;
	///撤单确认时间
	TVolumeType	CancelDelay;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///TWap订单查询请求
struct CQryTWapPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///MIT和Stop订单查询请求
struct CMITStopPlotInputField
{
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///最小触发量
	TVolumeType	MinTrigQty;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///触发委托价
	TPriceType	TrigPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///策略报单类型
	TMITStopTypeType	MITStopType;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
};

///MIT和Stop订单查询
struct CMITStopPlotField
{
	///策略执行状态
	TPlotStatusTypeType	Status;
	///插入日期
	TDateType	InsertDate;
	///插入时间
	TTimeType	InsertTime;
	///修改日期
	TDateType	ModifyDate;
	///修改时间
	TTimeType	ModifyTime;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///最小触发量
	TVolumeType	MinTrigQty;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///触发委托价
	TPriceType	TrigPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///策略报单类型
	TMITStopTypeType	MITStopType;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///报单状态
	TOrderStatusType	OrderStatus;
	///持仓成本
	TMoneyType	PositionCost;
	///买成交剩余量
	TVolumeType	BuyRemainVolume;
	///卖成交剩余量
	TVolumeType	SellRemainVolume;
	///买冻结数量
	TVolumeType	FrozenBuyVolume;
	///卖冻结数量
	TVolumeType	FrozenSellVolume;
	///是否达到触发价，达到触发价下次开始发单
	TBoolType	IsSendFirst;
	///最小报单数量
	TVolumeType	MinLimitOrderVolume;
	///最大报单数量
	TVolumeType	MaxLimitOrderVolume;
	///最新价
	TPriceType	LastPrice;
	///卖一价
	TPriceType	AskPrice;
	///买一价
	TPriceType	BidPrice;
	///浮动盈亏
	TMoneyType	FloatMoney;
};

///MIT和Stop订单策略修改
struct CMITStopPlotActionField
{
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///买卖方向
	TDirectionType	Direction;
	///投机套保标志
	THedgeFlagType	HedgeFlag;
	///开平标志
	TOffsetFlagType	OffsetFlag;
	///最小触发量
	TVolumeType	MinTrigQty;
	///盯盘类型
	TReffPriceTypeType	ReffPriceType;
	///触发委托价
	TPriceType	TrigPrice;
	///价差
	TPriceType	PriceDiff;
	///报单数量
	TVolumeType	Volume;
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///MIT和Stop订单查询请求
struct CQryMITStopPlotField
{
	///登录经纪公司编号
	TBrokerIDType	LogBrokerID;
	///登录用户代码
	TUserIDType	LogUserID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///策略执行状态
	TPlotStatusTypeType	Status;
	///投资者编号
	TInvestorIDType	InvestorID;
};

///订阅的行情列表
struct CSubMarketQuotoListField
{
	///连接编号
	TFrontIDType	LinkID;
	///连接类型,QDP,QDAM,CTP
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
	///交易所代码
	TExchangeIDType	ExchangeID;
	///合约代码
	TInstrumentIDType	InstrumentID;
	///是否订阅
	TBoolType	IsActive;
};

///对应各环境连接管理器
struct CEnvManagerField
{
	///环境编号
	TEnvNoType	EnvNo;
	///环境名称
	TShortNameType	EnvName;
	///环境描述
	TLongNameType	EnvDesc;
	///连接类型
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
	///连接地址
	TTCPAddressType	TradeAddress;
	///连接地址
	TTCPAddressType	MarketAddress;
	///订阅主题号
	TTopicIDType	TopicID;
};

///连接管理
struct CAPIInnerLinkField
{
	///连接编号
	TFrontIDType	LinkID;
	///前台交易用户代码
	TUserIDType	UserID;
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///后台投资者编号
	TInvestorIDType	InvestorID;
	///密码
	TPasswordType	Password;
	///是否活跃
	TBoolType	IsActive;
	///环境编号
	TEnvNoType	EnvNo;
	///是否接收行情
	TBoolType	IsMrkActive;
	///是否只接收自选合约行情QuotCrtList 1=是
	TBoolType	IsRcvQuotList;
	///连接类型
	TAPITypeType	APIType;
	///业务连接类型，同一接口多个交易所使用
	TLinkTypeType	LinkType;
	///连接地址
	TTCPAddressType	TradeAddress;
	///连接地址
	TTCPAddressType	MarketAddress;
	///订阅主题号
	TTopicIDType	TopicID;
};

///策略消息通知
struct CPlotNtyMessageField
{
	///经纪公司编号
	TBrokerIDType	BrokerID;
	///策略执行编号
	TOrderLocalIDType	PlotID;
	///错误代码
	TErrorIDType	ErrorID;
	///消息摘要
	TAbstractType	Abstract;
};



#endif
