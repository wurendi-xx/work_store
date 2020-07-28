#ifndef PARAMETER_H
#define PARAMETER_H

typedef struct
{
    uint32_t				   	Running;

    uint32_t				   	Dir;

    TurnTable_Mode_t			Last_State;

    TurnTable_Mode_t			Set_State;

    uint32_t                 	Difference;

    uint32_t                 	AllPulse;

    uint32_t                 	RunPulse;

    uint32_t                 	ResetCnt;
}TurnTable_State_t;

#define COVERADC   2
#define ADCNUM     5
#define ADCBUFNUM  10
typedef struct
{
    uint32_t				  		Buf[ADCBUFNUM][ADCNUM];
    uint32_t				   		BufFit[ADCBUFNUM];
    uint32_t				   		Dat[ADCNUM];
    uint32_t				   		Cnt;
}ADC_t;
extern ADC_t ADC_C;


typedef enum
{
    CoverReset          = 0x00,//下拉
    CoverOpen           = 0x01,//下拉
    CoverClose          = 0x02,  //下拉
    CoverStop           = 0x03,  //下拉
} Cover_Mode_t;

typedef struct
{
    uint32_t				  	   Running;
    Cover_Mode_t				   State;
    Cover_Mode_t			   	   Last_State;
}Cover_State_t;

typedef enum
{
    StirReset          = 0x02,
    StirRun			   = 0x01,
    StirStop           = 0x00,
} Stir_Mode_t;

typedef struct
{
    uint32_t						Running;
    Stir_Mode_t						State;
    Stir_Mode_t						LastState;
    uint32_t						Stir_Cyc;
}Stir_State_t;

//typedef struct
//{
//  uint32_t				   Running;
//
//  Push_State_t			   State;
//
//  uint32_t				   Set;
//}SteeringEngine_State_t;


typedef struct
{
    volatile uint8_t cmd;
    volatile uint8_t data;
}LCD_TypeDef;

#define LCD_BASE ((uint32_t)(0x60000000 | 0x0000FFFF)) //A16:A0  1111 1111 1111 1111 ????????
#define LCD      ((LCD_TypeDef *) LCD_BASE)
#define LCD_CMD   (*(uint16_t *)(0x60000000 | 0))
#define LCD_DATA  (*(uint16_t *)(0x60000000 | 0x10000))//2^16*2

/**********************通讯 参数设置 控制*********************/


typedef enum
{
    Set_OpenState           = 0x00,
    Set_CloseState          = 0x01,
    Set_Heating    			= 0x02,
    Set_Seasoning     		= 0x03,
    Set_Washing        		= 0x04,
    Set_Waiting     		= 0x05,
} SetRun_State_t;
//0x00: 开盖
//0x01: 关盖
//0x02: 加热过程
//0x03: 加料过程
//0x04: 清洗过程
//0x05: 等待过程


typedef enum
{

    PowerOff          = 0x64,
    RunStart    	  = 0x65,
    RunSuspend     	  = 0x66,
    RunStop     	  = 0x67,
} SetRunPower_State_t;
//0x63: 开机
//0x64: 关机
//0x65: 启动
//0x66; 暂停
//0x67; 停止

typedef struct
{
    uint8_t				   RunStep;
    SetRun_State_t		   RunState;
    uint8_t				   VoiceNum;
    uint8_t				   CoverState;
    uint8_t				   StirTimes;
    uint8_t				   StirTimemin;
    uint8_t				   StirCycle;
    uint8_t				   HeatTemperature;
    uint8_t				   HeatTimes;
    uint8_t				   HeatTimemin;
    uint8_t				   Seasoning1;
    uint8_t				   Seasoning2;
    uint8_t				   Seasoning3;
    uint8_t				   Seasoning4;
    uint8_t				   Seasoning5;
    uint8_t				   Seasoning6;
    uint8_t				   Seasoning7;
    uint8_t				   Seasoning8;
    uint8_t				   Seasoning9;
    uint8_t				   Seasoning10;
    uint8_t				   Drain;
    uint8_t				   Washtime;
    uint8_t				   WashDrain;
}CookBook_t;


/*************************************/
typedef struct
{
    uint8_t    AllBookNum;
    uint8_t    NowBookNum;
    CookBook_t CookBook[20];
}CookMenu_t;



