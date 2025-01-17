// (CS 301) Assignment 2
// Medical Clinic Program

#include "stdafx.h"
#include "LinkedQue.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function Prototypes
int displayMenu();
int getSpecialty();
int getRoomNumber();

void doctorCheckIn();
void doctorCheckOut();
void patientCheckIn();
void patientCheckOut();
void assignDoctor(patient&);

void showOccupiedRooms();
void openOutputFile();

// Doctor information
struct doctor {
	string docName;
	int roomNumber;
	int specCode;
};

// Exam room information
struct examRoom {
	bool doctorIn;
	bool patientIn;
	LinkedQue waitRoom;
	patient p;
	doctor d;
};

// Declare Global Variables for use by all.
examRoom eRoom[20];		// Create an array of 20 examination rooms.
ofstream trans;			// Used to write all screen input and ouput to a file.

// main method to run the menu options
int main()
{
	// Open the output file to record the session.
	openOutputFile();

	int menuSelect = 0; // Hold the user's menu selection.

	// While the user doesn't exit the program.
	while (menuSelect != 6)
	{
		menuSelect = displayMenu(); // Use the displayMenu function to get the user's choice.

		// Doctor check-in
		if (menuSelect == 1)
		{
			doctorCheckIn();
		}
		// Doctor check-out
		else if (menuSelect == 2)
		{
			doctorCheckOut();
		}
		// Patient check-in
		else if (menuSelect == 3)
		{
			patientCheckIn();
		}
		// Patient check-out
		else if (menuSelect == 4)
		{
			patientCheckOut();
		}
		// Show occupied rooms
		else if (menuSelect == 5)
		{
			showOccupiedRooms();
		}
		// Exit the program.
		else if (menuSelect == 6)
		{
			cout << "\n\tPROGRAM ENDING......" << endl;

			trans << "\n\tPROGRAM ENDING......" << endl;
			exit(0);
		}
	}
	return 0;
}

// Display the main menu
int displayMenu()
{
	int select = 0;	// Hold the user's selection.

	// Display the clinic menu. Prompt user for a selection.
	cout << "\nWELCOME TO THE LOCAL MEDICAL CLINIC" << endl;
	cout << "\t1. Doctor Check-In" << endl;
	cout << "\t2. Doctor Check-Out" << endl;
	cout << "\t3. Patient Check-In" << endl;
	cout << "\t4. Patient Check-Out" << endl;
	cout << "\t5. Show Occupied Rooms" << endl; 
	cout << "\t6. Exit" << endl;
	cout << "Enter selection: ";

	trans << "\n\tWELCOME TO THE LOCAL MEDICAL CLINIC" << endl;
	trans << "\t1. Doctor Check-In" << endl;
	trans << "\t2. Doctor Check-Out" << endl;
	trans << "\t3. Patient Check-In" << endl;
	trans << "\t4. Patient Check-Out" << endl;
	trans << "\t5. Show Occupied Rooms" << endl;
	trans << "\t6. Exit" << endl;
	trans << "Enter selection: ";

	cin >> select;
	trans << select << endl;

	// Validate the user's input.
	while (select < 1 || select > 6)
	{
		cout << "\nInvalid Entry! Try again." << endl;
		cout << "\nEnter selection: ";

		trans << "\nInvalid Entry! Try again." << endl;
		trans << "\nEnter selection: ";

		cin >> select;
		trans << select << endl;
	}
	return select;
}

