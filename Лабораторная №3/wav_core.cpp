#include <cstdio>
#include <cstring>
#include <iostream>
#include "wav_header.h"

// TODO: Remove all 'magic' numbers
// TODO: Make the code more secure. Get rid of pointers (after creating a class, of course).

void WavData::CreateFromFile(const char *filename)
{
    printf( ">>>> read_header( %s )\n", filename );
	memset(&header, 0, sizeof(wav_header_s));  // Fill header with zeroes.

    FILE* f = fopen( filename, "rb" );
    if ( !f ) {
        throw new IO_ERROR();
    }

    size_t blocks_read = fread( &header, sizeof(wav_header_s), 1, f);
    if ( blocks_read != 1 ) {
        // can't read header, because the file is too small.
		throw new BAD_FORMAT();
    }

    fseek( f, 0, SEEK_END ); // seek to the end of the file
    size_t file_size = ftell( f ); // current position is a file size!
    
	SetPCMData(f);
	IsHeaderCorrect(file_size);
	fclose(f);
}

void WavData::GetDescription()
{
    printf( "-------------------------\n" );
    printf( " audioFormat   %u\n", header.audioFormat );
    printf( " numChannels   %u\n", header.numChannels );
    printf( " sampleRate    %u\n", header.sampleRate );
    printf( " bitsPerSample %u\n", header.bitsPerSample );
    printf( " byteRate      %u\n", header.byteRate );
    printf( " blockAlign    %u\n", header.blockAlign );
    printf( " chunkSize     %u\n", header.chunkSize );
    printf( " subchunk1Size %u\n", header.subchunk1Size );
    printf( " subchunk2Size %u\n", header.subchunk2Size );
    printf( "-------------------------\n" );
}

void WavData::SetPCMData( FILE* f )
{
    fseek( f, 44, SEEK_SET ); // Seek to the begining of PCM data.

    int chan_count = header.numChannels;
    int samples_per_chan = ( header.subchunk2Size / sizeof(short) ) / chan_count;

    // 1. Reading all PCM data from file to a single vector.
    std::vector<short> all_channels;
    all_channels.resize( chan_count * samples_per_chan );
    size_t read_bytes = fread( all_channels.data(), 1, header.subchunk2Size, f );
    if ( read_bytes != header.subchunk2Size ) {
        printf( "extract_data_int16() read only %zu of %u\n", read_bytes, header.subchunk2Size );
        throw new IO_ERROR();
    }
   // fclose( f );


    // 2. Put all channels to its own vector.
    channels_data.resize( chan_count );
    for ( size_t ch = 0; ch < channels_data.size(); ch++ ) {
        channels_data[ ch ].resize( samples_per_chan );
    }

    for ( int ch = 0; ch < chan_count; ch++ ) {
        std::vector<short>& chdata = channels_data[ ch ];
        for ( size_t i = 0; i < samples_per_chan; i++ ) {
            chdata[ i ] = all_channels[ chan_count * i + ch ];
        }
    }
}

