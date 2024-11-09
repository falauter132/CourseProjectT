#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

const int MAX_TASKS = 100;

string titles[MAX_TASKS];
int priorities[MAX_TASKS];
string descriptions[MAX_TASKS];
time_t dueDates[MAX_TASKS];

// Функція для додавання завдання
void addTask(int& taskCount) {
    if (taskCount >= MAX_TASKS) {
        cout << "Досягнуто максимум задач!" << endl;
        return;
    }

    string title, description;
    int priority;
    time_t dueDate;
    tm dateStruct = {};

    cout << "Назва: ";
    cin.ignore();
    getline(cin, title);
    cout << "Пріоритет (1-3): ";
    cin >> priority;
    cout << "Опис: ";
    cin.ignore();
    getline(cin, description);

    cout << "Дата виконання (рік місяць день години хвилини): ";
    cin >> dateStruct.tm_year >> dateStruct.tm_mon >> dateStruct.tm_mday >> dateStruct.tm_hour >> dateStruct.tm_min;
    dateStruct.tm_year -= 1900;
    dateStruct.tm_mon -= 1;
    dueDate = mktime(&dateStruct);

    titles[taskCount] = title;
    priorities[taskCount] = priority;
    descriptions[taskCount] = description;
    dueDates[taskCount] = dueDate;
    taskCount++;
}

void removeTask(int& taskCount, const string& title) {
    for (int i = 0; i < taskCount; ++i) {
        if (titles[i] == title) {
            for (int j = i; j < taskCount - 1; ++j) {
                titles[j] = titles[j + 1];
                priorities[j] = priorities[j + 1];
                descriptions[j] = descriptions[j + 1];
                dueDates[j] = dueDates[j + 1];
            }
            taskCount--;
            return;
        }
    }
    cout << "Задачу не знайдено!" << endl;
}

void editTask(int taskCount, const string& title) {
    for (int i = 0; i < taskCount; ++i) {
        if (titles[i] == title) {
            cout << "Нова назва: ";
            cin.ignore();
            getline(cin, titles[i]);
            cout << "Новий пріоритет (1-3): ";
            cin >> priorities[i];
            cout << "Новий опис: ";
            cin.ignore();
            getline(cin, descriptions[i]);

            tm dateStruct = {};
            cout << "Нова дата виконання (рік місяць день години хвилини): ";
            cin >> dateStruct.tm_year >> dateStruct.tm_mon >> dateStruct.tm_mday >> dateStruct.tm_hour >> dateStruct.tm_min;
            dateStruct.tm_year -= 1900;
            dateStruct.tm_mon -= 1;
            dueDates[i] = mktime(&dateStruct);
            return;
        }
    }
    cout << "Задачу не знайдено!" << endl;
}

void displayTasks(int taskCount) {
    char buffer[26];
    for (int i = 0; i < taskCount; ++i) {
        ctime_s(buffer, sizeof(buffer), &dueDates[i]);
        cout << "Назва: " << titles[i]
            << ", Пріоритет: " << priorities[i]
            << ", Опис: " << descriptions[i]
            << ", Дата: " << buffer;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int taskCount = 0;
    int choice;

    while (true) {
        cout << "\nМеню:\n1. Додати\n2. Видалити\n3. Редагувати\n4. Переглянути\n0. Вийти\n";
        cin >> choice;

        switch (choice) {
        case 1: addTask(taskCount); break;
        case 2: {
            string title;
            cout << "Введіть назву для видалення: ";
            cin.ignore();
            getline(cin, title);
            removeTask(taskCount, title);
            break;
        }
        case 3: {
            string title;
            cout << "Введіть назву для редагування: ";
            cin.ignore();
            getline(cin, title);
            editTask(taskCount, title);
            break;
        }
        case 4: displayTasks(taskCount); break;
        case 0: return 0;
        default: cout << "Неправильний вибір!" << endl;
        }
    }
}
