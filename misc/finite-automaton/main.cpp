#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

struct FiniteAutomaton {
  bool deterministic{};
  int inputs{};
  int start{};
  int current_state{};
  std::vector<int> states;
  std::unordered_map<int, std::vector<int>> e_transitions;
  std::vector<int> accepting;
  std::vector<std::unordered_map<int, int>> transitions;
};

void set_data(FiniteAutomaton &automaton, std::string file_name) {
  {
    std::string line;
    std::ifstream file(file_name);
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string cmd;
      iss >> cmd;
      if (cmd == "deterministic") {
        automaton.deterministic = true;
      } else if (cmd == "states") {
        int num_states{};
        iss >> num_states;
        automaton.transitions.resize(num_states);
        automaton.states.resize(num_states);
      } else if (cmd == "inputs") {
        iss >> automaton.inputs;
      } else if (cmd == "start") {
        iss >> automaton.start;
      } else if (cmd == "accepting") {
        int state;
        while (iss >> state) automaton.accepting.push_back(state);
      } else if (cmd == "transitions") {
        while (getline(file, line)) {
          std::istringstream transition_iss(line);
          int start, end, input;
          transition_iss >> start >> end >> input;
          if (input == -1 && !automaton.deterministic)
            automaton.e_transitions[start].push_back(end);
          automaton.transitions[start][input] = end;
        }
      }
    }
  }
}

bool is_accepted(FiniteAutomaton &automaton) {
  for (const int &i : automaton.accepting)
    if (i == automaton.current_state) return true;
  return false;
}

void handle_transition(FiniteAutomaton &automaton, int input) {
  auto it = automaton.transitions[automaton.current_state].find(input);
  if (it != automaton.transitions[automaton.current_state].end())
    automaton.current_state =
        automaton.transitions[automaton.current_state][input];
}

bool check_epsilon(FiniteAutomaton &automaton, int current) {
  return (automaton.e_transitions.find(current) !=
          automaton.e_transitions.end());
}

bool handle_transitions(FiniteAutomaton &automaton, std::queue<int> q) {
  while (!q.empty()) {
    int input = q.front();
    handle_transition(automaton, input);
    q.pop();
  }
  return (is_accepted(automaton));
}

bool handle_etransitions(FiniteAutomaton &automaton, std::queue<int> q) {
  while (!q.empty()) {
    // create a variable to check this current input
    int input = q.front();
    // handle transition
    handle_transition(automaton, input);
    // check if current state has epsilon transition
    if (check_epsilon(automaton, automaton.current_state)) {
      // recursively follow epsilon path
      std::vector<int> routes =
          automaton.e_transitions[automaton.current_state];
      for (const int &i : routes) {
        automaton.current_state = i;
        bool accepted = handle_etransitions(automaton, q);
        if (accepted) break;
      }
      return is_accepted(automaton);
    } else {
      q.pop();
    }
  }
  return is_accepted(automaton);
}

std::queue<int> create_queue(std::string line) {
  // create queue
  std::istringstream iss(line);
  int symbol;
  std::queue<int> q;
  while (iss >> symbol) q.push(symbol);
  return q;
}

int main(int argc, char *argv[]) {
  std::string file;
  if (argc > 0)
    file = argv[1];
  else
    std::domain_error("no input file");

  FiniteAutomaton automaton;
  set_data(automaton, file);

  std::string line;
  while (std::getline(std::cin, line)) {
    std::queue<int> q = create_queue(line);
    automaton.current_state = automaton.start;
    bool accepted =
        (automaton.deterministic ? handle_transitions(automaton, q)
                                 : handle_etransitions(automaton, q));
    std::cout << (accepted ? "accepted" : "rejected") << '\n';
  }
  return 0;
}