typedef enum
{
    Preparation          = 0x00,//
    CoverControl         = 0x01, //
    Heating    	 	 	 = 0x02,//
    Feeding     	 	 = 0x03,//
    Cleaning     	 	 = 0x04,  //
    Waitting     	 	 = 0x05, //
    PowerOn     	 	 = 0x06, //
    NetCheck     	 	 = 0x07,//
    ModeSet     	 	 = 0x08,
    MenuSelect     	 	 = 0x09,
    Suspend      	 	 = 0x0A,
    Testing      	 	 = 0x0B,
    SeasonList			 = 0x0C,
    CheckPreparation     = 0x0D,
    FixedModeSelect      = 0x0E,
    FixedModeWork        = 0x0F,
} Run_State_t;//下拉


typedef enum
{
    SelectMenu           = 0x00,
    Fixedmode            = 0x01,
    Setting    	 	 	 = 0x03,
    Create    	 	 	 = 0x02,
} Run_Mode_t;

typedef enum
{
    QuickFry	         = 0x00,
    Frying               = 0x01,
    Cooking    	 	 	 = 0x02,
} Fixed_Mode_t;




typedef enum
{
    VoiceTesting           = 0x00,
    HeatTesting           = 0x01,
    WeightTesting          = 0x02,
    CoverTesting           = 0x03,
    StirTesting    	 	   = 0x04,
    SeasonTesting    	   = 0x05,
    AUTOTest       		   = 0x06,
} Test_Mode_t;


typedef struct
{
    Test_Mode_t 			Step;
    uint8_t 				ClassB;
    uint8_t				    VoiceNum;
    uint8_t				    FlashID;
    uint8_t				    Weight;
    uint8_t				    Cover;
    uint8_t				    Stir;
    uint8_t				    Seasoning;
    uint8_t				    AUTOTest;
}Test_state_t;

typedef struct
{
    uint32_t                MenuNum;
    uint32_t                SetAllTime;
    uint32_t                RunTime;
    uint32_t                LastTime;
    uint32_t                SetSeasoningStepNum;
    uint32_t                SetRunStepNum;
    uint32_t                SeasoningStep;
    uint32_t                RealtimeStep;
    Run_State_t 			State;
    uint32_t 				Cover;
    uint32_t 				Stir;
    uint32_t 				Power;
    uint32_t 				Time;
    uint32_t 				Temperature;
    uint32_t 				SetTemperature;
    uint32_t 				Mode;
    Run_Mode_t 				Mode_LevelA;
    Test_state_t 			Test;
    Fixed_Mode_t			FixedModeLevel;
}Running_state_t;


