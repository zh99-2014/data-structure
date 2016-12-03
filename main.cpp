#include<iostream>
#include<vector>
using namespace::std;

struct Coordinate {//set up coordinates of a point
	int x;
	int y;
};

//merge function
void merge(vector<Coordinate> &V_Points, int lo, int mi, int hi,int &count) {
	vector<Coordinate> Vb_Points;//ask for new V_Points named b
	int loa = lo, hia = hi;
	int lob = 0, hib = mi - lo;
	int loc = mi, hic = hi;//set up flags of vector a,b,c
//	int count = 0;//for counting the number of pairs of points
	for (; loa != mi;)//copy Vb from Va
		Vb_Points.push_back(V_Points[loa++]);
	loa = lo;
	//new Vb is ready

	//bug: elements in the smaller vector can only be examed once
	//perhaps it will miss the the other elements in bigger vector
	//e.g. c:(1,1),(2,2),(3,3)
	//	   b:(4,4),(5,5)
	//we will get (1,4),(2,4),(3,4) and miss pairs of 5

	for (int i = loa, j = lob, k = loc; (j < hib) || (k < hic);) {
		if (k < hic) {//c is in range
			if (j < hib) {//b is in range
				if (V_Points[k].x < Vb_Points[j].x) {//c is smaller
					V_Points[i] = V_Points[k];//c is assigned for a
					int temp = j;//do loop with the copy of j
								 //j is in range and smaller c is compared with b whose x larger than c
					while (temp < hib && V_Points[k].y <= Vb_Points[temp++].y)
						++count;
				//	if (V_Points[i].y <= Vb_Points[j].y)//c is smaller in both x && y
				//		++count;
					++i; ++k;
				}
			} else {
				V_Points[i] = V_Points[k];//c is assigned for a
				++i; ++k;
			}
		}
		if (j < hib) {//b is in range
			if (k < hic) {//c is in range
				if (Vb_Points[j].x <= V_Points[k].x) {//b is smaller or equal with c
					V_Points[i] = Vb_Points[j];//b is assigned for a
					int temp = k;//do loop with the copy of k
								 //k is in range and smaller b is compared with c whose x is larger than b
					while (temp < hic && Vb_Points[j].y <= V_Points[temp++].y)
						++count;
				//	if (Vb_Points[j].y <= V_Points[k].y)//b is smaller in both x && y
				//		++count;
					++i; ++j;
				}
			} else {
				V_Points[i] = Vb_Points[j];//b is assigned for a
				++i; ++j;
			}
		}


/*	for (int i = loa, j = lob, k = loc; (j < hib) || (k < hic);) {
		if ((k < hic) && (!(j < hib) || (V_Points[k].x < Vb_Points[j].x)))//c is in range, and (b is out or c is smaller)
			V_Points[i++] = V_Points[k++];//c is assigned for a
		if ((j < hib) && (!(k < hic) || (Vb_Points[j].x <= V_Points[k].x)))//b is in range, and (c is out or b is smaller)
			V_Points[i++] = Vb_Points[j++];//b is assigned for a
*/	}

}

//mergesort function
void mergesort(vector<Coordinate> &V_Points,int lo,int hi,int &count) {
	if (hi - lo < 2) return;//basis of recursion
	int mi = (lo + hi) / 2;//set up middle point
	mergesort(V_Points, lo, mi, count);
	mergesort(V_Points, mi, hi, count);
	merge(V_Points, lo, mi, hi, count);//merge two parts of a vector
}

int main() {
	Coordinate Point;//set up a point
	vector<Coordinate> V_Points;//set up a vector of points
	int n = 0;//n means the amount of lighthouses(points)
	cin >> n;
	for (int i = 0; i != n; ++i) {
		cin >> Point.x >> Point.y;//get in the coordidnates of a point
		V_Points.push_back(Point);//push back points into vector
	}
	//now we have a vector contains points(x, y)

	int count = 0;//for counting the number of pairs of points
	//sort the vector with mergesort
	mergesort(V_Points, 0, V_Points.size(), count);
	cout << count << endl;
	return 0;
}