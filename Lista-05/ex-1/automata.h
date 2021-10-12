#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <vector>


class Automata
{
    public:
        int initial_state;
        int symbols_qtd;
        int states_qtd;
        std::vector<char> symbols;
        std::vector<std::vector<int>> states;
        std::vector<int> final_states;

        Automata(){};
        Automata(std::vector<char> symbols, std::vector<std::vector<int>> states, int initial_state, std::vector<int> final_states);

        void init(std::vector<char> symbols, std::vector<std::vector<int>> states, int initial_state, std::vector<int> final_states);

        int symbolPos(char symbol);
        bool isFinalState(int state);
        void display();

    private:
        void setSymbols(std::vector<char> aux);
        void setStates(std::vector<std::vector<int>> aux);
        void setInitialState(int state);
        void setFinalStates(std::vector<int> final_states);


};

#endif