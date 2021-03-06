/*                                 SUCHAI
 *                      NANOSATELLITE FLIGHT SOFTWARE
 *
 *      Copyright 2013, Tomas Opazo Toro, tomas.opazo.t@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cmdTHK.h"

cmdFunction thkFunction[THK_NCMD];
int thk_sysReq[THK_NCMD];

void thk_onResetCmdTHK(){
    printf("        thk_onResetCmdTHK\n");

    int i;
    for(i=0; i<THK_NCMD; i++) thk_sysReq[i] = CMD_SYSREQ_MIN;

    //De display
    thkFunction[(unsigned char)thk_id_debug] = thk_debug;

    thkFunction[(unsigned char)thk_id_executeBeforeFlight] = thk_executeBeforeFlight;
    thkFunction[(unsigned char)thk_id_debug2] = thk_debug2;
    
    thkFunction[(unsigned char)thk_id_silent_time_and_pictures] = thk_silent_time_and_pictures;
    thkFunction[(unsigned char)thk_id_get_AntSwitch_isOpen] = thk_get_AntSwitch_isOpen;
    thkFunction[(unsigned char)thk_id_deployment_registration] = thk_deployment_registration;

    thkFunction[(unsigned char)thk_id_get_dep_ant_deployed] = thk_get_dep_ant_deployed;
    thkFunction[(unsigned char)thk_id_get_dep_ant_tries] = thk_get_dep_ant_tries;
    thkFunction[(unsigned char)thk_id_get_dep_year] = thk_get_dep_year;
    thkFunction[(unsigned char)thk_id_get_dep_month] = thk_get_dep_month;
    thkFunction[(unsigned char)thk_id_get_dep_week_day] = thk_get_dep_week_day;
    thkFunction[(unsigned char)thk_id_get_dep_day_number] = thk_get_dep_day_number;
    thkFunction[(unsigned char)thk_id_get_dep_hours] = thk_get_dep_hours;
    thkFunction[(unsigned char)thk_id_get_dep_minutes] = thk_get_dep_minutes;
    thkFunction[(unsigned char)thk_id_get_dep_seconds] = thk_get_dep_seconds;

    //Power budget restriction
    thkFunction[(unsigned char)thk_id_deploy_antenna] = thk_deploy_antenna;
    thk_sysReq[(unsigned char)thk_id_deploy_antenna]  = CMD_SYSREQ_MIN + SCH_DEPLOYMENT_SYS_REQ;
    thkFunction[(unsigned char)thk_id_suchai_deployment] = thk_suchai_deployment;
    thk_sysReq[(unsigned char)thk_id_suchai_deployment]  = CMD_SYSREQ_MIN + SCH_DEPLOYMENT_SYS_REQ;

}

//------------------------------------------------------------------------------
int thk_debug(void *param){
    unsigned int address=0;
    unsigned int data=0x1000;

    printf("(Destructive) Testing memEEPROM\r\n");
    for(address=MEP_FIRST_ADDR; address<=MEP_LAST_ADDR; address++, data++){
        //con_printf("testing address j="); Hex16ToAscii( address); con_printf(buffer); con_printf("\n");

        printf("writing: ");
        writeIntEEPROM1(address, data);
        printf("value[%d] = %d \r\n", address, data);

        printf("reading: ");
        unsigned int res = readIntEEPROM1(address);
        printf("value[%d] = %d \r\n", address, res);

        printf("comparing: ");
        if(data==res){ printf("ok\r\n"); }
        else{ printf("fail\r\n"); }
    }

    unsigned int indxVar;
    data = -1;  //0xFFFF

    for(indxVar=MEP_FIRST_ADDR; indxVar<=MEP_LAST_ADDR; indxVar++){
        writeIntEEPROM1(indxVar, data);
    }

    return 1;
}

//-----------------------------------------------------
int thk_get_dep_ant_deployed(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_ant_deployed;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_ant_tries(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_ant_tries;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
//rtc
int thk_get_dep_year(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_year;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_month(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_month;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_week_day(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_week_day;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_day_number(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_day_number;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_hours(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_hours;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_minutes(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_minutes;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}
int thk_get_dep_seconds(void* param){
    MemEEPROM_Vars mem_eeprom_var = mem_dep_seconds;
    int res = readIntEEPROM1(mem_eeprom_var);
    return res;
}

//
//int thk_set_dep_ant_deployed(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_ant_deployed;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_ant_tries(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_ant_tries;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_year(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_year;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_month(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_month;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_week_day(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_week_day;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_day_number(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_day_number;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_hours(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_hours;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_minutes(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_minutes;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//int thk_set_dep_seconds(void* param){
//    MemEEPROM_Vars mem_eeprom_var = mem_dep_seconds;
//    int value = *((int*)param);
//    writeIntEEPROM1(mem_eeprom_var, value);
//    return 1;   //se asume operacion exitosa
//}
//------------------------------------------------------------------------------
int thk_suchai_deployment(void *param)
{
    printf("[thk_suchai_deployment] Suchai deployment routine..\r\n");
    
    int delay_min = *( (int*)param );
//    portTickType xLastWakeTime = xTaskGetTickCount();
//    portTickType delay_60s    = 60000;    //Task period in [ms]
//    portTickType delay_tick_60s = delay_60s / portTICK_RATE_MS; //Task period in ticks

    unsigned long initial_tick_10ms = xTaskGetTickCount(); //get initial tick-time
    //unsigned long silent_time_10ms = (180000);     // 30 minutes = 1800 sec = 180000 [10ms]
    unsigned long silent_time_10ms = delay_min*60*100; // time_s*100 [ms] = time_ms
    unsigned long final_tick_10ms = initial_tick_10ms + silent_time_10ms;

    printf("[thk_suchai_deployment] initial_tick_10ms = %lu | final_tick_10ms = %lu \r\n", initial_tick_10ms, final_tick_10ms);

    // print rtc time
    rtc_print(NULL);

    //take picture
    #if(SCH_PAY_CAM_nMEMFLASH_ONBOARD==1 )
        #if(SCH_THK_SILENT_REALTIME==1)
            pay_takePhoto_camera(NULL); //takes 10min to complete
        #else
            printf("  Jumping pay_takePhoto_camera(NULL) call, it takes 10min to complete ..\r\n");
        #endif
    #endif

    // print rtc time
    rtc_print(NULL);

    unsigned int elapsed_mins = 0;
    while(TRUE){
        unsigned long int cu_tick_10ms = xTaskGetTickCount();
        if( cu_tick_10ms >= final_tick_10ms || elapsed_mins>35 ){
            printf("[thk_suchai_deployment] Waiting timeout, cu_tick_10ms = %lu, elapsed_mins = %d\r\n", cu_tick_10ms, elapsed_mins);
            break;
        }
        printf("[thk_suchai_deployment] Waiting for timeout, cu_tick_10ms = %lu, elapsed_mins = %d\r\n", cu_tick_10ms, elapsed_mins);
        //vTaskDelayUntil(&xLastWakeTime, delay_tick_60s); //Suspend task 60 sec
        ClrWdt();
        __delay_ms(60000);  //delay 60sec
        elapsed_mins++;

    }

    // print rtc time
    rtc_print(NULL);

    /* Deploy Antena */
    #if (SCH_ANTENNA_ONBOARD==1)
        int rt_mode = SCH_THK_ANT_DEP_REALTIME; /* 1=Real Time, 0=Debug Time */
        thk_deploy_antenna(&rt_mode);
    #endif

    // print rtc time
    rtc_print(NULL);

    ClrWdt();
    __delay_ms(60000);  //delay 60sec to avoid drain-out the EPS

    /* Ceploy langmuir should NOT be here, but there is no way
     * to check deployment, so its included here */
    #if (SCH_ANTENNA_ONBOARD==1 && SCH_PAY_LANGMUIR_ONBOARD==1)
        if( sta_get_stateVar(sta_pay_lagmuirProbe_isDeployed)==0 ){
            int rt_mode = SCH_THK_ANT_DEP_REALTIME; /* 1=Real Time, 0=Debug Time */
            pay_deploy_langmuirProbe(rt_mode);    //realtime mode
            //set var lang dep = 1
        }
    #endif

    //other "only once"-tasks
    //..

    return 1;
}

