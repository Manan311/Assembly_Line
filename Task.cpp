#include "Task.h"
using namespace std;

Task::Task(const string& record): Item(record){
	m_pNextTask = nullptr;
}

void Task::runProcess(ostream& os){
	if (!m_orders.empty()){
		if (!m_orders.front().getOrderFillState()){
			while (!m_orders.front().getItemFillState(getName())){
				m_orders.front().fillItem(*this, os);
			}
		}
	}
}

bool Task::moveTask(){
	bool state;

	if (!m_orders.empty()){
		if (m_pNextTask){
			if (m_orders.front().getItemFillState(getName())){
				*m_pNextTask += move(m_orders.front());
				m_orders.pop_front();
			}
		}
		state = true;
	}
	else {
		state = false;
	}

	return state;
}

void Task::setNextTask(Task& task){
	m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& customerOrd){
	bool state;

	if (!m_orders.empty() && m_orders.front().getOrderFillState()){
		customerOrd = move(m_orders.front());
		m_orders.pop_front();
		state = true;
	}
	else {
		state = false;
	}

	return state;
}

void Task::validate(ostream& os){
	os << getName() << " --> "
	<< (m_pNextTask ? m_pNextTask->getName() : "END OF LINE") << endl;
}

Task& Task::operator+=(CustomerOrder&& customerOrd){
	m_orders.push_back(move(customerOrd));
	return *this;
}