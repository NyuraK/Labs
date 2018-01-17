#ifndef WAV_CORE_H
#define WAV_CORE_H
#include<exception>

class IO_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "IO_ERROR\n";
	};
};
class BAD_PARAMS : public std::exception {
	virtual const char* what() const throw() {
		return "BAD_PARAMS\n";
	};
};
class BAD_FORMAT : public std::exception {
	virtual const char* what() const throw() {
		return "BAD_FORMAT\n";
	};
};
class UNSUPPORTED_FORMAT : public std::exception {
	virtual const char* what() const throw() {
		return "UNSUPPORTED_FORMAT: Only 16-bit samples is supported\n";
	};
};

class LIMIT_EXCEED : public std::exception {
	virtual const char* what() const throw() {
		return "Duration is lesser than cutting time\n";
	};
};

//HEADER
class HEADER_RIFF_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_RIFF_ERROR\n";
	};
};
class HEADER_FILE_SIZE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_FILE_SIZE_ERROR\n";
	};
};
class HEADER_WAVE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_WAVE_ERROR\n";
	};
};
class HEADER_FMT_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_FMT_ERROR\n";
	};
};
class HEADER_NOT_PCM : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_NOT_PCM\n";
	};
};
class HEADER_SUBCHUNK1_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_SUBCHUNK1_ERROR\n";
	};
};
class HEADER_BYTES_RATE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_BYTES_RATE_ERROR\n";
	};
};
class HEADER_BLOCK_ALIGN_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_BLOCK_ALIGN_ERROR\n";
	};
};
class  HEADER_SUBCHUNK2_SIZE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return " HEADER_SUBCHUNK2_SIZE_ERROR\n";
	};
};
#endif // WAV_CORE_H
