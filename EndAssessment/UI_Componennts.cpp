#include "UI_Components.h"

void showProgressBar(int progress, int total, int x, int y) {
	int barWidth = 50; 
	int position = progress * barWidth / total; 

	UI_Utilities::gotoxy(y, x);
	std::cout << "[";
	for (int i = 0; i < barWidth; ++i) {
		if (i < position) {
			UI_Utilities::setTextColor(10);
			std::cout << "D"; // Filled part of the bar
		}
		else {
			std::cout << " "; // Empty part of the bar
		}
	}
	UI_Utilities::setTextColor(7);
	std::cout << "] " << (progress * 100 / total) << "%\r"; // Show percentage
	std::cout.flush(); // Ensure the output is displayed immediately
}

void ProgressBar(int totalSteps, int x, int y) {
	int progress = totalSteps;
	for (int step = 0; step <= progress; ++step) {
		showProgressBar(step, progress, x , y); // Update the progress bar
	}
}

void UI_Utilities::clearScreen() {
	std::system("CLS");
}

void UI_Utilities::setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void UI_Utilities::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Menu::Menu(const string_vector& menuoptions) : options(menuoptions), selectedOption(0) {}

void Menu::setOptions(const string_vector data) {
	options = data;
}

void Menu::onOptionSelected(int option) {
	// Virtual function to be overridden by the child class
}

void Menu::displayMenu(const int start, const int end) {
	clearScreen();
	char key;

	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	UI_Utilities::setTextColor(10);
	std::cout << std::setw(15) << " " << "Bukana - CRVM" << std::endl;
	UI_Utilities::setTextColor(7);
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;

	while (true) {
		// Display the menu options
		for (int i = start; i < end; ++i) {
			gotoxy(10, 5 + i);
			setTextColor(i == selectedOption ? 10 : 7);  // Highlight the selected option
			std::cout << options[i];
		}

		key = _getch();  // Wait for user input

		if (key == -32) {  // Check for arrow key prefix
			key = _getch();  // Get the actual arrow key
			if (key == 72 && selectedOption > 0) {  // Up arrow key
				selectedOption--;
			}
			if (key == 80 && selectedOption < end - 1) {  // Down arrow key
				selectedOption++;
			}
		}

		if (key == 13) {  // Enter key
			clearScreen();  // Clear the screen
			onOptionSelected(selectedOption);  // Call the virtual function
			break;  // Exit the loop after selection
		}
	}
}

void Login_UI::login() {
	bool loginSuccess = false;

	while (!loginSuccess) {
		clearScreen();
		setTextColor(7); // White color

		gotoxy(10, 5);
		std::cout << "========================= Login =========================";
		gotoxy(10, 7);
		std::cout << "Username: ";
		std::cin >> username;

		gotoxy(10, 8);
		std::cout << "Password: ";
		char ch;
		password = "";
		while ((ch = _getch()) != '\r') { // '\r' is the Enter key
			if (ch == '\b' && !password.empty()) { // Backspace handling
				password.pop_back();
				std::cout << "\b \b"; // Move cursor back, erase character, and move back again
			}
			else if (ch != '\b') {
				password += ch;
				std::cout << '*'; // Display an asterisk for each character
			}
		}

		ProgressBar(1000, 10, 10);

		loginSuccess = validateCredentials(username, password);

		if (!loginSuccess) {
			setTextColor(4); // Red color
			gotoxy(10, 11);
			std::cout << "Invalid username or password. Please try again.";
			(void)_getch(); // Wait for user to press a key before retrying
		}
	}

	clearScreen();
}

bool Login_UI::validateCredentials(const str username, const str password) {
	return (false);
}

bool UI_Utilities::Validate(const str& data) {
	if (data.size() == 0) return false;
	return true;
}

bool UI_Utilities::ValidateNumber(const str& data) {
	for (char num : data) {
		// If any character is not a digit, the cellphone number is not valid
		if (!std::isdigit(num)) {
			return false;
		}
	}
	return true;
}

