#include <bits/stdc++.h> 
using namespace std; 

struct ProcessTable { 
	int processno; 
	int burst_time;  
	int arrival_time;  
}; 

// Function to find the waiting time for all processes 
void CalculateWaitingTime(ProcessTable processindex[], int n, int wt[]) 
{ 
	int copyb[n]; 

	// Copy the burst time into copyb[] 
	for (int i = 0; i < n; i++) 
		copyb[i] = processindex[i].burst_time; 

	int complete = 0, t = 0, minimumof = INT_MAX; 
	int smallest = 0, compeletion; 
	bool crosscheck = false; 

	// Process until all processes gets completed 
	while (complete != n) 
	{ 

		// Find process with minimum remaining time among the processes that arrives till the current time
		for (int j = 0; j < n; j++) { 
			if ((processindex[j].arrival_time <= t) && (copyb[j] < minimumof) && copyb[j] > 0) 
			{ 
				minimumof = copyb[j]; 
				smallest = j; 
				crosscheck = true; 
			} 
		} 

		if (crosscheck == false) { 
			t++; 
			continue; 
		} 

		// Reduce remaining time by one 
		copyb[smallest]--; 

		// Update minimum 
		minimumof = copyb[smallest]; 
		if (minimumof == 0) 
			minimumof = INT_MAX; 

		// If a process gets finished
		if (copyb[smallest] == 0) { 

			// Increment complete 
			complete++; 
			crosscheck = false; 

			// Find finish time of current process 
			compeletion = t + 1; 

			// Calculate waiting time 
			wt[smallest] = compeletion - 
						processindex[smallest].burst_time - 
						processindex[smallest].arrival_time; 

			if (wt[smallest] < 0) 
				wt[smallest] = 0; 
		} 
		// Increment time 
		t++; 
	} 
} 

// Function to calculate turn around time 
void CalculateTurnAround(ProcessTable processindex[], int n, int wt[], int tat[]) 
{ 
	// calculating turn around
	for (int i = 0; i < n; i++) 
		tat[i] = processindex[i].burst_time + wt[i]; 
} 

// Function to calculate average time 
void CalculateAverage(ProcessTable processindex[], int n) 
{ 
	int wt[n], tat[n], total_wt = 0, total_tat = 0; 

	// Function to find waiting time of all processes 
	CalculateWaitingTime(processindex, n, wt); 

	// Function to find turn around time for
	CalculateTurnAround(processindex, n, wt, tat); 

	// Display processes
	cout << "Processes "
		<< " Burst time "
		<< " Waiting time "
		<< " Turn around time\n"; 

	// Calculating total waiting time and total turnaround time 
	for (int i = 0; i < n; i++) { 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		cout << " " << processindex[i].processno << "\t\t"
			<< processindex[i].burst_time << "\t\t " << wt[i] 
			<< "\t\t " << tat[i] << endl; 
	} 

	cout << "\nAverage Waiting Time = "<< (float)total_wt / (float)n; 
	cout << "\nAverage Turn Around Time = "<< (float)total_tat / (float)n; 
} 

int main() 
{ 
	ProcessTable processindex[] = 
	{
	 { 1, 6, 0 }, { 2, 2, 3 } , { 3, 1, 5 } , { 4, 7, 9 } , { 5, 5,10} ,
	 { 6, 3, 12}, { 7, 4, 14} , { 8, 5, 16} , { 9, 7, 17} , {10, 2,19}
					
	}; 
					
	int n = sizeof(processindex) / sizeof(processindex[0]); 
	CalculateAverage(processindex, n); 
	return 0; 
} 