#define THK_SILENT_TIME_MIN 30          ///< cuantos "minutos" (65,535[s]) estara en inactividad antes de iniciarse
#define THK_MAX_TRIES_ANT_DEPLOY 10               ///< cuantas veces tratara desplegar la antena antes de anunciar fracaso
#define THK_DEPLOY_TIME 45311          ///< 2*THK_DEPLOY_TIME/1000 indica cuantos "ms" estara activo el bus de 3.3V quemando el nilon
#define THK_REST_DEPLOY_TIME 5000       ///< cuantos "ms" estara inactivo el bus de 3.3V descanzando de tratar de quemar el nilon
#define THK_RECHECK_TIME 2000           ///< despues de cuantos "ms" RE-chequeara que efectivamente se desplego la antena
/**
 * Deploys satellite antennas
 * @param param 1 realime, 0 debug time
 * @return 1 success, 0 fails
 */
int thk_deploy_antenna(void *param)
{
    #if (SCH_TASKDEPLOYMENT_VERBOSE>=1)
        printf("\n[thk_deploy_antenna] Deploying TRX Antenna... \r\n");
        //rtc_print(NULL);
    #endif

    //Realtime=1 DebugTime=0
    unsigned int delay_dep_time, delay_rest_dep_time, delay_recheck_dep_time;
    int mode= *( (int *)param );
    if(mode)
    {
//        delay_dep_time = (THK_DEPLOY_TIME) / portTICK_RATE_MS;
//        delay_rest_dep_time = (THK_REST_DEPLOY_TIME) / portTICK_RATE_MS;
//        delay_recheck_dep_time = (THK_RECHECK_TIME) / portTICK_RATE_MS;
        delay_dep_time = (THK_DEPLOY_TIME);
        delay_rest_dep_time = (THK_REST_DEPLOY_TIME);
        delay_recheck_dep_time = (THK_RECHECK_TIME);
    }
    else
    {
//        delay_dep_time = (600) / portTICK_RATE_MS;
//        delay_rest_dep_time = (400) / portTICK_RATE_MS;
//        delay_recheck_dep_time = (200) / portTICK_RATE_MS;
        delay_dep_time = (600);
        delay_rest_dep_time = (400);
        delay_recheck_dep_time = (200);
    }
    
    //intentos quemando el nylon
    int tries_indx = 0;

    #if(SCH_ANTENNA_ONBOARD == 1)
    {
        for(tries_indx=1; tries_indx<=THK_MAX_TRIES_ANT_DEPLOY; tries_indx++)
        {
            #if (SCH_TASKDEPLOYMENT_VERBOSE>=2)
                printf("    [Deploying] Attempt #%d\r\n", tries_indx);
            #endif

            PPC_ANT12_SWITCH=1;
            PPC_ANT1_SWITCH=1;
            PPC_ANT2_SWITCH=0;
            //PPC_ANT1_SWITCH=0;
            //PPC_ANT2_SWITCH=1;
//            vTaskDelay(delay_dep_time);   /* tiempo de intento ANT1 */
//            vTaskDelay(delay_dep_time);   /* tiempo de intento ANT1 */
            __delay_ms(delay_dep_time);
            ClrWdt();
            __delay_ms(delay_dep_time);

            PPC_ANT12_SWITCH=0;
            PPC_ANT1_SWITCH=0;
            PPC_ANT2_SWITCH=0;
//            vTaskDelay(delay_rest_dep_time);   /* tiempo de descanso */
            __delay_ms(delay_rest_dep_time);
            ClrWdt();

            PPC_ANT12_SWITCH=1;
            PPC_ANT1_SWITCH=0;
            PPC_ANT2_SWITCH=1;
            //PPC_ANT1_SWITCH=1;
            //PPC_ANT2_SWITCH=0;
//            vTaskDelay(delay_dep_time);   /* tiempo de intento ANT2 */
//            vTaskDelay(delay_dep_time);   /* tiempo de intento ANT2 */
            __delay_ms(delay_dep_time);
            ClrWdt();
            __delay_ms(delay_dep_time);

            PPC_ANT12_SWITCH=0;
            PPC_ANT1_SWITCH=0;
            PPC_ANT2_SWITCH=0;
//            vTaskDelay(delay_rest_dep_time);   /* tiempo de descanso */
            __delay_ms(delay_rest_dep_time);
            ClrWdt();

            if( thk_get_AntSwitch_isOpen(&delay_recheck_dep_time) == 1 )
            {
                thk_deployment_registration(&tries_indx);

                #if (SCH_TASKDEPLOYMENT_VERBOSE>=1)
                    printf("    ANTENNA DEPLOYED SUCCESSFULLY [%d TRIES]\r\n", tries_indx);
                    rtc_print(NULL);
                #endif
                return 1;
            }
        }
    }
    #endif

    //after the for() tries_indx == THK_MAX_TRIES_ANT_DEPLOY+1
    tries_indx = THK_MAX_TRIES_ANT_DEPLOY+1; //por si acaso
    thk_deployment_registration(&tries_indx);

    #if (SCH_TASKDEPLOYMENT_VERBOSE>=2)
        printf("    ANTENNA DEPLOY FAIL [%d TRIES]\r\n", THK_MAX_TRIES_ANT_DEPLOY);
        rtc_print(NULL);
    #endif

    return 0;
}