/********add start*******/
 typedef struct
{
    uint8_t    				Header;
    uint8_t    				TargetAddr;
    uint8_t    				SourceAddr;
    uint8_t    				Length;
    uint8_t    				ID1;
    uint8_t    				ID2;
    uint8_t    				CMD;
    uint8_t    				Version;
    uint8_t    				Version1;
    uint8_t    				Version2;
    uint8_t    				Num;
    SetRun_State_t			State;
    uint8_t    				SpecialSet;
    uint8_t				    S_Run;
    uint8_t				    S_Dir;
    uint8_t				    S_Speed;
    uint8_t				    S_AllPulse1;
    uint8_t				   	S_AllPulse2;
    uint8_t				  	S_AllPulse3;
    uint8_t				   	S_AllPulse4;
//	uint32_t				S_AllPulse;
    uint8_t				   	S_Location;
    uint8_t				    P_Run;
    uint8_t				    P_Dir;
    uint8_t				    P_Speed;
    uint8_t				    P_AllPulse1;
    uint8_t				   	P_AllPulse2;
    uint8_t				  	P_AllPulse3;
    uint8_t				   	P_AllPulse4;
//	uint32_t				P_AllPulse;
    uint8_t				    BP_Run;
    uint8_t				    BP_Dir;
    uint8_t				    BP_Speed;
    uint8_t				    BP_AllPulse1;
    uint8_t				   	BP_AllPulse2;
    uint8_t				  	BP_AllPulse3;
    uint8_t				   	BP_AllPulse4;
//	uint32_t				BP_AllPulse;
    uint8_t				    BP3_Run;
    uint8_t				    BP3_Dir;
    uint8_t				    BP3_Speed;
    uint8_t				    BP3_AllPulse1;
    uint8_t				   	BP3_AllPulse2;
    uint8_t				  	BP3_AllPulse3;
    uint8_t				   	BP3_AllPulse4;
//	uint32_t				P3_AllPulse;
    uint8_t				    SE_Location;
//	uint8_t				   	SheeringAngle1;
//	uint8_t				   	SheeringAngle2;
    uint8_t				   	HALLSet;
    uint8_t				   	Year;
    uint8_t				   	Month;
    uint8_t				   	Day;
    uint8_t				   	Hour;
    uint8_t				   	Min;
    uint8_t				   	CheckSum;
}UartTx_state_t;

 typedef struct
{
    uint8_t    				Header;
    uint8_t    				TargetAddr;
    uint8_t    				SourceAddr;
    uint8_t    				Length;
    uint8_t    				ID1;
    uint8_t    				ID2;
    uint8_t    				CMD;
    uint8_t    				Version;
    uint8_t    				Version1;
    uint8_t    				Version2;
    uint8_t    				Num;
    SetRun_State_t			State;
    uint8_t    				SpecialSet;
    uint8_t				    S_Run;
    uint8_t				    S_Dir;
    uint8_t				    S_Speed;
    uint8_t				    S_AllPulse1;
    uint8_t				   	S_AllPulse2;
    uint8_t				  	S_AllPulse3;
    uint8_t				   	S_AllPulse4;
//	uint32_t				S_AllPulse;
    uint8_t				   	S_Location;
    uint8_t				    P_Run;
    uint8_t				    P_Dir;
    uint8_t				    P_Speed;
    uint8_t				    P_AllPulse1;
    uint8_t				   	P_AllPulse2;
    uint8_t				  	P_AllPulse3;
    uint8_t				   	P_AllPulse4;
//	uint32_t				P_AllPulse;
    uint8_t				    BP_Run;
    uint8_t				    BP_Dir;
    uint8_t				    BP_Speed;
    uint8_t				    BP_AllPulse1;
    uint8_t				   	BP_AllPulse2;
    uint8_t				  	BP_AllPulse3;
    uint8_t				   	BP_AllPulse4;
//	uint32_t				BP_AllPulse;
    uint8_t				    BP3_Run;
    uint8_t				    BP3_Dir;
    uint8_t				    BP3_Speed;
    uint8_t				    BP3_AllPulse1;
    uint8_t				   	BP3_AllPulse2;
    uint8_t				  	BP3_AllPulse3;
    uint8_t				   	BP3_AllPulse4;
//	uint32_t				P3_AllPulse;
    uint8_t				    SE_Location;
//	uint8_t				   	SheeringAngle1;
//	uint8_t				   	SheeringAngle2;
    uint8_t				   	HALLSet;
    uint8_t				   	AD1;
    uint8_t				   	AD2;
    uint8_t				   	LNum;
    uint8_t  				Name;


    uint16_t 				Ful1;
    uint16_t 				Remainder;
    uint16_t 				QualityDay;

    uint8_t  				Year;
    uint8_t  				Month;
    uint8_t	 				Day;

    uint8_t				   	Error1;
    uint8_t				   	Error2;
    uint8_t				   	Error3;
    uint8_t				   	Error4;

    uint8_t  				RealYear;
    uint8_t  				RealMonth;
    uint8_t	 				RealDay;
    uint8_t				   	RealHour;
    uint8_t				   	RealMin;

    uint8_t				   	Over;

    uint8_t				   	CheckSum;
}UartRx_state_t;
//IAP
 typedef struct
{
    uint8_t    				Header;
    uint8_t    				TargetAddr;
    uint8_t    				SourceAddr;
    uint8_t    				Length;
    uint8_t    				ID1;
    uint8_t    				ID2;
    uint8_t    				CMD;
    uint8_t    				Version;
    uint8_t    				Version1;
    uint8_t    				Version2;

    uint8_t    				Address1;
    uint8_t    				Address2;
    uint8_t    				Address3;
    uint8_t    				Address4;
    uint8_t					Bin[1024];
    uint8_t				   	CheckSum;
}IAPTx_state_t;

 typedef struct
{
    uint8_t    				Header;
    uint8_t    				TargetAddr;
    uint8_t    				SourceAddr;
    uint8_t    				Length;
    uint8_t    				ID1;
    uint8_t    				ID2;
    uint8_t    				CMD;
    uint8_t    				Version;
    uint8_t    				Version1;
    uint8_t    				Version2;

    uint8_t    				Address1;
    uint8_t    				Address2;
    uint8_t    				Address3;
    uint8_t    				Address4;
    uint8_t					Data1;
    uint8_t					Data2;
    uint8_t				   	CheckSum;
}IAPRx_state_t;
//buf
 typedef struct
{
    uint8_t    				Header;
    uint8_t    				TargetAddr;
    uint8_t    				SourceAddr;
    uint8_t    				Length;
    uint8_t    				ID1;
    uint8_t    				ID2;
    uint8_t    				CMD;
    uint8_t    				Version;
    uint8_t    				Version1;
    uint8_t    				Version2;
    uint8_t					Buff[1030];
}Rx_Buff_t;



