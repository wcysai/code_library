const int STK_SZ = 2000000;
char STK[STK_SZ * sizeof(void*)];     
void *STK_BAK;

#if defined(__i386__)
#define SP "%%esp"
#elif defined(__x86_64__)
#define SP "%%rsp"
#endif

int main() {
  asm volatile("mov " SP ",%0; mov %1," SP: "=g"(STK_BAK):"g"(STK+sizeof(STK)):);
  
  // main program
  
  asm volatile("mov %0," SP::"g"(STK_BAK));
  return 0;
}