// Display the specialty menu. Prompt user for a selection.
int getSpecialty()
{
	int select; // Holds the user's selection.

	cout << "\nSelect a specialty from the list below:" << endl;
	cout << "\t1.  PED  Pediatrics" << endl;
	cout << "\t2.  GEN  General Practice" << endl;
	cout << "\t3.  INT  Internal Medicine" << endl;
	cout << "\t4.  CAR  Cardiology" << endl;
	cout << "\t5.  SUR  Surgeon" << endl;
	cout << "\t6.  OBS  Obstetrics" << endl;
	cout << "\t7.  PSY  Psychiatry" << endl;
	cout << "\t8.  NEU  Neurology" << endl;
	cout << "\t9.  ORT  Orthopedics" << endl;
	cout << "\t10. DET  Dermatology" << endl;
	cout << "\t11. OPT  Ophthalmology" << endl;
	cout << "\t12. ENT  Ear, Nose, and Throat" << endl;
	cout << "Enter Selection: ";

	trans << "\nSelect a specialty from the list below:" << endl;
	trans << "\t1.  PED  Pediatrics" << endl;
	trans << "\t2.  GEN  General Practice" << endl;
	trans << "\t3.  INT  Internal Medicine" << endl;
	trans << "\t4.  CAR  Cardiology" << endl;
	trans << "\t5.  SUR  Surgeon" << endl;
	trans << "\t6.  OBS  Obstetrics" << endl;
	trans << "\t7.  PSY  Psychiatry" << endl;
	trans << "\t8.  NEU  Neurology" << endl;
	trans << "\t9.  ORT  Orthopedics" << endl;
	trans << "\t10. DET  Dermatology" << endl;
	trans << "\t11. OPT  Ophthalmology" << endl;
	trans << "\t12. ENT  Ear, Nose, and Throat" << endl;
	trans << "Enter Selection: ";

	cin >> select;
	trans << select;

	// Validate the user's input.
	while (select < 1 || select > 12)
	{
		cout << "\nInvalid Entry! Try again." << endl;
		cout << "\nEnter Selection: ";
	
		trans << "\nInvalid Entry! Try again." << endl;
		trans << "\nEnter Selection: ";

		cin >> select;
		trans << select;
	}
	return select;
}

// Get the user to check into a room number
int getRoomNumber()
{
	int roomNumber; // Hold the user's room number.

	// Prompt the user for a room number from which the doctor will check into.
	cout << "\nEnter a room number (1-20): ";
	trans << "\nEnter a room number (1-20): ";

	cin >> roomNumber;
	trans << roomNumber << endl;

	// Validate the user's input.
	while (roomNumber < 0 || roomNumber > 20)
	{
		cout << "\nInvalid Entry! Try again." << endl;
		cout << "\nEnter a room number (1-20): ";

		trans << "\nInvalid Entry! Try again." << endl;
		trans << "\nEnter a room number (1-20): ";

		cin >> roomNumber;
		trans << roomNumber << endl;
	}

	// Correct the room number to represent a position in the array.
	roomNumber = roomNumber - 1;

	// If the room has no doctor.
	if (eRoom[roomNumber].doctorIn == false) 
	{
		cout << "Room #" << roomNumber + 1 << " is available." << endl;
		trans << "Room #" << roomNumber + 1 << " is available." << endl;

		eRoom[roomNumber].doctorIn = true; // set doctorIn to true to show the room is filled
		return roomNumber; 
	}
	else // The room has a doctor.
	{
		cout << "Room #" << roomNumber + 1 << " is unavailable. Please select another room." << endl;
		trans << "Room #" << roomNumber + 1 << " is unavailable. Please select another room." << endl;

		getRoomNumber();
	}
}

// Have the doctor check into the room number specified in getRoomNumber()
void doctorCheckIn()
{
	cout << "\n\tDOCTOR CHECK-IN" << endl;
	trans << "\n\tDOCTOR CHECK-IN" << endl;

    // Hold the user's room number from the getRoomNumber() function.
	int roomNumber = getRoomNumber(); 

	cin.ignore();

	// Get the doctor's name.
	cout << "Please enter the doctor's name: ";
	trans << "Please enter the doctor's name: ";

	getline(cin, eRoom[roomNumber].d.docName);
	trans << eRoom[roomNumber].d.docName;

	// Get the doctor's specialty.
	eRoom[roomNumber].d.specCode = getSpecialty();
}

