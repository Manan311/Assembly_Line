#include "Utilities.h"
using namespace std;

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t fieldW){
	m_widthField = fieldW;
}

size_t Utilities::getFieldWidth() const{
	return m_widthField;
}

const string Utilities::extractToken(const string& str, size_t& next_pos, bool& more){
	string token;

	if (more){
		size_t pos = str.find(getDelimiter(), next_pos + 1u);
		
		if (pos != string::npos){
			token = str.substr(next_pos, pos - next_pos);
			more = true;

			if (pos == next_pos) {
				throw string("ERROR: two delimiters found back to back");
			}

			next_pos = pos + 1u;

			if (m_widthField < static_cast<int>(token.size())) {
				setFieldWidth(token.size());
			}
		}
		else{
			token = str.substr(next_pos, str.length());
			more = false;
		}
	}

	if (token.back() == '\r') {
		token.pop_back();
	}

	return token;
}

void Utilities::setDelimiter(const char delimiter){
	m_delimiter = delimiter;
}

const char Utilities::getDelimiter() const{
	return m_delimiter;
}