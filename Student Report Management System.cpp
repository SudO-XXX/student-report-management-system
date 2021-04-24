#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
struct address{
	string city;
	string res;
	unsigned int zip;
};
//a Structure for storing the address of each student
class student {
private:
	unsigned int rollno;
	unsigned int n;      //to store the number of subjects.
	float per;          //The total percent of the student.
	float * marks;     //A pointer of the dynamic array with n elements to store marks
	string grade;     //The total grade of the student.
	string dep;      //The department name of the student.
	string name;    //The name of the student.
	address a;     //The address of the student.
	void calculate();  //A function to calculate the total percent and the grade of the student.
	void creatmarks(){ marks = new float[n]; };  /*Creating the dynamic array in the heap to store the
												  degrees of the student after knowing the number of subjects*/
public:
	void st_output(ostream&);     //Outputs the data of the student to a stream
	void st_input(string s);     //Gets the data of a student from a string as a line, and the columns of the data are comma-separated.
	void st_input(bool f);      //Fills in a student object through the terminal.
	void show_data();          //Shows the record card of a single student onto the terminal.
	string rename();          //Returns the name of a student object.
	unsigned int rerollno(); //Returns the rollno of a student object.
};
vector <student> starr;     //A vector to store the student objects to access them easily.

void student::calculate(){      /*Creating the dynamic array in the heap to store the
												  degrees of the student after knowing the number of subjects*/
	per = 0;
	for (unsigned int i = 0; i < n; i++)  /*Summing all the degrees of the student.
										    assuming that for each subject the full score is 100.*/
		per += marks[i];
	per /= n;        //Calculating the total percent.
	if (per >= 85)       //getting the grade of the student.
		grade = 'A';
	else if (per >= 75)
		grade = 'B';
	else if (per >= 65)
		grade = 'C';
	else if (per >= 50)
		grade = 'D';
	else
		grade = 'F';
}

void student::st_input(bool f){  //The argument is 0 for modifying a student and 1 for adding a new student.
	string input;          //To store each input data from the user.
	cout << "\nEnter the rollno of the student\n\n>>";
	cin.ignore();
	if (getline(cin, input) && input != "")   //Getting the rollno from the user, if the user press enter nothing changes.
		rollno = stoi(input);
	cout << "\nEnter the name of the student\n\n>>";
	if (getline(cin, input) && input != "")    //Getting the name of the student.
		name = input;
	cout << "Enter the department of the student:\n\n>>";    //Storing the department of the student.
	if (getline(cin, input) && input != "")
		dep = input;
	cout << "\nEnter the adress of the student\n\nCity: ";   //Storing the address of the student.
	if (getline(cin, input) && input != "")                  //city.
		a.city = input;
	cout << "\nResidential area: ";   //Storing the residential area of the student.
	if (getline(cin, input) && input != "")
		a.res = input;
	cout << "\nZip code: ";                   //Storing the zipcode of the student.
	if (getline(cin, input) && input != "")
		a.zip = stoi(input);
	cout << "\nEnter the student's degrees in the subjects \n";       //Storing the degrees in the subjects.
	if (f){   /*If it's adding a new student it will create a dynamic array for the degrees of the subject
			   and if it is modifying an existing student nothing changes about the number of subjects.*/
		cout << "\n\nEnter the number of subjects to this student\n\n>>";
		if (getline(cin, input) && input != ""){
			n = stoi(input);
			creatmarks();      //Creating the dynamic array for storing the degree of each subject of the student.
		}
	}
	cout << '\n';
	for (unsigned int i = 0; i < n; i++){        //Filling in the array of the degrees of the subjects.
		cout << "Subject #" << i + 1 << " : ";
		if (getline(cin, input) && input != "")
			marks[i] = stof(input);
	}
	calculate();  //Calculates the grade and the percent of the student.
}
void student::st_input(string line){     /*Fills in the data of a student object by a string line
										  containing the data in a comma-separated form with a specific sequence as follows:
										     rollno,st_name,dep.,city,res.area,zip_code,no_subjects,degree_in_sub1,,,,*/
	vector <string>(column);
	stringstream ss(line);       //Creating a string stream ss and initialize its buffer by string line.
	string temp;  //String variable to separate the data in the string stream.
	while (getline(ss, temp, ',')){ //separating the data in one line in the file into columns each as an element in a string vector.
		column.push_back(temp);
	}
	rollno = stoi(column[0]);	/*Storing the rollno of the student form the first
								column after changing it from a string into an integer value.*/

	name = column[1];			/*Storing the name of the student form the second column.*/
	dep = column[2];            /*Storing the department of the student form the second column*/
	a.city = column[3];			/*Storing the city of the student*/
	a.res = column[4];			//Storing the residential area of the student.
	a.zip = stoi(column[5]);   //Storing the zipcode of the student after converting it into an integer value.
	n = stoi(column[6]);       //Storing the number of subjects
	creatmarks();
	for (unsigned int i = 0; i < n; i++)
		marks[i] = stof(column[i + 7]);   //Storing the marks of the student.
	calculate();						//Calculate the percent and optaining the grade of the student.
}
void student::st_output(ostream& out){       //Outputs the student data into an output file stream in csv form.
	out << rollno << ',' << name << ',' << dep << ','
		<< a.city << ',' << a.res << ',' << a.zip << ',' << n << ',';
	for (unsigned int i = 0; i < n; i++)
		out << marks[i]<< ',';
	out << grade << ',' << per << '\n';
}
void student::show_data(){  //Outputs the data of single student in a tabulated form.
	cout.precision(3);
	cout << rollno << setw(25) << name << setw(7) << dep << setw(11);  //Where setw() sets the widthe of each cell.
	cout << a.city << setw(15) << a.res << setw(7) << a.zip << setw(5) << n << setw(12) << grade << setw(10) << per << '%' << setw(8);
	for (unsigned int i = 0; i < n - 1; i++)
		cout << marks[i] << setw(6);
	cout << marks[n - 1] << '\n';
}
string student::rename(){ return name; }      //Returns the name of a student object.
unsigned int student::rerollno(){ return rollno; }  //Returns the rollno of a student object.
int display_required(string&);      /*Returns the index of a student object in starr by it's name
								   ****NOT case sensitive****/