/**
 *
 * @param param
 * @return 1=AntennaSqitch is open, 0 = AntennaSqitch is closed
 */
int thk_get_AntSwitch_isOpen(void* param){
    unsigned int recheck_time_ms = *( (unsigned int*)param );
    
    if(recheck_time_ms >= 10000){   //cut everything longer than 10seg
        recheck_time_ms = 10000;
    }
    
    if(PPC_ANT12_CHECK == 0){   /* reviso */
//        vTaskDelay(delay_recheck_dep_time);   /* tiempo de RE-chequeo */
        __delay_ms(recheck_time_ms);
        if(PPC_ANT12_CHECK == 0){   /* RE-reviso */
            return 1;
        }
    }
    return 0;
}

/**
 * Command that writes DEP registration. It takes care of:
 * 1) Register success or failure of antenna deployment
 * 2) Reset Antenna DEP vars to a Before Fligth condition
 * @param param -1 = Reset, [1, MAX_TRIES] registration as succes,
 * [MAX_TRIES+1 = registration as failure
 * @return 1 = On a correct parameter, 0 incorrect parameter (no change in vars)
 */
int thk_deployment_registration(void *param)
{
    int dep_tries = *( (int *)param );
    int dep_state;
    MemEEPROM_Vars mem_eeprom_var; int value;
    BOOL valid_dep_tries = FALSE;

    //Reset antenna DEP variables (EBF routine)
    if(dep_tries == (-1) ) {
        mem_eeprom_var = mem_dep_ant_deployed; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_ant_tries; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);

        //RTC
        mem_eeprom_var = mem_dep_year; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_month; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        
        mem_eeprom_var = mem_dep_day_number; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        
        mem_eeprom_var = mem_dep_week_day; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        
        mem_eeprom_var = mem_dep_hours; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        
        mem_eeprom_var = mem_dep_minutes; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        
        mem_eeprom_var = mem_dep_seconds; value = 0;
        writeIntEEPROM1(mem_eeprom_var, value);
        return 1;
    }
    // Antennas were NOT deployed
    if(dep_tries == (THK_MAX_TRIES_ANT_DEPLOY+1) ){
        dep_state = 0;
        dep_tries = THK_MAX_TRIES_ANT_DEPLOY+1;
        valid_dep_tries = TRUE;
    }
    //Antennas were deployed
    if( (dep_tries >= 1) && (dep_tries <= THK_MAX_TRIES_ANT_DEPLOY) ){
        dep_state = 1;
        valid_dep_tries = TRUE;
    }

    //Register only if valid_dep_tries == TRUE;
    if( valid_dep_tries == TRUE ){
        mem_eeprom_var = mem_dep_ant_deployed; value = dep_state;
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_ant_tries; value = dep_tries;
        writeIntEEPROM1(mem_eeprom_var, value);


        //RTC
        mem_eeprom_var = mem_dep_year; value = RTC_get_year();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_month; value = RTC_get_month();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_day_number; value = RTC_get_day_num();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_week_day; value = RTC_get_week_day();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_hours; value = RTC_get_hours();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_minutes; value = RTC_get_minutes();
        writeIntEEPROM1(mem_eeprom_var, value);

        mem_eeprom_var = mem_dep_seconds; value = RTC_get_seconds();
        writeIntEEPROM1(mem_eeprom_var, value);

        return 1;
    }
    else{
        return 0;
    }
}
//------------------------------------------------------------------------------

