#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
using std::filesystem::exists;

// this module allows tho load and store the STATE of the kat audio
// l'estensione del file è .xdg (expand dong)

class STATE
{
private:    
public:
    std::string file_path;

    size_t sample_rate;
    double bpm;
    size_t Lenth_F;

    // std::string frase;
    std::vector <short>          Frequenze;
    std::vector <unsigned short> Intensita;
    std::vector <unsigned short> Lunghezze;
     STATE ( );
     STATE ( std::string file_path, size_t dimension = 1 );
    ~STATE ( );

    int resize_buff ( size_t dimension );
    int load ( std::string path = "");
    int save ( std::string path = "", bool forze = false );

    size_t get_lenth ( );
    size_t get_sampl ( );
    double get_bpm ( );

    size_t set_lenth ( size_t lenth );
    size_t set_sampl ( size_t sample_rate );
    double set_bpm ( double bpm );

    short get_frequ ( uint frame );
    short get_inten ( uint frame );
    short get_frlen ( uint frame );
    // char* get_chars ( );

    short set_frequ ( uint frame, short value );
    short set_inten ( uint frame, short value );
    short set_frlen ( uint frame, short value );        
    // char* set_chars ( char* caracters );

    std::vector < short > get_all_frequ ();
    std::vector < unsigned short > get_all_inten ();
    std::vector < unsigned short > get_all_lenth ();

    void add_frame ( );
    void add_frame ( short, unsigned short, 
                    unsigned short, unsigned short );

    friend std::ostream& operator << (std::ostream& os, const STATE& dt);
};

void STATE::add_frame ( ) { resize_buff ( Lenth_F + 1 ); }
void STATE::add_frame ( short F, unsigned short I, 
                       unsigned short P1, unsigned short L1 ) {
    resize_buff ( Lenth_F + 1 );
    Frequenze[Lenth_F + 1] = F;
    Intensita[Lenth_F + 1] = I;
    Lunghezze[Lenth_F * 2 + 2] = P1;
    Lunghezze[Lenth_F * 2 + 3] = L1;
}

STATE::STATE () {
    sample_rate = 44100;
    bpm = 120.0;
    resize_buff(1);
}

STATE::STATE ( std::string file_path, size_t dimension ) {
    sample_rate = 44100;
    bpm = 120.0;
    resize_buff (dimension);

    this->file_path = file_path;
    if ( exists ( file_path ) ) {
        load ( ); 
    }
}

STATE::~STATE () {

}

int STATE::resize_buff ( size_t dimension ) {
    Lenth_F = dimension;
    Frequenze.reserve (Lenth_F);
    Intensita.reserve (Lenth_F);
    Lunghezze.reserve (Lenth_F*2-1);
    return 0;
}

int STATE::load ( std::string path ) {
    if ( path != "" ) { file_path = path; }
    if ( file_path == "" ) { return -1; }
    // verify that the file exist
    if ( !exists ( file_path ) ) {

        return 1;
    }
    // load file
    std::ifstream file ( file_path );

    file.read ((char*) & Lenth_F, 8);
    file.ignore ();
    file.read ((char*) & bpm, 8);
    file.ignore ();
    file.read ((char*) & sample_rate, 8);
    file.ignore ();

    resize_buff ( Lenth_F );

    char* F = (char*) malloc (Lenth_F * 2);
    file.read( F, Lenth_F*2 );
    for (size_t i = 0; i < Lenth_F; i++) {
        short t = 0;
        char* t1 = (char*) & t;
        t1[0] = F[i*2];
        t1[1] = F[i*2+1];
        // std::cout << t << std::endl;
        Frequenze[i] = t;        
    }
    file.ignore();

    char* I = (char*) malloc (Lenth_F * 2);
    file.read( I, Lenth_F*2 );
    for (size_t i = 0; i < Lenth_F; i++) {
        short t = 0;
        char* t1 = (char*) & t;
        t1[0] = I[i*2];
        t1[1] = I[i*2+1];
        // std::cout << t << std::endl;
        Intensita[i] = t;        
    }
    file.ignore();

    char* L = (char*) malloc (Lenth_F * 4 - 2);
    file.read( L, Lenth_F*4 -2 );
    for (size_t i = 0; i < Lenth_F*2-1; i++) {
        short t = 0;
        char* t1 = (char*) & t;
        t1[0] = L[i*2];
        t1[1] = L[i*2+1];
        // std::cout << t << std::endl;
        Lunghezze[i] = t;        
    }

    return 0;
}

