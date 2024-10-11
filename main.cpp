#include <iostream>
#include <string>

using namespace std;

class TestCase {
private:
    string input;    // Входные данные для теста
    string expected; // Ожидаемый результат
public:
    TestCase(const string& input_str, const string& expected_str) // с помощью списка инициализации
            : input(input_str), expected(expected_str) {}

    const string& getInput() const { return input; }
    const string& getExpected() const { return expected; }
    // const указывает, что этот метод не изменяет состояние объекта.
    // Это гарантирует, что метод может быть вызван даже для константных объектов.
};

class TestSuite {
private:
    TestCase* tests;    // Массив тестов
    int test_count;     // Количество тестов
public:
    TestSuite(TestCase* tests_array, int count) : tests(tests_array), test_count(count) {}

    TestCase* getTests() const { return tests; }
    int getTestCount() const { return test_count; }
};

class Task {
private:
    string description;      // Описание задачи
    TestSuite test_suite;    // Набор тестов для задачи
public:
    Task(const string& desc, TestSuite suite) : description(desc), test_suite(suite) {}

    const string& getDescription() const { return description; }
    TestSuite getTestSuite() const { return test_suite; }
};

class UserSolution {
private:
    string solution_code; // Код решения пользователя
public:
    UserSolution(const string& code) : solution_code(code) {}

    const string& getSolutionCode() const { return solution_code; }
};

class ExecutionResult {
private:
    string actual_output;  // Фактический результат выполнения
    int is_passed;         // Успешность прохождения теста (1 - прошел, 0 - не прошел)
public:
    ExecutionResult() : is_passed(0) {}

    void setActualOutput(const string& output) {
        actual_output = output;
    }

    const string& getActualOutput() const { return actual_output; }

    void setIsPassed(int passed) {
        is_passed = passed;
    }

    int getIsPassed() const { return is_passed; }
};

class Submission {
private:
    UserSolution solution;        // Решение пользователя
    ExecutionResult* results;     // Результаты выполнения тестов
    int total_passed;             // Общее количество пройденных тестов
public:
    Submission(UserSolution user_solution, int test_count) : solution(user_solution), total_passed(0) {
        results = new ExecutionResult[test_count];
    }

    ~Submission() {
        delete[] results;
    }

    void setTotalPassed(int passed) { total_passed = passed; }
    int getTotalPassed() const { return total_passed; }

    ExecutionResult* getResults() const { return results; }
    UserSolution getSolution() const { return solution; }
};

class TestRun {
private:
    TestSuite suite;              // Набор тестов
    ExecutionResult* results;     // Массив результатов для каждого теста
public:
    TestRun(TestSuite ts) : suite(ts) {
        results = new ExecutionResult[suite.getTestCount()];
    }

    ~TestRun() {
        delete[] results;
    }

    ExecutionResult* getResults() const { return results; }
    TestSuite getSuite() const { return suite; }
};

// Метод для симуляции выполнения теста
ExecutionResult run_test_case(UserSolution solution, TestCase test) {
    ExecutionResult result;
    result.setActualOutput(test.getInput());  // Симуляция выполнения решения
    result.setIsPassed(result.getActualOutput() == test.getExpected());
    return result;
}

// Метод для выполнения всех тестов
TestRun run_all_tests(UserSolution solution, TestSuite suite) {
    TestRun run(suite);

    for (int i = 0; i < suite.getTestCount(); i++) {
        run.getResults()[i] = run_test_case(solution, suite.getTests()[i]);
    }

    return run;
}

// Метод для проверки решения пользователя
Submission check_solution(UserSolution solution, Task task) {
    Submission submission(solution, task.getTestSuite().getTestCount());

    int total_passed = 0;
    for (int i = 0; i < task.getTestSuite().getTestCount(); i++) {
        submission.getResults()[i] = run_test_case(solution, task.getTestSuite().getTests()[i]);
        if (submission.getResults()[i].getIsPassed()) {
            total_passed++;
        }
    }

    submission.setTotalPassed(total_passed);
    return submission;
}

int main() {
    TestCase test1("input1", "expected1");
    TestCase test2("input2", "input2");

    // Динамический массив объектов класса TestCase
    TestCase* tests = new TestCase[2] {test1, test2};

    // Создание набора тестов
    TestSuite suite(tests, 2);

    // Создание задачи
    Task task("Example Task", suite);

    // Решение пользователя
    UserSolution solution("user_solution_code");

    // Запуск проверки решения
    Submission submission = check_solution(solution, task);

    // Вывод результатов
    cout << "Total tests passed: " << submission.getTotalPassed() << " out of " << suite.getTestCount() << endl;
    for (int i = 0; i < suite.getTestCount(); i++) {
        cout << "Test " << i + 1 << ": " << (submission.getResults()[i].getIsPassed() ? "Passed" : "Failed") << endl;
    }

    // Освобождение памяти для динамического массива объектов класса
    delete[] tests;

    return 0;
}
