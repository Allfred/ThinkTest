#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "Interval_map.h"



int main()
{
	char val = 'F';
	interval_map<int, char> obj(val);
	obj.assign(1, 5, 'W');
	obj.assign(1, 5,'p');
	obj.assign(7, 11,'I');
	
	for (auto it=obj.m_map.begin();it!=obj.m_map.end();++it)
	{
		std::cout << it->first << "->" << it->second << std::endl;
	}
	
	system("pause");
}
