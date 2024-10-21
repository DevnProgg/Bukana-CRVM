#include "UI_Components.h"

void showProgressBar(int progress, int total, int x, int y) {

	int barWidth = 50;
	int position = progress * barWidth / total;

	UI_Utilities::gotoxy(y, x);
	std::cout << "[";
	for (int i = 0; i < barWidth; ++i) {
		if (i < position) {
			UI_Utilities::setTextColor(10);
			std::cout << "D";
		}
		else {
			std::cout << " "; 
		}
	}
	UI_Utilities::setTextColor(7);
	std::cout << "] " << (progress * 100 / total) << "%\r"; 
	std::cout.flush(); 
}

void progressBar(int totalSteps, int x, int y) {

	int progress = totalSteps;
	for (int step = 0; step <= progress; ++step) {
		showProgressBar(step, progress, x, y); 
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

str Login_UI::Login() {

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

		progressBar(1000, 10, 10);

		loginSuccess = validateCredentials(username, password);

		if (!loginSuccess) {
			setTextColor(4); // Red color
			gotoxy(10, 11);
			std::cout << "Invalid username or password. Please try again.";
			(void)_getch(); // Wait for user to press a key before retrying
		}
	}

	clearScreen();
	return Utilities::Database::loginUser(username, password);
}

bool Login_UI::validateCredentials(const str Username, const str Password) {

	str response = Utilities::Database::loginUser(Username, Password);
	if (response == "fail") {
		return false;
	}
	return (true);
}

bool UI_Utilities::Validate(const str data) {

	if (data.size() == 0) return false;
	return true;
}

bool UI_Utilities::validateNumber(const str data) {

	for (char num : data) {
		// If any character is not a digit, the cellphone number is not valid
		if (!std::isdigit(num)) {
			return false;
		}
	}
	return true;
}

bool UI_Utilities::validateDateOfbirth(const str data) {

	std::istringstream iss(data);
	str month, day, year;
	string_vector result;

	// Split the dob by /
	if (std::getline(iss, month, '/') &&
		std::getline(iss, day, '/') &&
		std::getline(iss, year)) {

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

bool UI_Utilities::validateAddresss(const str data) {


	std::istringstream iss(data);
	str Town, District;
	string_vector result;

	// Split the address by commas
	if (std::getline(iss, Town, ',') &&
		std::getline(iss, District)) {

		Town.erase(0, Town.find_first_not_of(" \t")); // Remove leading spaces
		Town.erase(Town.find_last_not_of(" \t") + 1); // Remove trailing spaces

		District.erase(0, District.find_first_not_of(" \t")); // Remove leading spaces
		District.erase(District.find_last_not_of(" \t") + 1); // Remove trailing spaces
	}

	// Check if all parts are non-empty
		// If any part is empty, the address is not in the correct format
	return !Town.empty() && !District.empty();
}

bool Registrations_UI::validateRegistration(const string_vector data) {

	return Utilities::Database::addUser(data);
}

void Registrations_UI::registerChildUI() {
	bool registrationSuccess = false;

	while (!registrationSuccess) {
		clearScreen();
		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||"
			<< "========================= Child Registration =========================" << std::endl;

		std::cout << std::setw(13) << " " << "Fullname: "

		// Fill additional information (same as before)
		child_Info[0] = Utilities::IDGenerator(child_Info[FirstName], child_Info[Surname], child_Info[DateOfBirth], Utilities::Database::countUsers() + 1);
		child_Info[Title] = "null";
		child_Info[PracticeNumber] = "null";
		child_Info[Resident_H_C] = "null";
		child_Info[C_H_Address] = "null";
		child_Info[CellphoneNumber] = "null";
		child_Info[Password] = Utilities::passwordGenerator(child_Info[FirstName]);
		child_Info[Usertype] = "child";

		clearScreen();
		//ProgressBar(1000, 10, 10); // Ensure ProgressBar() works as intended

		registrationSuccess = validateRegistration(child_Info);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Registration was not successful. Please try again." << std::endl;
			(void)_getch();
			progress = 0; // Reset progress to start over
		}
		else {
			setTextColor(10); // Green color
			std::cout << std::setw(10) << " " << "Registration was successful." << std::endl;
			std::cout << std::setw(10) << " " << "Your Username is " << child_Info[FirstName] << std::endl;
			std::cout << std::setw(10) << " " << "Your Password is " << child_Info[Password] << std::endl;
			(void)_getch();
		}
	}

	clearScreen();
}


void Registrations_UI::registerDoctorUI() {

	bool registrationSuccess = false;
	int progress = 0;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||" // Using setw to indent the text
			<< "========================= Doctor Registration =========================" << std::endl;

		while (progress < TotalSteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case ID: continue; break;
			case FirstName: promptMessage = "FirstName: "; break;
			case Title: continue; break;
			case Surname: promptMessage = "Surname: "; break;
			case DateOfBirth: continue; break;
			case MotherName: continue; break;
			case FatherName: continue; break;
			case Village: continue; break;
			case Chief: continue; break;
			case District: continue; break;
			case PracticeNumber: promptMessage = "Practice Number: "; break;
			case Resident_H_C: promptMessage = "Resident Hospital/ Clinic: "; break;
			case C_H_Address: promptMessage = "Clinic / Hospital Address (Town, District)"; break;
			case CellphoneNumber: promptMessage = "Cellphone Number"; break;
			case Password: continue; break;
			case Usertype: continue; break;
			}

			std::cout << std::setw(10) << " ||" // Aligning input prompt to the right
				<< promptMessage;
			std::getline(std::cin, doctor_Info[progress + 1]); // Store the input in child_Info

			// Validate the input based on the field type
			if (progress == PracticeNumber) {
				isValidInput = validateNumber(doctor_Info[progress + 1]);
			}
			else if (progress == C_H_Address) {
				isValidInput = validateAddresss(doctor_Info[progress + 1]);
			}
			else if (progress == CellphoneNumber) {
				isValidInput = validateNumber(doctor_Info[progress + 1]);
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
		doctor_Info[Password] = Utilities::passwordGenerator(doctor_Info[FirstName]);
		doctor_Info[Usertype] = "doctor";

		clearScreen();
		progressBar(1000, 10, 10);

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

void Registrations_UI::registerNurseUI() {

	bool registrationSuccess = false;
	int progress = 0;

	while (!registrationSuccess) {
		clearScreen();

		setTextColor(7); // White color
		std::cout << std::setw(10) << " ||" // Using setw to indent the text
			<< "========================= Nurse Registration =========================" << std::endl;

		while (progress < TotalSteps) {
			bool isValidInput = false;
			std::string promptMessage;

			switch (progress) {
			case ID: continue; break;
			case Title: promptMessage = "Title (defualt = Sister): "; break;
			case FirstName: promptMessage = "FirstName: "; break;
			case Surname: promptMessage = "Surname: "; break;
			case DateOfBirth: continue; break;
			case MotherName: continue; break;
			case FatherName: continue; break;
			case Village: continue; break;
			case Chief: continue; break;
			case District: continue; break;
			case PracticeNumber: promptMessage = "Practice Number: "; break;
			case Resident_H_C: promptMessage = "Resident Hospital/ Clinic: "; break;
			case C_H_Address: promptMessage = "Clinic / Hospital Address (Town, District)"; break;
			case CellphoneNumber: promptMessage = "Cellphone Number"; break;
			case Password: continue; break;
			case Usertype: continue; break;
			}

			std::cout << std::setw(10) << " ||" // Aligning input prompt to the right
				<< promptMessage;
			std::getline(std::cin, nurse_Info[progress + 1]); // Store the input in child_Info

			// Validate the input based on the field type
			if (progress == Title) {
				nurse_Info[progress] = "Sister";
			}
			if (progress == PracticeNumber) {
				isValidInput = validateNumber(nurse_Info[progress + 1]);
			}
			else if (progress == C_H_Address) {
				isValidInput = validateAddresss(nurse_Info[progress + 1]);
			}
			else if (progress == CellphoneNumber) {
				isValidInput = validateNumber(nurse_Info[progress + 1]);
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
		nurse_Info[Password] = Utilities::passwordGenerator(nurse_Info[FirstName]);
		nurse_Info[Usertype] = "nurse";

		clearScreen();
		progressBar(1000, 10, 10);

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

void Medical_UI::onOptionSelected(int option, const str operation) {

	if (operation == "print") {
		std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();
		Utilities::printMedicalReport(_options[option].first);
		return;
	}

	if (operation == "display") {
		std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();
		Medical_UI::displayMedicalReport(_options[option].first);
		return;
	}
}

void Medical_UI::displayChildren(const string_vector Options, const str operation) {

	clearScreen();
	char key;
	int selectedOption = 0;

	while (true) {
		for (int i = 0; i < Options.size(); ++i) {
			gotoxy(10, 5 + i);
			setTextColor(i == selectedOption ? 10 : 7);
			std::cout << Options[i];
		}

		key = _getch();

		if (key == -32) {
			key = _getch();
			if (key == 72 && selectedOption > 0) {
				selectedOption--;
			}
			if (key == 80 && selectedOption < Options.size() - 1) {
				selectedOption++;
			}
		}

		if (key == 13) {
			clearScreen();
			onOptionSelected(selectedOption, operation);
			break;
		}
	}
}

void Medical_UI::printMedicalReport(const str ID, const str userType) {

	if (userType == "child") {
		Utilities::printMedicalReport(ID);
	}

	std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();

	for (const auto& pair : _options) {
		childrenOptions.push_back(pair.second);
	}
	displayChildren(childrenOptions, "print");
	return;
}

void Medical_UI::displayMedicalReport(const str ID) {

	bool showData = false;
	char response;
	string_vector childData = Utilities::Database::getUserInfo(ID);
	string_vector medicalReports = Utilities::Database::getMedicalReports(ID);
	str id, treatment, medication, childId, weight, height, doctor, clinic, consulationDate, checkupDate;

	while (showData) {
		clearScreen();
		std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(10) << " " << "Child's Medical Report" << std::endl;
		std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

		std::cout << std::setw(11) << " " << "Child Fullname:    " << childData[0] << " " << childData[2] << " " << childData[3] << std::endl;
		std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << childData[childData.size()] << std::endl;
		std::cout << std::setw(11) << " " << "Date Of Birth:     " << childData[4] << std::endl;
		std::cout << std::setw(11) << " " << "Medical Consultations: " << std::endl;
		for (int i = 0; i < medicalReports.size(); ++i) {
			std::stringstream ss(medicalReports[i]);

			if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, medication, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, doctor, ',') && std::getline(ss, clinic, ',') && std::getline(ss, consulationDate, ',')) {
				std::cout << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << treatment << "| Medication: " << medication << "| Weight: " << weight << "kg | Height: " << height << "cm | Doctor: " << doctor << " | Clinic: " << clinic << " | Date: " << consulationDate << std::endl;
			}
		}

		std::cout << std::setw(11) << " " << "Date for next Checkup:  " << checkupDate << std::endl;

		std::cout << "\n Press ENTER to go back to Main Menu ";
		(void)_getch();
		clearScreen();
		return;
	}
	//hide data
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "|" << std::setw(10) << " " << "Child's Medical Report" << std::endl;
	std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(11) << " " << "Child Fullname:    " << Utilities::DataMasking::fixedPositionMask(childData[0], 1, childData[0].length()) << " " << Utilities::DataMasking::fullMask(childData[2]) << " " << Utilities::DataMasking::fixedPositionMask(childData[3], 0, childData[3].length() - 3) << std::endl;
	std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << Utilities::DataMasking::fixedPositionMask(childData[childData.size()], 1, childData[childData.size()].length()) << std::endl;
	std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
	std::cout << std::setw(11) << " " << "Medical Consultations: " << std::endl;

	for (int i = 0; i < medicalReports.size(); ++i) {
		std::stringstream ss(medicalReports[i]);

		if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, medication, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, doctor, ',') && std::getline(ss, clinic, ',') && std::getline(ss, consulationDate, ',')) {
			std::cout << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << Utilities::DataMasking::fullMask(treatment) << "| Medication: " << medication << "| Weight: " << weight << "kg | Height: " << height << "cm | Doctor: " << doctor << " | Clinic: " << clinic << " | Date: " << consulationDate << std::endl;
		}
	}

	std::cout << std::setw(11) << " " << "Date for next Checkup:  " << checkupDate <<  std::endl;

	std::cout << "\n Show Sensitive Informtion? (Y/N):  ";
	std::cin >> response;

	if (response == 'y' || response == 'Y') showData = true;
	else showData = false;
}
bool Medical_UI::validateMedicalForm(const string_vector data) {

	return Utilities::Database::addMedicalReport(data);
}

void Medical_UI::addMedicalReport() {

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
				isValidInput = validateDateOfbirth(medicalForm[progress + 1]);
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
				setTextColor(7);
				continue;
			}

			progress++;
		}
		clearScreen();
		medicalForm[ID] = std::to_string(rand() % 1000000 + 1) + medicalForm[ChildRecordID];

		progressBar(1000, 10, 10);
		registrationSuccess = validateMedicalForm(medicalForm);

		if (!registrationSuccess) {
			setTextColor(4); // Red color
			std::cout << std::setw(10) << " " << "Process was not successful. Please try again." << std::endl;
			(void)_getch(); // Wait for user to press a key before retrying
			progress = 0;
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

void Medical_UI::deleteMedicalReport(const str ID) {

	Utilities::Database::deleteMedicalReport(ID);
	return;
}

void Medical_UI::updateMedicalReport(const str ID) {

	deleteMedicalReport(ID);
	addMedicalReport();
	return;
}

bool Vaccine_UI::validateVaccineForm(const string_vector data) {

	return Utilities::Database::addVaccineReport(data);
}

void Vaccine_UI::addVaccineReport() {

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
				isValidInput = validateDateOfbirth(vaccineForm[progress + 1]);
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
		vaccineForm[ID] = std::to_string(rand() % 1000000 + 1) + vaccineForm[ChildRecordID];

		progressBar(1000, 10, 10);
		registrationSuccess = validateVaccineForm(vaccineForm);

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

void Vaccine_UI::printVaccineReport(const str ID, const str userType) {

	if (userType == "child") {
		Utilities::printMedicalReport(ID);
	}

	std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();

	for (const auto& pair : _options) {
		childrenOptions.push_back(pair.second);
	}
	return;
}

void Vaccine_UI::displayVaccineReport(const str ID) {

	bool showData = false;
	char response;
	string_vector childData = Utilities::Database::getUserInfo(ID);
	string_vector VaccineReports = Utilities::Database::getVaccineReports(ID);
	str id, treatment, vaccine, childId, weight, height, nurse, clinic, clinicDate, nextClinicDate;

	while (showData) {
		clearScreen();
		std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
		std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

		std::cout << std::setw(11) << " " << "Child Fullname:    " << childData[0] << " " << childData[2] << " " << childData[3] << std::endl;
		std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << childData[childData.size()] << std::endl;
		std::cout << std::setw(11) << " " << "Date Of Birth:     " << childData[4] << std::endl;
		std::cout << std::setw(11) << " " << "Vaccinations Administered: " << std::endl;

		for (int i = 0; i < VaccineReports.size(); ++i) {
			std::stringstream ss(VaccineReports[i]);

			if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, vaccine, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, nurse, ',') && std::getline(ss, clinic, ',') && std::getline(ss, clinicDate, ',')) {
				std::cout << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << treatment << "| Medication: " << vaccine << "| Weight: " << weight << "kg | Height: " << height << "cm | Nurse: " << nurse << " | Clinic: " << clinic << " | Date: " << clinicDate << std::endl;
			}
		}

		std::cout << std::setw(11) << " " << "Date for next Vaccine:  " << NextClinicDate << std::endl;

		std::cout << "\n Press ENTER to go back to Main Menu ";
		(void)_getch();
		clearScreen();
		return;
	}
	//hide data
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
	std::cout << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

	std::cout << std::setw(11) << " " << "Child Fullname:    " << Utilities::DataMasking::fixedPositionMask(childData[0], 1, childData[0].length()) << " " << Utilities::DataMasking::fullMask(childData[2]) << " " << Utilities::DataMasking::fixedPositionMask(childData[3], 0, childData[3].length() - 3) << std::endl;
	std::cout << std::setw(11) << " " << "Guardian/Parents Name(s):      " << Utilities::DataMasking::fixedPositionMask(childData[childData.size()], 1, childData[childData.size()].length()) << std::endl;
	std::cout << std::setw(11) << " " << "Date Of Birth:     " << std::endl;
	std::cout << std::setw(11) << " " << "Vaccinations Administered: " << std::endl;

	for (int i = 0; i < VaccineReports.size(); ++i) {
		std::stringstream ss(VaccineReports[i]);

		if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, vaccine, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, nurse, ',') && std::getline(ss, clinic, ',') && std::getline(ss, clinicDate, ',')) {
			std::cout << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << Utilities::DataMasking::fullMask(treatment) << "| Medication: " << vaccine << "| Weight: " << weight << "kg | Height: " << height << "cm | Nurse: " << nurse << " | Clinic: " << clinic << " | Date: " << clinicDate << std::endl;
		}
	}

	std::cout << std::setw(11) << " " << "Date for next Vaccine:  " << NextClinicDate << std::endl;

	std::cout << "\n Show Sensitive Informtion? (Y/N):  ";
	std::cin >> response;

	if (response == 'y' || response == 'Y') showData = true;
	else showData = false;
}

void Vaccine_UI::deleteVaccineReport(const str ID) {

	Utilities::Database::deleteVaccineReport(ID);
	return;
}

void Vaccine_UI::updateVaccineReport(const str ID) {

	deleteVaccineReport(ID);
	addVaccineReport();
	return;
}

void Vaccine_UI::onOptionSelected(int option, const str operation) {
	if (operation == "print") {
		std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();
		Utilities::printMedicalReport(_options[option].first);
		return;
	}

	if (operation == "display") {
		std::vector<std::pair<str, str>> _options = Utilities::Database::getUsers();
		Vaccine_UI::displayVaccineReport(_options[option].first);
		return;
	}
}

void Vaccine_UI::displayChildren(const string_vector Options, const str operation) {
	clearScreen();
	char key;
	int selectedOption = 0;

	while (true) {
		for (int i = 0; i < Options.size(); ++i) {
			gotoxy(10, 5 + i);
			setTextColor(i == selectedOption ? 10 : 7);
			std::cout << Options[i];
		}

		key = _getch();

		if (key == -32) {
			key = _getch();
			if (key == 72 && selectedOption > 0) {
				selectedOption--;
			}
			if (key == 80 && selectedOption < Options.size() - 1) {
				selectedOption++;
			}
		}

		if (key == 13) {
			clearScreen();
			onOptionSelected(selectedOption, operation);
			break;
		}
	}
}