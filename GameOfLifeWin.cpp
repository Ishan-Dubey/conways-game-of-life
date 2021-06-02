/* CONWAY'S GAME OF LIFE
 * Implemented by Ishan Dubey
 * 
 * "People think that mathematics is complicated.
 * Mathematics is the simple bit,
 * it’s the stuff we CAN understand.
 * It’s cats that are complicated."
 * - John Conway
 */

#include<bits/stdc++.h>
using namespace std;
void welcome(){
	//Print the welcome message.
	cout<<"CONWAY'S GAME OF LIFE\n";
	cout<<"Programmed by Ishan Dubey\n";
	cout<<endl;
	cout<<"The rules are simple:\n";
	cout<<"1. Any live cell with two or three live neighbours lives on to the next generation.\n";
	cout<<"2. Any live cell with fewer than two live neighbours dies of loneliness.\n";
	cout<<"3. Any live cell with more than three live neighbours dies of overcrowding.\n";
	cout<<"4. Any dead cell with exactly three live neighbours comes back to life.\n";
	cout<<endl;
	cout<<"Press ENTER to begin. (Ctrl+C to exit)\n";
	getchar();
}
void is_alive(vector<vector<bool> >& grid, vector<vector<bool> >& gen, int i, int j){
	/* Iterate through the neighbors of a cell
	 * and mark the cell alive or dead in the next
	 * generation accoring to the rules
	 */
	vector<int> x = {-1, -1, -1, 0, 0, 1, 1, 1};
	vector<int> y = {-1, 0, 1, -1, 1, 0, 1, -1};
	int neighbors = 0;
	for(int next=0; next<8; next++){
		if(grid[i+x[next]][j+y[next]]){
			neighbors++;
		}
	}
	if(grid[i][j]==true && (neighbors==2 || neighbors==3)){
		gen[i][j] = true;
		return;
	}
	if(grid[i][j]==false && neighbors==3){
		gen[i][j] = true;
		return;
	}
	else{
		gen[i][j] = false;
		return;
	}
}
void print_grid(vector<vector<bool> >& grid, int rows, int cols){
	// Print the current generation inside a box
	cout<<" ";
	for(int x=1; x<=cols; x++){
		cout<<"_";
	}
	cout<<"\n";
	for(int i=1; i<=rows; i++){
		cout<<"|";
		for(int j=1; j<=cols; j++){
			if(grid[i][j]){
				cout<<"O";
			}
			else{
				cout<<" ";
			}
		}
		cout<<"|\n";
	}
	cout<<" ";
	for(int x=1; x<=cols; x++){
		cout<<"_";
	}
	cout<<"\n";
}
int main(){
	welcome();
	int rows, cols, speed;
	rowHandle:
	cout<<"Enter height of grid: ";
	cin >> rows;
	if(rows<=0){
		cout<<"Height must be positive\n";
		goto rowHandle;
	}
	colHandle:
	cout<<"Enter width of grid: ";
	cin >> cols;
	if(cols<=0){
		cout<<"Width must be positive\n";
		goto colHandle;
	}
	speedHandle:
	cout<<"Enter speed (1-10): ";
	cin >> speed;
	if(speed<1 || speed>10){
		cout<<"Speed must be from 1 to 10.\n";
		goto speedHandle;
	}
	system("cls"); //Regex to clear screen
	speed = (11-speed)*100; //Scale speed to milliseconds
	vector<vector<bool> > grid(rows+2, vector<bool>(cols+2));
	vector<vector<bool> > gen(rows+2, vector<bool>(cols+2));
	srand(time(NULL));
	//Generate initial generation randomly
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			grid[i][j] = rand()%2==0?false:true;
		}
	}
	while(1){
		print_grid(grid, rows, cols); //Print current generation
		for(int i=1; i<=rows; i++){
			for(int j=1; j<=cols; j++){
				is_alive(grid, gen, i, j); //Update future generation
			}
		}
		//Move to next generation
		for(int i=1; i<=rows; i++){
			for(int j=1; j<=cols; j++){
				grid[i][j] = gen[i][j];
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(speed)); //Sleep
		
		system("cls"); //Clear screen
	}
	return 0;
}
	
