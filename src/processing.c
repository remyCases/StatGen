#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "processing.h"
#include "utilsIO.h"

extern void compute_array_fortran_(float*, int*, float*);
extern void sum_matrixes_(int*, int*, int*, int*);

#define NB_BYTES 256

typedef struct seq_s
{
	uint8_t *tokens;
	uint64_t len;
} seq_t;

int init_seq(seq_t* p_seq, uint64_t len)
{
	p_seq->tokens = (uint8_t*)calloc(len, sizeof(uint8_t));
	p_seq->len = len;

	return !!p_seq->tokens;
}

void free_seq(seq_t* p_seq)
{
	free(p_seq->tokens);
}

void print_entry(char* buf)
{
	for(;*buf;buf++)
	{
		printf("%02X ", (uint8_t)*buf);
	}
	printf("\n");
}

void print_frequency(uint64_t frequency[NB_BYTES])
{
	for(int byte = 0; byte < NB_BYTES; byte++)
	{
		if (!frequency[byte]) continue;
		printf("%02X : %llu\n", byte, frequency[byte]);
	}
}

void print_vocab(uint8_t vocab[NB_BYTES], uint8_t vocab_size)
{
	printf("Tokens:\n");
	for(int byte = 0; byte < vocab_size; byte++)
	{
		printf("%02X\n", vocab[byte]);
	}
}

void set_vocab(uint8_t vocab[NB_BYTES], uint8_t reverse_vocab[NB_BYTES], uint64_t frequency[NB_BYTES], uint8_t* vocab_size)
{
	for(int byte = 0; byte < NB_BYTES; byte++)
	{
		if (!frequency[byte]) continue;
		vocab[byte] = *vocab_size;
		reverse_vocab[*vocab_size] = byte;
		(*vocab_size)++;
	}
}

int run_rnn() 
{
	FILE* fp = fopen("data/names_test", "r");

	uint64_t frequency[NB_BYTES] = { 0 };
	memset(frequency, 0, NB_BYTES*sizeof(uint64_t));
	uint8_t vocab[NB_BYTES] = { 0 };
	memset(vocab, 0xFF, NB_BYTES*sizeof(uint8_t));
	uint8_t reverse_vocab[NB_BYTES] = { 0 };
	memset(reverse_vocab, 0, NB_BYTES*sizeof(uint8_t));
	uint8_t vocab_size = 0;

	if (!fp) 
	{
		return EXIT_FAILURE;
	}

	io_buffer_t io_buffer = { 0 };
    set_io_buffer(&io_buffer);
	while(io_buffer.iteration < MAX_ITERATION_ALLOWED)
	{
		FGETS(fp);
		print_entry(io_buffer.ptr);

		for(;*io_buffer.ptr;io_buffer.ptr++)
		{
			frequency[(uint8_t)*io_buffer.ptr]++;
		}
	}
	
	if (io_buffer.iteration == MAX_ITERATION_ALLOWED) 
	{
        printf("Max iteration allowed (%u), result can be false.\n", MAX_ITERATION_ALLOWED);
    }

	set_vocab(vocab, reverse_vocab, frequency, &vocab_size);
	print_vocab(reverse_vocab, vocab_size);

	if (fclose(fp))
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
