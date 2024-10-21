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
		"->  Back"
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
	str getID() { return id; }
	str getUser() { return UserType;  }

	void onOptionSelected(int option) override {

		str ID;

		switch (option) {

		case 0:

			ID = _login.Login();
			setId(ID);
			process++;
			break;

		case 1:

			_registrations.registerChildUI();
			process = 0;
			break;

		case 2:

			process = 0;
			break;

		case 3:

			_medicals.displayMedicalReport(getID());
			break;

		case 4:

			_vaccines.displayVaccineReport(getID());
			break;

		case 5:

			_medicals.printMedicalReport(getID(), getUser());
			break;

		case 6:

			_vaccines.printVaccineReport(getUser(), "child");
			break;

		case 7:

			process = 0;
			break;

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
		"->  Update Medical Report",
		"->  Delete Medical Report",
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
	string_vector children;
	str ID;

public:
	//constructor
	Doctor() {

		UserType = "doctor";
	}

	//class ui
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
	//set methood
	void setChildren() {

		std::vector<std::pair<str, str>> getChildrenNames = Utilities::Database::getUsers();

		for (const auto& pair : getChildrenNames) {

			this -> children.push_back(pair.second);
		}
		return;
	}

	//set method
	void setID(str iD) { this->ID = iD; }

	//get method
	str getID() { return this->ID; }

	string_vector getChildren() { return this->children;  }

	void onOptionSelected(int option) override {

		str response;

		switch (option) {

		case 0:

			_login.Login();
			process++;
			break;

		case 1:

			_registrations.registerDoctorUI();
			process = 0;
			break;

		case 2:

			_medicals.addMedicalReport();
			break;

		case 3:

			setChildren();
			_medicals.displayChildren(getChildren(), "display");
			break;

		case 4:

			_medicals.clearScreen();
			std::cout << std::setw(15) << " " << "Enter User id : " << std::endl;
			std::getline(std::cin, response);
			setID(response);
			_medicals.updateMedicalReport(getID());
			break;

		case 5:

			_medicals.clearScreen();
			std::cout << std::setw(15) << " " << "Enter User id : " << std::endl;
			std::getline(std::cin, response);
			setID(response);
			_medicals.deleteMedicalReport(getID());
			break;

		case 6:

			setChildren();
			_vaccines.displayChildren(getChildren(), "display");
			break;

		case 7:

			setChildren();
			_medicals.displayChildren(getChildren(), "print");
			break;

		case 8:

			setChildren();
			_vaccines.displayChildren(getChildren(), "print");
			break;

		case 9:

			process = 0;

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
		"->  Display Vaccine Report",
		"->  Update Vaccine Report",
		"->  Delete Vaccine Report",
		"->  Display Medical Report",
		"->  Print Medical Report",
		"->  Print Vaccine Report",
		"->  Exit"
	};

	Login_UI _login;
	Registrations_UI _registrations;
	Medical_UI _medicals;
	Vaccine_UI _vaccines;

	int process = 0;
	string_vector children;
	str ID;
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

	//set methood
	void setChildren() {

		std::vector<std::pair<str, str>> getChildrenNames = Utilities::Database::getUsers();

		for (const auto& pair : getChildrenNames) {

			this->children.push_back(pair.second);
		}
		return;
	}

	//set method
	void setID(str iD) { this->ID = iD; }

	//get method
	str getID() { return this->ID; }

	string_vector getChildren() { return this->children; }

	void onOptionSelected(int option) override {
		str response;

		switch (option) {

		case 0:

			_login.Login();
			process++;
			break;

		case 1:

			_registrations.registerNurseUI();
			process = 0;
			break;

		case 2:

			_vaccines.addVaccineReport();
			break;

		case 3:

			setChildren();
			_vaccines.displayChildren(getChildren(), "display");
			break;

		case 4:

			_vaccines.clearScreen();
			std::cout << std::setw(15) << " " << "Enter User id : " << std::endl;
			std::getline(std::cin, response);
			setID(response);
			_vaccines.updateVaccineReport(getID());
			break;

		case 5:

			_vaccines.clearScreen();
			std::cout << std::setw(15) << " " << "Enter User id : " << std::endl;
			std::getline(std::cin, response);
			setID(response);
			_vaccines.deleteVaccineReport(getID());
			break;

		case 6:

			setChildren();
			_medicals.displayChildren(getChildren(), "display");
			break;

		case 7:

			setChildren();
			_medicals.displayChildren(getChildren(), "print");
			break;

		case 8:

			setChildren();
			_vaccines.displayChildren(getChildren(), "print");
			break;

		case 9:

			process = 0;

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

		progressBar(1000, 10, 10);
		UI_Utilities::clearScreen();

		displayMenu(0, 4);
	}
};

int main() {
	UI ui = UI();
	ui.run();

	return 0;
}