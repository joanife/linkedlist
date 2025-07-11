// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Student class definition
class Student {
public:
	// Constructor used when GPA value is not provided
	Student(string* firstName, string* lastName, string mNumber, string birthDay) {
		first_name = *firstName;
		last_name = *lastName;
		m_number = mNumber;
		gpa = 0.0;
		birthday = StringToTime(birthDay);
	};

	// Constructor used when GPA value is provided
	Student(string* firstName, string* lastName, string mNumber, float* gpA, string birthDay) {
		first_name = *firstName;
		last_name = *lastName;
		m_number = mNumber;
		gpa = *gpA;
		birthday = StringToTime(birthDay);
	};

	// Function to return the student's full name
	string GetName() {
		return first_name + " " + last_name;
	};

	// Function to return the student's M Number
	string GetMNumber() {
		return m_number;
	};

	int GetAge() {
		time_t timestamp = time(&timestamp);
		struct tm currDate;
		localtime_s(&currDate, &timestamp);

		if (birthday.tm_mon < currDate.tm_mon) {
			return currDate.tm_year - birthday.tm_year;
		}

		else if (birthday.tm_mon > currDate.tm_mon) {
			return currDate.tm_year - birthday.tm_year - 1;
		}

		else {
			if (birthday.tm_mday <= currDate.tm_mday) {
				return currDate.tm_year - birthday.tm_year;
			}

			else {
				return currDate.tm_year - birthday.tm_year - 1;
			}
		}
	};

	bool operator>(const Student& student2) const {
		return m_number > student2.m_number;
	};

	bool operator<(const Student& student2) const {
		return m_number < student2.m_number;
	};

	bool operator==(const Student& student2) const {
		return m_number == student2.m_number;
	};

	void display() {
		cout << "Student Name: " << GetName() << endl;
		cout << "M Number: " << GetMNumber() << endl;
		cout << "GPA: " << gpa << endl << endl;
	}

private:
	string first_name;
	string last_name;
	string m_number;
	float gpa;
	struct tm birthday;
	struct tm StringToTime(string birthDay) {
		struct tm datetime;
		datetime.tm_year = stoi(birthDay.substr(6, 4)) - 1900;
		datetime.tm_mday = stoi(birthDay.substr(3, 2));
		datetime.tm_mon = stoi(birthDay.substr(0, 2)) - 1;

		return datetime;
	};
};

class Node {
private:
	Student* student_info;
	Node* next;

public:
	// constructor when only data is provided
	Node(Student* new_student) {
		student_info = new_student;
		next = nullptr;
	}

	// constructor when both data and next node are provided
	Node(Student* new_student, Node* next_node) {
		student_info = new_student;
		next = next_node;
	}

	// Function to set or change the given node's next node
	void SetNext(Node* new_next) {
		next = new_next;
	}

	// Function to return the current node's next node
	Node* GetNext() {
		return next;
	}

	// Function to return the current node's Student object
	Student* GetStudentInfo() {
		return student_info;
	}
};

class LinkedList {
public:
	Node* head;
	Node* tail;
	int location_index = 0;

	// Default constructor
	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void AddItem(string* firstName, string* lastName, string mNumber, string birthDay) {
		Student* new_student = new Student(firstName, lastName, mNumber, birthDay);
		Node* new_node = new Node(new_student);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}