void WavData::IsHeaderCorrect(size_t file_size_bytes) 
{
    // Go to wav_header.h for details

    if ( header.chunkId[0] != 'R' ||
         header.chunkId[1] != 'I' ||
         header.chunkId[2] != 'F' ||
         header.chunkId[3] != 'F' )
    {
		throw new HEADER_RIFF_ERROR();
    }

    if ( header.chunkSize != file_size_bytes - 8 ) {
        throw new HEADER_FILE_SIZE_ERROR();
    }

    if ( header.format[0] != 'W' ||
         header.format[1] != 'A' ||
         header.format[2] != 'V' ||
         header.format[3] != 'E' )
    {
        throw new HEADER_WAVE_ERROR();
    }

    if ( header.subchunk1Id[0] != 'f' ||
         header.subchunk1Id[1] != 'm' ||
         header.subchunk1Id[2] != 't' ||
         header.subchunk1Id[3] != ' ' )
    {
        throw new HEADER_FMT_ERROR();
    }

    if ( header.audioFormat != 1 ) {
        throw new HEADER_NOT_PCM();
    }

    if ( header.subchunk1Size != 16 ) {
        throw new HEADER_SUBCHUNK1_ERROR();
    }

    if ( header.byteRate != header.sampleRate * header.numChannels * header.bitsPerSample/8 ) {
        throw new HEADER_BYTES_RATE_ERROR();
    }

    if ( header.blockAlign != header.numChannels * header.bitsPerSample/8 ) {
        throw new HEADER_BLOCK_ALIGN_ERROR();
    }

    if ( header.subchunk2Id[0] != 'd' ||
         header.subchunk2Id[1] != 'a' ||
         header.subchunk2Id[2] != 't' ||
         header.subchunk2Id[3] != 'a' )
    {
        throw new HEADER_FMT_ERROR();
    }

    if ( header.subchunk2Size != file_size_bytes - 44 )
    {
        throw new HEADER_SUBCHUNK2_SIZE_ERROR;
    }
}

void WavData::SetDefault()
{
    // Go to wav_header.h for details

    header.chunkId[0] = 'R';
    header.chunkId[1] = 'I';
    header.chunkId[2] = 'F';
    header.chunkId[3] = 'F';

    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';

    header.subchunk1Id[0] = 'f';
    header.subchunk1Id[1] = 'm';
    header.subchunk1Id[2] = 't';
    header.subchunk1Id[3] = ' ';

    header.subchunk2Id[0] = 'd';
	header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';

    header.audioFormat   = 1;
    header.subchunk1Size = 16;
    header.bitsPerSample = 16;

}

void WavData::SetWavParam(int chan_count, int bits_per_sample, int sample_rate, int samples_count_per_chan)
{
    if ( bits_per_sample != 16 ) {
        throw new UNSUPPORTED_FORMAT;
    }

    if ( chan_count < 1 ) {
        throw new BAD_PARAMS;
    }

	SetDefault();

    int file_size_bytes = 44 + chan_count * (bits_per_sample/8) * samples_count_per_chan;

    header.sampleRate    = sample_rate;
    header.numChannels   = chan_count;
    header.bitsPerSample = 16;

    header.chunkSize     = file_size_bytes - 8;
    header.subchunk2Size = file_size_bytes - 44;

    header.byteRate      = header.sampleRate * header.numChannels * header.bitsPerSample/8;
    header.blockAlign    = header.numChannels * header.bitsPerSample/8;

}

void WavData::SaveToFile(const char* filename)
{
    printf( ">>>> make_wav_file( %s )\n", filename );

    int chan_count = (int)channels_data.size();

    if ( chan_count < 1 ) {
        throw new BAD_PARAMS();
    }

    int samples_count_per_chan = (int)channels_data[0].size();

    // Verify that all channels have the same number of samples.
    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( channels_data[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw new BAD_PARAMS;
        }
    }

    SetWavParam( chan_count, 16, header.sampleRate, samples_count_per_chan );

    std::vector<short> all_channels;
    all_channels.resize( chan_count * samples_count_per_chan );

    for ( int ch = 0; ch < chan_count; ch++ ) {
        const std::vector<short>& chdata = channels_data[ ch ];
        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            all_channels[ chan_count * i + ch ] = chdata[ i ];
        }
    }

    FILE* f = fopen( filename, "wb" );
    fwrite( &header, sizeof(wav_header_s), 1, f );
    fwrite( all_channels.data(), sizeof(short), all_channels.size(), f );
    if ( !f ) {
        throw new IO_ERROR;
    }

    fclose( f );

}

