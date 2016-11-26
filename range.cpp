#include<iostream>
#include<vector>
using namespace::std;

void merge(vector<int> &vA, int lo, int mi, int hi) {	//��·�鲢
	vector<int> vB;		//����B����
	//lo,mi,hi����A��C��������λ�ã�ֱ������B�ᵼ��Խ��
	int lob = 0, hib = mi - lo;		//����B������lo,hi
	int loc = mi, hic = hi;		//����C������lo,hi
	int temp = lo;
	for (; lob < hib; ++lob)	//A������ǰ���[lo,mi)����B����������[mi,hi)Ĭ����C
		vB.push_back(vA[lo++]);
	lo = temp;
	lob = 0;
	//��·�鲢�Ƚ�B��C
	for (int i = lo, j = lob, k = mi; (j < hib) || (k < hic);) {	//�����������Ҫ���жϣ���Ȼ����Խ�磡
		if ( (k < hic) && ( !(j < hib) || (vA[k] < vB[j]) ) ) vA[i++] = vA[k++];	//��cδ���磩�ң�b���磬��vc�ϴ�
		if ( (j < hib) && ( !(k < hic) || (vB[j] <= vA[k]) ) ) vA[i++] = vB[j++];	//��bδ���磩�ң�c���磬��vb�ϴ�
	}
	vB.resize(0);
}

void mergesort(vector<int> &vA, int lo, int hi) {	//�鲢����0 <= lo < hi <= size
	if (hi - lo < 2) return;	//��Ԫ��������Ȼ����.��� hi - lo = 1�����һֱѭ����ȥ����СΪ2����֤mi�ɲ������߽߱磬Ȼ�󷵻�
	int mi = (lo + hi) / 2;	//�е�
	mergesort(vA, lo, mi);
	mergesort(vA, mi, hi);	//�ֱ����������������ݹ�ֽ�
	merge(vA, lo, mi, hi);	//�鲢
}

int getMi(vector<int> v, int lo, int hi, int e) {
	if ( !(e < v[0]) && !(e > v[v.size()-1]) ) {
		int mi = lo + (hi - lo)*(e - v[lo]) / (v[hi] - v[lo]);
		return mi;
	}
	else if (e < v[0]) return 0;
	else return v.size() - 1;
}

int result_of_Inter(vector<int> v,int lo,int hi,int e) {
	int mi = 0;
	mi = getMi(v, lo, hi, e);//��ȡ���� a ��Ӧ�����
	while ((lo < hi) && (mi != lo) && (mi != hi)) {
		if (v[mi] < e) //mi��С�ˣ�ʹmi���Ʊ��
			lo = mi;
		else if (e < v[mi]) //mi�Ҵ��ˣ�ʹmi���Ʊ�С
			hi = mi;
		else break;
		mi = getMi(v, lo, hi, e);//��ȡ���� a ��Ӧ�����
	}

	return mi;
}

int InterpolationSearch(vector<int> v, int lo, int hi, int a, int b) {//��ֵ����
	int mi = 0;//Ϊ�˷�����㣬hiȡ����v�����һ��Ԫ��
	
	mi = result_of_Inter(v, lo, hi, a);	//�����Ѿ��ҵ��߽� a �Ĵ��λ��
	if (v[mi] < a)  a = ++mi;			//����Ҫ�������ж� a ��һ��ֵ�ڽ������ı߽��ж����Ƿ���
	else a = mi;						//���mi��lo�غϣ�ȡa=mi+1����֤a��Ӧ��ֵ�ܹ�ȡ��
	
	mi = result_of_Inter(v, lo, hi, b);
	if (v[mi] > b)	b = --mi;			//���mi��hi�غϣ�ȡb=mi-1����֤b��Ӧ��ֵ�ܹ�ȡ��
	else b = mi;

	return (b - a + 1);
}

int main() {
	vector<int> v;
	int n = 0, m = 0, a = 0, b = 0;
	cin >> n >> m;	//n,m����ȷ����
	for (int i = 0; i != n; ++i) {	//n�����Ѿ�����vector<int> v
		int temp = 0;
		cin >> temp;
		v.push_back(temp);
	}
	while (m--) {
		cin >> a >> b;	//a,b����

		//��δ����Ԫ���ظ����
		//�ȶ������򣬿��ǹ鲢����
		mergesort(v, 0, (int)v.size());

		//���ڶ�����в��ҡ���ֵ����.
		int loc = 0;
		loc = InterpolationSearch(v, 0, (int)v.size() - 1, a, b);
		cout << loc << endl;
	}
}