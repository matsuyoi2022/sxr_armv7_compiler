#ifndef STRING_SPLIT_HPP
#define STRING_SPLIT_HPP
#include <iostream>
#include <vector>
using namespace std;

// 使用字符分割
void string_split(const string& str, const char split, vector<string>& res) {
	if (str == "")
		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + split;
	size_t pos = strs.find(split);

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos) {
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

// 使用字符串分割
void string_split(const string& str, const string& splits, vector<string>& res) {
	if (str == "")
		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos) {
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

/*
// test string_split()
int main()
{
	vector<string> strList;
	string str("This-is-a-test");
	string_split(str, '-', strList);
	for (auto s : strList)
		cout << s << " ";
	cout << endl;

	vector<string> strList2;
	string str2("This%20is%20a%20test");
	string_split(str2, "%20", strList2);
	for (auto s : strList2)
		cout << s << " ";
	cout << endl;
	return 0;
}
*/
#endif