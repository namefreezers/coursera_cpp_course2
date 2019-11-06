#include <iostream>
#include <iostream>
#include <map>
#include <string>
#include <iostream>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string &person) const {
		return db.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string &person) {
		db[person][TaskStatus::NEW]++;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person,
			int task_count) {
		if (db.count(person) == 0) {
			return { {}, {}};
		}

		TasksInfo to_upd, not_updated;
		for (const auto& [status, amount] : db.at(person)) {
			if (status == TaskStatus::DONE) {
				break;
			}
			int amount_to_do = min(task_count, amount);
			task_count -= amount_to_do;
			if (amount_to_do > 0) {
				to_upd[status] = amount_to_do;
			}
			if ((amount - amount_to_do) > 0) {
				not_updated[status] = amount - amount_to_do;
			}
		}

		TasksInfo to_upd_return;
		for (const auto& [status, amount] : to_upd) {
			TaskStatus next_status =
					static_cast<TaskStatus>(static_cast<int>(status) + 1);

			db[person][status] -= amount;
			if (db[person][status] == 0) {
				db[person].erase(status);
			}
			db[person][next_status] += amount;
			to_upd_return[next_status] = amount;
		}

		return {to_upd_return, not_updated};
	}

private:
	map<string, TasksInfo> db;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" << ", "
			<< tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
			<< ", " << tasks_info[TaskStatus::TESTING]
			<< " tasks are being tested" << ", " << tasks_info[TaskStatus::DONE]
			<< " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}
