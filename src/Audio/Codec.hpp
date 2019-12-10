/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Codec
*/

#ifndef CODEC_HPP_
    #define CODEC_HPP_
    #include <opus.h>

    namespace babel {
        #define APPLICATION     OPUS_APPLICATION_VOIP
        #define BITRATE         64000
        #define MAX_PACKET_SIZE (3 * 1276 + 4)
        #define FRAME_SIZE          960
        #define NUM_CHANNELS        2
        #define SAMPLE_RATE         48000
        #define MAX_FRAME_SIZE      (6 * 960)

        class Codec {
            public:
                Codec();
                ~Codec();

                int encode(unsigned char *cbits, char *dataInput);
                int decode(unsigned char *cbits, char *dataOutput, int nbBytes);

            private:
                OpusEncoder *_encoder;
                OpusDecoder *_decoder;
                int _error;
        };
    }

#endif /* !CODEC_HPP_ */
