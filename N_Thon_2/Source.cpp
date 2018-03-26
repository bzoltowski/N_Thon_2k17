#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

struct Point2D {
	int x;
	int y;
};

int solution(vector<Point2D> &A)
{
	if (A.size() < 3)
		return 0;
	int AllTriplets = 0; //count of all triplets
						 /* 0<=P<Q<R<N */
	for (int i = 0; i < A.size() - 2; i++) // 0 <= P=i < Q=j
	{
		for (int j = i + 1; j < A.size() - 1; j++) // P=i < Q=j < R=k
		{
			int a, b;
			// y1= a*x1 + b
			int x1 = A[i].x;
			int y1 = A[i].y;
			// y2= a*x2 + b
			int x2 = A[j].x;
			int y2 = A[j].y;

			if ((x1 - x2) != 0)
			{
				a = (y1 - y2) / (x1 - x2);
				b = y2 - (a*x2);
				/*a and b could not be correct value bc we use only integer numbers,
				so let's check x1 and x2 with a and b return correct y1 and y2, if yes, then search for third point */
				if ((y1 == (a*x1 + b)) && (y2 == (a*x2 + b)))
				{
					cout <<endl<< "X1:" << x1 << " Y1:" << y1 << " " << i << endl;
					cout << "X2:" << x2 << " Y2:" << y2 << " " << j << endl;
					for (int k = j + 1; k < A.size(); k++) // Q=j < R=k < N=(sizeof vector A)
					{
						cout << endl << "X1:" << x1 << " Y1:" << y1 << " " << i << endl;
						cout << "X2:" << x2 << " Y2:" << y2 << " " << j << endl;
						cout << "X3:" << A[k].x << " Y3:" << A[k].y << " " << k << endl;
						cout << "Y= " << a << "X - " << b << endl;
						if (A[k].y == (a*A[k].x + b)) // y3 = a*x3 + b
						{
							AllTriplets++;
							cout << "############################" << endl;
						}
					}
				}
			}
		}
	}
	if (AllTriplets < 100000000)
		return AllTriplets;
	else
		return -1;
}

int main()
{

	vector<Point2D> A(7);
	A[0].x = 0; A[0].y = 0;
	A[1].x = 1; A[1].y = 1;
	A[2].x = 2; A[2].y = 2;
	A[3].x = 3; A[3].y = 3;
	A[4].x = 3; A[4].y = 2;
	A[5].x = 4; A[5].y = 2;
	A[6].x = 5; A[6].y = 1;
	cout <<"SOLUTION: "<<solution(A)<<endl;
	_getch();
	system("PASUE");
	return 0;
}

