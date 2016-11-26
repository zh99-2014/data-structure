#include<iostream>
#include<vector>
using namespace::std;

void merge(vector<int> &vA, int lo, int mi, int hi) {	//二路归并
	vector<int> vB;		//申请B向量
	//lo,mi,hi都是A（C）向量的位置，直接用于B会导致越界
	int lob = 0, hib = mi - lo;		//定义B向量的lo,hi
	int loc = mi, hic = hi;		//定义C向量的lo,hi
	int temp = lo;
	for (; lob < hib; ++lob)	//A向量的前半段[lo,mi)赋给B向量，后半段[mi,hi)默认是C
		vB.push_back(vA[lo++]);
	lo = temp;
	lob = 0;
	//二路归并比较B和C
	for (int i = lo, j = lob, k = mi; (j < hib) || (k < hic);) {	//不出界的条件要先判断！不然容易越界！
		if ( (k < hic) && ( !(j < hib) || (vA[k] < vB[j]) ) ) vA[i++] = vA[k++];	//（c未出界）且（b出界，或vc较大）
		if ( (j < hib) && ( !(k < hic) || (vB[j] <= vA[k]) ) ) vA[i++] = vB[j++];	//（b未出界）且（c出界，或vb较大）
	}
	vB.resize(0);
}

void mergesort(vector<int> &vA, int lo, int hi) {	//归并排序，0 <= lo < hi <= size
	if (hi - lo < 2) return;	//单元素区间自然有序.如果 hi - lo = 1，则会一直循环下去；最小为2，保证mi可插入两边边界，然后返回
	int mi = (lo + hi) / 2;	//中点
	mergesort(vA, lo, mi);
	mergesort(vA, mi, hi);	//分别排序两个向量，递归分解
	merge(vA, lo, mi, hi);	//归并
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
	mi = getMi(v, lo, hi, e);//获取查找 a 对应的轴点
	while ((lo < hi) && (mi != lo) && (mi != hi)) {
		if (v[mi] < e) //mi找小了，使mi右移变大
			lo = mi;
		else if (e < v[mi]) //mi找大了，使mi左移变小
			hi = mi;
		else break;
		mi = getMi(v, lo, hi, e);//获取查找 a 对应的轴点
	}

	return mi;
}

int InterpolationSearch(vector<int> v, int lo, int hi, int a, int b) {//插值查找
	int mi = 0;//为了方便计算，hi取的是v中最后一个元素
	
	mi = result_of_Inter(v, lo, hi, a);	//现在已经找到边界 a 的大概位置
	if (v[mi] < a)  a = ++mi;			//现在要做的是判断 a 这一个值在接下来的边界判断中是否保留
	else a = mi;						//如果mi和lo重合，取a=mi+1，保证a对应的值能够取到
	
	mi = result_of_Inter(v, lo, hi, b);
	if (v[mi] > b)	b = --mi;			//如果mi和hi重合，取b=mi-1，保证b对应的值能够取到
	else b = mi;

	return (b - a + 1);
}

int main() {
	vector<int> v;
	int n = 0, m = 0, a = 0, b = 0;
	cin >> n >> m;	//n,m可正确读入
	for (int i = 0; i != n; ++i) {	//n个数已经读入vector<int> v
		int temp = 0;
		cin >> temp;
		v.push_back(temp);
	}
	while (m--) {
		cin >> a >> b;	//a,b读入

		//暂未考虑元素重复情况
		//先对其排序，考虑归并排序
		mergesort(v, 0, (int)v.size());

		//现在对其进行查找。插值查找.
		int loc = 0;
		loc = InterpolationSearch(v, 0, (int)v.size() - 1, a, b);
		cout << loc << endl;
	}
}