void WavData::ConvertStereoToMono()
{
	//source = chan
	//edit = dest
    int chan_count = (int)channels_data.size();

    if ( chan_count != 2 ) {
        throw new BAD_PARAMS;
    }

    int samples_count_per_chan = (int)channels_data[0].size();

    // Verify that all channels have the same number of samples.
    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( channels_data[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw new BAD_PARAMS;
        }
    }
	std::vector< std::vector <short>> channels_data_copy(channels_data);
	//может перед этим channnels ещё и обнулить
    channels_data.resize( 1 );
    std::vector<short>& mono = channels_data[ 0 ];
    mono.resize( samples_count_per_chan );

    // Mono channel is an arithmetic mean of all (two) channels.
    for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
        mono[ i ] = ( channels_data_copy[0][i] + channels_data_copy[1][i] ) / 2;
    }

}

void WavData::ApplyReverb(double delay_seconds, float decay)
{
	std::vector<std::vector<short>>& sounds = channels_data;
    int chan_count = (int)sounds.size();

    if ( chan_count < 1 ) {
        throw new BAD_PARAMS;
    }

    int samples_count_per_chan = (int)sounds[0].size();

    // Verify that all channels have the same number of samples.
    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( sounds[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw new BAD_PARAMS;
        }
    }

    int delay_samples = (int)(delay_seconds * header.sampleRate);


    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        std::vector<float> tmp;
        tmp.resize(sounds[ch].size());

        // Convert signal from short to float
        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            tmp[ i ] = sounds[ ch ][ i ];
        }

        // Add a reverb
        for ( size_t i = 0; i < samples_count_per_chan - delay_samples; i++ ) {
            tmp[ i + delay_samples ] += decay * tmp[ i ];
        }

        // Find maximum signal's magnitude
        float max_magnitude = 0.0f;
        for ( size_t i = 0; i < samples_count_per_chan - delay_samples; i++ ) {
            if ( abs(tmp[ i ]) > max_magnitude ) {
                max_magnitude = abs(tmp[ i ]);
            }
        }

        // Signed short can keep values from -32768 to +32767,
        // After reverb, usually there are values large 32000.
        // So we must scale all values back to [ -32768 ... 32768 ]
        float norm_coef = 30000.0f / max_magnitude;
        printf( "max_magnitude = %.1f, coef = %.3f\n", max_magnitude, norm_coef );

        // Scale back and transform floats to shorts.
        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            sounds[ ch ][ i ] = (short)(norm_coef * tmp[ i ]);
        }
    }

}

bool WavData::isStereo() {
	if ((int)channels_data.size() == 2) return true;
	else return false;
}

void WavData::ChangeSampleRate(float new_rate) {
	int chan_count = (int)channels_data.size();
	int samples_count_per_chan = (int)channels_data[0].size();
	SetWavParam(chan_count, 16, new_rate, samples_count_per_chan);
}

//Решение подсмотрела у товарища: https://github.com/toshiks/OOP/blob/master/OOP_3/src/WAV/Wav.cpp

void WavData::CutEnd(float seconds) {
	float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
	if (fDurationSeconds < seconds) throw new LIMIT_EXCEED();
	float byteRate = header.byteRate / header.numChannels;
	float curByte = (byteRate*seconds) / sizeof(short);

	for (size_t ch = 0; ch < channels_data.size(); ch++) {
		std::vector<short> &tmp = channels_data[ch];
		for (int i = 0; i < curByte; i++)
			tmp.pop_back();
	}
	//обрезать то значение, которое строго меньше размера файла
}

void WavData::CutBegin(float seconds) {
	float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
	if (fDurationSeconds < seconds) throw new LIMIT_EXCEED();
	float byteRate = header.byteRate / header.numChannels;
	float curByte = (byteRate*seconds) / sizeof(short);

	for (size_t ch = 0; ch < channels_data.size(); ch++) {
		std::vector<short> &tmp = channels_data[ch];
		std::reverse(tmp.begin(), tmp.end());
		for (int i = 0; i < curByte; i++)
			tmp.pop_back();
		std::reverse(tmp.begin(), tmp.end());
	}
}