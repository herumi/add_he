/*
	homo add crypto sample
	cl sum_crypto.cpp -I../mcl/include -DMCL_NO_AUTOLINK ../mcl/src/fp.cpp
*/
#include <iostream>
#include <fstream>
#include <cybozu/random_generator.hpp>
#include <cybozu/option.hpp>
#include <cybozu/itoa.hpp>
#include <mcl/she.hpp>

using namespace mcl::she;
using namespace mcl::bn_current;

typedef std::vector<int> IntVec;

const std::string secFile = "sum_sec.txt";
const std::string pubFile = "sum_pub.txt";

std::string GetSheetName(size_t n)
{
	return std::string("sum_") + cybozu::itoa(n) + ".txt";
}

struct Param {
	std::string mode;
	IntVec iv;
	Param(int argc, const char *const argv[])
	{
		cybozu::Option opt;
		opt.appendVec(&iv, "l", ": list of int(eg. 1 5 3 2)");
		opt.appendHelp("h", ": put this message");
		opt.appendParam(&mode, "mode", ": init/enc/sum/dec");
		if (!opt.parse(argc, argv)) {
			opt.usage();
			exit(1);
		}
	}
};

void SysInit()
{
	SHE::init();
	SHE::setRangeForDLP(1024);
}

template<class T>
void Load(T& t, const std::string& name)
{
	std::ifstream ifs(name.c_str(), std::ios::binary);
	if (!ifs) {
		throw cybozu::Exception("Load:can't read") << name;
	}
	ifs >> t;
}

template<class T>
void Save(const std::string& name, const T& t)
{
	std::ofstream ofs(name.c_str(), std::ios::binary);
	ofs << t;
}

void Init()
{
	puts("init");

	SecretKey sec;
	sec.setByCSPRNG();
	PublicKey pub;
	sec.getPublicKey(pub);
	printf("make privateKey=%s, publicKey=%s\n", secFile.c_str(), pubFile.c_str());
	Save(secFile, sec);
	Save(pubFile, pub);
}

void Enc(const IntVec& iv)
{
	PublicKey pub;
	Load(pub, pubFile);
	for (size_t i = 0; i < iv.size(); i++) {
		CipherTextG1 c;
		pub.enc(c, iv[i]);
		std::cout << '"' << c << '"';
		if (i < iv.size() - 1) {
			std::cout << ',';
		}
	}
}

void Sum()
{
	PublicKey pub;
	Load(pub, pubFile);
	CipherTextG1 result;
	pub.enc(result, 0);
	std::string line;
	while (std::getline(std::cin, line, ',')) {
		if (!line.empty() && line[line.size() - 1] == '\n') {
			line.resize(line.size() - 1);
		}
		const char *begin = line.c_str();
		const char *end = begin + line.size();
		if (begin != end) {
			if (*begin == '"') begin++;
			if (begin != end) {
				if (end[-1] == '"') end--;
				if (begin != end) {
					CipherTextG1 c;
					std::string s(begin, end);
					std::istringstream is(s);
					is >> c;
					result.add(c);
				}
			}
		}
	}
	std::cout << result;
}

void Dec()
{
	SecretKey sec;
	Load(sec, secFile);
	CipherTextG1 c;
	std::cin >> c;
	int sum = sec.dec(c);
	std::cout << sum;
}

int main(int argc, char *argv[])
	try
{
	const Param p(argc, argv);
	SysInit();
	if (p.mode == "init") {
		Init();
	} else
	if (p.mode == "enc") {
		Enc(p.iv);
	} else
	if (p.mode == "sum") {
		Sum();
	} else
	if (p.mode == "dec") {
		Dec();
	} else
	{
		printf("bad mode=%s\n", p.mode.c_str());
		return 1;
	}
} catch (std::exception& e) {
	printf("ERR %s\n", e.what());
}
