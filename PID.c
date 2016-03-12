#include<avr/io.h>
#include<util/delay.h>

/*====================================================================================================
PID Function
The PID (比例、积分、微分) function is used in mainly
control applications. PIDCalc performs one iteration of the PID
algorithm.
While the PID function works, main is just a dummy program showing
a typical usage.
=====================================================================================================*/
typedef struct PID {
	float SetPoint; // 设定目标Desired value
	float Proportion; // 比例常数Proportional Const
	float Integral; // 积分常数Integral Const
	float Derivative; // 微分常数Derivative Const
	float LastError; // Error[-1]	
	float PrevError; // Error[-2]
	float SumError; // Sums of Errors
} PID;
/*====================================================================================================/
PID计算部分
=====================================================================================================*/
PID   vPID={0,1.5,0.1,1,0,0,0};
//PID vPID={0,5,0,4,0,0,0,};

float PIDCalc( PID *pp, float NextPoint )
{	float dError,Error;	
	Error = pp->SetPoint-NextPoint; // 偏差
	pp->SumError += Error; // 积分
	dError = pp->LastError - pp->PrevError; // 当前微分
	pp->PrevError = pp->LastError;
	pp->LastError = Error;
	 
    if(pp->SumError>900)  pp->SumError=900;
    else if(pp->SumError<-900)	  pp->SumError=-900;

	return (pp->Proportion * Error // 比例项
	+ pp->Integral * pp->SumError // 积分项
	+ pp->Derivative * dError // 微分项
	);
}

float Vol(int vSet,int v3){

	float vOut; // PID Response (Output)
	float vIn; // PID Feedback (Input)

	vPID.SetPoint = vSet; // Set PID Setpoint
	vIn = (float)v3; // Read Input
	vOut = PIDCalc ( &vPID,vIn ); // Perform PID Interation	 
	return vOut;
}				 