// Have the doctor check out of a room.
void doctorCheckOut()
{
	cout << "\n\tDOCTOR CHECK-OUT" << endl;
	trans << "\n\tDOCTOR CHECK-OUT" << endl;

	int roomNum; // Hold the user's room number.

	// Prompt the user for a room number from which the doctor will check out from.
	cout << "\nEnter a room number (1-20): ";
	trans << "\nEnter a room number (1-20): ";

	cin >> roomNum;
	trans << roomNum << endl;

	// Validate the user's input.
	while (roomNum < 0 || roomNum > 20)
	{
		cout << "\nInvalid Entry!" << endl;
		cout << "\nEnter a room number (1-20): ";

		trans << "\nInvalid Entry!" << endl;
		trans << "\nEnter a room number (1-20): ";

		cin >> roomNum;
		trans << roomNum;
	}

	// Correct the room number to represent a position in the array.
	roomNum = roomNum - 1;

	// If the room has no doctor.
	if (eRoom[roomNum].doctorIn == false)
	{
		cout << "There is no doctor in room #" << roomNum + 1 << "." << endl;
		trans << "There is no doctor in room #" << roomNum + 1 << "." << endl;
	}
	else // The room has a doctor.
	{
		eRoom[roomNum].doctorIn = false;

		cout << "Goodbye Dr. " << eRoom[roomNum].d.docName << "." << endl;
		trans << "Goodbye Dr. " << eRoom[roomNum].d.docName << "." << endl;

		cout << "Dr. " << eRoom[roomNum].d.docName << " has checked out of the room." << endl;
		trans << "Dr. " << eRoom[roomNum].d.docName << " has checked out of the room." << endl;

		// If the waiting room is empty.
		if (eRoom[roomNum].waitRoom.IsEmpty())
		{
			cout << "There are no patients in the waiting room to move." << endl;
			trans << "There are no patients in the waiting room to move." << endl;
		}
		else // The waiting room has patients.
		{
			// Holds the number of patients in the queue. 
			int numPatients = eRoom[roomNum].waitRoom.GetLength();

			// Assign a patient from a waiting room to another doctor.
			for (int i = 0; i < numPatients; i++)
			{
				patient tempPat;	// Hold the patient.
				eRoom[roomNum].waitRoom.Dequeue(tempPat);
				cout << "\nReassigning Patient " << i + 1 << ": " << tempPat.name;
				trans << "\nReassigning Patient " << i + 1 << ": " << tempPat.name;

				// Pass the patient to the assignDoctor function.
				assignDoctor(tempPat);
			}
		}
	}
}

// Assign the patient to a doctor.
void patientCheckIn()
{
	cout << "\n\tPATIENT CHECK-IN" << endl;
	trans << "\n\tPATIENT CHECK-IN" << endl;

	patient tempPatient; // Hold the patient information

	// Get the patient's name.
	cout << "\nEnter the patient's name: ";
	trans << "\nEnter the patient's name: ";

	cin.ignore();
	getline(cin, tempPatient.name);
	trans << tempPatient.name << endl;

	// Get the patient's age.
	cout << "Enter the patient's age: ";
	trans << "Enter the patient's age: ";

	cin >> tempPatient.age;
	trans << tempPatient.age << endl;

	// Get the patient's emergency indication.
	cout << "Enter the patient's emergency indication (30 characters max):" << endl;
	trans << "Enter the patient's emergency indication (30 characters max):" << endl;

	cin.ignore();
	getline(cin, tempPatient.emergencyInd);
	trans << tempPatient.emergencyInd << endl;

	// Validate the user's input.
	while (tempPatient.emergencyInd.length() > 30)
	{
		cout << "Invalid Entry! Too many characters. Please try again." << endl;
		trans << "Invalid Entry! Too many characters. Please try again." << endl;

		cin >> tempPatient.emergencyInd;
		trans << tempPatient.emergencyInd << endl;
	}

	// Get a specialty code on the patient.
	tempPatient.specialty = getSpecialty();

	// Assign the patient to a doctor.
	assignDoctor(tempPatient);
}

