# gen_sample.sh

Generates header-files with sound from text with the help of espeak, ffmpeg and xxd

    $ for i in `seq 0 10 100`; do ./gen_sample.sh -t ${i} -f say_${i}; done 
    Saying '0' to WAV .. converting to smaller WAV .. converting to a headerfile: say_0.h
    Saying '10' to WAV .. converting to smaller WAV .. converting to a headerfile: say_10.h
    Saying '20' to WAV .. converting to smaller WAV .. converting to a headerfile: say_20.h
    Saying '30' to WAV .. converting to smaller WAV .. converting to a headerfile: say_30.h
    Saying '40' to WAV .. converting to smaller WAV .. converting to a headerfile: say_40.h
    Saying '50' to WAV .. converting to smaller WAV .. converting to a headerfile: say_50.h
    Saying '60' to WAV .. converting to smaller WAV .. converting to a headerfile: say_60.h
    Saying '70' to WAV .. converting to smaller WAV .. converting to a headerfile: say_70.h
    Saying '80' to WAV .. converting to smaller WAV .. converting to a headerfile: say_80.h
    Saying '90' to WAV .. converting to smaller WAV .. converting to a headerfile: say_90.h
    Saying '100' to WAV .. converting to smaller WAV .. converting to a headerfile: say_100.h

## usage

    $ ./gen_sample.sh -h               
    usage: ./gen_sample.sh -t <string> -f <name> [-hrk]

    generates a soundfile as C-header from text with TTS.

     -h               this help
     -t <string>      the text you want to say
     -f <name>        the filename (without extension)
     -r <int>         the sample-rate (default=8000)
     -k               keep the wav-files


## based on:

https://www.xtronical.com/basics/audio/dacs-for-sound/playing-wav-files/