int display_required(int);        //Returns the index of a student object in starr vector by it's rollno.
void lower(string& stt){       //Turning a string object int lower case.
	for_each(stt.begin(), stt.end(), [](char & c){c = tolower(c);});   /*usig lambdas turning each charcter in the st
																	   ring into lower by tolower() function.*/
}
int main(){
	student *st;    //A pointer of type student.
	fstream file;
	string line, ratname;
	int ratno;
	unsigned short choice, choice1;
	bool re, re1;
	file.open("student_report.txt", ios::in);         //Open the student_report.txt in the file stream.
	for (unsigned int i = 0; getline(file, line); i++){   // Reading the student data line by line as each line contains the data of one student.
		st = new student;            //Creating a student object in the heap.
		(*st).st_input(line);     //Fill in the student object.
		starr.push_back(*st);     //Appending the starr vector with the student.
		delete st;                //Restoring the allocated memory to the free store.
	}
	file.close();	//closing student_report.txt
	file.open("student_report.txt", ios::out);  //Opening the file to write the percent and the grade for each student in the file.
	file.seekp(0);    //Seeking the writing pointer of the output file stream to the start of the file.
	for (unsigned int i = 0; i < starr.size(); i++)   //Over write the file for each line to enclud the percent and the grade.
		starr[i].st_output(file);
	file.close();     //Closing the file.
	do{
		system("cls");   //To clear the screen.
		system("color f6");    //Setting the color of the console, for the screen to be more user friendly.
		cout << "\n\n1.Display all data\n\n2.Add a student\n\n3.Modify a record\n\n"   //Display the minue of options.
			<< "4.Search for a student by name\n\n5.Search for student by num\n\n"
			<< "6.Show the grade and the final score of a student\n\n7.delete a student record\n\n"
			<< ">>";
		cin >> choice;     //Storing the choice of the user to perform the operation.
		switch (choice)
		{
		case 1:  //displays a single student from the file for each time the user presses 1.
			system("cls");
			//The heading of the table, it's printed before printing the data of  the students.
			cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
				<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
			for (unsigned int i = 0; i < starr.size(); i++){    /*Printing the data of a
																single student time the user enters one*/
				starr[i].show_data();
				cout << endl << "Show another student(Yes->1,No->0)\n\n>>";  /*Asking if the user wants to show
																			 another student data or seek to the main minue.*/
				cin >> re1;
				if (!re1)
					break;
				cout << endl;
			}
			break;
		case 2:						//Adding a new student.
			st = new student;      //Creating a new student object in the heap.
			system("cls");
			(*st).st_input(1);   //Filling in the object from the console.
			starr.push_back(*st);   //Appending the starr vector with the new student.
			file.open("student_report.txt", ios::out | ios::app);  //Appending the file with new student.
			(*st).st_output(file);
			file.close();
			delete st;   //Release the allocated memory to the heap.
			break;
		case 3:						//Modifying an existing student.
			system("cls");
			cout << "\nEnter the rollno of the sudent you want to modify:\n\n>>";
			cin >> ratno;
			ratno = display_required(ratno);   //Searching for the index of the student in starr vector.
			if (ratno == -1){                  //If not found.
				cout << "Not found!!\n";
				break;
			}
			cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
				<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
			starr[ratno].show_data();  //Showing the data of the required student if found.
			cout << "\n if you want some data to remain as it is, just press enter.\n\n";
			starr[ratno].st_input(0);  //Modifying the student.
			file.open("student_report.txt", ios::out);   //Modifying the file.
			file.seekp(0);
			for (unsigned int i = 0; i < starr.size(); i++)
				starr[i].st_output(file);
			file.close();
			cout << "\nFile has been modified!\n\n";
			break;
		case 4:		//Search for a student by his name.
			system("cls");
			cout << "\nEnter the name of the student you want to show his record:\n\n>>";
			cin.ignore();
			getline(cin, ratname);   //Storing the name of the student.
			if (ratname == ""){  //If nothing entered.
				cout << "\nDidn't enter a name to search!!\n\n";
				break;
			}
			lower(ratname);
			ratno = display_required(ratname); //Finding the index of the student after turning it into lower case.
			if (ratno == -1){ //If not found
				cout << "Not found!!\n\n";
				break;
			}
			cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
				<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
			starr[ratno].show_data();  //Showing the data of that student.
			break;
		case 5:      //Search for a student object by it's rollno.
			system("cls");
			cout << "\nEnter the rollno of the student you want to show his record:\n\n>>";
			cin >> ratno;  //Storing the required rollno.
			ratno = display_required(ratno); //Finding the index of the student in starr vector.
			if (ratno == -1) { //If not found.
				cout << "Not found!\n\n";
				break;
			}
			cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
				<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
			starr[ratno].show_data();//Show it's data.
			break;
		case 6:    //Calculate the grade and percent of a specific student.
			system("cls");
			cout << "\nChoose to search for the student with it's rollno or by his/her name:\n\n"
				<< "1.By rollno\n2.By name\n\n"
				<< ">>";
			cin >> choice1;
			switch (choice1){   //Searching for the student.
			case 1: //By roll no.
				system("cls");
				cout << "Enter rollno of the student:\n\n>>";
				cin >> ratno;
				ratno = display_required(ratno);  //Finding the student.
				if (ratno == -1){  //Not found.
					cout << "\n\nnot found!!\n";
					break;
				}
				cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
					<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
				starr[ratno].show_data(); //Showing the data.
				break;
			case 2: //By name.
				system("cls");
				cout << "Enter rollno of the student:\n\n>>";
				cin.ignore();
				getline(cin, ratname); //Storing the name of the student.
				if (ratname == ""){
					cout << "\nDidn't enter a name to search!!\n\n";
					break;
				}
				lower(ratname);
				ratno = display_required(ratname);  //Finding the student.
				if (ratno == -1){
					cout << "\nNot found!!\n\n";
					break;
				}
				cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
					<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
				starr[ratno].show_data();//Showing it's data.
				break;
			}
			break;
		case 7: //Delete a specific student.
			system("cls");
			cout << "Enter the roll of the student you want to delete his record\n\n>> ";
			cin >> ratno;
			ratno = display_required(ratno); //Finding the student by rollno.
			if (ratno == -1){
				cout << "\n\nnot found!\n\n";
				break;
			}
			cout << "\nRollno" << setw(20) << "Name" << setw(8) << "Dep." << setw(10) << "City" << setw(15) << "Res." << setw(7)
				<< "ZIP" << setw(12) << "No.subjects" << setw(7) << "Grade" << setw(11) << "Percent" << setw(10) << "Degrees" << endl;
			starr[ratno].show_data(); //Showing it's data.
			cout << "\nAre you sure you want to delete the record!(yes->1, n->0)\n\n>> ";
			cin >> re;  //Asking to proceed to delete.
			if (re){  //Delete!!!**
				for (int i = ratno; i < starr.size()-1; i++) //Moving the elements in vector starr to keep the order of the objects unchanged
					starr[i] = starr[i + 1];				//The last two objects in the vector become identical at the end of the loop
				starr.pop_back();							//Removing the last object from the vector.
				cout << "\n Modifing the file\n\n";
				file.open("student_report.txt", ios::out);	//Modifying the file.
				file.seekp(0);
				for (unsigned int i = 0; i < starr.size(); i++)
					starr[i].st_output(file);     //Printing student object to the file.
				file.close();
				cout << "File has been modified!\n\n";
			}
			break;
		default:   //In case for choosing wrong choice.
			system("cls");
			cout << "\nPlease enter a valid option\n\n";
			break;
		}
		cout << "\nBack to main minue?(1 -> yes,0 -> no)\n\n>>";
		cin >> re; //For returning to the main minue of closing the program.
	} while (re);
	return 0;
}
int display_required(string& rat){
	bool found = 0;
	string temp;
	for (int i = 0; i < starr.size(); i++){  //Looping over starr.
            temp = starr[i].rename();
            lower(temp);
		if (temp == rat){
			cout << "\nfound!\n\n";
			found = 1;
			return i;
		}
	}
	if (!found){ //If not found.
		cout << "\nStudent not found !\n\n";
		return -1;
	}
}
int display_required(int rat){
	bool found = 0;
	for (int i = 0; i < starr.size(); i++){//Looping over starr.
		if (starr[i].rerollno() == rat){
			cout << "\nfound!\n\n";
			found = 1;
			return i;
		}
	}
	if (!found){//If not found.
		cout << "\nStudent not found !\n\n";
		return -1;
	}
}
