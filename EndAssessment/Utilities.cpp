#include "Utilities.h"

//utilities

str Utilities::Data_Masking::Full_Mask(const str& text) {
	str result = text;

	for (size_t i = 0; i < text.length(); ++i) {
		result[i] = '*';
	}
	return result;
}

str Utilities::Data_Masking::Fixed_Position_Mask(const str& text, const size_t& start, const size_t& end) {
	str result = text;
	for (size_t i = start; i < end; ++i) {
		result[i] = '*';
	}
	return result;
}

str Utilities::Data_Masking::Fixed_Character_Mask(const str& text, const str& target) {
	str result = text;
	size_t pos = result.find(target);
	str encrypted_target;

	for (size_t i = 0; i < target.length(); i++) {
		encrypted_target = '*';
	}
	result.replace(pos, target.length(), encrypted_target);
	return result;
}

str Utilities::PasswordGenerator(const str name) {
	return name + "@123";
}

str Utilities::IDGenerator(const str firsname, const str lastname, const str dob, int num) {
	return firsname.substr(0, 2) + "-" + lastname.substr(0, 2) + "-" + dob + "-" + std::to_string(num);
}

bool Utilities::Database::addUser(const str data[]) {
	std::ofstream file("Users.csv", std::ios::app);

	if (!file) {
		return false;
	}
	for (size_t i = 0; i < data->size(); ++i) {
		file << data[i] << (i < data->size() - 1 ? "," : "");
	}
	file << '\n';

	return true;
}

bool Utilities::Database::addVaccineReport(const str data[]) {
	std::ofstream file("Vaccinations.csv", std::ios::app);

	if (!file) {
		return false;
	}
	for (size_t i = 0; i < data->size(); ++i) {
		file << data[i] << (i < data->size() - 1 ? "," : "");
	}
	file << '\n';

	return true;
}

bool Utilities::Database::addMedicalReport(const str data[]) {
	std::ofstream file("MedicalReport.csv", std::ios::app);

	if (!file) {
		return false;
	}
	for (size_t i = 0; i < data->size(); ++i) {
		file << data[i] << (i < data->size() - 1 ? "," : "");
	}
	file << '\n';

	return true;
}

bool Utilities::Database::deleteUser(const str id) {
	std::ifstream file("Users.csv");
	if (!file.is_open()) {
		return false;
	}

	string_vector fileContent;
	str line;
	bool recordDeleted = false;

	while (std::getline(file, line)) {
		if (line.find(id) == str::npos) {
			fileContent.push_back(line);
		}
		else {
			recordDeleted = true;
		}
	}

	file.close();

	if (!recordDeleted) {
		return false;
	}

	// Write the remaining records back to the CSV file
	std::ofstream outFile("Users.csv");
	if (!outFile.is_open()) {
		return false;
	}

	for (const auto& record : fileContent) {
		outFile << record << '\n';
	}

	outFile.close();
	return true;
}
int Utilities::Database::countUsers() {
	std::ifstream file("Users.csv");
	int userCount = 0;
	std::string line;

	if (!file.is_open()) {
		return -1;
	}

	while (std::getline(file, line)) {
		if (!line.empty()) {
			++userCount;
		}
	}

	file.close();
	return userCount;
}

bool Utilities::Database::checkIfExists(const str id) {
	std::ifstream file("Users.csv");
	std::string line;

	if (!file.is_open()) {
		return false;
	}

	while (std::getline(file, line)) {
		std::size_t pos = line.find(',');
		if (pos != std::string::npos) {
			std::string currentId = line.substr(0, pos);
			if (currentId == id) {
				file.close();
				return true;
			}
		}
	}

	file.close();
	return false; // User not found
}