int thk_silent_time_and_pictures(void *param){
    #if (SCH_TASKDEPLOYMENT_VERBOSE>=1)
        con_printf("\n[thk_silent_time_and_pictures] Mandatory inactivity time...\r\n");
        rtc_print(NULL);
    #endif

    //1) Silencio el TRX
    #if (SCH_TRX_ONBOARD==1)
        #if (SCH_TASKDEPLOYMENT_VERBOSE>=2)
            con_printf("    * Turning off TX\r\b");
        #endif

        int trx_mode = 2; //TODO: Implement trx_setmode
        trx_set_operation_mode( (void *)&trx_mode );
    #endif

    //2) tomo foto
    pay_init_camera(NULL);
    //int arg = CAM_MODE_VERBOSE;
    int arg = CAM_MODE_BOTH;
    pay_take_camera(&arg);
    pay_stop_camera(NULL);
   //parar ciclo de Payload
    //int cam_state = SRP_PAY_XXX_STATE_INACTIVE;
    PAY_xxx_State cam_state = pay_xxx_state_inactive;
    pay_set_state_camera(&cam_state);

    //3) duermo el SUCHAI por 30min
    #if (SCH_TASKDEPLOYMENT_VERBOSE>=1)
        con_printf("    * System halted at ");
        rtc_print(NULL);
    #endif

    int mode= *( (int *)param );
    if(mode)    /* RealTIme */
    {
//        const unsigned int time_out = (0xFFFF) / portTICK_RATE_MS; /* 65,535[s]*/
        const unsigned int time_out = (0xFFFF); /* 65,535[s]*/

        unsigned int indx2;
        for(indx2=0; indx2<THK_SILENT_TIME_MIN-1; indx2++)
        {
            //vTaskDelay(time_out);
            __delay_ms(time_out);
            ClrWdt()
        }

        con_printf("    * 65[s] remaining ...\r\n");
        //vTaskDelay(time_out);
        __delay_ms(time_out);
        ClrWdt()
    }
    else    /* NO RealTIme */
    {
//        const unsigned int time_out = (10000) / portTICK_RATE_MS; /* 10[s]*/
        const unsigned int time_out = (10000); /* 10[s]*/
        
        //vTaskDelay(time_out);
        __delay_ms(time_out);
        ClrWdt()
    }

    #if (SCH_TASKDEPLOYMENT_VERBOSE>=1)
        con_printf("    * System resumed at ");
        rtc_print(NULL);
        con_printf("    FINISHING SILENT TIME\r\n");
    #endif

    //4) normalizo el TRX
    #if (SCH_TRX_ONBOARD==1)
        #if (SCH_TASKDEPLOYMENT_VERBOSE>=2)
            con_printf("    * Turning on TX\r\b");
        #endif

        trx_mode = 5; //TODO: Implement trx_setmode
        trx_set_operation_mode( (void *)&trx_mode );
    #endif

    return 1;
}
//------------------------------------------------------------------------------
int thk_debug2(void *param){
    rtc_print(NULL);
    
    printf("Bus Hardware (initialized in dep_init_bus_hw)..\r\n");
    /* this info is updated at start-up vy dep_init_bus_hw()..*/
    printf("PPC_MB_nOE_USB_nINT_CHECK = %d \r\n", PPC_MB_nOE_USB_nINT_CHECK );
    printf("PPC_MB_nOE_MHX_CHECK = %d \r\n", PPC_MB_nOE_MHX_CHECK );
    printf("PPC_MB_nON_MHX_CHECK = %d \r\n", PPC_MB_nON_MHX_CHECK );
    printf("PPC_MB_nON_SD_CHECK = %d \r\n", PPC_MB_nON_SD_CHECK );
    printf("sta_RTC_isAlive = %d \r\n", sta_get_stateVar(sta_RTC_isAlive) );
    printf("sta_TRX_isAlive = %d \r\n", sta_get_stateVar(sta_TRX_isAlive) );
    printf("sta_EPS_isAlive = %d \r\n", sta_get_stateVar(sta_EPS_isAlive) );
    printf("sta_MemEEPROM_isAlive = %d \r\n", sta_get_stateVar(sta_MemEEPROM_isAlive) );
    printf("sta_MemSD_isAlive = %d \r\n", sta_get_stateVar(sta_MemSD_isAlive) );
    printf("sta_SUCHAI_isDeployed = %d \r\n", sta_get_stateVar(sta_AntSwitch_isOpen) );
    #if (SCH_ANTENNA_ONBOARD==1)
        int ant12 = PPC_ANT12_CHECK;
        printf("PPC_ANT12_CHECK = %d => ", ant12 );
        if(ant12==1){
            printf("Antenna NOT deployed \r\n");
        }
        else{
            printf("Antenna deployed \r\n");
        }
    #endif
    printf("******************************************\r\n");

    printf("Payload Hardware (initialized by each pay_init_xxx)..\r\n");
    /* this info is updated at start-up by dep_init_bus_hw()..*/
    #if (SCH_PAY_SENSTEMP_ONBOARD==1)
        pay_init_sensTemp(NULL);
        pay_stop_sensTemp(NULL);
    #endif
    #if (SCH_PAY_GYRO_ONBOARD==1)
        pay_init_gyro(NULL);
        pay_stop_gyro(NULL);
    #endif
    #if (SCH_PAY_CAM_nMEMFLASH_ONBOARD==1)
        pay_init_camera(NULL);
        pay_stop_camera(NULL);

    #endif
    #if (SCH_PAY_GPS_ONBOARD==1)
        pay_init_gps(NULL);
        pay_stop_gps(NULL);
    #endif
    #if (SCH_PAY_FIS_ONBOARD==1)
        pay_init_expFis(NULL);
        pay_stop_expFis(NULL);
    #endif
    #if (SCH_PAY_BATTERY_ONBOARD==1)
        pay_init_battery(NULL);
        printf("  sta_pay_battery_isAlive = %d \r\n", sta_get_stateVar(sta_pay_battery_isAlive) );
    #endif
    #if (SCH_PAY_DEBUG_ONBOARD==1)
        pay_init_debug(NULL);
        printf("  sta_pay_test2_isAlive = %d \r\n", sta_get_stateVar(sta_pay_debug_isAlive) );
    #endif
    #if (SCH_PAY_LANGMUIR_ONBOARD==1)
        pay_init_lagmuirProbe(NULL);
        pay_stop_lagmuirProbe(NULL);
    #endif
    pay_init_tmEstado(NULL);
    printf("******************************************\r\n");

    rtc_print(NULL);

    //thk_executeBeforeFlight(NULL);
    return 1;
}
//------------------------------------------------------------------------------
int thk_executeBeforeFlight(void *param){
    printf("thk_executeBeforeFlight()..\n");

    drp_executeBeforeFlight(NULL);
    srp_executeBeforeFlight(NULL);

    printf("****************************************************\r\n");
    printf("thk_executeBeforeFlight finalizo\r\n");
    printf("Para quedar en config de vuelo, se\r\n");
    printf("DEBE apagar el SUCHAI, hagalo ANTES de:\r\n");
    printf("****************************************************\r\n");

    int i;
    for(i=10;i>=1;i--){
        __delay_ms(1000);
        printf("%d segundos..\r\n", i);
    }

    ppc_reset(NULL);

    return 1;
}
