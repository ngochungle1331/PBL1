#include<iostream>
#include<windows.h>
#include<string.h>

using namespace std;

char arr[26][10];
int output[26][10], row=26, col=10, MaxSeats=260, SeatsNum, ticket[500], k=0;

int allOccupied(char arr[26][10]); //Kiem tra tat ca cho ngoi con trong hay khong
int check(char arr[26][10], string s,int ticket[]); //Kiem tra ghe can dat con trong hay khong

void Intro();
void open(); //Nhap ma open
void menu(); //Hien thi menu chinh
void seats(char arr[26][10]); //Hien thi so do cho ngoi
void updateSeat(char arr[26][10],int row,int col, string s, int ticket[]); //Cap nhat thong tin cho ngoi
void airline(char arr[26][10]); //Dat cho
void updateFile(int output[26][10], int row, int col, int ticket[]); // In thong tin vao file
void read(int output[26][10]); // lay thong tin tu file output

string i1;
string flightInfo(); //Lay ma chuyen bay
string seatInfo(); //Lay thong tin dat ve tu ban phim
int ticketInfo(); //Lay ma ve

int main(){
	Intro();
	read(output);
	open();
	i1=flightInfo();
	menu();
	return 0;
}

void Intro(){
	cout <<"|---------------------------------------------------------------------------------";
	cout <<"|\n";
	cout <<"|   DE TAI 706: UNG DUNG DAT CHO NGOI TREN MAY BAY CUA HANG HANG KHONG ITF-AIRWAY |\n|---------------------------------------------------------------------------------|"<< endl;
	cout <<"| - GVHD: Tran Ho Thuy Tien                                                       |"<< endl;
	cout <<"| - SV thuc hien:                                                                 |\n|\t1. Le Ngoc Hung\t        Lop: 20T1\t    Nhom 5                        |"<< endl;
	cout <<"|\t2. Nguyen Huu Duc\tLop: 20T2\t    Nhom 5                        |\n|                                                                                 |"<< endl;
	cout <<"|---------------------------------------------------------------------------------|\n";
	cout <<"\n|---------------------------------------------------------------------------------|";
	cout <<"\n|                                                                                 |\n|                 WELCOME TO ITF-AIRWAY SEATS ARRANGEMENTS SYSTEM!!               |";
	cout <<"\n|                                                                                 |\n|---------------------------------------------------------------------------------|"<< endl;
}

void read(int output[26][10]){
	FILE *fp;
   	int i, j;
   	fp = fopen("output.txt", "r");
   	// doc noi dung file output
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            fscanf(fp, "%d\n", &output[i][j]);
        }
   }
   fclose(fp);
}


void open(){
	string op;
	int i=1;
	cout<<"\nEnter Opening Code: "; //Nhap ma Open
	cin>>op;
	while (op!="ITFACULTY"){
		cout<<"Wrong Code, try again: "; // Nhap sai ma Open
		cin>>op;
		i++;
		if (i==5){
			cout<<"Try again after 10s!\n"<<endl; // Nhap sai ma Open qua nhieu lan
			for (int x=10; x>=1; x--){
				cout<<x<<"s...";
				Sleep(1000);
			}
			cout<<endl;
			i=1;
		}
	}
	cout <<"\n";
}

string flightInfo(){ 
	char s[7];
	int t=1;
	cout<<"Enter Flight Code: "; // Nhap ma chuyen bay
	cin>>s;
	while (s[0]!='I' || s[1]!='T' || s[2]!='F' || s[3]!='2' || s[4]!='0' || s[5]!='2' || s[6]!='1'){ 
		cout <<"Please enter valid Flight Code:  "; // Vui long nhap ma chuyen bay hop le
		cin>>s;
		t++;
		if(t==5){
			cout<<"Incorrect Flight Code. Try again after 10s!\n"; // Nhap sai ma chuyen bay qua nhieu lan. Nhap lai sau 10s
			for (int x=10; x>=1; x--){
				cout<<x<<"s...";
				Sleep(1000);
			}
			cout<<endl;
			t++;
		}
	}
	cout<<"\n";
	return s;
}