bool UI_Utilities::ValidateDateOfbirth(const str& data) {
	// Create an input stream from the DOB string
	std::istringstream iss(data);
	str month, day, year;
	string_vector result;

	// Split the dob by /
	if (std::getline(iss, month, '/') &&
		std::getline(iss, day, '/') &&
		std::getline(iss, year)) {
		// Trim leading and trailing spaces from each part
		// This is necessary because the input string may contain leading or trailing spaces
		// or spaces between the / and the parts of the dob
		month.erase(0, month.find_first_not_of(" \t")); // Remove leading spaces
		month.erase(month.find_last_not_of(" \t") + 1); // Remove trailing spaces

		day.erase(0, day.find_first_not_of(" \t")); // Remove leading spaces
		day.erase(day.find_last_not_of(" \t") + 1); // Remove trailing spaces

		year.erase(0, year.find_first_not_of(" \t")); // Remove leading spaces
		year.erase(year.find_last_not_of(" \t") + 1); // Remove trailing spaces
	}
	else {
		// If the input string is not in the correct format, set the validity flag to false
		return false;
	}

	// Check if all parts are non-empty
	// If any part is empty, the DOB is not in the correct format
	return  !month.empty() && !day.empty() && !year.empty();
}

bool UI_Utilities::ValidateAddresss(const str& data) {
	// Create an input stream from the address string
	std::istringstream iss(data);
	str Town, District;
	string_vector result;

	// Split the address by commas
	if (std::getline(iss, Town, ',') &&
		std::getline(iss, District)) {
		// Trim leading and trailing spaces from each part
		// This is necessary because the input string may contain leading or trailing spaces
		// or spaces between the commas and the parts of the address

		Town.erase(0, Town.find_first_not_of(" \t")); // Remove leading spaces
		Town.erase(Town.find_last_not_of(" \t") + 1); // Remove trailing spaces

		District.erase(0, District.find_first_not_of(" \t")); // Remove leading spaces
		District.erase(District.find_last_not_of(" \t") + 1); // Remove trailing spaces
	}

	// Check if all parts are non-empty
		// If any part is empty, the address is not in the correct format
	return !Town.empty() && !District.empty();
}

bool Registrations_UI::validateRegistration(const str data[]) {
	return Utilities::Database::addUser(data);
}

void Registrations_UI::Register_Child_UI() {
	bool registrationSuccess = false;
	int progress = 1;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||"
			<< "========================= Child Registration =========================" << std::endl;

		while (progress < TotalSteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case FirstName: promptMessage = "FirstName: "; break;
			case MiddleName: promptMessage = "Middlename: "; break;
			case Surname: promptMessage = "Surname: "; break;
			case DateOfBirth: promptMessage = "Date of Birth (DD/MM/YYYY): "; break;
			case MotherName: promptMessage = "Mother Name: "; break;
			case FatherName: promptMessage = "Father Name: "; break;
			case Village: promptMessage = "Village: "; break;
			case Chief: promptMessage = "Chief: "; break;
			case District: promptMessage = "District: "; break;
			}

			std::cout << std::setw(10) << " ||" << promptMessage;
			std::getline(std::cin, child_Info[progress + 1]);

			if (progress == DateOfBirth) {
				isValidInput = ValidateDateOfbirth(child_Info[progress + 1]);
			}
			else {
				isValidInput = Validate(child_Info[progress + 1]);
			}

			if (!isValidInput) {
				setTextColor(4); // Red color
				std::cout << std::setw(10) << " " << "You can't leave it empty. Try again!" << std::endl;
				(void)_getch();
				clearScreen();
				setTextColor(7); //white color
				continue;
			}

			progress++;
		}

		child_Info[ID] = Utilities::IDGenerator(child_Info[FirstName], child_Info[Surname], child_Info[DateOfBirth], Utilities::Database::countUsers() + 1);
		child_Info[Title] = "null";
		child_Info[PracticeNumber] = "null";
		child_Info[Resident_H_C] = "null";
		child_Info[C_H_Address] = "null";
		child_Info[CellphoneNumber] = "null";
		child_Info[Password] = Utilities::PasswordGenerator(child_Info[FirstName]);
		child_Info[Usertype] = "child";

		clearScreen();
		ProgressBar(1000 , 10, 10);

		registrationSuccess = validateRegistration(child_Info);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Registration was not successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 1; // Restart the registration process
		}
		else {
			setTextColor(10);
			std::cout << std::setw(10) << " " << "Registration Was Successful." << std::endl;
			std::cout << std::setw(10) << " " << "Your Username is " << child_Info[FirstName] << std::endl;
			std::cout << std::setw(10) << " " << "Your Password is " << child_Info[Password] << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
}

