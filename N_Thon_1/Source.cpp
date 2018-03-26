int solution(vector<int> &A) {
	/*	If Vector A is empty then return 0	*/
	if (A.size() == NULL)
		return 0;

	bool status = NULL; //initialize in first loop below
	int i = 1;
	int CriticalPoints = 1; // count of all critical points
	/*	Loop to search second critical point and initialize first (bool)status	*/
	for (; i < A.size(); i++)
	{
		if (A[i] > A[i-1])
		{
			status = 1;// True if hill
			CriticalPoints++;
			break;
		}
		if (A[i] < A[i - 1])
		{
			status = 0;//False if valley
			CriticalPoints++;
			break;
		}
	}
	/*	If first loop end without break and 'i' is equal size of vector A, then
	all items in this vector have this same value, so return CriticalPoints (== 1)	*/
	if (i == A.size())
		return CriticalPoints;
	/*  Else, search all critical points in this vector and return their count  */
	for (; i < A.size(); i++)
	{
		if ((status && A[i] < A[i - 1]) || (!status && A[i] > A[i - 1]))
		{
			CriticalPoints++;
			status = !status;
		}
	}

	return CriticalPoints;
}