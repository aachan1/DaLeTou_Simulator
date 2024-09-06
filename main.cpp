#include <iostream>
#include <Windows.h>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>



using namespace std;


//����͸ǰ�κ���
vector<int> numstarts = { 1,05,9,14,20 ,
						16,19,22,27,35,
						02,12,19,22,32 ,
						04,10,24,31,35 ,
						03,10,15,19 ,29 ,
						07,11,12,14,19 ,
						02,03,23,27,31};

//����͸��κ���
vector<int> numends = { 05,11 ,
						6,10,
						5,11,
						5,8,
						9,10,
						2,8,
						1,10};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis35(1, 35);	//���ֵ1-35��Χ
std::uniform_int_distribution<> dis12(1, 12);	//���ֵ1-12��Χ


//��ȡ����͸����	//ȡֵ��Χ,��ú������,����ĺ���,���˵ĺ���
void GetDaLeTouNum(std::uniform_int_distribution<> disNum,int needCount,vector<int> &outNums,vector<int> filterNums)
{
	while (1)
	{
		bool isExist = false;
		int num = disNum(gen);
		for (auto v : filterNums)
		{
			if (v == num)
			{
				isExist = true;
				break;
			}
		}
		if (isExist)continue;
		for (auto v : outNums)
		{
			if (v == num) {
				isExist = true;
				break;
			}
		}
		if (isExist)continue;
		outNums.push_back(num);
		if (outNums.size() == needCount)break;
	}

	cout << "����:";
	for (auto f : outNums)
	{
		cout << f << " ";
	}
	cout << endl;
}



//��ѡ��Ҫ���˵ĺ���
void analyzeNumbers(const int max,const std::vector<int>& numbers,std::vector<int> &arr0, std::vector<int>& arr1) {
	std::unordered_map<int, int> countMap;
	for (int i = 1; i <= max; ++i) {
		countMap[i] = 0;
	}
	for (int num : numbers) {
		if (num >= 1 && num <= 35) {
			countMap[num]++;
		}
	}

	int minCount = numbers.size();
	int minNumber = -1;
	std::vector<int> notAppearedNumbers;
	for (int i = 1; i <= max; ++i) {
		if (countMap[i] < minCount) {
			minCount = countMap[i];
			minNumber = i;
		}
		if (countMap[i] == 0) {
			notAppearedNumbers.push_back(i);
		}
	}

	//std::cout << "�����ظ�����ͳ�ƣ�" << std::endl;
	for (const auto& pair : countMap) {
		if (pair.second == 0)arr0.push_back(pair.first);
		if (pair.second > 1)arr1.push_back(pair.first);
	}

	std::cout << "��δ���ֹ��������У�";
	for (int num : notAppearedNumbers) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	std::cout << "�������1�������У�";
	for (int num : arr1) {
		std::cout << num << " ";
	}
	std::cout << std::endl<<endl;
}


int checkNum(vector<int> fns, vector<int> ens,vector<int> ff,vector<int> ee)
{
	int fz = 0;
	int ez = 0;


	for (auto v : fns)
	{
		for (auto vv : ff)
		{
			if (vv == v)fz++;
		}
	}
	cout << "ǰ������ " << fz << " ��" << endl;

	for (auto v : ens)
	{
		for (auto vv : ee)
		{
			if (vv == v)ez++;
		}
	}
	cout << "������� " << ez << " ��" << endl<<endl;


	if (fz == 5 && ez == 2)return 1;
	if (fz == 5 && ez > 0)return 2;
	if (fz == 5)return 3;
	if (fz > 3 && ez == 2)return 4;
	if (fz > 3 && ez > 0)return 5;
	if (fz > 2 && ez == 2)return 6;
	if (fz > 3)return 7;
	if (fz > 2 && ez > 0)return 8;
	if (fz > 2 || (fz > 0 && ez == 2) || (fz > 1 && ez > 0) || ez == 2)return 9;

	return 0;
}


int main()
{
	vector<int> frontNums;
	vector<int> endNums;

	vector<int> arr0, arr1;
	analyzeNumbers(35,numstarts, arr0, arr1);
	vector<int> arr2, arr3;
	analyzeNumbers(12,numends, arr2, arr3);


	int index = 10;
	while (index)
	{
		index--;
		frontNums.clear();
		endNums.clear();

		GetDaLeTouNum(dis35,5, frontNums, arr1);
		GetDaLeTouNum(dis12, 2, endNums, arr3);

		int ret=checkNum(frontNums, endNums, { 19,21,29,32,33 }, { 6,8 });

		if (ret)
		{
			cout << "\t\t\t\t\t����" << ret << "�Ƚ�" << endl<<endl;
		}
	}


	system("pause");
	return 0;
}
