/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "Codec.hpp"
#include <portaudio.h>

namespace babel {
    #define FRAMES_PER_BUFFER   960
    #define PA_SAMPLE_TYPE      paInt16

    struct Stream //VERIFIER SI L'ABSTRACTION EST TOUJOURS VALIDE
    {
        PaStream *stream;
        const PaDeviceInfo *info;
        PaStreamParameters params;
    };

    class Audio {
        public:
            Audio();
            ~Audio();

            void    init(void);
            void    close(void);

            int    read(char *buffer);
            void    write(char *buffer);

        private:
            Stream *    _input;
            Stream *    _output;
            Codec       _codec;
            PaError     _error;
    };
}


#endif /* !AUDIO_HPP_ */
