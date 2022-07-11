#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <C:\Users\vanba\source\repos\cryptopp860\cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <C:\Users\vanba\source\repos\cryptopp860\md5.h>
#include <C:\Users\vanba\source\repos\cryptopp860\hex.h>
#include <C:\Users\vanba\source\repos\cryptopp860\filters.h>
#include <C:\Users\vanba\source\repos\cryptopp860\files.h>
#include <C:\Users\vanba\source\repos\cryptopp860\sha.h>
#include <C:\Users\vanba\source\repos\cryptopp860\sha3.h>
#include <C:\Users\vanba\source\repos\cryptopp860\crc.h>
#include <chrono>
#include <C:\Users\vanba\source\repos\control_sum\control_sum\ini.h>
#include <windows.h>

std::string md5(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	Weak::MD5 hash;
	byte digest[Weak::MD5::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string sha1(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	SHA1 hash;
	byte digest[SHA1::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string sha256(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	SHA256 hash;
	byte digest[SHA256::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string sha224(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	SHA224 hash;
	byte digest[SHA224::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string sha384(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	SHA384 hash;
	byte digest[SHA384::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string sha512(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	SHA256 hash;
	byte digest[SHA512::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string crc32(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	CRC32 hash;
	byte digest[CRC32::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

std::string crc32c(const std::string& data) {
	using namespace CryptoPP;

	std::string res;
	CRC32C hash;
	byte digest[CRC32C::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)data.c_str(), data.size());

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(res));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return res;
}

void check(std::string path) {
	std::filesystem::path p(path);
	if (!std::filesystem::exists(p)) {
		std::string file_name1;
		getline(std::cin, file_name1);
		if (file_name1 != "") {
			std::ifstream file_check;
			file_check.open(file_name1);
			if (!file_check.is_open()) throw "Can't open this file";
			else {

				std::string msg;
				std::string a;

				while (getline(file_check, a)) msg.insert(msg.size(), a);
				file_check.close();

				std::cout << md5(msg);
			}
		}
		else std::cout << "usage" << std::endl;
	}
	else {
		std::ifstream file;
		file.open(p);
		if (!file.is_open()) { throw "Can't open!"; }
		else {
			std::string str;
			while (getline(file, str)) {
				for (int i = 0; i < str.size();) {
					if (str[i] == ' ') {
						str.erase(i, 1);
					}
					else i++;
				}

				std::string file_name;
				std::string::iterator it = str.begin();
				for (int i = 0; i < str.size(); i++) {
					if (str[i] != '=') {
						file_name.push_back(str[i]);
						it++;
					}
					else break;
				}
				it++;

				std::string sum;
				for (; it != str.end(); it++) {
					sum.push_back(*it);
				}

				std::ifstream file_check;
				file_check.open(file_name);

				std::string msg;
				std::string a;

				while (getline(file_check, a)) msg.insert(msg.size(), a);
				file_check.close();

				std::string digest = md5(msg);

				if (sum == digest) std::cout << "It's ok" << std::endl;
				else std::cout << "Wrong control sum" << std::endl;
			}
		}
		file.close();
	}

}

void perms(std::filesystem::perms p) {
	std::cout << "owner_read " << ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-") << std::endl;
	std::cout << "owner_write " << ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-") << std::endl;
	std::cout << "owner_exec " << ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-") << std::endl;
	std::cout << "group_read " << ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-") << std::endl;
	std::cout << "group_write " << ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-") << std::endl;
	std::cout << "group_exec " << ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-") << std::endl;
	std::cout << "others_read " << ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-") << std::endl;
	std::cout << "others_write " << ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-") << std::endl;
	std::cout<< "others_exec " << ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-") << std::endl;
}

void info(std::filesystem::path p) {
	if (!std::filesystem::exists(p)) throw "No such file exists";
	else {
		time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << p.filename() << std::endl;
		std::cout << std::filesystem::file_size(p) << std::endl;
		std::cout << (time / 3600) % 24 + 3 << ':' << (time / 60) % 60 << ':' << time % 60 << std::endl;
		perms(std::filesystem::status(p).permissions());
		//file_owner(p);

		std::ifstream file_check;
		file_check.open(p);

		std::string msg;
		std::string a;

		while (getline(file_check, a)) msg.insert(msg.size(), a);
		file_check.close();

		std::cout << "CRC32: " << crc32(msg) << std::endl;
		std::cout << "MD5: " << md5(msg) << std::endl;
		std::cout << "SHA1: " << sha1(msg) << std::endl;
	}
}

//void file_owner(std::filesystem::path p) {
//	DWORD dwRtnCode = 0;
//	PSID pSidOwner = NULL;
//	BOOL bRtnBool = TRUE;
//	LPTSTR AcctName = NULL;
//	LPTSTR DomainName = NULL;
//	DWORD dwAcctName = 1, dwDomainName = 1;
//	SID_NAME_USE eUse = SidTypeUnknown;
//	HANDLE hFile;
//	PSECURITY_DESCRIPTOR pSD = NULL;
//
//	hFile = CreateFile(
//		TEXT(path),
//		GENERIC_READ,
//		FILE_SHARE_READ,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//}

void options(char* argv, std::string& opt, std::string& hash_func) {
	std::string str;
	int i = 0;
	while (argv[i] != 0) {
		str.push_back(argv[i]);
		i++;
	}
	if (str == "-md5" || str == "-sha1" || str == "-sha256" || str == "-sha224" || str == "-sha384" || str == "-sha512" || str == "-crc32" || str == "-crrc32c") {
		hash_func = str;
	}
	else opt = str;
	
}

void  print(std::string file_name, std::string hash, bool flag = 0, std::string file_out = "") {
	if (flag == 1) {
		std::fstream file_output;
		file_output.open(file_out);
		if (!file_output.is_open()) throw "Can't open this file";
		else {
			file_output << file_name << " = " << hash << std::endl;
		}
	}
	else {
		std::cout << file_name << " = " << hash << std::endl;
	}
}

std::string sum_file(std::string file_name, std::string hash_func) {
	std::fstream file;
	file.open(file_name);
	std::string hash;
	if (!file.is_open()) throw "Can't open this file";
	else {
		std::string msg;
		std::string a;
		while (getline(file, a)) msg.insert(msg.size(), a);
		if (hash_func == "-md5") {
			hash = md5(msg);
		}
		else if (hash_func == "-sha1") {
			hash = sha1(msg);
		}
		else if (hash_func == "-sha256") {
			hash = sha256(msg);
		}
		else if (hash_func == "-sha224") {
			hash = sha224(msg);
		}
		else if (hash_func == "-sha384") {
			hash = sha384(msg);
		}
		else if (hash_func == "-sha512") {
			hash = sha512(msg);
		}
		else if (hash_func == "-crc32") {
			hash = crc32(msg);
		}
		else if (hash_func == "-crc32c") {
			hash = crc32c(msg);
		}
	}
	file.close();

	return hash;
}

int main(int argc, char** argv) {
	try {
		std::ifstream file;
		/*file.open("C:\\Users\\vanba\\source\\repos\\control_sum\\control_sum\\проверОчка.txt");
		std::string str;
		getline(file, str);
		file.close();
		std::cout << md5(str) << std::endl;*/
		if (argc == 1) {
			check("C:\\Users\\vanba\\source\\repos\\control_sum\\control_sum\\cksum.ini");
		}
		else {
			std::string hash_func = "-md5";
			std::string option;
			std::string file_out;
			std::string file_in;
			bool flag = 0;
			for (int i = 1; i < argc; i++) {
				if (argv[i][0] == '-') {
					options(argv[i], option, hash_func);
					if (option == "-c" && i !=argc - 1) {
						int j = 0;
						std::string file_name;
						while (argv[i + 1][j] != 0) {
							file_name.push_back(argv[i + 1][j]);
							j++;
						}
						std::filesystem::path p(file_name);
						if (std::filesystem::exists(p)) check(file_name);
						else throw "File doesn't exist";
						i++;
					}
					else if (option == "-o" && i != argc - 1) {
						int j = 0;
						file_out.clear();
						while (argv[i + 1][j] != 0) {
							file_out.push_back(argv[i + 1][j]);
							j++;
						}
						std::filesystem::path p(file_out);
						if (std::filesystem::exists(p)) flag = 1;
						i++;
					}
					else if (option == "-i" && i != argc - 1) {
						int j = 0;
						file_in.clear();
						while (argv[i + 1][j] != 0) {
							file_in.push_back(argv[i + 1][j]);
							j++;
						}
						std::fstream file_input;
						file_input.open(file_in);
						if (!file_input.is_open()) throw "Can't open this file";
						else {
							std::string file_name;
							while (getline(file_input, file_name)) {
								std::string hash = sum_file(file_name, hash_func);
								print(file_name, hash, flag, file_out);
							}
						}
						file_input.close();
						i++;
					}
					else if (option == "-about" && i != argc - 1) {
						int j = 0;
						std::string file_info;
						while (argv[i + 1][j] != 0) {
							file_info.push_back(argv[i + 1][j]);
							j++;
						}
						std::filesystem::path p(file_info);
						info(p);
						i++;
					}
					else if (option == "-help") {
						std::cout << "'-c' + file ---> checking control sum" << std::endl;
						std::cout << "'-o' + file ---> output in file" << std::endl;
						std::cout << "'-i' + file ---> input from file and count control sum" << std::endl;
						std::cout << "'-info' + file ---> information about file";
						std::cout << "'-md5' ---> md5" << std::endl;
						std::cout << "'-sha1' ---> sha1" << std::endl;
						std::cout << "'-sha256' ---> sha256" << std::endl;
						std::cout << "'-sha224' ---> sha224" << std::endl;
						std::cout << "'-sha384' ---> sh384" << std::endl;
						std::cout << "'-sha512' ---> sha512" << std::endl;
						std::cout << "'-crc32' ---> crc32" << std::endl;
						std::cout << "'-crc32c' ---> crc32c" << std::endl;
					}
				}
				else {
					std::string file_name;
					int j = 0;
					while (argv[i][j] != 0) {
						file_name.push_back(argv[i][j]);
						j++;
					}
					std::string hash = sum_file(file_name, hash_func);
					print(file_name, hash, flag, file_out);
				}
			}
		}
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	return 0;
}