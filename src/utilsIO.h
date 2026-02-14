#ifndef UTILSIO_H
#define UTILSIO_H

#define BUFFER_SIZE 300u
#define MAX_ITERATION_ALLOWED 10000u

#define FGETS(FILE_PTR)		io_buffer.out_fgets = fgets(io_buffer.buf, BUFFER_SIZE, FILE_PTR); \
							io_buffer.ptr = io_buffer.buf; \
        					io_buffer.iteration++; \
							if (!io_buffer.out_fgets) { \
								break; \
							}


typedef struct io_buffer_s 
{
	char buf[BUFFER_SIZE];
	char* ptr;
	char* out_fgets;
	size_t iteration;
	int count;
} io_buffer_t;

void set_io_buffer(io_buffer_t* p_io_buffer);

#endif // UTILSIO_H
