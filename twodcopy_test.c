#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWOD_COPY_SYSCALL 451

int main()
{


    float testCaseArray[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

    float generatedArray[3][3];

    long sys_call_status;

    sys_call_status = syscall(TWOD_COPY_SYSCALL, testCaseArray, generatedArray);

    if (sys_call_status != EFAULT)
    {
        printf("System Call 451 twodcopy_system_call was successfuly invoked \n");
        printf("TestCaseArray was - \n");

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                printf("%f ", testCaseArray[i][j]);
            }
            printf("\n");
        }

        printf("CopiedArray was - \n");

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                printf("%f ", generatedArray[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
