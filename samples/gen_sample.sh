#!/bin/bash

_sample_rate=8000
_keep=""

usage () {
    echo "usage: ${0} -t <string> -f <name> [-hrk]"
    echo ""
    echo "generates a soundfile as C-header from text with TTS."
    echo ""
    echo " -h               this help"
    echo " -t <string>      the text you want to say"
    echo " -f <name>        the filename (without extension)"
    echo " -r <int>         the sample-rate (default=${_sample_rate})"
    echo " -k               keep the wav-files"
    echo ""
}


while getopts "kt:f:r:h" OPTION; do
    case ${OPTION} in
        h)
            usage
            exit 255
        ;;
        t)
            _text="${OPTARG}"
        ;;
        f)
            _filename="${OPTARG}"
        ;;
        r)
            _sample_rate="${OPTARG}"
        ;;
        k)
            _keep=true
        ;;
        *)
            usage
            exit 255
        ;;
    esac
done

if [ ! "${_filename}" ]; then usage; exit 4; fi
if [ ! "${_text}" ]; then usage; exit 5; fi

# Check dependencies
for i in espeak xxd ffmpeg; do
    if ! which ${i} > /dev/null; then
        echo "You need to to install '${i}' first!"
        exit 254
    fi
done

echo -ne "Saying '$_text' to WAV .. "
espeak --stdout -p 60 -s 200 -w ${_filename}_orig.wav "${_text}"
echo -ne "converting to smaller WAV .. "
ffmpeg -guess_layout_max 0 -loglevel warning -ac 1 -i ${_filename}_orig.wav -ar ${_sample_rate} -ac 1 -acodec pcm_u8 ${_filename}.wav
echo "converting to a headerfile: ${_filename}.h"
xxd -i ${_filename}.wav > ${_filename}.h

if [ ! "${_keep}" ]; then
    rm ${_filename}.wav ${_filename}_orig.wav
fi

