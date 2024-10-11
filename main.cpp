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
int main() {
    TestCase test1("input1", "expected1");
    TestCase test2("input2", "expected2");

    // Динамический массив объектов класса TestCase
    TestCase* tests = new TestCase[2] {test1, test2};
}
