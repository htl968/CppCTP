#ifndef QUANT_CTP_MANAGER_H
#define QUANT_CTP_MANAGER_H

#include <list>
#include <map>
#include <string>
#include "Login.h"
#include "MdSpi.h"
#include "TdSpi.h"
#include "DBManager.h"
#include "Trader.h"

using std::map;
class MdSpi;

class CTP_Manager {

public:
	CTP_Manager();
	///登陆
	bool CheckIn(Login *login);

	/// trader login
	bool TraderLogin(string traderid, string password, Trader *op);

	/// admin login
	bool AdminLogin(string adminid, string password);

	///订阅行情
	int submarketData(char *instrument[]);

	/// 创建交易对象并且登陆
	User * CreateAccount(User *user, list<Strategy *> *l_strategys);

	/// 创建行情
	MdSpi * CreateMd(string td_frontAddress, string td_broker, string td_user, string td_pass, list<Strategy *> *l_strategys);

	///释放
	void ReleaseAccount(User *user);

	///订阅行情
	void SubmarketData(MdSpi *mdspi, list<string > *l_instrument);

	///取消订阅行情
	void UnSubmarketData(MdSpi *mdspi, string instrumentID, list<string > *l_instrument);

	/// 添加合约
	list<string> * addSubInstrument(string instrumentID, list<string> *l_instrument);

	/// 删除订阅合约
	list<string> * delSubInstrument(string instrumentID, list<string> *l_instrument);

	/// 统计合约数量
	int calInstrument(string instrumentID, list<string> *l_instrument);

	/// 退订合约增加
	list<string> addUnSubInstrument(string instrumentID, list<string> l_instrument);

	/// 得到l_instrument
	list<string> *getL_Instrument();

	/// 得到数据库操作对象
	DBManager *getDBManager();

	/// 设置l_trader
	void addTraderToLTrader(string trader);

	/// 获取trader是否在l_trader里
	bool checkInLTrader(string trader);

	/// 得到l_trader
	list<string> *getL_Trader();

	/// 得到l_obj_trader
	list<Trader *> * getL_Obj_Trader();

	/// 移除元素
	void removeFromLTrader(string trader);

	/// 增加用户期货账户
	void addFuturesToTrader(string traderid, User *user);

	/// 获取期货账户map
	map<string, list<User *> *> getTraderMap();

	/// 返回用户列表
	list<User *> *getL_User();

	/// 得到strategy_list
	list<Strategy *> *getListStrategy();

	/// 得到strategy_list
	list<Strategy *> *getListStrategyYesterday();

	/// 设置strategy_list
	void setListStrategy(list<Strategy *> *l_strategys);

	/// 设置mdspi
	void setMdSpi(MdSpi *mdspi);

	/// 获得mdspi
	MdSpi *getMdSpi();

	/// 初始化
	bool init();

	/// 设置开关
	int getOn_Off();
	void setOn_Off(int on_off);

	/// 处理客户端发来的消息
	static void HandleMessage(int fd, char *msg, CTP_Manager *ctp_m);

	/// 设置交易日
	void setTradingDay(string trading_day);

	/// 获得交易日
	string getTradingDay();

	/// 初始化昨仓
	bool initYesterdayPosition();

private:
	Login *login;
	list<string> *l_instrument;
	list<string > *l_unsubinstrument;
	list<string> *l_trader;
	list<User *> *l_user;
	list<Trader *> *l_obj_trader;
	map<string, list<User *> *> m_trader;
	DBManager *dbm;
	list<Strategy *> *l_strategys;
	list<Strategy *> *l_strategys_yesterday;
	MdSpi *mdspi;
	int on_off; //开关
	string trading_day;
};
#endif