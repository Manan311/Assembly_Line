#include <fstream>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;

LineManager::LineManager(const string& fName, vector<Task*>& v_task, vector<CustomerOrder>& v_customerOrd){
	ifstream f(fName);
	Utilities local;
	size_t next_pos = 0u;
	string record;
	string task;
	string task2;
	bool ck = true;
	bool ck_first = true;

	while (!f.eof()){
		getline(f, record);
		task = local.extractToken(record, next_pos, ck);
		
		if (ck) {
			task2 = local.extractToken(record, next_pos, ck);
		}

		for (size_t i = 0u; i < v_task.size(); ++i){
			if (v_task[i]->getName() == task){
				if (ck_first){
					pos_first = i;
					ck_first = !ck_first;
				}
				if (!task2.empty()){
					for (size_t j = 0u; j < v_task.size(); ++j){
						if (v_task[j]->getName() == task2){
							v_task[i]->setNextTask(*v_task[j]);
							break;
						}
					}
				}
				else {
					pos_last = i;
				}
				break;
			}
		}

		next_pos = 0u;
		task.clear();
		task2.clear();
		ck = true;
	}

	for (size_t i = 0u; i < v_customerOrd.size(); ++i) {
		ToBeFilled.push_back(move(v_customerOrd[i]));
	}

	v_customerOrd.erase(v_customerOrd.begin(), v_customerOrd.end());
	AssemblyLine = v_task;
}

bool LineManager::run(ostream& os){
	CustomerOrder buff;
	bool status = true;

	if (!ToBeFilled.empty()){
		*AssemblyLine[pos_first] += move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (size_t i = 0u; i < AssemblyLine.size(); ++i){
		AssemblyLine[i]->runProcess(os);
	}

	if (AssemblyLine[pos_last]->getCompleted(buff)) {
		Completed.push_back(move(buff));
	}

	for (size_t i = 0u; i < AssemblyLine.size(); ++i){
		if (AssemblyLine[i]->moveTask()) {
			status = false;
		}
	}

	return status;
}

void LineManager::displayCompleted(ostream& os) const {
	if (!Completed.empty()) {
		for (size_t i = 0u; i < Completed.size(); ++i) {
		Completed[i].display(os);
		}
	}
}

void LineManager::validateTasks() const {
	if (!AssemblyLine.empty()) {
		for (size_t i = 0u; i < AssemblyLine.size(); ++i) {
			AssemblyLine[i]->validate(cout);
		}
	}
}