//Muhammad Umair Khalid
//21I-0455
//B-CS
#include <iostream>
#include<fstream>
#include<string>
#include <vector>
using namespace std;


#define INT_MAX 999999		//To initialize an Infinity Value


				//The Variable were initially made local but converted them to
				//global to use less stack while recursion; Efficient Approach

vector<char> Vertices;					//Creating a vector to store Vertices Names
vector<int> Waits;						//This Vector stores the time that the robot
//has to wait at each vertex

int V = 0;								// V as Total NUmber of Vertices
int** adj = NULL;						//Adjacency Matrix

int TT = 0;								//Stores Total Time limit

int wait_time = 0;						//To Store Total Time the Robot takes at every stop
int* path = NULL;						//A 1D array to store traversed path
int p_idx = 1;							//Path array index
bool feasible = false;					//To show if path is feasible or not
int min_sum = 999999;					//To store 

//Function to Run Test Cases
bool Handle_File(string f_name) {


	ifstream file(f_name);

	if (file.is_open()) {

		//cout << "File was Successfully Opened" << endl;

		string temp;						//String that stores the text line
		temp.clear();
		int counter = 0;

		while (!file.eof()) {					//Run untill end of file

			getline(file, temp);				//To retrieve a single line from file

			if (counter == 0) {					//For Vertices

				counter++;
				char c;

				for (int i = 0; temp[i] != '\0'; i++) {				//Loop to Count Total Number of Vertices
					c = temp[i];

					if (c == '{') {				//Start when first Bracket found
						i++;
						c = temp[i];
						while (c != '}') {

							if (c != ',') {
								V++;
								Vertices.push_back(c);				//Pushing vertices in a Char Vector to store thier names
								Waits.push_back(0);				//At the same time assigning their wait time as zero; will be updated afterwards
							}

							i++;
							c = temp[i];
						}
					}
				}

				adj = new int* [V] {0};
				for (int i = 0; i < V; i++) {				//Initializing 2D Dynamic Adjacency Matrix
					adj[i] = new int[V] {0};
				}
				temp.clear();								//Clearing temp string to store next line

			}
			else if (counter == 1) {			//For Edges
				counter++;

				string weight;
				weight.clear();
				getline(file, weight);			//getting Weight line as well and inserting edge and weight at the same time
				counter++;
				int w = 0;

				for (int i = 0; weight[i] != '\0'; i++) {			//Loop To get the First Weight Value for First Edge
					if (weight[i] == '{') {					//Start when first Bracket found
						w = i + 1;
						break;
					}
				}
				string wc;
				wc.clear();

				w = w - 2;			//Doing this so that can set W to a right starting point


				//wc = wc + weight[w];				//To store Weight Value
			
				//if (weight[w + 1] != ',') {

				//	for (int l = w+1; weight[l] != ','; l++) {
				//		wc = wc + weight[l];
				//		w++;
				//	}
				//}
				char c;
				int m = 0;
				int n = 0;

				for (int i = 0; temp[i] != '\0'; i++) {				//Loop to check Edges bw Vertices
					c = temp[i];

					if (c == '{') {

						while (c != '}') {

							w = w + 2;			//Moving Plus 2 in Weight line and getting Weight Value
							wc = wc + weight[w];

							if (weight[w + 1] != ',' && weight[w + 1] != '}') {

								for (int l = w + 1; weight[l] != ',' && weight[l] != '}'; l++) {
									wc = wc + weight[l];
									w++;
								}
							}

							i = i + 2;
							c = temp[i];				//Now pointer at " ( "

							for (int j = 0; j < V; j++) {

								if (Vertices[j] == c) {	//Gets the Index value from 2nd Vertices from Vector by their Char Name
									m = j;
									break;
								}
							}
							
							i = i + 2;
							c = temp[i];				//Now pointer at " , "

							for (int j = 0; j < V; j++) {

								if (Vertices[j] == c) {		//Gets the Index value from 2nd Vertices from Vector by their Char Name
									n = j;
									break;
								}
							}

							i = i + 2;				//Now pointer at " ) "
							c = temp[i];
							adj[m][n] = stoi(wc);			//Converting Char Weight to Int
							adj[n][m] = stoi(wc);			//And storing in Adj Maatrix  A->B;B<-A
							wc.clear();

							
						}
					}

				}

				temp.clear();			//Clearing temp String

			}
			else if (counter == 2) {				//For Weights Line 

				counter++;				//Now need to check weights line here as weights we already assigned while
										//checking for Edges between Vertices

			}
			else if (counter == 3) {				//For Wait times
				int idx = 0;
				counter++;
				char c;
				for (int i = 0; temp[i] != '\0'; i++) {			//Loop runs till Retrieved Wait line doesnt end
					c = temp[i];

					if (temp[i] == '(') {			//TO find First ' ( '
						i++;
						c = temp[i];

						for (int j = 0; j < V; j++) {

							if (Vertices[j] == c) {
								idx = j;					//Finding the index from Vertice Vector acording to Vertice Name
								break;
							}
						}

						i++;
					}

					if (temp[i] == '=') {			//When found First  " = " in Wait line

						i++;
						c = temp[i];


						if (temp[i + 1] != ',' && temp[i + 1] != '\0') {

							i++;
							string tm;
							tm.clear();
							tm = tm + c;

							while (temp[i] != ',' && temp[i] != '\0') {			//To Run till Next Comma or eof line
								tm = tm + temp[i];
								i++;
							}
							
																	//if Value is 2 or 3 digit #stirng
							//Waits.insert(idx,stoi(tm));
							wait_time = wait_time + stoi(tm);
							Waits.insert(Waits.begin() + idx, stoi(tm));		//Insert Wait Value in Vector According to Index

							i--;		//Decreasing i by one to restore pointer to " , "
						}
						else {
																	//if Value is 1 digit #char
							/*cout << idx << "," << c << " ";*/
							wait_time = (wait_time +( int(c) - 48) ) ;
							Waits.insert(Waits.begin() + idx, int(c) - 48); 		//Insert Wait Value in Vector According to Index
						}
					}

				}
				temp.clear();
			}
			else if (counter == 4) {				//For Total Time
				counter++;
				string t;
				t.clear();
				for (int i = 0; temp[i] != '\0'; i++) {

					if (temp[i] == '=') {				//Start when First Found =
						i++;
						while (temp[i] != '\0') {
							t = t + temp[i];			//Keep getting the number untill not end of line
							i++;
						}
						break;
					}
				}
				TT = stoi(t);			//Storing Total Time Limit
			}
		}
		file.close();


		
	}
	else {
		cout << "Failed To Open File :(" << endl;			//Return And Show error if file not opened successfully
		return false;
	}

	return true;			//Return true if all went smooth :)
}

