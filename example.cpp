#include <KAT_audio_api.hpp>

/*
This file will generate cbat.wav and cbat.xdg
where are contained the first few notes of cbat rappresented using a sin wave
*/
int main ( ) {
    // creating the player
    kat_audio cbat_player;
    // setting the bpm
    cbat_player.set_bpm (82.0);
    // setting the sample rate
    cbat_player.set_sampl (44100);

    // adding the notes
    cbat_player.add_frame ( 2, 20000, 0,  8 );
    cbat_player.add_frame ( 3, 20000, 0,  4 );
    cbat_player.add_frame ( 1, 20000, 0, 12 );
    cbat_player.add_frame ( 2, 20000, 0,  8 );
    cbat_player.add_frame ( 0, 20000, 0,  4 );
    cbat_player.add_frame ( 0, 20000, 0,  4 );
    cbat_player.add_frame ( 0, 20000, 0,  8 );
    cbat_player.add_frame (-2, 20000, 0, 16 );

    cbat_player.add_frame ( -1, 20000, 0, 8 );
    cbat_player.add_frame (  0, 20000, 0, 4 );
    cbat_player.add_frame ( -2, 20000, 0,12 );
    cbat_player.add_frame ( -1, 20000, 0, 8 );
    cbat_player.add_frame ( -3, 20000, 0, 4 );
    cbat_player.add_frame ( -3, 20000, 0, 4 );
    cbat_player.add_frame ( -3, 20000, 0, 8 );
    cbat_player.add_frame ( -5, 20000, 0,16 );

    // saving the file in cbat.xdg
    cbat_player.save ( "cbat.xdg" );
    // exporting the file in cbat.wav
    cbat_player.export_wav ( "cbat.wav" );

    std::cout << "END\n";    
}