void Registrations_UI::Register_Doctor_UI() {
	bool registrationSuccess = false;
	int progress = 1;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||" // Using setw to indent the text
			<< "========================= Doctor Registration =========================" << std::endl;

		while (progress < TotalSteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case FirstName: promptMessage = "FirstName: "; break;
			case Surname: promptMessage = "Surname: "; break;
			case PracticeNumber: promptMessage = "Practice Number: "; break;
			case Resident_H_C: promptMessage = "Resident Hospital/ Clinic: "; break;
			case C_H_Address: promptMessage = "Clinic / Hospital Address (Town, District)"; break;
			case CellphoneNumber: promptMessage = "Cellphone Number"; break;
			}

			std::cout << std::setw(10) << " ||" // Aligning input prompt to the right
				<< promptMessage;
			std::getline(std::cin, doctor_Info[progress + 1]); // Store the input in child_Info

			// Validate the input based on the field type
			if (progress == PracticeNumber) {
				isValidInput = ValidateNumber(doctor_Info[progress + 1]);
			}
			else if (progress == C_H_Address) {
				isValidInput = ValidateAddresss(doctor_Info[progress + 1]);
			}
			else if (progress == CellphoneNumber) {
				isValidInput = ValidateNumber(doctor_Info[progress + 1]);
			}
			else {
				isValidInput = Validate(doctor_Info[progress + 1]);
			}

			if (!isValidInput) {
				setTextColor(4); // Red color
				std::cout << std::setw(10) << " " << "You can't leave it empty. Try again!" << std::endl;
				(void)_getch(); // Wait for user to acknowledge the error
				clearScreen();
				setTextColor(7); //white color
				continue; // Retry the same input
			}

			progress++; // Move to the next step if input is valid
		}

		doctor_Info[ID] = "null";
		doctor_Info[Title] = "null";
		doctor_Info[MiddleName] = "null";
		doctor_Info[DateOfBirth] = "null";
		doctor_Info[MotherName] = "null";
		doctor_Info[FatherName] = "null";
		doctor_Info[Village] = "null";
		doctor_Info[Chief] = "null";
		doctor_Info[District] = "null";
		doctor_Info[Password] = Utilities::PasswordGenerator(doctor_Info[FirstName]);
		doctor_Info[Usertype] = "doctor";

		clearScreen();
		ProgressBar(1000, 10, 10);

		registrationSuccess = validateRegistration(doctor_Info);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Registration was not successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 0; // Restart the registration process
		}
		else {
			setTextColor(10);
			std::cout << std::setw(10) << " " << "Registration Was Successful." << std::endl;
			std::cout << std::setw(10) << " " << "Your Username is " << doctor_Info[FirstName] << std::endl;
			std::cout << std::setw(10) << " " << "Your Password is " << doctor_Info[Password] << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
}

void Registrations_UI::Register_Nurse_UI() {
	bool registrationSuccess = false;
	int progress = 1;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||" // Using setw to indent the text
			<< "========================= Nurse Registration =========================" << std::endl;

		while (progress < TotalSteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case Title: promptMessage = "Title (defualt = Sister): "; break;
			case FirstName: promptMessage = "FirstName: "; break;
			case Surname: promptMessage = "Surname: "; break;
			case PracticeNumber: promptMessage = "Practice Number: "; break;
			case Resident_H_C: promptMessage = "Resident Hospital/ Clinic: "; break;
			case C_H_Address: promptMessage = "Clinic / Hospital Address (Town, District)"; break;
			case CellphoneNumber: promptMessage = "Cellphone Number"; break;
			}

			std::cout << std::setw(10) << " ||" // Aligning input prompt to the right
				<< promptMessage;
			std::getline(std::cin, nurse_Info[progress + 1]); // Store the input in child_Info

			// Validate the input based on the field type
			if (progress == Title) {
				nurse_Info[progress] = "Sister";
			}
			if (progress == PracticeNumber) {
				isValidInput = ValidateNumber(nurse_Info[progress + 1]);
			}
			else if (progress == C_H_Address) {
				isValidInput = ValidateAddresss(nurse_Info[progress + 1]);
			}
			else if (progress == CellphoneNumber) {
				isValidInput = ValidateNumber(nurse_Info[progress + 1]);
			}
			else {
				isValidInput = Validate(nurse_Info[progress + 1]);
			}

			if (!isValidInput) {
				setTextColor(4); // Red color
				std::cout << std::setw(10) << " " << "You can't leave it empty. Try again!" << std::endl;
				(void)_getch(); // Wait for user to acknowledge the error
				clearScreen();
				setTextColor(7); //white color
				continue; // Retry the same input
			}

			progress++; // Move to the next step if input is valid
		}

		nurse_Info[ID] = "null";
		nurse_Info[Title] = nurse_Info[Title] == " " || nurse_Info[Title] == "\r" ? "Sister" : nurse_Info[Title];
		nurse_Info[MiddleName] = "null";
		nurse_Info[DateOfBirth] = "null";
		nurse_Info[MotherName] = "null";
		nurse_Info[FatherName] = "null";
		nurse_Info[Village] = "null";
		nurse_Info[Chief] = "null";
		nurse_Info[District] = "null";
		nurse_Info[Password] = Utilities::PasswordGenerator(nurse_Info[FirstName]);
		nurse_Info[Usertype] = "nurse";

		clearScreen();
		ProgressBar(1000, 10, 10);

		registrationSuccess = validateRegistration(nurse_Info);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Registration was not successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 0; // Restart the registration process
		}
		else {
			setTextColor(10);
			std::cout << std::setw(10) << " " << "Registration Was Successful." << std::endl;
			std::cout << std::setw(10) << " " << "Your Username is " << nurse_Info[0] << std::endl;
			std::cout << std::setw(10) << " " << "Your Password is " << nurse_Info[7] << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
}

