#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <numeric>
//��������� �������: 
/*

��� ������� ������ �������� ��� �������. ����� ������ �������� ��� ����������� ������� ���� � ����� ������� � ������������� � ��������� � ������� ������ � ������,������� ���� ������� ��� �����������.

������ ������ ��� ������������,��� ������� � ������� ��� ID ������������,� �������� - ���������� �������,����������� �������������.

������ ������ ��� ������ ������� ��� ������� � ������� ��� ����� ��������,� �������� ��� ���������� ������������� ���������� �� ������ ��������.

�� ���������� �������� ��� ������� �� ������������ �������� ������,��� �� ������ ���������� � ������������� ������������ ����� ������. 

pages_read[0] - ��� ��� ������� �������� �� ������,���������� ��� ���������� ����� ���������� ������� ����� ������������� � ������ ������ ������ �����.

*/
class Persons {
public:
	Persons(): persons_(std::vector<uint16_t>(100001, 0)), pages_read_(std::vector<uint32_t>(1001, 0)){ //�������������� ������� ������� ����� �������� �������������� �����������
		
	}

	void AddPerson(uint32_t id,  uint16_t pages_read) {
		
		if (persons_[id] != 0) {
			pages_read_[persons_[id]]--; 
			pages_read_[0]--;
		}
		pages_read_[0]++;
		persons_[id] = pages_read;
		pages_read_[pages_read]++;
	}

	double Cheer(int id) {

		if (persons_[id] == 0) {
			return 0.0;
		}
		if (pages_read_[0] == 1) return 1;

		uint32_t counter = std::accumulate(pages_read_.begin() + 1, pages_read_.begin() + persons_[id], 0);

		return static_cast<double>(counter * (1 / static_cast<double>((pages_read_[0] - 1)))); //�� ���� ,��� ��� ����������� ���������� static_cast'�� �� ��� ����� �������� ��� ��������� ����������� ���������� assert'��
	}
	

	std::vector<uint16_t> persons_;// ������ ������� � ���������� ����������� ������� � ������� � ���������� id.
	std::vector<uint32_t> pages_read_;// ������ ������� � ���������� id ���������� �� ���� �������� ������� � ���������� �������.
};

static void HandleStream(std::istream& i_stream = std::cin, std::ostream& o_stream = std::cout) {
	Persons persons;

	uint32_t count;
	i_stream >> count;
	for (uint32_t i = 0; i < count; i++) {
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

