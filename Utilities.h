#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <string>

class Utilities{
	int m_widthField = 1;
	static char m_delimiter;
public:
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char);
	const char getDelimiter() const;
};

#endif