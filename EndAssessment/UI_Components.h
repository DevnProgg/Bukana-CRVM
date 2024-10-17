#pragma once

#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Utilities.h"

using string_vector = std::vector<std::string>;
using str = std::string;

void showProgressBar(int progress, int total, int x, int y);
void ProgressBar(int totalSteps, int x, int y);

class UI_Utilities {
public:
	static void clearScreen(); // Clears the console screen
	static void setTextColor(int color); // Changes the text color in the console
	static void gotoxy(int x, int y); // Moves the cursor to a specified position in the console
	static bool Validate(const str& data);
	static bool ValidateNumber(const str& data);
	static bool ValidateAddresss(const str& data);
	static bool ValidateDateOfbirth(const str& data);
};

class Menu : public UI_Utilities {
protected:
	string_vector options;  // List of menu options
	int selectedOption;  // Currently selected option

public:
	void setOptions(const string_vector data);
	// Virtual function to handle the action when an option is selected
	virtual void onOptionSelected(int option);

	// Function to display the menu
	void displayMenu(const int start, const int end);
};

class Login_UI : public UI_Utilities {
public:
	void login(); // Function to display the login screen

private:
	str username;
	str password;

	bool validateCredentials(const str username, const str password);
};

class Registrations_UI : public UI_Utilities {
private:
	str child_Info[17];
	str doctor_Info[17];
	str nurse_Info[17];
	enum RegistrationStep {
		ID,
		FirstName,
		Title,
		MiddleName,
		Surname,
		DateOfBirth,
		MotherName,
		FatherName,
		Village,
		Chief,
		District,
		PracticeNumber,
		Resident_H_C,
		C_H_Address,
		CellphoneNumber,
		Password,
		Usertype,
		TotalSteps
	};

	bool validateRegistration(const str data[]);
public:
	void Register_Child_UI();
	void Register_Doctor_UI();
	void Register_Nurse_UI();
};

class Medical_UI : public UI_Utilities {
private:
	enum MedicalRecordStep {
		Treatment,
		Medication,
		ChildRecordID,
		Weight,
		Height,
		Doctor,
		Clinic,
		ConsultationDate,
		CheckupDate,
		m_Totalsteps
	};
	str medicalForm[m_Totalsteps];
	bool validateMedicalForm(const str data[]);

public:

	void PrintMedicalReport();
	void DisplayMedicalReport();
	void AddMedicalReport();
	void DeleteMedicalReport(const str& id);
	void UpdateMedicalReport(const str& id);
};

class Vaccine_UI : public UI_Utilities {
private:

	enum VaccineRecordStep {
		Treatment,
		Vaccine,
		ChildRecordID,
		Weight,
		Height,
		Nurse,
		Clinic,
		ClinicDate,
		NextClinicDate,
		m_Totalsteps
	};
	str vaccineForm[m_Totalsteps];
	bool ValidateVaccineForm(const str data[]);
public:

	void PrintVaccineReport();
	void DisplayVaccineReport();
	void AddVaccineReport();

	void DeleteVaccineReport(const str& id);
	void UpdateVaccineReport(const str& id);
};
