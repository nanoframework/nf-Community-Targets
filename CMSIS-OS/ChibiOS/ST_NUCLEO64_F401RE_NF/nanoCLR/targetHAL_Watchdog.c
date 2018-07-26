//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
#if (HAL_USE_WDG == TRUE) 

#include <hal.h>
#include <nanoHAL_Watchdog.h>
#include <targetHAL_Watchdog.h>
#include <swo.h>

//Watchdog configuration structure required by ChibiOS
static WDGConfig wdgConfig = {STM32_IWDG_PR_256,STM32_IWDG_RL(0xFFF)}; //default is max for this MCU (~32 sec)

/**
* Method to initialize the watchdog. Watchdog must be initialized 
* only once (when the system starts, generally in main after system and HAL initialization).
* Since this is ChibiOS, watchdog is initialized by the halInit() method itself. 
* There is no need to call this function in ChibiOS based implementations.
*/
void Watchdog_Init()
{
    Watchdog_SetMaxTimeout(); //reset to default
}

/**
 * Start the watchdog. If watchdog timeout is not set using the "SetTimeout/SetMaxTimeout" method
 * then for the first time, the highest timeout is used. After that, the last
 * timeout value set is used.
 * @return  true when watchdog started successfully else false
 */ 
bool Watchdog_Start()
{
    wdgStart(&WDGD1,&wdgConfig);
    SwoPrintString("Watchdog started...\r\n");
    return true;
}

/**
 * Stop the watchdog
 */  
void Watchdog_Stop()
{
    wdgStop(&WDGD1);
}
/**
 * Reset the watchdog. If not done without the timout period,
 * the watchdog will trigger and MCU will reset
 */ 
void Watchdog_Reset()
{    
    wdgReset(&WDGD1);
}
/**
 * Check if watchdog is running
 * @return  bool    true if watchdog is running else false
 */ 
bool Watchdog_IsRunning()
{
    return(WDGD1.state == WDG_READY);
}
/**
 * Set the watchdog timeout. This must be called before watchdog is 
 * started. The minimum timeout supported in this implementation is
 * approx.1 ms and the maximum timeout is approx 32768 ms.
 * Remember, timeout is always an approximation and not exact due to LSI clock approximation.
 * If the required timeout value is beyond this range, then it is adjusted accordingly.
 * @param   timeoutMillis   The timeout in milliseconds. 
 */ 
void Watchdog_SetTimeout(uint16_t timeoutMillis)
{
 
    if(timeoutMillis < MIN_TIMEOUT_SUPPORTED_MILLIS)
        timeoutMillis = MIN_TIMEOUT_SUPPORTED_MILLIS;
    else if(timeoutMillis > MAX_TIMEOUT_SUPPORTED_MILLIS)
        timeoutMillis = MAX_TIMEOUT_SUPPORTED_MILLIS;
    
    uint16_t timeoutBoundary = 512;
    uint16_t counter=0;
    uint16_t prescaler[] = {STM32_IWDG_PR_4,STM32_IWDG_PR_8,STM32_IWDG_PR_16,
                            STM32_IWDG_PR_32,STM32_IWDG_PR_64,STM32_IWDG_PR_128,
                            STM32_IWDG_PR_256};
    uint16_t dividor = 4;
    while(timeoutBoundary <= MAX_TIMEOUT_SUPPORTED_MILLIS)
    {
        if(timeoutMillis <= timeoutBoundary)
        {            
            wdgConfig.pr = prescaler[counter];
            dividor = dividor << wdgConfig.pr;
            wdgConfig.rlr= (uint32_t)((IWATCHDOG_CLK_TYPICAL / dividor) * (timeoutMillis / 1000));
            if(wdgConfig.rlr > 0xFFF) wdgConfig.rlr = 0xFFF;//limit to max reload value
            break;
        }
        else
        {
            timeoutBoundary = timeoutBoundary << 1;
            counter++;
        }
    }  
}
/**
 * Set the maximum timeout allowed for the platform.
 * For this platform STM32F401xYY the max is approximately 32 secs
 */ 
void Watchdog_SetMaxTimeout()
{
    wdgConfig.pr = STM32_IWDG_PR_256;
    wdgConfig.rlr= STM32_IWDG_RL(0xFFF);
}
#endif
