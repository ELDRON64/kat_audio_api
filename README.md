# KAT_AUDIO api (v. 0.1a)

this is an audio api for the kat-projekt.
this api is the interface with xdg files.

## what is xdg?

xdg is the custom file extension for the kat-project_audio
the porpuse of this file is to store vocal data.
expressed via their parameters.

## how does it works?

## which are the methods that i can use?

first you nead to create a kat_audio interface:

```cpp – C++
#include <KAT_audio_api.hpp>

kat_audio interface;
```

to load a file in the interface you can call:

```cpp – C++
interface.load ( "<file_name>.xdg" );
```

to save the file you can call:

```cpp – C++
interface.save ( "<file_name>.xdg", (bool) <forze_save> );
```

to display you can call:

```cpp – C++
#include <iostream>

std::cout << interface;
```

to export to wav you can use:

```cpp – C++
interface.export_wav ( "<file_name>.wav", (bool) <forze_save> );
```

to regenerate the exported audio you can use:

```cpp – C++
interface.generate_audio ( );
```

to get/set the infos for the data stored you can call:

- to get basic informations  
  `interface.get_lenth ( )`  lenth  
  `interface.get_sampl ( )`  sample_rate  
  `interface.get_bpm   ( )`  bpm  

- to set basic informations  
  `interface.set_lenth ( size_t lenth )`  
  `interface.set_sampl ( size_t sample_rate )`  
  `interface.set_bpm ( double bpm )`  

- to get specific frames of the recording  
  `interface.get_frequ ( uint frame )`  frequenze  
  `interface.get_inten ( uint frame )`  intensity  
  `interface.get_frlen ( uint frame )`  lenth  

- to set specific frames of the recording  
  `interface.set_frequ ( uint frame, short value )`  
  `interface.set_inten ( uint frame, short value )`  
  `interface.set_frlen ( uint frame, short value )`  

- with this methods you will get a pointer to the first frame  
  `interface.get_all_frequ ( )`  
  `interface.get_all_inten ( )`  
  `interface.get_all_lenth ( )`  
