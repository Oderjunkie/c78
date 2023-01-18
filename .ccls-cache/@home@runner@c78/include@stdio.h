typedef struct FILE {} FILE;
extern int printf();
extern int fprintf();
extern FILE *fopen();
extern char* fgets();
extern int fgetc();
extern char* fputs();
extern int fputc();
extern int fclose();
/* stdin */
/* stderr */
/* stdout */
#define getc(stream) fgetc(stream)
#define putc(char, stream) fputc(char, stream)
/* #define putchar(char) putc(char, stdout) */
/* #define getchar(char) getc(stdout) */
extern int unget();