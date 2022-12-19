#include "SCPIInterface/SCPIInterface.h" //�����ӿ�ͷ�ļ�

using namespace SCPI;//�����ռ�SCPI

//������
class SCPITest
{
public:
	SCPITest() {};
	~SCPITest() {};

public:
	void addCommand()
	{
		//�������Ƶ��ָ�� :FREQ:CENT 5 GHz
		//�������Ƶ��ָ�� :FREQ:CENT 'dfdgdg' �ַ�������
		m_iterfc.addCommand("[:SENSe]:FREQuency:CENTer", bind(&SCPITest::SetFreq));
		//��Ӳ�ѯ����ָ��  TRAC?
		m_iterfc.addCommand("TRAC?", bind(&SCPITest::Trace));
		//��Ӳ�ѯƵ��ָ��  :FREQ:CENT?
		m_iterfc.addCommand("[:SENSe]:FREQuency:CENTer?", bind(&SCPITest::GetFreq));
		//�������ָ��
		m_iterfc.endAdd();
	}

	void start()
	{
		m_iterfc.startListen(5050);//��ʼ����5050�˿�
	}

	void stop()
	{
		m_iterfc.stopListen();//ֹͣ����
	}

private:
	CommandHandler bind(bool(SCPITest::* funPtr)(const SCPIInterface& inter))
	{
		return std::bind(funPtr, this, std::placeholders::_1);
	}

	//����Ƶ��ָ��ص�����
	bool SetFreq(const SCPIInterface& inter)
	{
		//����ַ�������
		string str;
		while (inter.getParam(str))//��ÿͻ��˷�����string���Ͳ���
		{
			int doSomething = 0;
		}

		//�����ֵ����
		//double param;
		//while (inter.getParam(param))//��ÿͻ��˷�����double���Ͳ���
		//{
		//	int doSomething = 0;
		//}

		//��ò���������λ��
		//scpi_number_t paramNum;
		//while (inter.getParam(paramNum))//��ÿͻ��˷�����scpi_number_t���Ͳ���
		//{
		//	m_params.emplace_back(paramNum);
		//}
		return true;
	}

	//��ѯ����ָ��ص�����
	bool Trace(const SCPIInterface& inter)
	{
		return inter.sendArray(data());//��ͻ��˷��ͼ�������
	}

	//��ѯƵ��ָ��ص�����
	bool GetFreq(const SCPIInterface& inter)
	{
		for (auto par : m_params)
		{
			inter.sendValue(par.content.value);//��ͻ��˷���Ƶ��
		}
		return true;
	}

private:
	//��������
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