#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void separator(char *s)
{
    printf("\n==============================\n");
    printf("%s\n", s);
    printf("==============================\n");
}

/* Test 1 */
void test_variable(void)
{
    separator("TEST 1 : Variable Restore");

    int x = 10;

    printf("before checkpoint x=%d\n", x);

    if(checkpoint(0) == 0){
        x = 99;
        printf("modified x=%d\n", x);
        restore(0);
    }else{
        printf("after restore x=%d\n", x);
    }
}

/* Test 2 */
void test_epc(void)
{
    separator("TEST 2 : Execution Point");

    if(checkpoint(0) == 0){
        printf("SAVE EPC\n");
        restore(0);
    }else{
        printf("RESTORE EPC\n");
    }
}

/* Test 3 */
void test_kernel(void)
{
    separator("TEST 3 : Kernel Stability");

    printf("Kernel still alive.\n");
}

/* Test 4 */
void test_heap(void)
{
    separator("TEST 4 : Heap");

    char *p = malloc(100);

    strcpy(p,"Operating Systems");

    if(checkpoint(0)==0){
        strcpy(p,"Changed");
        restore(0);
    }else{
        printf("%s\n",p);
    }

    free(p);
}

/* Test 5 */
void stackfunc(void)
{
    int a=123;

    if(checkpoint(0)==0){
        a=999;
        restore(0);
    }else{
        printf("Stack=%d\n",a);
    }
}

void test_stack(void)
{
    separator("TEST 5 : Stack");
    stackfunc();
}


/* Test 6 */
void test_overwrite(void)
{
    separator("TEST 6 : Overwrite Checkpoint");

    checkpoint(0);

    printf("first checkpoint\n");

    checkpoint(0);

    printf("second checkpoint on same slot\n");
}

/* Test 7 */
void test_file(void)
{
    separator("TEST 7 : File");

    int fd;
    char buf[32];

    fd=open("a",O_CREATE|O_RDWR);

    write(fd,"ABC",3);

    if(checkpoint(0)==0){
        write(fd,"DEF",3);
        restore(0);
    }

    write(fd,"XYZ",3);

    close(fd);

    fd=open("a",O_RDONLY);

    int n=read(fd,buf,sizeof(buf)-1);

    buf[n]=0;

    printf("file=%s\n",buf);

    close(fd);
}


/* Test 8 */
void test_invalid_restore(void)
{
    separator("TEST 8 : Invalid Restore");

    printf("restore(5)=%d\n",restore(5));
}

/* Test 9 */
void test_invalid_checkpoint(void)
{
    separator("TEST 9 : Invalid Checkpoint");

    printf("checkpoint(10)=%d\n",checkpoint(10));
}

int
main(void)
{
    test_variable();

    test_epc();

    test_kernel();

    test_heap();

    test_stack();

    test_overwrite();

    test_file();

    test_invalid_restore();

    test_invalid_checkpoint();

    printf("\nAll tests finished.\n");

    exit(0);
}