void Medical_UI::PrintMedicalReport() {
	//todo code implementation
}

void Medical_UI::DisplayMedicalReport() {
	bool showData = false;
	char response;

	while (showData) {
		clearScreen();
		std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(10) << " " << "Child's Medical Report" << std::endl;
		std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

		std::cout << std::setw(11) << " " << "Child Fullname:    " << std::endl;
		std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << std::endl;
		std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
		std::cout << std::setw(11) << " " << "Medical Consultations: " << std::endl;

		//for loop

		std::cout << std::setw(11) << " " << "Date for next Checkup:  " << std::endl;

		std::cout << "\n Press ENTER to go back to Main Menu ";
		(void)_getch();
		clearScreen();
		return;
	}
	//hide data
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
	std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

	std::cout << std::setw(11) << " " << "Child Fullname:    " << std::endl;
	std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << std::endl;
	std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
	std::cout << std::setw(11) << " " << "Medical Consultations: " << std::endl;

	//for loop

	std::cout << std::setw(11) << " " << "Date for next Checkup:  " << std::endl;

	std::cout << "\n Show Sensitive Informtion? (Y/N):  ";
	std::cin >> response;

	if (response == 'y' || response == 'Y') showData = true;
	else showData = false;
}
bool Medical_UI::validateMedicalForm(const str data[]) {
	return Utilities::Database::addMedicalReport(data);
}

void Medical_UI::AddMedicalReport() {
	bool registrationSuccess = false;
	int progress = 0;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << "||" << std::setfill('=') << std::setw(10) << " " // Using setw to indent the text
			<< "========================= Medical Report Form =========================" << std::endl;

		while (progress < m_Totalsteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case Treatment: promptMessage = "Treatment: "; break;
			case Medication: promptMessage = "Medication: "; break;
			case ChildRecordID: promptMessage = "Child Record ID: "; break;
			case Weight: promptMessage = "Weight: "; break;
			case Height: promptMessage = "Height: "; break;
			case Doctor: promptMessage = "Doctor: "; break;
			case Clinic: promptMessage = "Clinic: "; break;
			case ConsultationDate: promptMessage = "Consultation Date (DD/MM/YYYY): "; break;
			case CheckupDate: promptMessage = "Checkup Date (DD/MM/YYYY): "; break;
			}

			std::cout << "||" << std::setw(10) << " " // Aligning input prompt to the right
				<< promptMessage;
			std::getline(std::cin, medicalForm[progress + 1]); // Store the input in child_Info

			// Validate the input based on the field type
			if (progress == ConsultationDate || progress == CheckupDate) {
				isValidInput = ValidateDateOfbirth(medicalForm[progress + 1]);
			}
			else if (progress == ChildRecordID) {
				isValidInput = Utilities::Database::checkIfExists(medicalForm[progress + 1]);
			}
			else {
				isValidInput = Validate(medicalForm[progress + 1]);
			}

			if (!isValidInput) {
				setTextColor(4); // Red color
				std::cout << std::setw(10) << " " << "You can't leave it empty. Try again!" << std::endl;
				(void)_getch(); // Wait for user to acknowledge the error
				clearScreen();
				setTextColor(7); //white color
				continue; // Retry the same input
			}

			progress++; // Move to the next step if input is valid
		}
		clearScreen();
		ProgressBar(1000, 10, 10);
		registrationSuccess = validateMedicalForm(medicalForm);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Process was not successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 0; // Restart the registration process
		}
		else {
			setTextColor(12);
			std::cout << std::setw(10) << " " << "Process was successful." << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
	return;
}

