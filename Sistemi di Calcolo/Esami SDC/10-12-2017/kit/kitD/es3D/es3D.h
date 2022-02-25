#ifndef __ES3D__
#define __ES3D__

typedef struct charset charset;

charset* charset_new      ();
void     charset_add      (charset* s, unsigned char c);
int      charset_contains (charset* s, unsigned char c);
void     charset_delete   (charset* s);

#endif
