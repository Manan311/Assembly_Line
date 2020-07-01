#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Task.h"

class LineManager{
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	size_t pos_first;
	size_t pos_last;
public:
	LineManager(const std::string& fName, std::vector<Task*>& v_task, std::vector<CustomerOrder>& v_customerOrd);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif