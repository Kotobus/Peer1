#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <numeric>
class Persons {
public:
	Persons() {
		persons_ = std::vector<uint32_t>(100001, 0);
		pages_read_ = std::vector<uint32_t>(1001, 0);
	}

	void AddPerson(uint32_t id, uint16_t pages_read) {

		if (persons_[id] != 0) {
			pages_read_[persons_[id]]--;
			pages_read_[0]--;
		}
		pages_read_[0]++;
		persons_[id] = pages_read;
		pages_read_[pages_read]++;
	}

	double Cheer(uint32_t id) {

		if (persons_[id] == 0) {
			return 0.0;
		}
		if (pages_read_[0] == 1) return 1;

		uint64_t counter = std::accumulate(pages_read_.begin() + 1, pages_read_.begin() + persons_[id], 0);
		return static_cast<double>(counter * (1 / static_cast<double>((pages_read_[0] - 1))));
	}
	~Persons() = default;

	std::vector<uint32_t> persons_;// [100001] ;
	std::vector<uint32_t> pages_read_;// [1001] ;
};

static void HandleStream(std::istream& i_stream = std::cin, std::ostream& o_stream = std::cout) {
	Persons persons;

	int count;
	i_stream >> count;
	for (int i = 0; i < count; i++) {
		std::string query;
		i_stream >> query;
		uint32_t id;
		i_stream >> id;
		if (query == "READ") {
			uint16_t pages;
			i_stream >> pages;
			persons.AddPerson(id, pages);
		}
		else {
			o_stream << std::setprecision(6) << persons.Cheer(id) << "\n";
		}
	}
}
int main() {
	HandleStream(std::cin, std::cout);
}