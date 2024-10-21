#include "Utilities.h"

str Utilities::DataMasking::fullMask(const str& text) {
    return str(text.length(), '*');
}

str Utilities::DataMasking::fixedPositionMask(const str& text, const size_t start, const size_t end) {
    if (start >= text.length() || end > text.length() || start >= end) {
        return text;
    }

    str result = text;
    for (size_t i = start; i < end; ++i) {
        result[i] = '*';
    }
    return result;
}

str Utilities::DataMasking::fixedCharacterMask(const str& text, const str& target) {
    str result = text;
    size_t pos = result.find(target);

    if (pos != str::npos) {
        str encrypted_target(target.length(), '*');
        result.replace(pos, target.length(), encrypted_target);
    }

    return result;
}

str Utilities::passwordGenerator(const str name) {
    str random_suffix = std::to_string(rand() % 1000);
    return name + "@" + random_suffix;
}

str Utilities::IDGenerator(const str firstname, const str lastname, const str dob, int num) {
    str id = (firstname.length() >= 2 ? firstname.substr(0, 2) : firstname) + "-" +
        (lastname.length() >= 2 ? lastname.substr(0, 2) : lastname) + "-" +
        dob + "-" + std::to_string(num);

    return id;
}

bool Utilities::Database::addUser(const string_vector& data) {
    if (data.empty()) {
        return false;
    }

    std::ofstream file("Users.csv", std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i] << (i < data.size() - 1 ? "," : "");
    }
    file << '\n';

    return true;
}

bool Utilities::Database::addVaccineReport(const string_vector& data) {
    if (data.empty()) {
        return false;
    }

    std::ofstream file("Vaccinations.csv", std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i] << (i < data.size() - 1 ? "," : "");
    }
    file << '\n';

    return true;
}

bool Utilities::Database::addMedicalReport(const string_vector& data) {
    if (data.empty()) {
        return false;
    }

    std::ofstream file("MedicalReport.csv", std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i] << (i < data.size() - 1 ? "," : "");
    }
    file << '\n';

    return true;
}

