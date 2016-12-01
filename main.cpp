#include<iostream>
#include<list>
using namespace::std;

//还未考虑四消除的情况
//判断函数
int Exam_need_delete(list<char> List, int k, char Ele) {
	list<char>::iterator list_iter = List.begin();//定义list内部迭代器
	
	if (List.size() < 3)//保证至少有三个元素
		return 0;
	for (int i = 0; i != k; ++i)//迭代器指向k位置
		++list_iter;
	
	//如果插在首尾元素
	if (list_iter == List.begin()) {//如果指向首元素
		if (Ele == *(++list_iter) && Ele == *(++list_iter))
			return 1;//1 0 0
		else return 0;
	}
	else if (++list_iter == List.end()) {//如果指向尾元素
		--list_iter;	//先把迭代器复位
		if (Ele == *(--list_iter) && Ele == *(--list_iter))
			return 3;//0 0 1
		else return 0;
	}
	else --list_iter;//上一个else中拨动迭代器，先将其复位
	
	//如果插在第二个位置
	if ((--list_iter) == List.begin()) {
		++list_iter;//复位迭代器
		if (Ele == *(--list_iter)) {//如果左一相同
			++list_iter;//复位迭代器
			if (Ele == *(++list_iter)) {//即左一同 且 右一同
		//		++list_iter;//再加一以便检测是否在倒数第二的位置
				if (++list_iter != List.end())//如果既是第二 且 不是倒数第二
					if (Ele == *(list_iter))//前后四个都相等
						return 4;//0 1 0 0
				else return 2;//0 1 0
			}
			else return 0;//左一同 且 右一不同
		}
		else {//左一不同
			++list_iter;//复位迭代器
			++list_iter;//再加一以便检测是否在倒数第二的位置
			if (++list_iter == List.end())	//如果既是第二也是倒数第二
				return 0;					//且左一已经不同
			else {
				--list_iter;
				--list_iter;//复位迭代器
				if (Ele == *(++list_iter)) {//右一同
					if (Ele == *(++list_iter))//右二同
						return 1;//1 0 0
					else return 0;//右一同 且 右二不同
				}
				else return 0;//左一不同 且 右一不同
			}
		}
	}
	++list_iter;//复位迭代器	
	++list_iter;//再加一以便检测是否在倒数第二的位置

	//如果插在倒数第二个位置
	if (++list_iter == List.end()) {
		--list_iter;
		--list_iter;//复位
		if (Ele == *(++list_iter)) {//如果右一相同
			--list_iter;//复位
			if (Ele == *(--list_iter))//如果左一相同
				return 2;//0 1 0
			else return 0;//右一同 而 左一不同
		} else { //右一不同 
			--list_iter;//复位
			if (Ele == *(--list_iter)) {//左一相同
				if (Ele == *(--list_iter))//左二相同
					return 3;//0 0 1
				else return 0;//左一同 而 左二不同
			}
			return 0;//左一不同
		}
	}
	--list_iter;
	--list_iter;//复位

	//一般情况
	if (Ele == *(--list_iter)) {//左一同
		if (Ele == *(--list_iter))//左二同
			return 3;//0 0 1
		else {//左二不同
			++list_iter;
			++list_iter;//复位
			if (Ele == *(++list_iter)) {//左一同 且 右一同
				if (Ele == *(++list_iter))//左一同 且 右一同 且 右二同
					return 4;//0 1 0 0
				else return 2;//0 1 0
			}
			else return 0;
		}
	} else {//左一不同
		++list_iter;//复位
		if (Ele == *(++list_iter)) {//右一同
			if (Ele == *(++list_iter))//右二同
				return 1;//1 0 0
			else return 0;
		}
		else return 0;
	}
}

//删除确定的三个元素
void remove(list<char>& List,int k,int a,int time_dupli) {//如果不设为引用，所有的操作只是对cha_list的副本的操作
	auto iter_be = List.begin();
	auto iter_en = List.begin();
	advance(iter_be, k + 1 - a);//将开始删除位置设为三/四个重复元素的第一个
	advance(iter_en, k + 4 - a + time_dupli - 3);//将结束删除位置设为三/四个重复元素之后的一个，保证能删除前三/四个
	List.erase(iter_be, iter_en);
}

//反复检查是否消除、是否连续消除
void swit_remove(list<char>& List, int k, char Ele) {
	int flag = 1;
	int flag_case = 0;//消除后需要把k前移的个数


	while (flag) {
		if (k >= flag_case)//保证一次消除后，指向消除的三/四个元素的前一个元素
			k -= flag_case;
		else k = 0;//同时如果是首元素或第二元素，直接指向首元素

		auto iter = List.begin();
		for (int i = 0; i != k; ++i)
			++iter;
		Ele = *(iter);

		flag = Exam_need_delete(List, k, Ele);
		switch (flag) {
		case 1:	remove(List, k, 1, 3); flag_case = 1; break;
		case 2:	remove(List, k, 2, 3); flag_case = 2; break;
		case 3: remove(List, k, 3, 3); flag_case = 3; break;
		case 4: remove(List, k, 2, 4); flag_case = 2; break;
		default:
			break;
		}
	}
}


int main() {
	list<char> cha_list;

	char cha[] = { '0' };	//定义数组以存储字母
	cin >> cha;		//可以输入字符串进数组
	int i = 0;		//暂时定义i
					//从数组里找字符并存入list
	while (cha[i] != '\0') {
		cha_list.push_back(cha[i]);		//cha_list中已经存入祖玛串
		++i;
	}
	i = 0;

	int n = 0;//要输入n次，即循环n次
	cin >> n;

	int k = 0;//数据为k和∑=Element
	char Element = 'a';

	for (i = 0; i != n; ++i) {
		cin >> k >> Element;
		auto iter = cha_list.begin();
		for (int i = 0; i != k; ++i)
			++iter;
		cha_list.insert(iter, Element);

		swit_remove(cha_list, k, Element);//检查后是否删除元素，删除哪个元素

		if (cha_list.size() == 0) {//如果链表空，执行下一次循环
			cout << '-' << endl;
			continue;
		}

		for (auto iter = cha_list.begin(); iter != cha_list.end(); ++iter)//输出链表结果
			cout << *iter << " ";
		cout << endl;
	}
	return 0;
}