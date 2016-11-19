
#include <project.h>
#include <dc_motor_library.h>
#include <malloc.h>

int main()
{
    int8 *motor_values = (int8 *)malloc(8*sizeof(int8));
    motor_values[0] = 0;
    motor_values[1] = 0;
    motor_values[2] = 0;
    motor_values[3] = 0;
    motor_values[4] = 0;
    motor_values[5] = 0;
    motor_values[6] = 0;
    motor_values[7] = 0;
    CyGlobalIntEnable; /* Enable global interrupts. */
    pwm_Write(0);
    pwm2_Write(0);
    pwm3_Write(0);
    pwm4_Write(0);
    Data_Write(1);
    Clock_Write(0);
    Fix_Write(0);
    clear_motor_register(motor_values);
    activate_motor(&motor_values,1,0);
   // activate_motor(&motor_values,2,0);
    set_register(motor_values);
    for(;;)
    {
        /* Place your application code here. */
    }
    free(motor_values);
}

/* [] END OF FILE */
