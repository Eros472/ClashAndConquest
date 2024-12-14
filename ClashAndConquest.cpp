/*
Name: Erick Hambardzumyan
Class: CS 4080
Assigment: Programming Project: Individual
Date: 12-13-2024
*/

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <vector>

// Token structure and types
enum TokenType { COMMAND, IDENTIFIER, NUMBER, END };

// Token data structure to store the type and value of each token
struct Token {
    TokenType type;       // Type of the token (COMMAND, IDENTIFIER, NUMBER, END)
    std::string value;    // The actual string value of the token
};

// Node structure for Abstract Syntax Tree (AST)
struct Node {
    std::string command;             // Command name (e.g., "create", "attack", etc.)
    std::vector<std::string> args;   // List of arguments for the command
};

class GamingScriptInterpreter {
private:
    std::unordered_map<std::string, int> variables; // Map to store variable names and their integer values

    // Helper function to get the value of a variable or a number
    int getValue(const std::string& token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            return std::stoi(token); // Convert numeric token to an integer
        }
        else if (variables.find(token) != variables.end()) {
            return variables[token]; // Retrieve the value of the variable from the map
        }
        else {
            throw std::runtime_error("Undefined variable: " + token); // Error for undefined variables
        }
    }

public:
    // Tokenizer function to split code into tokens (Lexer)
    std::vector<Token> tokenize(const std::string& code) {
        std::vector<Token> tokens;
        std::istringstream stream(code);
        std::string word;

        while (stream >> word) {
            // Classify tokens based on their value
            if (word == "create" || word == "attack" || word == "defend" || word == "print") {
                tokens.push_back({ COMMAND, word });
            }
            else if (isdigit(word[0]) || (word[0] == '-' && word.size() > 1)) {
                tokens.push_back({ NUMBER, word });
            }
            else {
                tokens.push_back({ IDENTIFIER, word });
            }
        }

        tokens.push_back({ END, "" }); // Add an END token to signal the end of input
        return tokens;
    }

    // Parser function to create an AST from tokens
    std::vector<Node> parse(const std::vector<Token>& tokens) {
        std::vector<Node> ast;
        size_t index = 0;

        while (index < tokens.size() && tokens[index].type != END) {
            if (tokens[index].type == COMMAND) {
                std::string command = tokens[index++].value;
                std::vector<std::string> args;

                // Collect arguments until the next command or the end of the tokens
                while (index < tokens.size() && tokens[index].type != COMMAND && tokens[index].type != END) {
                    args.push_back(tokens[index++].value);
                }

                ast.push_back({ command, args }); // Add the parsed command and its arguments to the AST
            }
            else {
                throw std::runtime_error("Syntax error: Unexpected token " + tokens[index].value);
            }
        }

        return ast;
    }

    // Evaluator function to execute commands from the AST
    void evaluate(const std::vector<Node>& ast) {
        for (const auto& node : ast) {
            if (node.command == "create") {
                if (node.args.size() != 2) throw std::runtime_error("Invalid arguments for 'create'");
                variables[node.args[0]] = std::stoi(node.args[1]); // Store the variable with its value
                std::cout << "Command: create - Created stat '" << node.args[0] << "' with value " << node.args[1] << std::endl;

            }
            else if (node.command == "attack") {
                if (node.args.size() != 3) throw std::runtime_error("Invalid arguments for 'attack'");
                variables[node.args[2]] = getValue(node.args[0]) + getValue(node.args[1]); // Sum of two stats
                std::cout << "Command: attack - Calculated '" << node.args[2] << "' as sum of " << node.args[0] << " and " << node.args[1] << " = " << variables[node.args[2]] << std::endl;

            }
            else if (node.command == "defend") {
                if (node.args.size() != 4) throw std::runtime_error("Invalid arguments for 'defend'");
                int totalattackdamage = getValue(node.args[0]); // Attacker's total damage
                int armor = getValue(node.args[1]);            // Defender's armor
                int damageTaken = totalattackdamage - armor;   // Calculate reduced damage
                if (damageTaken < 0) damageTaken = 0;          // Ensure damageTaken is not negative

                int health = getValue("health");               // Defender's health
                int remainingHealth = health - damageTaken;    // Calculate remaining health

                // Store results
                variables[node.args[2]] = damageTaken;
                variables[node.args[3]] = remainingHealth;

                // Output detailed calculation
                std::cout << "Command: defend - Damage Taken = " << totalattackdamage << " (Total Attack Damage) - "
                    << armor << " (Armor) = " << damageTaken << "\n";
                std::cout << "Remaining Health = " << health << " (Initial Health) - " << damageTaken
                    << " (Damage Taken) = " << remainingHealth << "\n";
            }
            else if (node.command == "print") {
                if (node.args.size() != 1) throw std::runtime_error("Invalid arguments for 'print'");
                std::cout << "Command: print - " << node.args[0] << " = " << getValue(node.args[0]) << std::endl;

            }
            else {
                throw std::runtime_error("Unknown command: " + node.command);
            }
        }
    }

    // Full execution format: Tokenize, Parse, and Evaluate
    void execute(const std::string& code) {
        auto tokens = tokenize(code);   // Tokenize the input code
        auto ast = parse(tokens);       // Parse tokens into an AST
        evaluate(ast);                  // Evaluate the AST
    }
};

int main() {
    GamingScriptInterpreter interpreter;
    std::cout << "Welcome to Clash and Conquest - Stats Based Fighting Game!\n";
    std::cout << "Define your champion stats and battle commands:\n\n";
    std::cout << "Available commands:\n";
    std::cout << "1. create <stat> <value> - Create a new stat (e.g., health, attackdamage, armor).\n";
    std::cout << "2. attack <stat1> <stat2> <result_stat> - Add two stats (e.g., attackdamage and bonusattack) to calculate totalattackdamage.\n";
    std::cout << "3. defend <stat1> <stat2> <damage_taken> <remaining_health> - Calculate damage taken (based on armor) and remaining \nhealth.\n";
    std::cout << "4. print <stat> - Display the value of a stat.\n\n";
    std::cout << "Enter your champion stats and commands (end by pressing ENTER on an empty line):\n";

    std::string script;
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) break;  // Break the loop on an empty line
        script += line + "\n";
    }

    try {
        interpreter.execute(script); // Execute the script
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print any errors encountered
    }

    return 0;
}
