#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace::std;

bool Pushinto_B(stack<int>& S_temp, vector<string>& S_acting, int& A, int nowNumber, int Max_size_S) {
	//if B can be formed, next number is the top of S
	//or it is in A
	//otherwise B cannot be formed
	if (!S_temp.empty()) {//S is not empty
		if (nowNumber == S_temp.top()) {//if now number is top of S
			S_temp.pop();//nownumber is push into B and then deleted
			S_acting.push_back("pop");
			return true;
		}
	}
	if (nowNumber >= A) {
		while (nowNumber >= A) {//if now number is smaller than or equal with numbers in A
								//that means now number is in A
			if (S_temp.size() < Max_size_S) {
				S_temp.push(A);
				S_acting.push_back("push");
				++A;//push all numbers into S until A+1
			} else {//S does not have enough room for another number
				if (nowNumber == A) {//if nownumber is A, just put push into B, consider it is true
					++A;
					return true;
				}
				else return false;
			}
		}
		S_temp.pop();//nownumber(top number of S) is push into B and then deleted
		S_acting.push_back("pop");
		return true;
	}
	else return false;//B cannot be got by S
}

int main() {
	stack<int> S_temp;//S for stack
	int n, m;//set up n for size of A, m for the largest size of S
	cin >> n >> m;
	vector<int> B_final;//set up a vector for B
	vector<string> S_acting;//set up a vector for what is doing to S
	for (int i = 0; i < n; ++i) {
		int temp = 0;
		cin >> temp;
		B_final.push_back(temp);//push element got from keyboard into B
	}

	bool push = false;
	int A = 1;//consider A as an array contains 1,2,3...n
	for (int i = 0; i != n; ++i) {//which is the number used in B looping
		push = Pushinto_B(S_temp, S_acting, A, B_final[i], m);
		if (!push) {//if Pushinto B got something wrong
			cout << "No" << endl;
			break;
		}
	}

	if (push)
		//if we want string in vector be output by iterator
		//we must include string.h
		//otherwise ostream cannot be convert to string
		for (auto iter = S_acting.begin(); iter != S_acting.end(); ++iter)
			cout << *iter << endl;
	
	return 0;
}