typedef struct Uart_Mcu_t
{
    Rx_Buff_t		Rx_Buff;
    UartTx_state_t  Tx_Data;
    //UartRx_state_t  Rx_state;
    UartRx_state_t  Rx_Data;
    IAPTx_state_t	IAPTx;
    IAPRx_state_t   IAPRx;
    rt_bool_t			RX_Ok;
    rt_bool_t			IAPRX_Ok;
}Uart_Add_tt;


/*****************钃濈墮****************/


/*************加热******************/
typedef struct
{
    uint8_t                Running;
    uint8_t				   SetTemperature;
    uint8_t                TemperatureA;
    uint8_t                TemperatureB;
    uint8_t                TemperatureC;
    uint8_t                Time;
    uint16_t               RemainderTimes;
}Heat_State_t;

typedef struct
{
    uint16_t                PowerA;
    uint16_t				PowerB;
    uint8_t                 ControlA;
    uint8_t                 ControlB;

}Heat_Set_t;

typedef struct
{
    uint8_t                 Power:5;
    uint8_t					Check:1;
    uint8_t                 Heat:1;
    uint8_t                 On:1;
    uint8_t                 reserve:2;
    uint8_t                 Fan:1;
    uint8_t                 reserve2:5;
    uint8_t					Checksum;
}RCHeat_Set_t;

typedef enum
{
    NoError          	= 0x0,
    NoPot            	= 0x1,
    Connection    	 	= 0x2,
    VoltageLow     	 	= 0x3,
    VoltageHigh      	= 0x4,
    NTCOpen   		 	= 0xB,
    NTCShort  		 	= 0xC,
    NTCOverTemp  		= 0xD,
} RCHeat_Error_t;
typedef enum
{
    SRQAD          		= 0x3,
    VoltageAD           = 0x4,
    ControlByte1    	= 0x5,
    ControlByte2     	= 0x6,
    RealCurrent      	= 0x8,
    TargetCurrent       = 0x9,
    PPGTA  		 		= 0xA,
    Plus  				= 0xB,
    Temperature1AD  	= 0xC,
    Temperature2AD  	= 0xD,
} RCHeat_Type_t;

typedef struct
{
    RCHeat_Error_t          Error:4;
    RCHeat_Type_t			Type:4;
    uint8_t                 Data:8;
    uint8_t					Checksum;
}RCHeat_RX_t;

typedef struct
{
    RCHeat_Set_t            Set;
    uint8_t					TxCnt;
    uint8_t					TxData[82];
    uint8_t					EnTx;
    uint8_t					RxCnt;
    uint8_t					RxHCnt;
    uint8_t					RxLCnt;
    uint8_t					bitStart;
    uint8_t					bitcnt;
    uint8_t					RxDataCnt;
    uint8_t					RxBuf[8];
    uint8_t					RxByteBuf[3];
    uint8_t					RxByteData[3];
    RCHeat_RX_t	   			RxData;
    uint8_t					EnRx;
    uint8_t					RxComplete;
    uint8_t    				Error;
    uint8_t    				SRQAD;
    uint8_t					VoltageAD;
    uint8_t					ControlByte1;
    uint8_t					ControlByte2;
    uint8_t					RealCurrent;
    uint8_t					TargetCurrent;
    uint8_t					PPGTA;
    uint8_t					Plus;
    uint8_t					Temperature1AD;
    uint8_t					Temperature2AD;
    uint8_t					Temperature1;
    uint8_t					Temperature2;
}RCHeat_t;

