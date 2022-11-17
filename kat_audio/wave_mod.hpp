#pragma once
#include "math.h"
#include <vector>
#include <iostream>

double F_period ( double x ) {
    return ((sin( x ) + 2* sin ( 2*x )) / 3) ;
}

std::vector < double > get_sample ( size_t duration, double Freq, double Inte, size_t crescita ) {
    std::vector < double > samples ;
    double Derivata_C;
    for (size_t i = 0; i < duration; i++) {
        
        if ( i >= crescita && i <= duration - crescita ) {
            Derivata_C = 1;
        } else if (i < crescita ) {
            Derivata_C = (double)i / (double)crescita;
        } else {
            Derivata_C = (double)( crescita - ( i - (duration - crescita) ) ) / (double)crescita;
        }
        
        samples.push_back ( Derivata_C * Inte * F_period ( Freq * (double) ( i ) ) );
    }
    
    return samples;   
}

std::vector <double> Isinfxx ( std::vector <short> Frequenze,
                               std::vector <unsigned short> Intensita,
                               std::vector <unsigned short> Lunghezze,
                               double bpm = 120, int sample_rate = 44100 ) 
{
    std::vector <double> Samples;
    // somma delle Lungezze * sample rate
    size_t lungezza_totale_note = 0;
    for ( short l : Lunghezze ) { lungezza_totale_note += l; }

    // nota lungezza 1/4 (16) = 1 bpm
    size_t sample_x_beat = ( ( sample_rate * 60 ) / bpm ) / 16; 
    // size_t sample_totali = sample_x_beat * lungezza_totale_note;

    // trovo i sample per L
    std::vector <size_t> sample_per_L;
    for ( unsigned short L : Lunghezze ) {
        sample_per_L.push_back ( (size_t) L * sample_x_beat );
    }

    // normalizzo frequenze
    std::vector <double> Frequenze_M;
    for ( short F : Frequenze ) {
        //std::cout << "Ft_: "<< pow ( 2, (double)F / 12.0 ) << " " << F << "\n";
        Frequenze_M.push_back ( 440.0 * pow ( 2, (double)F / 12.0 ));
    }

    std::vector <double> Frequenze_N;
    for ( auto F: Frequenze_M ) {
        Frequenze_N.push_back ( F * 2 * M_PI / sample_rate );
    }

    // normalizzo intesinta
    std::vector <double> Intensita_M;
    for ( unsigned short I : Intensita ) {
        //std::cout << "Ft_: "<< pow ( 2, (double)F / 12.0 ) << " " << F << "\n";
        Intensita_M.push_back ( (double) I / 65536);
    }

    // print 
    for ( auto F : Frequenze_M )  { std::cout << "F: " << F << "\n";}
    for ( auto L : sample_per_L ) { std::cout << "L: " << L << "\n";}
    for ( auto I : Intensita_M )    { std::cout << "I: " << I << "\n";}
    
    size_t comulative_x = 0;
    for (size_t i = 0; i < sample_per_L.size ( ); i++)
    {
        
        size_t current_L = sample_per_L[i];
        
        if ( (i + 1) % 2 == 0) {
            for (size_t x = 0; x < current_L; x++) {
                Samples.push_back ( 0 );
            }
        } else {    
            std::vector <double> sample_L = get_sample ( current_L, Frequenze_N[i/2],Intensita_M[i/2], (size_t)current_L / 4 );
            Samples.insert(Samples.end(), sample_L.begin(), sample_L.end());
        }
        comulative_x += current_L;
    }


    return Samples;
}