//(starting vertice, current pos ,max visited value,Adjacency Mat , Total Vertices, Distinct Values )
int  Shortest_Path (int mask, int pos, int IF_ALL_VISITED_VAL, int** &ds) {
	
		if (mask == IF_ALL_VISITED_VAL) {			//If all vertices have been visited return back to the pervious vertice

			if (adj[path[V-1]][0] > 0) {			//if the last element of path has an edge with the strating point

				int sum = 0;
				path[V] = 0;
				for (int i = 0; i < V; i++) {
					sum = sum + adj[path[i]][path[i + 1]];				//Finding sum of traversed path
				}
				sum = sum + wait_time;
				bool flag = false;

				if (sum <= TT) {
					
					flag = true;					//If less than time limit
				}

				if (flag == true) {
					feasible = true;						//To show that there exists atleast one feasible path

					if (sum < min_sum) {
						min_sum = sum;
					}
					for (int i = 0; i < V; i++) {
						cout << Vertices[path[i]] << " ";					//Printing Path traversed
					}

					cout << Vertices[path[0]] << " = " << sum << endl;					//Printing last vertice and sum
				}
			}

			return adj[pos][0];				//with weight value + Robot Wait time at vertex
		
		}
		//Dynamic Programming Happens here
		else if (ds[mask][pos] != -1) {		//here it check if there is any value in Mask Table

			return ds[mask][pos];				//If yes then reutrn it

		}
		else {

			int ans = INT_MAX;		//Current ans value is infinity; will change when any min value is found

			//This loop visits all the unvisited vertices
			for (int cur_vertice = 0; cur_vertice < V; cur_vertice++) {

				// if we take AND bw initial Mask Value 0001 and Current Mask value the previous
				// bit to the current mask moves one up so we get to know if the previous value 
				// was 1 or 0 which tell if previous node was visited or not

				if ((mask & (1 << cur_vertice)) == 0 && adj[pos][cur_vertice] > 0) { //AND's the Mask value with current vertice mask
														//if value 0 then path incomplete node was not visited
						
					path[p_idx] = cur_vertice;			//To store the vertice that is now going to be visited
					p_idx++;
					//Real Magic Happens Here
					int newAns = adj[pos][cur_vertice] +
						Shortest_Path (mask | (1 << cur_vertice), cur_vertice, IF_ALL_VISITED_VAL, ds);
				
					//From the New and Previous Answer use the Minimum One
					ans = min(ans, newAns);

					path[p_idx] = -1;				//To Recur back vertices in the path
					p_idx--;
				}

			}

			return ds[mask][pos] = ans;			//insert the final weight value in distinct
		}

	}
	

