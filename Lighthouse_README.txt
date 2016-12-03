Tsinghua Online Judge
����(LightHouse)
________________________________________
Description
As shown in the following figure, If another lighthouse is in gray area, they can beacon each other.
 
For example, in following figure, (B, R) is a pair of lighthouse which can beacon each other, while (B, G), (R, G) are NOT.
 
Input
1st line: N
2nd ~ (N + 1)th line: each line is X Y, means a lighthouse is on the point (X, Y).
Output
How many pairs of lighthourses can beacon each other
( For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same )
Example
Input
3
2 2
4 3
5 1
Output
1
Restrictions
For 90% test cases: 1 <= n <= 3 * 105
For 95% test cases: 1 <= n <= 106
For all test cases: 1 <= n <= 4 * 106
For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same.
1 <= x, y <= 10^8
Time: 2 sec
Memory: 256 MB
Hints
The range of int is usually [-231, 231 - 1], it may be too small.
����
��������������Ϊ��·��ֻ������
 
��ͼһ��
��ͼһ��ʾ��ÿ������������һյ̽�յƣ������䶫�������������Զ���ֱ������̽�յƵĹ���֮�����Ը����κξ��롣�������������֮С�����Լٶ����ǲ���˴��ڵ���
 
��ͼ����
������A��B���ڶԷ���������Χ�ڣ���������ܹ������˴ˡ�������ͼ����ʵ���У�����������������˴ˣ������̵������ǣ��졢�̵���Ҳ���ǡ�
���ڣ������κ�һ������ĵ����������������ж��ٶԵ����ܹ������˴ˡ�
����
��n+1�С�
��1��Ϊ1������n����ʾ������������
��2��n+1��ÿ�а���2������x, y���ֱ��ʾ�������ĺᡢ�����ꡣ
���
1����������ʾ�������˴˵ĵ����Ե�������
����
��Ӣ������
����
����90%�Ĳ�����1 �� n �� 3��105
����95%�Ĳ�����1 �� n �� 106
ȫ��������1 �� n �� 4��106
����������x, y���������Ҳ�ͬ������x, y���������
1 �� x, y �� 10^8
ʱ�䣺2 sec
�ڴ棺256 MB
��ʾ
ע����������ͱ����ķ�Χ��C/C++�е�int����ͨ���������32λ�������䷶ΧΪ[-231, 231 - 1]����һ���㹻���ɱ���������
________________________________________
UI powered by Twitter Bootstrap.
Tsinghua Online Judge is designed and coded by Li Ruizhe.
For all suggestions and bug reports, contact oj[at]liruizhe[dot]org.