int STATE::save ( std::string path , bool forze ) {
    if ( path != "" ) { file_path = path; }
    if ( file_path == "" ) { return -1; }
    // verify that the file exist
    if ( !forze ) { if ( exists ( file_path ) ) { return 1; } }
    

    // load file
    std::ofstream file ( file_path );

    char* lenF = (char*) & Lenth_F;
    for (char i = 0; i < 8; i++) { file.put(lenF[i]); }
    file << "\n";

    char* bpmC = (char*) & bpm;
    for (char i = 0; i < 8; i++) { file.put(bpmC[i]); }
    file << "\n";

    char* samp = (char*) & sample_rate;
    for (char i = 0; i < 8; i++) { file.put(samp[i]); }

    file << "\n";

    for ( short freq : Frequenze ) { 
        char* f = (char*) & freq;
        for (char i = 0; i < 2; i++) { file.put(f[i]); }
    }
    file << "\n";

    for ( unsigned short inte : Intensita ) {
        char* f = (char*) & inte;
        for (char i = 0; i < 2; i++) { file.put(f[i]); } 
    }
    file << "\n";

    for ( unsigned short lent : Lunghezze ) {
        char* f = (char*) & lent;
        for (char i = 0; i < 2; i++) { file.put(f[i]); }
    }

    return 0;
}

size_t STATE::get_lenth ( ) { return Lenth_F; }
size_t STATE::get_sampl ( ) { return sample_rate; }
double STATE::get_bpm   ( ) { return bpm; }

size_t STATE::set_lenth ( size_t lenth ) {
    Lenth_F = lenth;
    return Lenth_F;
}
size_t STATE::set_sampl ( size_t sample_rate ) {
    this->sample_rate = sample_rate;
    return this->sample_rate;
}
double STATE::set_bpm ( double bpm ) {
    this->bpm = bpm;
    return this->bpm;
}

short STATE::get_frequ ( uint frame ) { return Frequenze [frame]; }
short STATE::get_inten ( uint frame ) { return Intensita [frame]; }
short STATE::get_frlen ( uint frame ) { return Lunghezze [frame]; }

short STATE::set_frequ ( uint frame, short value ) {
    if ( frame + 1  > Lenth_F ) { return -1; }

    Frequenze [frame] = value;
    return Frequenze [frame];
}
short STATE::set_inten ( uint frame, short value ) {
    if ( frame + 1  > Lenth_F ) { return -1; }

    Intensita [frame] = value;
    return Intensita [frame];
}
short STATE::set_frlen ( uint frame, short value ) {
    if ( frame + 1  > Lenth_F*2-1 ) { return -1; }

    Lunghezze [frame] = value;
    return Lunghezze [frame];
}

std::vector < short > STATE::get_all_frequ () { return Frequenze; }
std::vector < unsigned short > STATE::get_all_inten () { return Intensita; }
std::vector < unsigned short > STATE::get_all_lenth () { return Lunghezze; }

std::ostream& operator << (std::ostream& os, STATE& p) {
    os << "\tvalues:" << std::endl;
    os << "\t\t" << p.get_bpm() << std::endl;
    os << "\t\t" << p.get_sampl() << std::endl;
    os << "\t\t" << p.get_lenth() << std::endl;

    os << std::endl;
    for (short i = 0; i < p.get_lenth(); i++)
    {
        os << "\tp values " << i << std::endl;
        os << "\t\tF:" << p.get_frequ ( i );
        os << "\t\tI:" << p.get_inten ( i );
        os << "\t\tL1:" << p.get_frlen ( i*2 );
        if ( i+1 < p.get_lenth()) 
        { os << "\t\tL2:" << p.get_frlen ( i*2+1 ); }
        os << std::endl;
    }
    return os;
}