// Have the patient check out of a room.
void patientCheckOut()
{
	cout << "\n\tPATIENT CHECK-OUT" << endl;
	trans << "\n\tPATIENT CHECK-OUT" << endl;

	int roomNumber; // Hold the user's room number.
	patient tempPatient; // Hold the patient information.

	// Prompt the user for a room number from which the patient will check out from.
	cout << "\nEnter the room number: ";
	trans << "\nEnter the room number: ";

	cin >> roomNumber;
	trans << roomNumber << endl;

	// Validate the user's input.
	while (roomNumber < 0 || roomNumber > 20)
	{
		cout << "\nInvalid Entry! Try again." << endl;
		cout << "\nEnter the room number: ";

		trans << "\nInvalid Entry! Try again." << endl;
		trans << "\nEnter the room number: ";

		cin >> roomNumber;
		trans << roomNumber << endl;
	}

	// Correct the room number to represent a position in the array.
	roomNumber = roomNumber - 1;

	// If the waiting room is empty.
	if (eRoom[roomNumber].waitRoom.IsEmpty())
	{
		cout << "There are no patients in room #" << roomNumber + 1 << "." << endl;
		trans << "There are no patients in room #" << roomNumber + 1 << "." << endl;
	}
	else // The waiting room has patients.
	{
		eRoom[roomNumber].waitRoom.Dequeue(tempPatient);

		// Display the patient information.
		cout << "Goodbye " << tempPatient.name << "." << endl;
		trans << "Goodbye " << tempPatient.name << "." << endl;

		cout << "PATIENT " << tempPatient.name << " has checked out of room #" << (roomNumber + 1) << "." << endl;
		trans << "PATIENT " << tempPatient.name << " has checked out of room #" << (roomNumber + 1) << "." << endl;
	}
}

// Show the rooms that are occupied by a doctor and the waiting patients.
void showOccupiedRooms()
{
	cout << "\n\tOCCUPIED ROOMS" << endl;
	trans << "\n\tOCCUPIED ROOMS" << endl;

	bool occupiedRooms = false;

	// Search each room for a doctor.
	for (int i = 0; i < 20; i++)
	{
		// If the room has a doctor.
		if (eRoom[i].doctorIn == true)
		{
			cout << "\n-------------------------------------------------------" << endl;
			cout << "Room #" << i + 1 << endl;
			cout << "Dr. " << eRoom[i].d.docName << endl;
			cout << "Specialty: " << eRoom[i].d.specCode << endl;

			trans << "\n-------------------------------------------------------" << endl;
			trans << "Room #" << i + 1 << endl;
			trans << "Dr. " << eRoom[i].d.docName << endl;
			trans << "Specialty: " << eRoom[i].d.specCode << endl;

			// If the room has no patients.
			if (eRoom[i].patientIn == false)
			{
				cout << "Patients: None" << endl;			
				cout << "-------------------------------------------------------" << endl;

				trans << "Patients: None" << endl;
				trans << "-------------------------------------------------------" << endl;
			}
			// The room has patients.
			else
			{
				cout << "Patients: " << eRoom[i].waitRoom.GetLength() << endl;
				cout << "-------------------------------------------------------" << endl;

				trans << "Patients: " << eRoom[i].waitRoom.GetLength() << endl;
				trans << "-------------------------------------------------------" << endl;
			}
			occupiedRooms = true;
		}
	}

	// If there are no occupied rooms.
	if (occupiedRooms == false)
	{
		cout << "\n-------------------------------------------------------" << endl;
		cout << "There are no rooms in use." << endl;
		cout << "-------------------------------------------------------" << endl;

		trans << "\n-------------------------------------------------------" << endl;
		trans << "There are no rooms in use." << endl;
		trans << "-------------------------------------------------------" << endl;
	}
}

