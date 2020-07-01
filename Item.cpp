#include <iomanip>
#include "Utilities.h"
#include "Item.h"
using namespace std;

int Item::m_widthField = 0;

Item::Item(const  string& record){
	Utilities local;
	bool more = true;
	size_t next_pos = 0u;

	m_name = local.extractToken(record, next_pos, more);
	m_serialNumber = local.extractToken(record, next_pos, more);
	m_quantity =  stoi(local.extractToken(record, next_pos, more));
	m_description = local.extractToken(record, next_pos, more);
	m_widthField = local.getFieldWidth();
}

const  string& Item::getName() const {
	return m_name; 
}

const unsigned int Item::getSerialNumber(){
	int serialNumber = stoi(m_serialNumber);
	m_serialNumber = to_string(serialNumber + 1);

	return serialNumber;
}

const unsigned int Item::getQuantity() {
	return m_quantity; 
}

void Item::updateQuantity() {
	if ((m_quantity - 1) != 0) {
		m_quantity--;
	}
}

void Item::display( ostream& os, bool full) const{
	os <<  setw(m_widthField) <<  left << m_name << " [" <<  setw(6) <<  right <<  setfill('0') 
		<< m_serialNumber <<  setfill(' ') << "]";
	
	if (full) {
		os << " Quantity: " << setw(m_widthField) << left << m_quantity << " Description: " << m_description;
	}
	
	os <<  endl;
}