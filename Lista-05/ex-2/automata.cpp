#include <iostream>

#include "automata.h"

using namespace std;

//PUBLICS
/*
Constructor da classe para criar um novo automato por meio de tabelas
*/
Automata::Automata(vector<char> symbols, vector<vector<int>> states, int initial_state, vector<int> final_states, vector<string> token_class){
    setInitialState(initial_state);
    setSymbols(symbols);
    setStates(states);
    setFinalStates(final_states);
    setTokenClass(token_class);
}

/*
Função auxiliar para iniciar a classe novamente em caso de passagem de parâmetros
*/
void Automata::init(vector<char> symbols, vector<vector<int>> states, int initial_state, vector<int> final_states, vector<string> token_class){
    setInitialState(initial_state);
    setSymbols(symbols);
    setStates(states);
    setFinalStates(final_states);
    setTokenClass(token_class);
}

/*
Imprime o autômato criado na tela
*/
void Automata::display(){
    //Print Symbols
    for(char i : this->symbols){
        cout << i << " ";
    }
    cout << endl;

    //Print States and Transitions
    for(vector<int> i : this->states){
        for(int j : i){
            cout << j << " ";
        }
        cout << endl;
    }

    cout << "symbols_qtd: " << this->symbols_qtd << endl;
    cout << "states_qtd: " << this->states_qtd << endl;
}

/*
Retorna a posição de um simbolo na lista de símbolos
*/
int Automata::symbolPos(char symbol){
    for(int i = 0; i < this->symbols.size(); i++){
        if(symbols[i] == symbol){
            return i;
        }
    }
    return -1;
}

/*
Verifica se um estado é final
*/
bool Automata::isFinalState(int state){
    for(int i : this->final_states){
        if(i == state){
            return true;
        }
    }
    return false;
}

//PRIVATES
/*
Define simbolos
*/
void Automata::setSymbols(vector<char> aux){
    this->symbols = aux;
    this->symbols_qtd = aux.size();
}

/*
Define os estados
*/
void Automata::setStates(vector<vector<int>> aux){
    this->states = aux;
    this->states_qtd = aux.size();
}

/*
Define o estado inicial
*/
void Automata::setInitialState(int state){
    this->initial_state = state;
}

/*
Define os estados finais
*/
void Automata::setFinalStates(vector<int> final_states){
    this->final_states = final_states;
}

void Automata::setTokenClass(vector<string>token_class){
    this->token_class = token_class;
}

int Automata::getIndexFinalState(int state){
    for(int i = 0; i < this->final_states.size(); i++){
        if(this->final_states[i] == state){
            return i;
        }
    }
    return -1;
}

string Automata::getTokenClass(int state, string token_resultado){
    int resultado = -1;
    string token = "";
    try{
        resultado = getIndexFinalState(state);
        token.assign(this->token_class[resultado]);
    }
    catch(const out_of_range& oor){
        token.assign("");
    }
    token_resultado.assign(token);
    return token;
}