str Utilities::Database::loginUser(const str username, const str password) {
    std::ifstream file("Users.csv");
    if (!file.is_open()) {
        return "fail";
    }

    string_vector fileContent;
    str line, ID;
    bool userFound = false;

    while (std::getline(file, line)) {
        if (line.find(username) != str::npos && line.find(password) != str::npos) {
            ID = line.substr(0, line.find(username) - 2);
            userFound = true;
        }
        else {
            fileContent.push_back(line);
        }
    }

    file.close();

    if (!userFound) {
        return "fail";
    }

    std::ofstream outFile("Users.csv");
    if (!outFile.is_open()) {
        return "fail";
    }

    for (const auto& record : fileContent) {
        outFile << record << '\n';
    }

    outFile.close();
    return ID;
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
    str line;

    if (!file.is_open()) {
        return 0;
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
    str line;

    if (!file.is_open()) {
        return false;
    }

    while (std::getline(file, line)) {
        std::size_t pos = line.find(',');
        if (pos != str::npos) {
            str currentId = line.substr(0, pos);
            if (currentId == id) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

bool Utilities::Database::checkIfMedicalsExists(const str id) {
    std::ifstream file("Medicals.csv");
    str line;

    if (!file.is_open()) {
        return false;
    }

    while (std::getline(file, line)) {
        std::size_t pos = line.find(',');
        if (pos != str::npos) {
            str currentId = line.substr(0, pos);
            if (currentId == id) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

bool Utilities::Database::checkIfVaccineExists(const str id) {
    std::ifstream file("Vaccinations.csv");
    str line;

    if (!file.is_open()) {
        return false;
    }

    while (std::getline(file, line)) {
        std::size_t pos = line.find(',');
        if (pos != str::npos) {
            str currentId = line.substr(0, pos);
            if (currentId == id) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

bool Utilities::Database::deleteVaccineReport(const str id) {
    std::ifstream file("Vaccinations.csv");
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

    std::ofstream outFile("Vaccinations.csv");
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& record : fileContent) {
        outFile << record << '\n';
    }

    outFile.close();
    return true;
}

bool Utilities::Database::deleteMedicalReport(const str id) {
    std::ifstream file("Medicals.csv");
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

    std::ofstream outFile("Medicals.csv");
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& record : fileContent) {
        outFile << record << '\n';
    }

    outFile.close();
    return true;
}

std::vector<std::pair<str, str>> Utilities::Database::getUsers() {
    std::ifstream file("Users.csv");
    std::vector<std::pair<std::string, std::string>> userRecords;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file for reading." << std::endl;
        return userRecords;
    }

    str line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        str id, name;

        if (std::getline(ss, id, ',') && std::getline(ss, name, ',')) {
            if (id != "null") userRecords.emplace_back(id, name);
        }
    }

    file.close();
    return userRecords;
}

string_vector Utilities::Database::getVaccineReports(const str Id) {
    std::ifstream file("Medicals.csv");
    string_vector fileContent;
    if (!file.is_open()) {
        return fileContent;
    }

    str line;

    while (std::getline(file, line)) {
        if (line.find(Id) != str::npos) {
            fileContent.push_back(line);
        }
    }

    file.close();
    return fileContent;
}

string_vector Utilities::Database::getMedicalReports(const str Id) {
    std::ifstream file("Vaccinations.csv");
    string_vector fileContent;
    if (!file.is_open()) {
        return fileContent;
    }

    str line;

    while (std::getline(file, line)) {
        if (line.find(Id) != str::npos) {
            fileContent.push_back(line);
        }
    }

    file.close();
    return fileContent;
}

void Utilities::printVaccineReport(const str Id) {
    string_vector VaccineReports = Utilities::Database::getVaccineReports(Id);
    string_vector UserInfomation = Utilities::Database::getUserInfo(Id);
    str id, treatment, vaccine, childId, weight, height, nurse, clinic, clinicDate, nextClinicDate;

    str filename = Id + ".txt";
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);

    // Check if the file opened successfully
    if (!file) {
        std::cerr << "Error: Could not open or create the Report!" << std::endl;
        return;
    }// Write the formatted report to the file
    file << "-------------------------------------------------------------------------------------------------------------" << std::endl;
    file << "|" << std::setw(10) << " " << "Child's Vaccine Report" << std::endl;
    file << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

    file << std::setw(11) << " " << "Child Fullname:    " << UserInfomation[0] << " " << UserInfomation[2] << " " << UserInfomation[3] << std::endl;
    file << std::setw(11) << " " << "Guardian/Parents Name(s):      " << UserInfomation[UserInfomation.size()] << std::endl;
    file << std::setw(11) << " " << "Date Of Birth:     " << UserInfomation[4] << std::endl;
    file << std::setw(11) << " " << "Medical Consultations: " << std::endl;

    for (int i = 0; i < VaccineReports.size(); ++i) {
        std::stringstream ss(VaccineReports[i]);

        if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, vaccine, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, nurse, ',') && std::getline(ss, clinic, ',') && std::getline(ss, clinicDate, ',')) {
            file << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << treatment << "| Medication: " << vaccine << "| Weight: " << weight << "kg | Height: " << height << "cm | Doctor: " << nurse << " | Clinic: " << clinic << " | Date: " << clinicDate << std::endl;
        }
    }
    file << std::setw(11) << " " << "Date for next Checkup:  " << nextClinicDate << std::endl;
    // Close the file
    file.close();
    std::cout << "Report written to" << filename << " successfully!" << std::endl;

    return;
}

void Utilities::printMedicalReport(const str Id) {
    string_vector MedicalReports = Utilities::Database::getMedicalReports(Id);
    string_vector UserInfomation = Utilities::Database::getUserInfo(Id);
    str id, treatment, medication, childId, weight, height, doctor, clinic, consulationdate, checkupdate;

    str filename = Id + ".txt";
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);

    // Check if the file opened successfully
    if (!file) {
        std::cerr << "Error: Could not open or create the Report!" << std::endl;
        return;
    }// Write the formatted report to the file
    file << "-------------------------------------------------------------------------------------------------------------" << std::endl;
    file << "|" << std::setw(10) << " " << "Child's Medical Report" << std::endl;
    file << "|" << "------------------------------------------------------------------------------------------------------------" << std::endl;

    file << std::setw(11) << " " << "Child Fullname:    " << UserInfomation[0] << " " << UserInfomation[2] << " " << UserInfomation[3] << std::endl;
    file << std::setw(11) << " " << "Guardian/Parents Name(s):      " << UserInfomation[UserInfomation.size()] << std::endl;
    file << std::setw(11) << " " << "Date Of Birth:     " << UserInfomation[4] << std::endl;
    file << std::setw(11) << " " << "Medical Consultations: " << std::endl;

    for (int i = 0; i < MedicalReports.size(); ++i) {
        std::stringstream ss(MedicalReports[i]);

        if (std::getline(ss, id, ',') && std::getline(ss, treatment, ',') && std::getline(ss, medication, ',') && std::getline(ss, childId, ',') && std::getline(ss, weight, ',') && std::getline(ss, height, ',') && std::getline(ss, doctor, ',') && std::getline(ss, clinic, ',') && std::getline(ss, consulationdate, ',')) {
            file << std::setw(12) << " " << "-> Consultation " << i + 1 << ": " << treatment << "| Medication: " << medication << "| Weight: " << weight << "kg | Height: " << height << "cm | Doctor: " << doctor << " | Clinic: " << clinic << " | Date: " << consulationdate << std::endl;
        }
    }
    file << std::setw(11) << " " << "Date for next Checkup:  " << consulationdate << std::endl;
    // Close the file
    file.close();
    std::cout << "Report written to" << filename << " successfully!" << std::endl;

    return;
}

string_vector Utilities::Database::getUserInfo(const str id) {
    std::ifstream file("Users.csv");
    string_vector userRecord;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file for reading." << std::endl;
        return userRecord;
    }

    str line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        str Id, firstname, title, middlename, surname, dob, mother;

        if (std::getline(ss, Id, ',') && std::getline(ss, firstname, ',') && std::getline(ss, title, ',') && std::getline(ss, middlename, ',') && std::getline(ss, surname, ',') && std::getline(ss, dob, ',') && std::getline(ss, mother, ',')) {
            if (Id.find(id) != str::npos) {
                userRecord.push_back(firstname);
                userRecord.push_back(title);
                userRecord.push_back(middlename);
                userRecord.push_back(surname);
                userRecord.push_back(dob);
                userRecord.push_back(mother);
            }
        }
    }

    file.close();
    return userRecord;
}
