#ifndef _CIRCULAR_BUF_H_
#define _CIRCULAR_BUF_H_

#define CBUF_SIZ 64

typedef struct {
  unsigned char buf[CBUF_SIZ];
  unsigned int start;
  unsigned int end;
  unsigned int size;
} circular_buf_t;

int cb_is_empty(circular_buf_t *cbuf);
int cb_is_full(circular_buf_t *cbuf);
int cb_bytes_left(circular_buf_t *cbuf);

/* returns how much bytes were indeed written/red */
int cb_read(circular_buf_t *cbuf, unsigned char *into_buf, int len);
int cb_write(circular_buf_t *cbuf, unsigned char *from_buf, int len);

#endif
