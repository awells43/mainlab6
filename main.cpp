#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int ROW_SIZE = 10;
const int COL_SIZE = 10;
const double FIXED_TEMP = 100.00;

void PrintPlate(double hotPlate[ROW_SIZE][COL_SIZE]);
void InitPlate(double hotPlate[ROW_SIZE][COL_SIZE]);
void IteratePlate(double hotPlate[ROW_SIZE][COL_SIZE]);
void CopyPlate(double oldPlate[ROW_SIZE][COL_SIZE], double newPlate[ROW_SIZE][COL_SIZE]);

int main() {
    double hotPlate[ROW_SIZE][COL_SIZE];
    double oldPlate[ROW_SIZE][COL_SIZE];
    double inputPlate[ROW_SIZE][COL_SIZE];

    cout << "Hotplate simulator" << endl << endl;
    cout << "Printing the initial plate values..." << endl; // part 1
    InitPlate(hotPlate);
    PrintPlate(hotPlate);
    cout << endl << endl;

    cout << "Printing plate after one iteration..." << endl; //part 2
    IteratePlate(hotPlate);
    PrintPlate(hotPlate);
    CopyPlate(oldPlate, hotPlate);
    cout << endl << endl;

    IteratePlate(hotPlate);
    cout << "Printing final plate..." << endl;

    bool notChanging = false;
    while(notChanging == false){
        notChanging = true;
        for (int i = 0; i < ROW_SIZE; ++i) {
            for (int j = 0; j < COL_SIZE; ++j) {
                if (abs(hotPlate[i][j] - oldPlate[i][j]) > 0.1){
                    CopyPlate(oldPlate,hotPlate);
                    IteratePlate(hotPlate);
                    notChanging = false;
                }
            }
        }

    }
    PrintPlate(hotPlate);

    cout << "Writing final plate to \"Hotplate.csv\"..." << endl << endl;
    ofstream outFS;
    outFS.open("Hotplate.csv");
    for (int i = 0; i < ROW_SIZE; ++i) { //height or row
        for (int j = 0; j < COL_SIZE; ++j) { // width column
            if (j != COL_SIZE - 1) {
                outFS << fixed << setprecision(3) << setw(9) << hotPlate[i][j] << ",";
            }

            else{
                outFS << fixed << setprecision(3) << setw(9) << hotPlate[i][j] << endl;
            }
        }
    }
    outFS.close();

    ifstream inFS;
    inFS.open("Inputplate.txt");
    for(int i = 0; i < ROW_SIZE; ++i) {
        for (int j = 0; j < COL_SIZE; ++j) {
            inFS >> inputPlate[i][j];
        }
    }

    cout << "Printing input plate after 3 updates..." << endl;
    IteratePlate(inputPlate);
    IteratePlate(inputPlate);
    IteratePlate(inputPlate);
    PrintPlate(inputPlate);

    return 0;
}

void PrintPlate(double hotPlate[ROW_SIZE][COL_SIZE]){ //part 1
    for (int i = 0; i < ROW_SIZE; ++i) { //height or row
        for (int j = 0; j < COL_SIZE; ++j) { // width column
            if (j != COL_SIZE - 1) {
                cout << fixed << setprecision(3) << setw(9) << hotPlate[i][j] << ",";
            }

            else{
                cout << fixed << setprecision(3) << setw(9) << hotPlate[i][j] << endl;
            }
        }
    }
}
void InitPlate(double hotPlate[ROW_SIZE][COL_SIZE]){
    for(int i = 0; i < ROW_SIZE; ++i) { //height or row
        for (int j = 0; j < COL_SIZE; ++j) { // width column
            if (i == 0 || i == ROW_SIZE - 1) {
                if (j == 0 || j == COL_SIZE - 1) {
                    hotPlate[i][j]= 0.000;
                }
                else{
                    hotPlate[i][j] = FIXED_TEMP;
                }
            }
            else{
                hotPlate[i][j] = 0.000;
            }
        }
    }
}
void IteratePlate(double hotPlate[ROW_SIZE][COL_SIZE]){
    double newPlate[ROW_SIZE][COL_SIZE];
    for(int i = 0; i < ROW_SIZE; ++i) { //height or row
        for (int j = 0; j < COL_SIZE; ++j) { // width column
            if (i == 0 || i == ROW_SIZE - 1) {
                if (j == 0 || j == COL_SIZE - 1) {
                    newPlate[i][j]= 0.000;
                }
                else{
                    newPlate[i][j] = FIXED_TEMP;
                }
            }
            else if ((j!= 0) && (j != COL_SIZE - 1)){
                newPlate[i][j] = (hotPlate[i - 1][j] + hotPlate[i + 1][j] + hotPlate[i][j-1] + hotPlate[i][j + 1]) / 4;
            }
            else{
                newPlate[i][j] = 0.000;
            }
        }
    }
    for (int i = 0; i < ROW_SIZE; ++i){
        for(int j = 0; j <COL_SIZE; ++j) {
            hotPlate[i][j] = newPlate[i][j];
        }
    }
}
void CopyPlate(double oldPlate[ROW_SIZE][COL_SIZE], double newPlate[ROW_SIZE][COL_SIZE]){
    for (int i = 0; i < ROW_SIZE; ++i){
        for(int j = 0; j <COL_SIZE; ++j) {
            oldPlate[i][j] = newPlate[i][j];
        }
    }
}