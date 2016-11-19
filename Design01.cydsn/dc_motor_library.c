#include <dc_motor_library.h>

void set_register(int8 *motor_values)
{
    int counter = 7;
     while (counter>=0)
     {
         if (!Clock_Read())
         {
            Data_Write(motor_values[counter]);
            Fix_Write(0);
            Clock_Write(1);
            CyDelay(20);
         }
         else
         {
            Clock_Write(0);
            Fix_Write(1);
            counter--;
         }
    }
}
void activate_motor(int8 **motor,short id,short mode)
{
    if (id==1)
    {
        pwm_Write(1);
        switch (mode)
        {
            case 0: (*motor)[2] = 1;break;
            case 1: (*motor)[3] = 1;break;
        }
    }
    else if (id ==2)
    {
        pwm2_Write(1);
        switch (mode)
        {   
            case 0: (*motor)[1] = 1;break;
            case 1: (*motor)[4] = 1;break;
        }
    }
    else if (id ==3)
    {
        pwm3_Write(1);
        switch (mode)
        {
            case 0: (*motor)[0] = 1;break;
            case 1: (*motor)[6] = 1;break;
        }
    }
    else if (id==4)
    {
        pwm4_Write(1);
        switch(mode)
        {
            case 0: (*motor)[5] = 1;break;
            case 1: (*motor)[7] = 1;break;
        }
    }
    return;
}

void clear_motor_register(int8 *motor)
{
    int8 counter = 7;
     while (counter!=0)
     {
         if (!Clock_Read())
         {
            Data_Write(motor[counter]);
            Fix_Write(0);
            Clock_Write(1);
            CyDelay(20);
         }
         else
         {
            Clock_Write(0);
            Fix_Write(1);
            counter--;
         }
    }
    return;
}

