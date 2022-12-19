/**
 * @file StringConv.h
 * @brief �ַ�����ʽת��
 * @author װ����ҵ������� ���� 
 * @version 0.1
 * @date 2020-12-09
 * 
 * @copyright Copyright (c) 2020  �й����ӿƼ����Ź�˾����ʮһ�о���
 * 
 */
#pragma once

#include <string>
#include <codecvt>
#include <locale>
#include <vector>

namespace StrConvert {
	// string�ı��뷽ʽΪutf8������ã�
	std::string wstringToUTF8(const std::wstring& str);
	std::wstring UTF8Towstring(const std::string& str);
	std::string GbkToUTF8(const std::string& str);
	std::string UTF8ToGbk(const std::string& str);
	long strToLong(const std::wstring& str);
	double strToDouble(const std::wstring& str);
	void extractWords(const std::wstring& context, const std::wstring& seps, std::vector<std::wstring>& result);
}

