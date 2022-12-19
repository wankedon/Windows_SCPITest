#include "SCPIInterface/SCPIInterface.h" //包含接口头文件

using namespace SCPI;//命名空间SCPI

//测试类
class SCPITest
{
public:
	SCPITest() {};
	~SCPITest() {};

public:
	void addCommand()
	{
		//添加设置频率指令 :FREQ:CENT 5 GHz
		//添加设置频率指令 :FREQ:CENT 'dfdgdg' 字符串参数
		m_iterfc.addCommand("[:SENSe]:FREQuency:CENTer", bind(&SCPITest::SetFreq));
		//添加查询迹线指令  TRAC?
		m_iterfc.addCommand("TRAC?", bind(&SCPITest::Trace));
		//添加查询频率指令  :FREQ:CENT?
		m_iterfc.addCommand("[:SENSe]:FREQuency:CENTer?", bind(&SCPITest::GetFreq));
		//结束添加指令
		m_iterfc.endAdd();
	}

	void start()
	{
		m_iterfc.startListen(5050);//开始监听5050端口
	}

	void stop()
	{
		m_iterfc.stopListen();//停止监听
	}

private:
	CommandHandler bind(bool(SCPITest::* funPtr)(const SCPIInterface& inter))
	{
		return std::bind(funPtr, this, std::placeholders::_1);
	}

	//设置频率指令回调函数
	bool SetFreq(const SCPIInterface& inter)
	{
		//获得字符串参数
		string str;
		while (inter.getParam(str))//获得客户端发来的string类型参数
		{
			int doSomething = 0;
		}

		//获得数值参数
		//double param;
		//while (inter.getParam(param))//获得客户端发来的double类型参数
		//{
		//	int doSomething = 0;
		//}

		//获得参数（带单位）
		//scpi_number_t paramNum;
		//while (inter.getParam(paramNum))//获得客户端发来的scpi_number_t类型参数
		//{
		//	m_params.emplace_back(paramNum);
		//}
		return true;
	}

	//查询迹线指令回调函数
	bool Trace(const SCPIInterface& inter)
	{
		return inter.sendArray(data());//向客户端发送迹线数据
	}

	//查询频率指令回调函数
	bool GetFreq(const SCPIInterface& inter)
	{
		for (auto par : m_params)
		{
			inter.sendValue(par.content.value);//向客户端发送频率
		}
		return true;
	}

private:
	//迹线数据
	std::vector<float> data()
	{
		std::vector<float> vec{ 7.1,8.2,9.3 };
		return vec;
	}

private:
	SCPIInterface m_iterfc;
	std::vector<scpi_number_t> m_params;
};

int main()
{
	SCPITest test;
	test.addCommand();
	test.start();
	system("pause");
	test.stop();
	return 0;
}