		else {
			Node* curNode = head;

			if ((curNode->GetStudentInfo()->GetMNumber() > mNumber) && (curNode == head)) {
				new_node->SetNext(curNode);
				head = new_node;
			}

			while (curNode != nullptr) {
				if (curNode->GetStudentInfo()->GetMNumber() < mNumber) {
					new_node->SetNext(curNode->GetNext());
					curNode->SetNext(new_node);

					return;
				}

				else if ((curNode->GetStudentInfo()->GetMNumber() < mNumber) && (curNode == tail)) {
					curNode->SetNext(new_node);
					tail = new_node;

					return;
				}

				curNode = curNode->GetNext();
			}
		}
	}

	void AddItem(string* firstName, string* lastName, string mNumber, float* gpA, string birthDay) {
		Student* new_student = new Student(firstName, lastName, mNumber, gpA, birthDay);
		Node* new_node = new Node(new_student);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}

		else {
			Node* curNode = head;

			if ((curNode->GetStudentInfo()->GetMNumber() > mNumber) && (curNode == head)) {
				new_node->SetNext(curNode);
				head = new_node;
			}

			while (curNode != nullptr) {
				if (curNode->GetStudentInfo()->GetMNumber() < mNumber) {
					new_node->SetNext(curNode->GetNext());
					curNode->SetNext(new_node);

					return;
				}

				else if ((curNode->GetStudentInfo()->GetMNumber() < mNumber) && (curNode == tail)) {
					curNode->SetNext(new_node);
					tail = new_node;

					return;
				}

				curNode = curNode->GetNext();
			}
		}
	}

	Student* GetItem(string mNumber) {
		Node* curNode = head;
		Node* prevNode = nullptr;

		while (curNode != nullptr) {
			if (curNode->GetStudentInfo()->GetMNumber() == mNumber) {
				if (curNode == head) {
					head = curNode->GetNext();
				}

				else {
					prevNode->SetNext(curNode->GetNext());
				}

				Student* requested_student = curNode->GetStudentInfo();
				delete curNode;
				return requested_student;
			}

			prevNode = curNode;
			curNode = curNode->GetNext();
		}

		return nullptr;
	}

	bool IsInList(string mNumber) {
		Node* curNode = head;

		while (curNode != nullptr) {
			if (curNode->GetStudentInfo()->GetMNumber() == mNumber) {
				return true;
			}

			curNode = curNode->GetNext();
		}

		return false;
	}

	bool IsEmpty() {
		if (head == nullptr) {
			return true;
		}

		else {
			return false;
		}
	}

	int Size() {
		Node* curNode = head;
		int number = 0;

		while (curNode != nullptr) {
			number += 1;

			curNode = curNode->GetNext();
		}

		return number;
	}

	Student* SeeNext() { 
		int length = Size();

		Node* curNode = head;

		for (int i = 0; i <= location_index; i++) {
			if (location_index >= length) {
				return nullptr;
			}

			if (i == location_index) {
				location_index += 1;
				return curNode->GetNext()->GetStudentInfo();
			}

			curNode = curNode->GetNext();
		}
	}

	Student* SeeAt(int userInput) { 
		int length = Size();

		location_index = userInput;

		Node* curNode = head;

		for (int i = 0; i <= location_index; i++) {
			if (i == location_index) {
				return curNode->GetStudentInfo();
			}

			curNode = curNode->GetNext();

		}
	}

	void Reset() {
		location_index = 0;
	}

	~LinkedList() {
		Node* curNode = head;

		while (curNode != nullptr) {
			Node* next_node = curNode->GetNext();
			delete curNode->GetStudentInfo();
			delete curNode;
			curNode = next_node;
		}
	}

	void display() {
		int length = Size();
		Node* curNode = head;

		for (int i = 0; i < length; i++) {
			curNode->GetStudentInfo()->display();

			curNode = curNode->GetNext();

		}
	}
};

int main() {
	LinkedList list;
	string keep_going;

	do {
		int function_to_do;

		cout << "Provided the following functions, which would you like to try? 1. Add Item\n2. Get Item\n"
			<< "3. Is In List\n4. Is Empty\n5. Size\n6. See Next\n7. See At\n8. Reset" << endl;

		cout << "Enter a number from 1 to 8 - ";
		cin >> function_to_do;

		if (function_to_do == 1) {
			string firstName;
			string lastName;
			string mNumber;
			string provide_gpa;
			string birthday;

			cout << "Please provide the following information" << endl;

			cout << "First Name: ";
			cin >> firstName;
			cout << "Last Name: ";
			cin >> lastName;
			cout << "M Number: ";
			cin >> mNumber;
			cout << "Birthday (use mm/dd/yyyy format): ";
			cin >> birthday;

			cout << "Do you want to provide a GPA? (Yes or No) ";
			cin >> provide_gpa;

			if (provide_gpa == "Yes") {
				float gpa;

				cout << "GPA: ";
				cin >> gpa;

				list.AddItem(&firstName, &lastName, mNumber, &gpa, birthday);
			}

			else {
				list.AddItem(&firstName, &lastName, mNumber, birthday);
			}
		}

		else if (function_to_do == 2) {
			string mnumber;

			cout << "Please provide the M Number: ";
			cin >> mnumber;

			Student* student = list.GetItem(mnumber);

			cout << student << endl;
		}

		else if (function_to_do == 3) {
			string mnumber;

			cout << "Please provide the M Number: ";
			cin >> mnumber;

			bool itemPresent = list.IsInList(mnumber);

			cout << itemPresent << endl;
		}

		else if (function_to_do == 4) {
			bool emptyList = list.IsEmpty();

			cout << emptyList << endl;
		}

		else if (function_to_do == 5) {
			int length = list.Size();

			cout << length << endl;
		}

		else if (function_to_do == 6) {
			Student* next_student = list.SeeNext();

			cout << next_student << endl;
		}

		else if (function_to_do == 7) {
			int index;
			int length = list.Size();

			cout << "Enter a number from 0 to " << length - 1 << " - ";
			cin >> index;

			Student* located_student = list.SeeAt(index);

			cout << located_student << endl;
		}

		else if (function_to_do == 8) {
			list.Reset();
		}

		cout << "Do you want to test another function? (Yes or No) ";
		cin >> keep_going;
	}

	while (keep_going == "Yes");

	return 0;
}