void menu(){
	cout <<"Function: "; // chuc nang
	cout <<" 	 1. Display Seats\n"<< endl; // Hien thi so do cho ngoi
	cout <<"		 2. Arrange Seat "<< endl; // Dat cho
	cout <<"\n 		 3. Exit\n"<< endl; // Thoat
	cout <<"Enter 1 function: "; // Nhap chuc nang can chon
	char choice;
	cin >> choice;
	while (choice != '1' && choice != '2' && choice != '3'){
		cout <<"Incorrect Function. Please enter again! "; // lua chon khong hop le
		char ch;
		cin >> ch;
		if(ch == '1' || ch == '2' || ch == '3') break;
	}if(choice == '3'){
		cout <<"\nTHANK YOU FOR CHOOSING ITF-AIRWAY. HAVE A GREAT TIME WITH YOUR FLIGHT!! "; // Loi cam on
		exit(0);
	}else if (choice=='1'){
		int k=0;
		while(true){
			if(k != 0){ //cho bien k chay de thoat khoi vong lap vo han
				break;
			}
			seats(arr);
			getchar();
			cout <<"\nDo you wish to arrange seat? (1.Yes | 2.No)  ";
			char c;
			cin >> c;
			if(c == '2'){
				cout <<"\nTHANK YOU FOR CHOOSING ITF-AIRWAY. HAVE A GREAT TIME WITH YOUR FLIGHT!! \n"; // Loi cam on
				exit(0);
			}
			else if(c == '1'){
				airline(arr);
				k++;
			}
		}
	}else if(choice == '2'){
		seats(arr);
		airline(arr);
	}
}

int ticketInfo(){ 
	int ve;
	cin>>ve;
	while(ve<=1000 || ve>1260){ 
		cout <<"Invalid ticket! Please enter again! "; // ma ve khong hop le
		cin>>ve;
	}
	return ve;
}

void seats(char arr[26][10]){
	FILE *fp;
   	int row=26, col=10, i, j;
   	fp = fopen("seats.txt", "r");
   	// doc noi dung ma tran
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            fscanf(fp, "%c\n", &arr[i][j]);
        }
   }
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            cout << arr[i][j] << " ";
        }
        cout <<""<< endl;
   }
   fclose(fp);
}

int allOccupied(char arr[26][10]){ 
	int count=0;
	for(int i=0;i<26;i++){
		for(int j=1;j<10;j++){
			if(arr[i][j] == 'X'){
				count++;
			}
		}
	}
	if(count==260){
		return 1;	
	}
	return 0;
}

string seatInfo(){ 
	char s[2];
	cin>>s;
	return s;
}

void updateSeat(char arr[26][10], int row,int col, string s, int ticket[]){
	FILE *f;
	f = fopen("seats.txt", "w");
	arr[row][col]='x';
	for(int i=0;i<26;i++){
		for(int j=0;j<10;j++){
			fprintf(f, "%c ", arr[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void updateFile(int output[26][10], int row, int col,string s,int ticket[]){
	FILE *f;
	f = fopen("output.txt", "w");
	int i,j;
	output[row][col]=ticket[k];
	k++;
	for(int i=0;i<26;i++){
		for(int j=0;j<10;j++){
			fprintf(f, "%d ", output[i][j]);
		}
		fprintf(f, "\n");
	}
	
}

int check(char arr[26][10], string s, int ticket[]){
	if(s[0]>'Z' || s[0]<'A' || s[1]>'9' || s[1]<'1'){
		cout <<"Invalid Seat. Please enter again! "; // Cho ngoi khong hop le
		return 0;
	}
	int row=-1,col=-1;    
	//Tim hang
	for(int i=0;i<26;i++){
		if(arr[i][0]==s[0])
		row=i;
	}
 	//Tim cot
	for(int j=0;j<10;j++){
		if(arr[row][j]==s[1])
		col=j;
	}
	//Kiem tra cho con trong hay khong
	if(col==-1){
		cout <<"Sorry. This seat has been taken. Please choose another seat!"<< endl; // cho ngoi da duoc dat
		cout <<"Enter your seat: " ;
		return 0;
	}
	// Cap nhat vi tri vao file
	else{
		updateSeat(arr,row,col,s,ticket);
		updateFile(output,row,col,s,ticket);  
	}
	return 1;
}



void airline(char arr[26][10]){
	string s,r;
	int i=1; 
	cout <<"Enter number of seats: ";
	cin >> SeatsNum;
	while (SeatsNum<1 || SeatsNum>260) {
		cout<<"Invalid number of seats. Please enter again! "<<endl; // So cho ngoi can dat khong hop le
		cin>>SeatsNum;
	}
	// Nhap vi tri can dat
	cout<<"Enter ticket info and seat position: "; // Nhap ma ve tuong ung voi so cho
	for (int i=0;i<SeatsNum;i++){
		ticket[i]=ticketInfo();
	}
	while(i<=SeatsNum){
		s = seatInfo();
		// Kiem tra cho
		if(check(arr,s, ticket)!=0) i++;
		if(allOccupied(arr)){
			cout <<"Sorry. All Seats has been arranged!!!"; // Tat ca cho da duoc dat
			break;
		}
	}
	cout <<"\n"<< endl;
	cout <<"Successfully Arranged!"<< endl;
	cout <<"Updating seats..."<<endl; 
	cout <<"Seats updated!\n"<<endl;
	menu(); // Ve lai menu chinh
}
