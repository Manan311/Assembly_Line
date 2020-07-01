#include <iomanip>
#include <iostream>
#include "Utilities.h"
#include "CustomerOrder.h"
using namespace std;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(){
	m_name = "";
	m_product = "";
	m_cntItem = 0u;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const string& record) : CustomerOrder(){
	Utilities local;
	size_t next_pos = 0u;
	size_t start = 0u;
	bool check = true;

	m_name = local.extractToken(record, next_pos, check);
	m_product = local.extractToken(record, next_pos, check);

	start = next_pos;

	m_cntItem = 0u;

	while (check) {
		local.extractToken(record, next_pos, check);
		m_cntItem++;
	}

	m_lstItem = new ItemInfo*[m_cntItem];
	check = true;

	for (unsigned int i = 0u; i < m_cntItem; i++) {
		m_lstItem[i] = new ItemInfo(local.extractToken(record, start, check));
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& other){
	throw string("Invalid Operation: CustomerOrder objects cannot be copied.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept{
	*this = move(other);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other){
	if (this != &other){
		m_name = other.m_name;
		m_product = other.m_product;
		m_cntItem = other.m_cntItem;
		m_lstItem = other.m_lstItem;
		other.m_lstItem = nullptr;
	}

	return *this;
}

CustomerOrder::~CustomerOrder(){
	delete[] m_lstItem;
}

bool CustomerOrder::getItemFillState(string item) const{
	for (unsigned int i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item) {
			return m_lstItem[i]->m_fillState;
		}
	}

	return true;
}

bool CustomerOrder::getOrderFillState() const{
	bool ck = true;
	for (unsigned int i = 0u; i < m_cntItem; i++) {
		if (!m_lstItem[i]->m_fillState) {
			ck = false;
		}
	}

	return ck;
}

void CustomerOrder::fillItem(Item & item, ostream & os){
	for (unsigned int i = 0u; i < m_cntItem; i++){
		if (m_lstItem[i]->m_itemName == item.getName()){
			if (item.getQuantity() > 0){
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				item.updateQuantity();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]";
			}
			else {
				os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]";
			}
			os << endl;
		}
	}
	
}

void CustomerOrder::display(ostream& os) const{
	os << m_name << " - " << m_product << endl;

	for (unsigned int i = 0u; i < m_cntItem; i++){
		os << "[" << setw(6) << right << setfill('0') << m_lstItem[i]->m_serialNumber 
			<< setfill(' ') << "] " << setw(16) << left
			<< m_lstItem[i]->m_itemName << " - " 
			<< (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING") << endl;
	}
}
