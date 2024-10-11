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

int main() {
    TestCase test1("input1", "expected1");
    TestCase test2("input2", "expected2");

    // Динамический массив объектов класса TestCase
    TestCase* tests = new TestCase[2] {test1, test2};

    // Создание набора тестов
    TestSuite suite(tests, 2);

    // Создание задачи
    Task task("Example Task", suite);

    // Решение пользователя
    UserSolution solution("user_solution_code");

}
