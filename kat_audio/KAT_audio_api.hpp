#ifndef KAT_AUDIO
#define KAT_AUDIO

#include <vector>
#include <string>
#include <state_manger.hpp>
#include <save_wav.hpp>
#include <wave_mod.hpp>

class kat_audio : public STATE {
private:
    std::vector<double> generated_audio;
    STATE current_state;
public:
     kat_audio ( ) { }
    ~kat_audio ( ) { }

    // audio generation methods
    int generate_audio ( );
    std::vector <double> get_audio ( );

    // export methos
    int export_wav ( std::string audio_path, bool forze = false );
};

int kat_audio::generate_audio ( ) {
    generated_audio = Isinfxx (current_state.get_all_frequ(),
                               current_state.get_all_inten(),
                               current_state.get_all_lenth(),
                               current_state.get_bpm(),
                               current_state.get_sampl());
    return 0;
}

int kat_audio::export_wav ( std::string audio_path, bool forze ) {
    if ( !forze ) { if ( exists ( audio_path ) ) { return 3; } }

    if (generated_audio.empty()) { if ( generate_audio () != 0 ) { return 2; } }

    return save_wav ( generated_audio, audio_path, sample_rate );
}

#endif