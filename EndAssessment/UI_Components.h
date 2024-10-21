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
void progressBar(int totalSteps, int x, int y);

class UI_Utilities {
public:
	static void clearScreen(); 
	static void setTextColor(int color);
	static void gotoxy(int x, int y); // Moves the cursor to a specified position in the console
	static bool Validate(const str data);
	static bool validateNumber(const str data);
	static bool validateAddresss(const str data);
	static bool validateDateOfbirth(const str data);
};

class Menu : public UI_Utilities {
protected:
	string_vector options;  
	int selectedOption;  

public:
	void setOptions(const string_vector data);
	// Virtual function to handle the action when an option is selected
	virtual void onOptionSelected(int option);

	// Function to display the menu
	void displayMenu(const int start, const int end);
};

class Login_UI : public UI_Utilities {
public:
	str Login(); // Function to display the login screen
private:
	str username;
	str password;

	bool validateCredentials(const str username, const str password);
};

class Registrations_UI : public UI_Utilities {
private:
	string_vector child_Info;
	string_vector doctor_Info;
	string_vector nurse_Info;
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
		Usertype
	};

	bool validateRegistration(const string_vector data);
public:
	void registerChildUI();
	void registerDoctorUI();
	void registerNurseUI();
};

class Medical_UI : public UI_Utilities {
private:
	enum MedicalRecordStep {
		ID,
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
	string_vector medicalForm;
	bool validateMedicalForm(const string_vector data);
	string_vector childrenOptions;
public:

	void printMedicalReport(const str ID, const str userType);
	void displayMedicalReport(const str ID);
	void addMedicalReport();

	void deleteMedicalReport(const str ID);
	void updateMedicalReport(const str ID);
	void onOptionSelected(int option, const str operation);
	void displayChildren(const string_vector Options, const str operation);
};

class Vaccine_UI : public UI_Utilities {
private:

	enum VaccineRecordStep {
		ID,
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
	string_vector vaccineForm;
	bool validateVaccineForm(const string_vector data);
	string_vector childrenOptions;
public:

	void printVaccineReport(const str ID, const str userType);
	void displayVaccineReport(const str ID);
	void addVaccineReport();

	void deleteVaccineReport(const str ID);
	void updateVaccineReport(const str ID);
	void onOptionSelected(int option, const str operation);
	void displayChildren(const string_vector Options, const str operation);
};
