#pragma once
#include <iostream>
#include <stdexcept>
#define punteggiatura "-_ ,.;:!?\0"
// #define vocali "aàeèiìoòuùAÀEÈIÌOÒUÙ"
#define vocali "aeiouAEIOU"
#define alphabet_min "abcdefghijklmnopqrstuvwxyz"
#define alphabet_cap "ABCDEFGHIJKLMNOPQRTSUVWXYZ"

// the languages supported by the sillabator
enum language {
    ITA,
    ENG,
    JAP,
    ONE
};
// the linked list that contains the sillab it's position and it's next and previous if any
struct sillaba {
    sillaba *previous;
    char* _sillaba;
    // 1: begin
    // 2: end
    // 3: middle
    char _sillaba_type;
    sillaba *next;
} sillaba_default = {nullptr,nullptr,0,nullptr };

// this class thakes as arguments a frase and language ad does the sillabels division of the insert frase in the specified language
class sillabator
{
private:
    // the orginal frase
    char* frase;
    // the sillabated frase
    char* frase_sillabata;
    // the specified language
    language current_lang;
    // the root of the sillaba list
    sillaba  sillabe_root;

    // utility
    /**
     * @brief converts a frase_sillabata to frase
     * 
     * @param frase 
     * @return char* 
     */
    static char*  clean_f  ( char* &frase );
    /**
     * @brief converts capital letters in the inserted frase all in minuscole letters
     * 
     * @param frase the frase mixed capital and minusole
     * @return minuscole_frase
     */
    static char*  capital  ( char* &frase );
    /**
     * @brief this function verifies if the char c is in the char[] t
     * if specified sets index at the position of the corresponding caracter
     * 
     * @param c caracter to verify
     * @param t set from where to verify
     * @param index (optional) if the caracter is in the array sets to the position
     * @return true if c is in t
     * @return false  if c is not in t
     */
    static bool   in       ( char &c, const char t [], size_t *index = nullptr );
    /**
     * @brief return the lenth of the str
     * 
     * @param str 
     * @return the lenth of the string 
     */
    static size_t len      ( char* &str );
    /**
     * @brief add '- to the frase at the index position 
     * 
     * @param frase 
     * @param index 
     * @return the new frase
     */
    static char*  add_dash ( char* &frase, size_t index );
    /**
     * @brief remove a caracter from the string in the selected index
     * 
     * @param frase 
     * @param index 
     * @return the new frase 
     */
    static char*  rmv_char ( char* &frase, size_t index );
    /**
     * @brief replace the index caracter with '_'
     * 
     * @param frase 
     * @param index 
     * @return char* 
     */
    static char*  rep_char ( char* &frase, size_t index );
    /**
     * @brief copy th content fo the frase* to a new frase1*
     * 
     * @param frase 
     * @return frase1
     */
    static char*  copy     ( char* &frase );

    // sillabators

    /**
     * @brief in base of the selected language starts a _sillaba_lang process
     * 
     */
    void _sillaba ( );
    /**
     * @brief does the sillabation procces in italian
     * 
     */
    void _sillaba_ita ( );
    /**
     * @brief does the sillabation procces in english
     * 
     */
    void _sillaba_eng ( );
    /**
     * @brief does the sillabation procces in japanese
     * 
     */
    void _sillaba_jap ( );
    /**
     * @brief create a sillable for every letter
     * 
     */
    void _sillaba_one ( );
    /**
     * @brief wrappes the sillabated_frase into a sillaba linked list
     * 
     */
    void   link_sil ( );

public:
    /**
     * @brief Construct a new sillabator object
     * 
     * @param frase the frase to sillabate
     * @param lang the language of the frase
     */
    sillabator ( char* frase, language lang ) : frase(frase), current_lang(lang) {
        _sillaba ( ); 
    }
    /**
     * @brief Construct a new sillabator lang is not lang but is integer ( for loading from STATE )
     * 
     * @param frase 
     * @param lang 
     */
    sillabator ( char* frase, size_t lang ) : frase(frase) {
        switch ( lang ) {
            case 0: this->current_lang = ITA; break;
            case 1: this->current_lang = ENG; break;
            case 2: this->current_lang = JAP; break;
            default: this->current_lang = ONE; break;
        }

        _sillaba ( );
    }
    /**
     * @brief Destroy the sillabator object
     * 
     */
    ~sillabator ( ) { 
        free ( frase_sillabata ); 
    }

    // chage methods
    /**
     * @brief change the frase langue to lang
     * 
     * @param lang 
     */
    void change_lang  ( language lang );
    /**
     * @brief change the frase to frase
     * 
     * @param frase 
     */
    void change_frase ( char* frase );

