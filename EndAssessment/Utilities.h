#pragma once

#include <vector>
#include <string>
#include <fstream>

using string_vector = std::vector<std::string>;
using str = std::string;

class Utilities {
public:
	class Data_Masking {
	public:
		static str Full_Mask(const str& text);
		static str Fixed_Position_Mask(const str& text, const size_t& start, const size_t& end);
		static str Fixed_Character_Mask(const str& text, const str& target);
	};

	static str PasswordGenerator(const str name);
	static str IDGenerator(const str firstname, const str lastname, const str dob, int num);

	class Database {
	public:
		static bool addUser(const str data[]);
		static bool addVaccineReport(const str data[]);
		static bool addMedicalReport(const str data[]);
		static bool deleteUser(const str id);
		static bool getUsers();
		static int countUsers();
		static bool checkIfExists(const str id);
	};
};