/*************************************************************************** 
  User Configuration File

  Company:
    Microchip Technology Inc.

  File Name:
    UPD301C_Basic_Sink_AE_BootCfg.c

  Summary:
    User Configuration Source file

  Description:
    This source file contains user configurable globals and functions.

************************************************************************** */
/*******************************************************************************
Copyright �  [2020] Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software and
any derivatives exclusively with Microchip products. It is your responsibility
to comply with third party license terms applicable to your use of third party
software (including open source software) that may accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES
OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN
ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST
EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "psf_stdinc.h"
#include <string.h>
#include "psf_adc.h"
/*******************************************************************/
/******************* Global variables********************************/
/*******************************************************************/

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void PSF_LoadConfig(GLOBAL_CFG_STATUS_DATA *pasCfgStatusData)
{

	UINT8 u8Length = SET_TO_ZERO;
	
    pasCfgStatusData->u16ProducdID = CFG_PRODUCT_ID;
    pasCfgStatusData->u16VendorID = CFG_VENDOR_ID;
    pasCfgStatusData->u16ProductTypeVDO = CFG_PRODUCT_TYPE_VDO;
    pasCfgStatusData->u16ProductVDO = CFG_PRODUCT_VDO;
    pasCfgStatusData->u16CertStatVDO = CFG_CERT_STAT_VDO;
    pasCfgStatusData->u16IDHeaderVDO = CFG_ID_HEADER_VDO;
    pasCfgStatusData->u8HWVersion = CFG_HW_VERSION;
    pasCfgStatusData->u8SiVersion = CFG_SILICON_VERSION; 
    pasCfgStatusData->u8ManfStringLength = CFG_MANUFACTURER_STR_LEN;

    while(u8Length < pasCfgStatusData->u8ManfStringLength)
    {
        pasCfgStatusData->u8aManfString[u8Length] = CFG_MANUFACTURER_STR[u8Length];
        u8Length++;
    }
    pasCfgStatusData->sPerPortData[PORT0].u32CfgData =       
        ((CFG_PORT_0_VCONN_OCS_ENABLE) | (CFG_PORT_0_ENABLE) | (CFG_PORT_0_RP_CURRENT_VALUE)| \
        (CFG_PORT_0_DUAL_ROLE_DATA_SUPPORT) | (CFG_PORT_0_POWER_ROLE));

    
    pasCfgStatusData->sPerPortData[PORT0].u8Pio_FAULT_IN = (UINT8)CFG_PORT_0_UPD_FAULT_IN_PIO_NO;
    pasCfgStatusData->sPerPortData[PORT0].u8Mode_FAULT_IN = (UINT8)CFG_PORT_0_UPD_FAULT_IN_MODE;
    pasCfgStatusData->sPerPortData[PORT0].u8Pio_EN_SINK  = (UINT8)CFG_PORT_0_UPD_EN_SNK;
    pasCfgStatusData->sPerPortData[PORT0].u8Mode_EN_SINK  = (UINT8)CFG_PORT_0_UPD_EN_SNK_PIO_MODE;
    pasCfgStatusData->sPerPortData[PORT0].u8OCSThresholdPercentage = SET_TO_ZERO;
    pasCfgStatusData->sPerPortData[PORT0].u8OVThresholdPercentage = CFG_OVER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT0].u8UVThresholdPercentage = CFG_UNDER_VOLTAGE_FACTOR;
    pasCfgStatusData->sPerPortData[PORT0].u8FaultInDebounceInms = CFG_FAULT_IN_OCS_DEBOUNCE_MS;
    pasCfgStatusData->sPerPortData[PORT0].u8VCONNOCSDebounceInms = CFG_VCONN_OCS_DEBOUNCE_IN_MS;
    pasCfgStatusData->sPerPortData[PORT0].u8VBUSMaxFaultCnt = CFG_MAX_VBUS_POWER_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT0].u8VCONNMaxFaultCnt = CFG_MAX_VCONN_FAULT_COUNT;
    pasCfgStatusData->sPerPortData[PORT0].u16PowerGoodTimerInms = MILLISECONDS_TO_TICKS(CFG_POWER_GOOD_TIMER_MS);
    pasCfgStatusData->sPerPortData[PORT0].u16MaxSrcPrtCurrentIn10mA = CFG_MAX_PORT_CURRENT_IN_10mA;
    
	pasCfgStatusData->sPerPortData[PORT0].u8SinkConfigSel = ((CFG_PORT_0_SINK_MODE)| \
            (CFG_PORT_0_SINK_USB_SUSP) | (CFG_PORT_0_SINK_GIVE_BACK_FLAG ));
			
        /*Assigning PDOs according to the ADC position*/
    pasCfgStatusData->sPerPortData[PORT0].u8SinkPDOCnt = CFG_PORT_0_SINK_NUM_OF_PDOS;
    UINT8 u8ADCPosition = Get_ADCPosition();
    memset(gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO,0,7);
    switch(u8ADCPosition)
    {
        case 0:
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 1;
            break;
        case 1:
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 2;
            break;
        case 2:
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
			gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_3;
			gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 2;
			break;
        case 3:
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
			gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_4;
			gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 2;
			break;
        case 4:
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 3;
			break;
        case 5:
            gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel |= CFG_PORT_0_SINK_MODEB;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 3;
			break;
		case 6:
			gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[3] = CFG_PORT_0_SINK_PDO_4;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 4;
			break;
		case 7:
			gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel |= CFG_PORT_0_SINK_MODEB;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
            gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[3] = CFG_PORT_0_SINK_PDO_4;
            gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt = 4;
			break;
	}
    /*Assigning maximum operating current and minimum operating current for Note
      type port to 3000mA and 1000mA respectively*/
    pasCfgStatusData->sPerPortData[PORT0].u16SnkMaxOperatingCurInmA = \
            CFG_PORT_0_SINK_MAX_OPERATING_CURRENT_InmA;
    pasCfgStatusData->sPerPortData[PORT0].u16SnkMinOperatingCurInmA = \
            CFG_PORT_0_SINK_MIN_OPERATING_CURRENT_InmA;


     /*Assigning PDO preferred minimum current*/
    pasCfgStatusData->sPerPortData[PORT0].u16aMinPDOPreferredCurInmA[INDEX_0] = \
            CFG_PORT_0_SINK_PDO_1_PREFERRED_MIN_CURRENT;
    pasCfgStatusData->sPerPortData[PORT0].u16aMinPDOPreferredCurInmA[INDEX_1] = \
            CFG_PORT_0_SINK_PDO_2_PREFERRED_MIN_CURRENT;
    pasCfgStatusData->sPerPortData[PORT0].u16aMinPDOPreferredCurInmA[INDEX_2] = \
            CFG_PORT_0_SINK_PDO_3_PREFERRED_MIN_CURRENT;
    pasCfgStatusData->sPerPortData[PORT0].u16aMinPDOPreferredCurInmA[INDEX_3] = \
            CFG_PORT_0_SINK_PDO_4_PREFERRED_MIN_CURRENT;
    
    /*Assigning DAC_I configuration*/
    pasCfgStatusData->sPerPortData[PORT0].u16DAC_I_CurrentInd_MaxInA = \
            CFG_PORT_0_SINK_DAC_I_CUR_INDICATION_MAX;
    pasCfgStatusData->sPerPortData[PORT0].u16DAC_I_MaxOutVoltInmV = \
            CFG_PORT_0_SINK_DAC_I_MAX_OP_VOLTAGE;
    pasCfgStatusData->sPerPortData[PORT0].u16DAC_I_MinOutVoltInmV = \
            CFG_PORT_0_SINK_DAC_I_MIN_OP_VOLTAGE;
    pasCfgStatusData->sPerPortData[PORT0].u8DAC_I_Direction = \
            CFG_PORT_0_SINK_DAC_I_DIR;
			
    /*Configure role swap policy for note type port*/
    pasCfgStatusData->sPerPortData[PORT0].u16SwapPolicy = CFG_PORT_0_ROLE_SWAP_POLICY;
               
}



/* *****************************************************************************
 End of File
 */