    // get methods
    /**
     * @brief Get the sillaba object at the frame position
     * 
     * @param frame 
     * @return sillaba 
     */
    sillaba  get_sillaba ( size_t frame );
    /**
     * @brief Get the courrent language
     * 
     * @return language 
     */
    language get_lang    ( ) { return current_lang; }
    /**
     * @brief Get the frase 
     * 
     * @return char* 
     */
    char*    get_frase   ( ) { return frase; }
    /**
     * @brief Get the frase_sillabata 
     * 
     * @return char* 
     */
    char*    get_frase_s ( ) { return frase_sillabata; }
};

char*  sillabator::clean_f  ( char* &frase ) {
    char* frase_pulita = copy ( frase );
    size_t i = 0;
    while ( frase_pulita[i] != '\0' ) {    
        if ( in ( frase_pulita[i], "-" ) ) {
            frase_pulita = rmv_char ( frase_pulita, i +1);
        } else if ( frase_pulita[i] == '_' ) {
            frase_pulita[i] = ' ';
        }
        
        i++;
    }

    return frase_pulita;
}
char*  sillabator::capital  ( char* &frase ) {
    // remove all capital leters
    char* frase_min = copy ( frase );
    for (size_t i = 0; i < len ( frase ); i++) {
        size_t p = 0;
        if ( in (frase_min[i],alphabet_cap,&p) ) {
            // std::cout << frase_min[i] << (char)alphabet_min[p];
            frase_min[i] = (char)alphabet_min[p]; 
        }
    }

    return frase_min;    
}
bool   sillabator::in       ( char &c, const char t [], size_t *index ) {
    size_t i = 0;
    while ( t[i] != 0 ) { 
        if ( c == t[i] ) { 
            if (index != nullptr) {*index = i;} 
            return true; 
        } i++; 
    }
    return false;
}
size_t sillabator::len      ( char* &str ) {
    int i = 1;
    while (str[i] != '\0') { i++; }
    return i == 0 ? 1 : i+1;
}
char*  sillabator::add_dash ( char* &frase, size_t index ) {
    char* frase2 = (char*) calloc (len(frase)+1,sizeof(char));
    for (size_t i = 0; i < len(frase) + 1; i++)
    {
        if (i < index) { frase2[i] = frase[i];
        } else if (i == index) { frase2[i] = '-';
        } else { frase2[i] = frase[i-1]; }
    }
    return frase2;
}
char*  sillabator::rmv_char ( char* &frase, size_t index ) {
    char* frase2 = (char*) calloc (len(frase)-1,sizeof(char));
    for (size_t i = 0; i < len(frase); i++)
    {
        if (i < index) { frase2[i] = frase[i];
        } else { frase2[i-1] = frase[i]; }
    }
    return frase2;
}
char*  sillabator::rep_char ( char* &frase, size_t index ) {
    char* frase2 = (char*) calloc (len(frase)-1,sizeof(char));
    for (size_t i = 0; i < len(frase); i++)
    {
        if (i == index) { frase2[i] = '_';
        } else { frase2[i] = frase[i]; }
    }
    return frase2;
}
char*  sillabator::copy     ( char* &frase ) {
    char* frase1 = (char*) calloc (len(frase),sizeof(char));
    for (size_t i = 0; i < len(frase); i++) { frase1[i] = frase[i]; }
    return frase1;
}
void   sillabator::link_sil ( ) {
    sillaba new_root;
    char* _curr_sillaba = (char*)"";
    bool inizio = true;
    bool fine = false;
    int i = 0;

    // tokenizzo this.frase_Sillabata ogni -/_ divido
    // sposto i token e le loro proprietà nel new_root e succesivi 
    while ( frase[i] != '\0') {
        /* code */
    }
}

void sillabator::change_lang  ( language lang ) {
    current_lang = lang;
    _sillaba ( ); 
}
void sillabator::change_frase ( char* frase ) {
    this->frase = frase;
    _sillaba ( );
}

sillaba sillabator::get_sillaba ( size_t frame ) {
    if (frame == 0) { return sillabe_root; }

    sillaba sillaba_get = *sillabe_root.next;
    for (size_t i = 0; i < frame - 1; i++) {
        sillaba_get = *sillaba_get.next;
    }

    return sillaba_get;
}

void sillabator::_sillaba () {
    this->frase = capital ( this->frase );
    this->frase = clean_f ( this->frase );
    switch ( current_lang ) {
        case 0: _sillaba_ita ( ); break;
        case 1: _sillaba_eng ( ); break;
        case 2: _sillaba_jap ( ); break;
        default: _sillaba_one ( ); break;
    }
}