typedef struct
{
    uint16_t                PowerA;
    uint16_t				PowerB;
    uint16_t                 Voltage;
    uint8_t                 Error;
    uint8_t                 TemperatureA;
    uint8_t                 TemperatureB;
    uint8_t                 IGBTTemperatureA;
    uint8_t                 IGBTTemperatureB;

}Heat_Read_t;


typedef struct
{
    uint8_t                 PowerValue;
    uint8_t                 ControlValue;
    uint8_t                 Num;
}RD_Heat_Set_t;

typedef struct
{
    uint8_t                 PowerValue;
    uint8_t                 ControlValue;
    uint8_t                 ErrorCode;
    uint8_t                 Current;
    uint8_t                 Voltage;
    uint8_t                 IgbtTemp;
    uint8_t                 BotTemp1;
    uint8_t                 BotTemp2;
    uint8_t                 PowerVersion;
    uint8_t                 Version;
    uint8_t                 PowerMin;
    uint8_t                 PowerMax;
    uint8_t                 Num;
}RD_Heat_Read_t;

/**********************菜谱**********************/
typedef struct
{
    uint8_t Name[20];
    uint32_t Weight;
}SeasoningInformation_t;


typedef struct
{
    uint32_t SeasoningNum;
    SeasoningInformation_t SeasoningInf[5];
}Seasoning_t;

typedef struct
{
    uint32_t State; //下拉
    uint32_t Cover;//下拉
    uint32_t Stir;//下拉
    uint32_t Power;//下拉
    uint32_t Time;//输入
    uint32_t Temperature;//输入
    uint8_t  Txt[40];//输入
}Running_Step_t;

typedef struct
{
    uint8_t                 DishName[20];//1
    uint32_t                AllTime;//2
    uint32_t                SeasoningStepNum;//3
    uint32_t                RunStepNum;//4
    Seasoning_t             Seasoning[5];//5
    uint8_t                 MainSeasoning[20];//6
    Running_Step_t			RunStep[36];//7 下拉
}Menu1_t;

typedef struct
{
    Menu1_t                 Dish[30];

}Menu2_t;
/*********************key************************/
typedef enum
{
    ButtonState_Unknow,
    ButtonState_Up,
    ButtonState_Down,
    ButtonState_Long
} Button_State_t;

typedef enum
{
    KEY_TRUE,
    KEY_FALSE,
    KEY_LONG,
    KEY_DEFAULT,
} Key_S_t;

typedef struct Button_t
{
    Button_State_t State;
    uint16_t 	UpTick;
    uint16_t 	DownTick;
    Key_S_t 	Value;
}Button_tt;

typedef struct Knob_t
{
    Key_S_t     ResetState;
    uint16_t 	ZZCnt;
    uint16_t 	FZCnt;
    uint16_t 	State;
}Knob_tt;


extern Button_tt Lock;
extern Button_tt UnLock;
extern Button_tt KA;
extern Button_tt KB;
extern Button_tt KC;
extern Knob_tt Knob;

extern const  uint32_t SteeringEngine_Angle[7];
extern TurnTable_State_t  TurnTable;
//extern Push_State_t 	 Push_State;
extern Cover_State_t 	 Cover;
//extern SteeringEngine_State_t 	 SteeringEngine_State;
extern uint32_t Key1_delay,Key2_delay,Key3_delay,Key4_delay;
extern uint32_t Stir_Time;
extern uint32_t Stop_Time;
extern uint32_t Adc_buf;
extern uint8_t iic_data[10];
extern rt_bool_t Lock_Close;
extern rt_bool_t Lock_Open;

extern CookMenu_t CookMenu;
extern Running_state_t Running_state;



extern rt_bool_t  Flag_TFT_RX;


extern Heat_Set_t Heat_Set;
extern Heat_Read_t Heat_Read;

extern RD_Heat_Set_t RD_Heat_Set;
extern RD_Heat_Read_t RD_Heat_Read;

extern const uint32_t  sigan_Pulse[10];
extern uint32_t SetPumpPluse;
extern uint8_t Pump_Pwm;

extern Stir_State_t Stir;
extern RCHeat_t RCHeat;

extern const Heat_Read_t e1;
extern const Menu2_t Menu;

extern Running_state_t Running;


#endif // PARAMETER_H
