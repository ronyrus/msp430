#include "circular_buf.h"

int inline cb_is_empty(circular_buf_t *cbuf)
{
  return !cbuf->size;
}

int inline cb_is_full(circular_buf_t *cbuf)
{
  return cbuf->size == CBUF_SIZ;
}

int inline cb_bytes_left(circular_buf_t *cbuf)
{
  return CBUF_SIZ - cbuf->size;
}

int cb_read(circular_buf_t *cbuf, unsigned char *into_buf, int len)
{
	int i, bytes_processed;

	if (len > cbuf->size)
		len = cbuf->size;

	bytes_processed = len;
	cbuf->size -= len;

	for (i = 0; i < len; i++)
	{
		*into_buf = cbuf->buf[cbuf->start];
		cbuf->start = (cbuf->start + 1) % CBUF_SIZ;
		into_buf++;
	}

	return bytes_processed;
}

int cb_write(circular_buf_t *cbuf, unsigned char *from_buf, int len)
{
	int i, bytes_processed;

	if (len > cb_bytes_left(cbuf))
		len = cb_bytes_left(cbuf);

	bytes_processed = len;
	cbuf->size += len;

	for (i = 0; i < len; i++)
	{
		cbuf->buf[cbuf->end] = *from_buf;
		cbuf->end = (cbuf->end + 1) % CBUF_SIZ;
		from_buf++;
	}

	return bytes_processed;
}