void sillabator::_sillaba_one ( ) {
    int i = 0;
    char* frase1 = copy ( this->frase );
    size_t carryoverI = 0;
    for (size_t i = 0; i < len(frase1)-1; i++) {
        if (in(frase1[i+carryoverI], punteggiatura)) 
           { frase1 = rep_char(frase1,i+carryoverI); }
        if (!in(frase1[i+carryoverI+1], punteggiatura)) { 
            frase1 = add_dash(frase1,i+carryoverI+++1); 
        }
    }

    char* frase2 = copy ( frase1 );
    for (size_t i = 0; i < len(frase2) -1; i++) {
        if (frase2[i] == '_' && frase2[i+1] == '-'){
            frase2 = rmv_char(frase2,i+2);
        }
    }

    this->frase_sillabata = frase2;
}
void sillabator::_sillaba_ita ( ) {
    size_t parole;
    char* frase1 = copy ( this->frase );

    // divide in parole la frase
    for (size_t i = 0; i < len(frase1); i++) {
        if (in(frase1[i], punteggiatura)) 
           { frase1 = rep_char(frase1,i); }
    }

    // procedo alla divisione
    // ad ogni vocale divido
    char* prima_divisione = copy ( frase1 );
    size_t i = 0;
    while ( prima_divisione[i] != '\0' ) {
        if ( in ( prima_divisione[i], vocali ) ) {
            prima_divisione = add_dash ( prima_divisione,i+1 );
            i++;
        } i++;
    }   
    // ad ogni doppia divido
    char* seconda_divisione = copy ( prima_divisione );
    i = 0;
    while ( seconda_divisione[i+1] != '\0' ) {
        if ( seconda_divisione[i] == seconda_divisione[i+1] ) {
            seconda_divisione = add_dash ( seconda_divisione,i+1 );
            i++;
        } i++;
    }   

    // procedo alla riunione delle sillabe
    // vocali spaiate
    char* prima_riunione = copy ( seconda_divisione );
    i = 0;
    while ( prima_riunione[i+2] != '\0' ) {
        if ( in ( prima_riunione[i], vocali ) && 
             in ( prima_riunione[i+1], "-" ) && 
             in ( prima_riunione[i+2], vocali ) ) {
            prima_riunione = rmv_char ( prima_riunione,i+2 );
            i++;
        } i++;
    }
    // consonanti spaiate
    char* seconda_riunione = copy ( prima_riunione );
    i = 0;
    while ( seconda_riunione[i+2] != '\0' ) {
        if ( in ( seconda_riunione[i], "-" ) && 
            !in ( seconda_riunione[i+1], vocali ) && 
             in ( seconda_riunione[i+2], punteggiatura ) ) {
            seconda_riunione = rmv_char ( seconda_riunione,i+1 );
            i++;
        } i++;
    }
    // stacco le n-m
    char* terza_riunione = copy ( seconda_riunione );
    i = 0;
    while ( terza_riunione[i+1] != '\0' ) {
        if ( in ( terza_riunione[i], "mn" ) && 
             in ( terza_riunione[i+1], "nm" ) ) {
            terza_riunione = add_dash ( terza_riunione,i+1 );
            i++;
        } i++;
    }

    // verify duble division / error divisions
    char* last_correction = copy (terza_riunione);
    size_t dubles = 0;
    for (size_t i = 0; i < len(last_correction); i++) {
        if (in(last_correction[i - dubles], punteggiatura) && in(last_correction[i - dubles + 1], punteggiatura)) { 
            last_correction = rmv_char ( last_correction,i - dubles + 1 ); 
            dubles ++;
        }
    }
    if ( in ( last_correction[0], punteggiatura ) ) {
        last_correction = rmv_char ( last_correction, 0 );
    }
    if ( in ( last_correction[ len(last_correction)-2 ], punteggiatura ) ) {
        last_correction = rmv_char ( last_correction, len(last_correction)-1 );
    }

    this->frase_sillabata = copy ( last_correction );
}
void sillabator::_sillaba_eng ( ) {
    std::cout << "lingua non ancora inplementata\n";
    _sillaba_one ( );
}
void sillabator::_sillaba_jap ( ) {
    int i = 0;
    char* frase1 = copy ( this->frase );
    size_t carryoverI = 0;
    for (size_t i = 0; i < len(frase1); i++) {
        if (in(frase1[i+carryoverI], punteggiatura)) 
           { frase1 = rep_char(frase1,i+carryoverI); }
        if (in(frase1[i+carryoverI], vocali) && !in(frase1[i+carryoverI+1], punteggiatura))
           { frase1 = add_dash(frase1,i+carryoverI+++1); }
    }

    this->frase_sillabata = frase1;
}

// print the sillabator
std::ostream& operator << (std::ostream& os, sillabator& dt) {
    os << "frase: " << dt.get_frase ( ) << std::endl;
    os << "language: ";
    switch ( dt.get_lang ( ) ) {
        case 0: os << "ITA"; break;
        case 1: os << "ENG"; break;
        case 2: os << "JAP"; break;
        default: os << "ONE"; break;
    }
    os << std::endl;
    os << "sillabe: " << dt.get_frase_s();

    return os;
}