void Medical_UI::DeleteMedicalReport(const str& id) {
	//Todo: add functionality
}

void Medical_UI::UpdateMedicalReport(const str& id) {
	//Todo: add functionality
}

bool Vaccine_UI::ValidateVaccineForm(const str data[]) {
	return Utilities::Database::addVaccineReport(data);
}

void Vaccine_UI::AddVaccineReport() {
	bool registrationSuccess = false;
	int progress = 0;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << "||" << std::setfill('=') << std::setw(10) << " "
			<< "========================= Vaccine Report Form =========================" << std::endl;

		while (progress < m_Totalsteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case Treatment: promptMessage = "Treatment: "; break;
			case Vaccine: promptMessage = "Vaccine: "; break;
			case ChildRecordID: promptMessage = "Child Record ID: "; break;
			case Weight: promptMessage = "Weight: "; break;
			case Height: promptMessage = "Height: "; break;
			case Nurse: promptMessage = "Nurse: "; break;
			case Clinic: promptMessage = "Clinic: "; break;
			case ClinicDate: promptMessage = "Clinic Date (DD/MM/YYYY): "; break;
			case NextClinicDate: promptMessage = "Next Clinic Date (DD/MM/YYYY): "; break;
			}

			std::cout << "||" << std::setw(10) << " "
				<< promptMessage;
			std::getline(std::cin, vaccineForm[progress + 1]);

			// Validate the input based on the field type
			if (progress == ClinicDate || progress == NextClinicDate) {
				isValidInput = ValidateDateOfbirth(vaccineForm[progress + 1]);
			}
			else if (progress == ChildRecordID) {
				isValidInput = Utilities::Database::checkIfExists(vaccineForm[progress + 1]);
			}
			else {
				isValidInput = Validate(vaccineForm[progress + 1]);
			}

			if (!isValidInput) {
				setTextColor(4); // Red color
				std::cout << std::setw(10) << " " << "You can't leave it empty. Try again!" << std::endl;
				(void)_getch(); // Wait for user to acknowledge the error
				clearScreen();
				setTextColor(7); //white color
				continue; // Retry the same input
			}

			progress++; // Move to the next step if input is valid
		}

		clearScreen();
		ProgressBar(1000, 10, 10);

		registrationSuccess = ValidateVaccineForm(vaccineForm);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Process was successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 0; // Restart the registration process
		}
		else {
			setTextColor(12);
			std::cout << std::setw(10) << " " << "Process was successful." << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
}

void Vaccine_UI::PrintVaccineReport() {
}

void Vaccine_UI::DisplayVaccineReport() {
	//todo get vaccine
	//Utilities _Utilities;
	bool showData = false;
	char response;

	while (showData) {
		clearScreen();
		std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
		std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

		std::cout << std::setw(11) << " " << "Child Fullname:    " << std::endl;
		std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << std::endl;
		std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
		std::cout << std::setw(11) << " " << "Vaccinations Administered: " << std::endl;

		//for loop

		std::cout << std::setw(11) << " " << "Date for next Vaccine:  " << std::endl;

		std::cout << "\n Press ENTER to go back to Main Menu ";
		(void)_getch();
		clearScreen();
		return;
	}
	//hide data
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
	std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

	std::cout << std::setw(11) << " " << "Child Fullname:    " << std::endl;
	std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << std::endl;
	std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
	std::cout << std::setw(11) << " " << "Vaccinations Administered: " << std::endl;

	//for loop

	std::cout << std::setw(11) << " " << "Date for next Vaccine:  " << std::endl;

	std::cout << "\n Show Sensitive Informtion? (Y/N):  ";
	std::cin >> response;

	if (response == 'y' || response == 'Y') showData = true;
	else showData = false;
}
void Vaccine_UI::DeleteVaccineReport(const str& id) {
}
void Vaccine_UI::UpdateVaccineReport(const str& id) {
}