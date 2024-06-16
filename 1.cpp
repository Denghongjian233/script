#include <iostream>

using namespace std;

class Calculator
{
public:
    int add(int a, int b)
    {
        return a + b;
    }

    int subtract(int a, int b)
    {
        return a - b;
    }

    int multiply(int a, int b)
    {
        return a * b;
    }

    int divide(int a, int b)
    {
        if (b == 0)
        {
            cerr << "Error: Division by zero is not allowed." << endl;
            return 0; // Handle division by zero error
        }
        return a / b;
    }
};

int main()
{
    Calculator calc;

    // Simple menu for operations
    cout << "Choose operation:" << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;

    int choice;
    cin >> choice;

    int num1, num2;
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    switch (choice)
    {
    case 1:
        cout << "Result: " << calc.add(num1, num2) << endl;
        break;
    case 2:
        cout << "Result: " << calc.subtract(num1, num2) << endl;
        break;
    case 3:
        cout << "Result: " << calc.multiply(num1, num2) << endl;
        break;
    case 4:
        cout << "Result: " << calc.divide(num1, num2) << endl;
        break;
    default:
        cerr << "Invalid choice." << endl;
        break;
    }

    return 0;
}
