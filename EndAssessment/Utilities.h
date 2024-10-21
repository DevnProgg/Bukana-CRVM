#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Type aliases for clarity
using string_vector = std::vector<std::string>;
using str = std::string;

class Utilities {
public:
	class DataMasking {
	public:
		static str fullMask(const str& text);
		static str fixedPositionMask(const str& text, size_t start, size_t end);
		static str fixedCharacterMask(const str& text, const str& target);
	};

	static str passwordGenerator(const str name);
	static str IDGenerator(const str firstName, const str lastName, const str dob, int num);

	class Database {
	public:
		static bool addUser(const  string_vector& data);
		static bool addVaccineReport(const string_vector& data);
		static bool addMedicalReport(const string_vector& data);
		static str loginUser(const str username, const str password);
		static bool deleteUser(const str id);

		static bool checkIfExists(const str id);
		static bool checkIfVaccineExists(const str id);
		static bool checkIfMedicalsExists(const str id);
		static bool deleteVaccineReport(const str id);
		static bool deleteMedicalReport(const str id);
		static std::vector<std::pair<str, str>> getUsers();
		static string_vector getVaccineReports(const str id);
		static string_vector getMedicalReports(const str id);
		static int countUsers();



		static string_vector getUserInfo(const str id);
	};

	static void printMedicalReport(const str id);
	static void printVaccineReport(const str id);
};