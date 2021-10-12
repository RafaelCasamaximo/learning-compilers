#ifndef LEXER_H
#define LEXER_H

#include "automata.h"
#include <string>

class Lexer{
    public:
        Automata automata;
        int current_state;          //Estado atual
        int last_final;             //Último estado final
        int c_begin_read;           //Cursor/ contador inicio da Leitura
        int c_current_pos;          //Cursor/ contador posição Atual
        int c_last_final_recon;     //Cursor/ contador último final reconhecido
        char current_input;         //Input  atual

        Lexer(){};
        Lexer(Automata automata);

        void init(Automata automata);

        void scan(std::string content);

    private:
        void continueScan(int next_state);
        int resetScan(std::string content, int next_state);
};

#endif