int main() {

	string f_name =  "C:\\Users\\umair\\OneDrive\\Desktop\\New folder\\i210455_B\\P2_test1.txt";			//Stored file name
	string ext = ".txt";
	string st;
	int test = 0;

	cout << "\t\t\t\t\t|| Welcome  To  Travelling  Salesman  Problem ||" << endl<<endl;
	cout << "\t\t\tEnter The Number of Test Cases "<<endl;
	cout << "\t\t\tAnswer = ";
	cin >> test;
	test = test + 1;

	bool flag = false;
	for (int p = 1; p < test; p++) {
	
		f_name.clear();
		f_name = "C:\\Users\\umair\\OneDrive\\Desktop\\New folder\\i210455_B\\P2_test1.txt";
		cout << endl;
		st = to_string(p);
		f_name = f_name + st + ext;
		cout << "Test : " << p << endl;

		flag = Handle_File(f_name);	//Reads test case and initializes  Varibles and Matrix	

		if (flag == false) {
			//cout << "Unable to Read File:(";		//If file failed return with error			
			cout << endl;
			return 0;
		}


		int s1 = pow(2, V);								//Storing 2^N
	
		int** distinct_states = new int* [s1];
		for (int i = 0; i < s1; i++) {					//A 2D Dynamic array to Bitmasking
			distinct_states[i] = new int[V];			//Stores weight values on the basis of Bitmask
		}

		for (int i = 0; i < s1; i++) {
			for (int j = 0; j < V; j++) {				//Initially Initializing to Zero
				distinct_states[i][j] = -1;
			}
		}

		path = new int[V+1];
		// Initialize the path array
		for (int i = 0; i < V+1; i++) {
			path[i] = -1;
		}
		path[0] = 0;

		//(1 << V ) = 2^N 
		int IF_ALL_VISITED_VAL = (1 << V) - 1;			//Use to store the end val that shows if all vertices have 
		//been visited; acts as a base case

		//(starting vertice, current pos ,max visited value,Adjacency Mat , Total Vertices, Distinct Values )
		int temp_time = Shortest_Path(1, 0, IF_ALL_VISITED_VAL, distinct_states);


		if (feasible == false) {
			cout << "No Feasible Path Available :(" << endl;
		}
		else {
			cout << "The Minimum Weighted Path is of = " << min_sum << endl;
		}

		Vertices.clear();
		Waits.clear();

		V = 0;								// V as Total NUmber of Vertices
		TT = 0;								//Stores Total Time limit
		wait_time = 0;
		for (int z = 0; z < V; z++) {
			delete[] adj[z];
		}
		delete[] adj;						//Adjacency Matrix

		for (int z = 0; z < s1; z++) {
			delete[] distinct_states[z];				//Deleting Memo Array
		}
		delete[] distinct_states;

		p_idx = 1;
		feasible = false;
		min_sum = 999999;
		delete[] path;						//Deleting path array
	}

	return 0;
}