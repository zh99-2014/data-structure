#include<iostream>
#include<list>
using namespace::std;

//��δ���������������
//�жϺ���
int Exam_need_delete(list<char> List, int k, char Ele) {
	list<char>::iterator list_iter = List.begin();//����list�ڲ�������
	
	if (List.size() < 3)//��֤����������Ԫ��
		return 0;
	for (int i = 0; i != k; ++i)//������ָ��kλ��
		++list_iter;
	
	//���������βԪ��
	if (list_iter == List.begin()) {//���ָ����Ԫ��
		if (Ele == *(++list_iter) && Ele == *(++list_iter))
			return 1;//1 0 0
		else return 0;
	}
	else if (++list_iter == List.end()) {//���ָ��βԪ��
		--list_iter;	//�Ȱѵ�������λ
		if (Ele == *(--list_iter) && Ele == *(--list_iter))
			return 3;//0 0 1
		else return 0;
	}
	else --list_iter;//��һ��else�в������������Ƚ��临λ
	
	//������ڵڶ���λ��
	if ((--list_iter) == List.begin()) {
		++list_iter;//��λ������
		if (Ele == *(--list_iter)) {//�����һ��ͬ
			++list_iter;//��λ������
			if (Ele == *(++list_iter)) {//����һͬ �� ��һͬ
		//		++list_iter;//�ټ�һ�Ա����Ƿ��ڵ����ڶ���λ��
				if (++list_iter != List.end())//������ǵڶ� �� ���ǵ����ڶ�
					if (Ele == *(list_iter))//ǰ���ĸ������
						return 4;//0 1 0 0
				else return 2;//0 1 0
			}
			else return 0;//��һͬ �� ��һ��ͬ
		}
		else {//��һ��ͬ
			++list_iter;//��λ������
			++list_iter;//�ټ�һ�Ա����Ƿ��ڵ����ڶ���λ��
			if (++list_iter == List.end())	//������ǵڶ�Ҳ�ǵ����ڶ�
				return 0;					//����һ�Ѿ���ͬ
			else {
				--list_iter;
				--list_iter;//��λ������
				if (Ele == *(++list_iter)) {//��һͬ
					if (Ele == *(++list_iter))//�Ҷ�ͬ
						return 1;//1 0 0
					else return 0;//��һͬ �� �Ҷ���ͬ
				}
				else return 0;//��һ��ͬ �� ��һ��ͬ
			}
		}
	}
	++list_iter;//��λ������	
	++list_iter;//�ټ�һ�Ա����Ƿ��ڵ����ڶ���λ��

	//������ڵ����ڶ���λ��
	if (++list_iter == List.end()) {
		--list_iter;
		--list_iter;//��λ
		if (Ele == *(++list_iter)) {//�����һ��ͬ
			--list_iter;//��λ
			if (Ele == *(--list_iter))//�����һ��ͬ
				return 2;//0 1 0
			else return 0;//��һͬ �� ��һ��ͬ
		} else { //��һ��ͬ 
			--list_iter;//��λ
			if (Ele == *(--list_iter)) {//��һ��ͬ
				if (Ele == *(--list_iter))//�����ͬ
					return 3;//0 0 1
				else return 0;//��һͬ �� �����ͬ
			}
			return 0;//��һ��ͬ
		}
	}
	--list_iter;
	--list_iter;//��λ

	//һ�����
	if (Ele == *(--list_iter)) {//��һͬ
		if (Ele == *(--list_iter))//���ͬ
			return 3;//0 0 1
		else {//�����ͬ
			++list_iter;
			++list_iter;//��λ
			if (Ele == *(++list_iter)) {//��һͬ �� ��һͬ
				if (Ele == *(++list_iter))//��һͬ �� ��һͬ �� �Ҷ�ͬ
					return 4;//0 1 0 0
				else return 2;//0 1 0
			}
			else return 0;
		}
	} else {//��һ��ͬ
		++list_iter;//��λ
		if (Ele == *(++list_iter)) {//��һͬ
			if (Ele == *(++list_iter))//�Ҷ�ͬ
				return 1;//1 0 0
			else return 0;
		}
		else return 0;
	}
}

//ɾ��ȷ��������Ԫ��
void remove(list<char>& List,int k,int a,int time_dupli) {//�������Ϊ���ã����еĲ���ֻ�Ƕ�cha_list�ĸ����Ĳ���
	auto iter_be = List.begin();
	auto iter_en = List.begin();
	advance(iter_be, k + 1 - a);//����ʼɾ��λ����Ϊ��/�ĸ��ظ�Ԫ�صĵ�һ��
	advance(iter_en, k + 4 - a + time_dupli - 3);//������ɾ��λ����Ϊ��/�ĸ��ظ�Ԫ��֮���һ������֤��ɾ��ǰ��/�ĸ�
	List.erase(iter_be, iter_en);
}

//��������Ƿ��������Ƿ���������
void swit_remove(list<char>& List, int k, char Ele) {
	int flag = 1;
	int flag_case = 0;//��������Ҫ��kǰ�Ƶĸ���


	while (flag) {
		if (k >= flag_case)//��֤һ��������ָ����������/�ĸ�Ԫ�ص�ǰһ��Ԫ��
			k -= flag_case;
		else k = 0;//ͬʱ�������Ԫ�ػ�ڶ�Ԫ�أ�ֱ��ָ����Ԫ��

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

	char cha[] = { '0' };	//���������Դ洢��ĸ
	cin >> cha;		//���������ַ���������
	int i = 0;		//��ʱ����i
					//�����������ַ�������list
	while (cha[i] != '\0') {
		cha_list.push_back(cha[i]);		//cha_list���Ѿ��������괮
		++i;
	}
	i = 0;

	int n = 0;//Ҫ����n�Σ���ѭ��n��
	cin >> n;

	int k = 0;//����Ϊk�͡�=Element
	char Element = 'a';

	for (i = 0; i != n; ++i) {
		cin >> k >> Element;
		auto iter = cha_list.begin();
		for (int i = 0; i != k; ++i)
			++iter;
		cha_list.insert(iter, Element);

		swit_remove(cha_list, k, Element);//�����Ƿ�ɾ��Ԫ�أ�ɾ���ĸ�Ԫ��

		if (cha_list.size() == 0) {//�������գ�ִ����һ��ѭ��
			cout << '-' << endl;
			continue;
		}

		for (auto iter = cha_list.begin(); iter != cha_list.end(); ++iter)//���������
			cout << *iter << " ";
		cout << endl;
	}
	return 0;
}