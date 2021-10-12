#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"
#include "automata.h"

using namespace std;

Lexer::Lexer(Automata automata){
    this->automata = automata;
    this->current_state = automata.initial_state;
    this->last_final = 0;
    this->c_begin_read = 0;
    this->c_current_pos = 0;
    this->c_last_final_recon = 0;
    this->current_input = '\0';
}

void Lexer::init(Automata automata){
    this->automata = automata;
    this->current_state = automata.initial_state;
    this->last_final = 0;
    this->c_begin_read = 0;
    this->c_current_pos = 0;
    this->c_last_final_recon = 0;
    this->current_input = '\0';
}

void Lexer::scan(string content){
    int i = 0;
    while(i < content.size()){
        char& c = content[i];

        current_input = c;
        int next_state = automata.states[current_state][automata.symbolPos(current_input)];
        if(next_state > 0){
            //continua leitura
            continueScan(next_state);
        }
        else{
            //reseta leitura
            i = resetScan(content, next_state);
        }

        i++;
    }
}

//PRIVATES

void Lexer::continueScan(int next_state){
    //Imprime input atual
    cout << current_input;

    //Atualiza o estado atual com o que acabou de ser lido
    current_state = next_state;
    //Atualiza o contador
    c_current_pos++;
    //Verifica se o estado atual é um estado final
    if(automata.isFinalState(current_state)){
        //Se for, atualiza o ultimo estado final visitado
        last_final = current_state;
        //Atualiza o último estado final que foi visitado (que é o atual)
        c_last_final_recon = c_current_pos;
    }
}

int Lexer::resetScan(string content, int next_state){
    //Compara se o estado final é 0/ ainda não foi alterado ou
    //se o estado atual não é um estado final para mudar o counter do começo
    if(last_final == 0 || !automata.isFinalState(current_state)){
        cout << "ERRO" << endl;
        c_begin_read++;
    }
    //Caso seja um final ou o final não seja 0 ele atualiza o c_begin_read
    else{
        cout << endl;
        c_begin_read = c_last_final_recon;
    }

    //Atualiza ponteiros e counters
    c_current_pos = c_begin_read;
    c_last_final_recon = c_begin_read;
    current_state = automata.initial_state;
    
    //retorna o index da string
    return c_begin_read;
}