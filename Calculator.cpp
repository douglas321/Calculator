#include <iostream>
#include <vector>
#include <string>
#include <fstream> // for file stuff
#include <cmath> // include math to add more calculations later



// class declaration for Operations
class Operations {
public:
    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        if (b == 0) {
            std::cout << "Error! Division by zero.\n";
            return 0;
        } else {
            return a / b;
        }
    }
};

// class declaration for CalculationHistory
class CalculationHistory {
public:
    // write calculation history to a file
    static void writeHistory(double num1, double num2, const char* op, double result) {
        std::ofstream file("calculation_history.txt", std::ios_base::app);

        if (file.is_open()) {
            file << num1 << " " << op << " " << num2 << " = " << result << std::endl;
            file.close();
        } 
        
        else {
            std::cout << "Unable to open file for writing history." << std::endl;
        }
    }

    static void readHistory() {
        std::ifstream file("calculation_history.txt");
        std::vector<std::string> lines;
        std::string line;

        if (file.is_open()) {
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        } else {
            std::cout << "Unable to open file for reading history." << std::endl;
            return;
        }

        int numLines = std::min(5, static_cast<int>(lines.size()));
        std::cout << "Last 5 calculations:\n";
        for (int i = lines.size() - numLines; i < lines.size(); ++i) {
            std::cout << lines[i] << std::endl;
        }
    }
};

void Calculate(int choice);

// main function
int main() {
    char again = 'y';
    int choice;

    while (again == 'y' || again == 'Y') {
        std::cout << "\nCalculator Menu:\n";
        std::cout << "1. Add\n";
        std::cout << "2. Subtract\n";
        std::cout << "3. Multiply\n";
        std::cout << "4. Divide\n";
        std::cout << "5. View Calculation History\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice) || choice < 1 || choice > 6) {
            std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (choice == 6) {
            return 0;
        } else if (choice == 5) {
            CalculationHistory::readHistory();
            continue;
        } else {
            Calculate(choice);
        }

        std::cout << "Would you like to perform another operation? (y/n): ";
        std::cin >> again;
    }

    return 0;
}

void Calculate(int choice) {
    Operations operate;
    double result;
    double num1, num2;
    const char* op;

    std::cout << "Enter two numbers, separated by a space: ";
    std::cin >> num1 >> num2;

    switch (choice) {
        case 1:
            result = operate.add(num1, num2);
            op = "+";
            break;
        case 2:
            result = operate.subtract(num1, num2);
            op = "-";
            break;
        case 3:
            result = operate.multiply(num1, num2);
            op = "*";
            break;
        case 4:
            result = operate.divide(num1, num2);
            op = "/";
            break;
    }

    //print result to Console
    std::cout << "Result: " << result << std::endl;
    
    // write calculation history to file
    CalculationHistory::writeHistory(num1, num2, op, result);
}
