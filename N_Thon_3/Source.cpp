#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>

using namespace std;
/*	Standard BST but I add one variable "index", this variable hold original index from vector A 	*/
struct node
{
	int data;
	int index;
	struct node *Left, *Right;
};

struct node *newNode(int key, int index_key)
{
	struct node *nD = (struct node*)malloc(sizeof(struct node));
	nD->data = key;
	nD->index = index_key;
	nD->Left = nD->Right = NULL;
	return nD;
}

struct node *insert(struct node *root, int key, int index_key)
{
	if (root == NULL)
		return newNode(key, index_key);
	if (root->data >= key)
		root->Left = insert(root->Left, key, index_key);
	if (root->data < key)
		root->Right = insert(root->Right, key, index_key);
	return root;
}

void AddToVector(struct node* root, vector<int> &IndexKey, vector<int> &Key, int &tmp)
{
	if (root)
	{
		AddToVector(root->Left, IndexKey, Key, tmp);
		IndexKey[tmp] = root->index;
		Key[tmp] = root->data;
		tmp++;
		AddToVector(root->Right, IndexKey, Key, tmp);
	}
}

int solution(vector<int> &A) {
	// write your code in C++14 (g++ 6.2.0)
	if ((A.size() < 2) || A.size() > 40000 )//not empty but we need minimum two numbers :)
		return -1;

	int distance = 40001;// sth larger than 40 000
						 //Create two new vectors, where IdxVec is vector with orginal indexs from vector A
						 //and vector Vec with sorted values from vector A
	vector<int> IdxVec(A.size());
	vector<int> Vec(A.size());//this vector may not exist if function "solution" don't have vector A like reference

							  //set first root in BST	
	struct node *root = NULL;
	root = insert(root, A[0], 0);
	//Adding values to BST
	for (int i = 1; i < A.size(); i++)
		insert(root, A[i], i);

	//Adding sorted values to vectors IdxVec & Vec 
	int index = 0;
	AddToVector(root, IdxVec, Vec, index);

	/* Calculating the distance from smallest to largest value in sorted vector */
	int tmpValue = Vec[0];
	int tmpIndex = 0;
	for (int i = 1; i < A.size(); i++)
	{
		//Values in vector can't be this same
		if (Vec[i] != tmpValue && (abs(IdxVec[i] - IdxVec[tmpIndex]) < distance))
		{
			distance = abs(IdxVec[i] - IdxVec[tmpIndex]);
			/*need this loop below if we have a few this same values in sorted vector,
			for example:
			IdxVec={1,4,3}//original index from vector A
			Vec={1,3,3}//sorted vector
			tmp=Vec[0]=1
			i=1,j=2
			Vec[i]=Vec[j]=3
			but distance is smallest from IdxVec[0]=1 to IdxVec[j]=3 than from IdxVec[0]=0 to IdxVec[i]=4*/
			for (int j = i + 1; j < A.size(); j++)
			{
				if (Vec[j] == Vec[i])
				{
					if (abs(IdxVec[j] - IdxVec[tmpIndex]) < distance)
						distance = abs(IdxVec[j] - IdxVec[tmpIndex]);
				}
				else
				{
					i = j - 1;// -1, bc i++ in main loop
					tmpValue = Vec[j - 1];
					tmpIndex = j - 1;
					break;
				}
			}
		}
		else
		{
			tmpValue = Vec[i];
			tmpIndex = i;

		}


	}
	/* this same calculating but from largest to smallest value */
	tmpValue = Vec[A.size() - 1];
	tmpIndex = A.size() - 1;
	for (int i = A.size() - 2; i >= 0; i--)
	{
		if (Vec[i] != tmpValue && (abs(IdxVec[i] - IdxVec[tmpIndex]) < distance))
		{
			distance = abs(IdxVec[i] - IdxVec[tmpIndex]);
			for (int j = i - 1; j >= 0; j--)
			{
				if (Vec[j] == Vec[i])
				{
					if (abs(IdxVec[j] - IdxVec[tmpIndex]) < distance)
						distance = abs(IdxVec[j] - IdxVec[tmpIndex]);
				}
				else
				{
					i = j + 1;
					tmpValue = Vec[j + 1];
					tmpIndex = j + 1;
					break;
				}
			}
		}
		else
		{
			tmpValue = Vec[i];
			tmpIndex = i;
		}
	}
	/*	End of calculating	*/
	if (distance == 400001)//if no adjacent indices exist
		return -1;
	return distance;//else return smallest distance
}



int main() {
	vector<int> A(8);
	A = { 0,3,3,7,5,3,11,1 };
	vector<int> B(6);
	B = { 1,4,7,3,3,5 };
	cout << "A : " << solution(A) << endl;
	cout << "B : " << solution(B) << endl;
	system("PAUSE");
	return 0;
}
//int solution(vector<int> &A) {
//	if (A.size() < 2)//not empty but we need minimuum 2indence :)
//		return -1;
//	int distance = 400001;//sth bigger than max index(not value) in array/vector
//	//in current exercise index can't be bigger than 40.000
//	for (int i = 0; i < A.size() - 1; i++)//0<= P=i < Q 
//	{
//		for (int j = i + 1; j < A.size(); j++)//P=i < Q=j < N=(sizeof vector A)
//		{
//			if (A[i] != A[j]) //A[P] != A[Q]
//			{
//				bool adjacent = 0;//1 if loop below find sth between A[P] and A[Q]
//				for (int k = 0; k < A.size(); k++)
//				{
//					if (((A[i] < A[j]) && (A[k] > A[i] && A[k] < A[j])) || ((A[j] < A[i]) && (A[k] > A[j] && A[k] < A[i])))
//					{
//						adjacent = 1;
//						break;
//					}
//				}
//				if (!adjacent && (abs(i - j) < distance))
//					distance = abs(i - j);
//			}
//		}
//
//	}
//	if (distance == 400001)//now know, any adjacent doesn't exist
//		return -1;
//	return distance;//but if exist then return lowest distance 
//}
//
//int main() {
//
//	vector<int> A(8);
//	A = { 0,3,3,7,5,3,11,1 };
//	vector<int> B(6);
//	B = { 1,4,7,3,3,5 };
//	cout << "A : " << solution(A) << endl;
//	cout << "B : " << solution(B) << endl;
//	_getch();
//	return 0;
//}