/* Reassign patients to a different doctor.
   Search each exam room for the doctor of the specialty needed. 
*/
void assignDoctor(patient& tempPat)
{
	bool doctorFound = false;

	// Assign the patient to a pediatrician if younger than 16.
	if (tempPat.age < 16)
	{
		// Search each room for a doctor.
		for (int i = 0; i < 20; i++)
		{
			// If the room has a doctor.
			if (eRoom[i].doctorIn == true)
			{
				// If the doctor is a pediatrician.
				if (eRoom[i].d.specCode == 1)
				{
					cout << "\n-------------------------------------------------------" << endl;
					cout << "Please direct the patient to:" << endl;
					cout << "\tRoom #" << i + 1 << endl;
					cout << "\tDr. " << eRoom[i].d.docName << endl;
					cout << "\tPediatrics (PED)" << endl;
					cout << "-------------------------------------------------------" << endl;

					trans << "\n-------------------------------------------------------" << endl;
					trans << "Please direct the patient to:" << endl;
					trans << "\tRoom #" << i + 1 << endl;
					trans << "\tDr. " << eRoom[i].d.docName << endl;
					trans << "\tPediatrics (PED)" << endl;
					trans << "-------------------------------------------------------" << endl;

					eRoom[i].waitRoom.Enqueue(tempPat);

					// Set patientIn to true to show the room contains a patient.
					eRoom[i].patientIn = true;
					// Set doctorFound to true to show the room contains a doctor.
					doctorFound = true;
					break;
				}
			}
		}

		// If there is no pediatric doctor available.
		if (doctorFound == false)
		{
			cout << "\nThere is no pediatric doctor available." << endl;
			cout << "Searching for general practitioner (GEN)." << endl;

			trans << "\nThere is no pediatric doctor available." << endl;
			trans << "Searching for general practitioner (GEN)." << endl;
		}
	}

	// Assign the patient to a dr. (non-PED) if older than 15, or younger than 16 if no PED dr. available.   
	if (tempPat.age > 15 || doctorFound == false)
	{
		// Search each room for a doctor.
		for (int i = 0; i < 20; i++)
		{
			// If the room has a doctor.
			if (eRoom[i].doctorIn == true)
			{
				// If the room has a doctor of the requested specialty.
				if (eRoom[i].d.specCode == tempPat.specialty)
				{
					// Check that this doctor has the shortest waiting list.
					int tempRoom; // Hold the room number with the shortest waiting list.
					int waitListSize; // Hold the number of people on the waiting list.		
					int smallestWaitList = 20; // Hold the room # with the shortest wait list searched so far.	

					for (int j = 0; j < 20; j++)
					{
						if (eRoom[j].doctorIn == true)
						{
							if (eRoom[j].d.specCode == tempPat.specialty)
							{
								waitListSize = eRoom[j].waitRoom.GetLength();

								if (waitListSize <= smallestWaitList)
								{
									tempRoom = j;
									smallestWaitList = waitListSize;
								}
							}
						}
					}

					// Assign the patient to the dr. of requested specialty with the shortest waiting list.
					cout << "\n-------------------------------------------------------" << endl;
					cout << "Please direct the patient to:" << endl;
					cout << "\tRoom #" << (tempRoom + 1) << endl;
					cout << "\tDr. " << eRoom[tempRoom].d.docName << endl;
					cout << "-------------------------------------------------------" << endl;

					trans << "\n-------------------------------------------------------" << endl;
					trans << "Please direct the patient to:" << endl;
					trans << "\tRoom #" << (tempRoom + 1) << endl;
					trans << "\tDr. " << eRoom[tempRoom].d.docName << endl;
					trans << "-------------------------------------------------------" << endl;

					eRoom[tempRoom].waitRoom.Enqueue(tempPat);

					// Set patientIn to true to show the room contains a patient.
					eRoom[tempRoom].patientIn = true;
					// Set doctorFound to true to show the room contains a doctor.
					doctorFound = true;
					break;
				}
			}
		}

		// Assign the patient to a general practitioner if no other specialty is found.
		if (doctorFound == false)
		{
			// Search each room for a doctor.
			for (int i = 0; i < 20; i++)
			{
				// If the room has a doctor.
				if (eRoom[i].doctorIn == true)
				{
					// If the doctor is a general practitioner.
					if (eRoom[i].d.specCode == 2)
					{
						cout << "\n-------------------------------------------------------" << endl;
						cout << "Please direct the patient to:" << endl;
						cout << "\tRoom #" << i + 1 << endl;
						cout << "\tDr. " << eRoom[i].d.docName << endl;
						cout << "\tGeneral Practice (GEN) " << endl;
						cout << "-------------------------------------------------------" << endl;

						trans << "\n-------------------------------------------------------" << endl;
						trans << "Please direct the patient to:" << endl;
						trans << "\tRoom #" << i + 1 << endl;
						trans << "\tDr. " << eRoom[i].d.docName << endl;
						trans << "\tGeneral Practice (GEN)" << endl;
						trans << "-------------------------------------------------------" << endl;

						eRoom[i].waitRoom.Enqueue(tempPat);

						eRoom[i].patientIn = true;
						doctorFound = true;
						break;
					}
				}
			}
		}

		// Assign the patient to the doctor with the smallest waiting queue if there's no requested specialty or GEN.
		if (doctorFound == false)
		{
			int tempRoom; // Hold the room number with the shortest waiting list.
			int waitListSize; // Hold the number of people on the waiting list.	
			int smallestWaitList = 20; // Hold the room # with the shortest wait list searched so far.

            // Search each room for a doctor.
			for (int i = 0; i < 20; i++)
			{
				// If the room has a doctor.
				if (eRoom[i].doctorIn == true)
				{
					waitListSize = eRoom[i].waitRoom.GetLength();

					if (waitListSize <= smallestWaitList)
					{
						tempRoom = i;
						smallestWaitList = waitListSize;
					}
				}
			}

			// Display the information to the user.
			cout << "\n-------------------------------------------------------" << endl;
			cout << "Please direct the patient to:" << endl;
			cout << "\tRoom #" << tempRoom + 1 << endl;
			cout << "\tDr. " << eRoom[tempRoom].d.docName << endl;
			cout << "-------------------------------------------------------" << endl;

			trans << "\n-------------------------------------------------------" << endl;
			trans << "Please direct the patient to:" << endl;
			trans << "\tRoom #" << tempRoom + 1 << endl;
			trans << "\tDr. " << eRoom[tempRoom].d.docName << endl;
			trans << "-------------------------------------------------------" << endl;

			eRoom[tempRoom].waitRoom.Enqueue(tempPat);

			eRoom[tempRoom].patientIn = true;
			doctorFound = true;
		}

		// If there is no doctor in the clinic.
		if (doctorFound == false)
		{
			cout << "\nThere is currently no doctor available in the clinic.\n" << endl;
			trans << "\nThere is currently no doctor available in the clinic.\n" << endl;
		}
	}
}

// Open a text file to write the program's input and output.
void openOutputFile()
{
	trans.open("trans.out", ios::app); // Open the file		

	// If the file is not open
	if (!trans.is_open())
	{
		cout << "The file could not be located." << endl;
		cout << "Program terminating...." << endl;

		trans << "The file could not be located." << endl;
		trans << "Program terminating...." << endl;

		exit(0);
	}

	trans << endl;
	trans << "************************** N E W    S E S S I O N **************************" << endl;
	trans << "****************************************************************************" << endl;
	trans << endl;
}