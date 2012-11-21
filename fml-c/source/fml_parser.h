#pragma once

// Copyright (C) 2012 John Judnich
// Released as open-source under The MIT Licence.

// This parser runs entirely in-place with no heap allocations whatosever.
// A memory buffer is given to the parser. The parser then reads through it on demand
// and may modify it (e.g. collapsing escape codes). Returned tokens reference memory
// within the original buffer, as no copying occurs. You retain allocation ownership 
// of the data though the parser may modify it in the process of parsing it. Free
// it yourself when you're done however you like. This way, you can close an fml_stream 
// without invalidating any token values extracted from it.

#include <ctype.h>

struct fml_stream
{
	char *data;
	size_t data_size;
	size_t index;
};

enum FML_TOKEN_TYPE
{
	FML_TOKEN_ERROR = 0, FML_TOKEN_EOF = 1,
	FML_TOKEN_OPEN = 2, FML_TOKEN_CLOSE = 3, FML_TOKEN_DIVIDER = 4, FML_TOKEN_ITEM = 5
};

struct fml_token
{
	enum FML_TOKEN_TYPE type;
	const char *value;
	size_t value_size;
	size_t offset;
};

struct fml_stream fml_stream_open(char *data, size_t data_size);
void fml_stream_close(struct fml_stream *stream);

struct fml_token fml_stream_pop(struct fml_stream *stream);




