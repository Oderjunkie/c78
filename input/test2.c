#define x

main()
{
  printf(
#ifdef x
    "Hello, World!\n"
#else
    "...Fuck!\n"
#endif
  );
}