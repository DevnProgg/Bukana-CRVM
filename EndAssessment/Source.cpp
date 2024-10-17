#include <iostream>
#include  "UI_Components.h"

class User : public Menu {
protected:
	str UserType;
};

class Child : public User {
private:
	str id;
	string_vector _Options = { "->  Login",
		"->  Register Child",
		"->  Medical Report",
		"->  Vaccine Report",
		"->  Print Medical Report",
		"->  Print Vaccine Report",
		"->  Exit"
	};

	Login_UI _login;
	Registrations_UI _registrations;
	Medical_UI _medicals;
	Vaccine_UI _vaccines;

	int process = 0;
public:
	Child() {
		UserType = "child";
	}
	void setId(str id) {
		this->id = id;
	}

	void onOptionSelected(int option) override {
		switch (option) {
		case 0:
			_login.login();
			process++;
			break;
		case 1:
			_registrations.Register_Child_UI();
			process++;
			break;
		case 2:
			_medicals.DisplayMedicalReport();
			process++;
			break;
		case 3:
			_vaccines.DisplayVaccineReport();
			process++;
			break;
		case 4:
			_medicals.PrintMedicalReport();
			process++;
			break;
		case 5:
			_vaccines.PrintVaccineReport();
			process++;
			break;
		case 6:
			return;
		default:
			std::cout << "Invalid option selected" << std::endl;
			break;
		}
	}

	void UserInterface() {
		while (process < 2) {
			setOptions(_Options);

			if (process == 0) {
				displayMenu(0, 2);
			}
			else {
				displayMenu(3, 8);
			}
		}
		return;
	}
};

class Doctor : public User {
private:
	string_vector _Options = { "->  Login",
		"->  Register",
		"->  Add New Medical Report",
		"->  Display Medical Report",
		"->  Display Vaccine Report",
		"->  Print Medical Report",
		"->  Print Vaccine Report",
		"->  Exit"
	};

	Login_UI _login;
	Registrations_UI _registrations;
	Medical_UI _medicals;
	Vaccine_UI _vaccines;

	int process = 0;
public:
	Doctor() {
		UserType = "doctor";
	}

	void UserInterface() {
		while (process < 2) {
			setOptions(_Options);

			if (process == 0) {
				displayMenu(0, 2);
			}
			else {
				displayMenu(3, 8);
			}
		}
		return;
	}

	void onOptionSelected(int option) override {
		switch (option) {
		case 0:
			_login.login();
			process++;
			break;
		case 1:
			_registrations.Register_Doctor_UI();
			process++;
			break;
		case 2:
			_medicals.DisplayMedicalReport();
			process++;
			break;
		case 3:
			_medicals.AddMedicalReport();
			process++;
			break;
		case 4:
			_vaccines.DisplayVaccineReport();
			process++;
			break;
		case 5:
			_medicals.PrintMedicalReport();
			process++;
			break;
		case 6:
			_vaccines.PrintVaccineReport();
			process++;
			break;
		case 7:
			return;
		default:
			std::cout << "Invalid option selected" << std::endl;
			break;
		}
	}
};

class Nurse : public User {
private:
	string_vector _Options = { "->  Login",
		"->  Register",
		"->  Add New Vaccine Report",
		"->  Display Medical Report",
		"->  Display Vaccine Report",
		"->  Print Medical Report",
		"->  Print Vaccine Report",
		"->  Exit"
	};

	Login_UI _login;
	Registrations_UI _registrations;
	Medical_UI _medicals;
	Vaccine_UI _vaccines;

	int process = 0;
public:
	Nurse() {
		UserType = "nurse";
	}

	void UserInterface() {
		while (process < 2) {
			setOptions(_Options);

			if (process == 0) {
				displayMenu(0, 2);
			}
			else {
				displayMenu(3, 8);
			}
		}
		return;
	}

	void onOptionSelected(int option) override {
		switch (option) {
		case 0:
			_login.login();
			process++;
			break;
		case 1:
			_registrations.Register_Nurse_UI();
			process++;
			break;
		case 2:
			_medicals.DisplayMedicalReport();
			process++;
			break;
		case 3:
			_vaccines.AddVaccineReport();
			process++;
			break;
		case 4:
			_vaccines.DisplayVaccineReport();
			process++;
			break;
		case 5:
			_medicals.PrintMedicalReport();
			process++;
			break;
		case 6:
			_vaccines.PrintVaccineReport();
			process++;
			break;
		case 7:
			return;
		default:
			std::cout << "Invalid option selected" << std::endl;
			break;
		}
	}
};

class UI : public Menu {
private:
	Child _child = Child();
	Doctor _doctor = Doctor();
	Nurse _nurse = Nurse();
public:
	bool appStatus = true;

	void onOptionSelected(int option) override {
		switch (option) {
		case 0:
			_child.UserInterface();
			break;
		case 1:
			_doctor.UserInterface();
			break;
		case 2:
			_nurse.UserInterface();
			break;
		case 3:
			appStatus = false;
		default:
			std::cout << "Program Stopped" << std::endl;
			break;
		}
	}

	void run() {
		setOptions({ "->   Child/Parent",
			"->   Doctor",
			"->   Nurse",
			"->   Exit"
			});

		ProgressBar(1000, 10, 10);
		UI_Utilities::clearScreen();

		displayMenu(0, 4);
	}
};

int main() {
	UI ui = UI();
	ui.run();

	return 0;
}