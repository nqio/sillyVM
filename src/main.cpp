namespace svm {
  enum class instruction_type {
    SAVE, // makes variable
    CHANGE,
    ADD,
    SUB,
    MUL,
    DIV,
    MOV,
    LABEL,
    GOTO // go to label in code
  };

  struct instruction {
    instruction_type instruction;
    std::array<std::string, 2> arguments;
  };
  
  std::array<unsigned int, 5000> memory = {0}; // giving it about 20 kilobytes
  std::unordered_map<std::string, size_t> variables;
  std::unordered_map<std::string, size_t> labels;

  size_t get_value(std::string n) {
    if(variables.count(n)) {
      return variables[n];
    }
    return (size_t) std::stoull(n);
  }

  void evaluate(std::vector<struct instruction> instructions) {
    for (int i = 0; i < instructions.size(); ++i) {
      switch (instructions[i].instruction) {
        case instruction_type::SAVE:
          variables.insert({instructions[i].arguments[0], get_value(instructions[i].arguments[1])});
          break;

        case instruction_type::CHANGE:
          variables[instructions[i].arguments[0]] = get_value(instructions[i].arguments[1]);
          break;

        case instruction_type::ADD:
          memory[get_value(instructions[i].arguments[0])] += memory[get_value(instructions[i].arguments[1])];
          break;

        case instruction_type::SUB:
          memory[get_value(instructions[i].arguments[0])] -= memory[get_value(instructions[i].arguments[1])];
          break;

        case instruction_type::MUL:
          memory[get_value(instructions[i].arguments[0])] *= memory[get_value(instructions[i].arguments[1])];
          break;

        case instruction_type::DIV:
          memory[get_value(instructions[i].arguments[0])] /= memory[get_value(instructions[i].arguments[1])];
          break;

        case instruction_type::MOV:
          memory[get_value(instructions[i].arguments[0])] = memory[get_value(instructions[i].arguments[1])];
          break;

        case instruction_type::LABEL:
          labels.insert({instructions[i].arguments[0], (size_t) i});
          break;
        
        case instruction_type::GOTO:
          i = labels[instructions[i].arguments[0]] - 1;
          break;
      }
    }
  }
}
