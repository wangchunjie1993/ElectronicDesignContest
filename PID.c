#include<avr/io.h>
#include<util/delay.h>

/*====================================================================================================
PID Function
The PID (���������֡�΢��) function is used in mainly
control applications. PIDCalc performs one iteration of the PID
algorithm.
While the PID function works, main is just a dummy program showing
a typical usage.
=====================================================================================================*/
typedef struct PID {
	float SetPoint; // �趨Ŀ��Desired value
	float Proportion; // ��������Proportional Const
	float Integral; // ���ֳ���Integral Const
	float Derivative; // ΢�ֳ���Derivative Const
	float LastError; // Error[-1]	
	float PrevError; // Error[-2]
	float SumError; // Sums of Errors
} PID;
/*====================================================================================================/
PID���㲿��
=====================================================================================================*/
PID   vPID={0,1.5,0.1,1,0,0,0};
//PID vPID={0,5,0,4,0,0,0,};

float PIDCalc( PID *pp, float NextPoint )
{	float dError,Error;	
	Error = pp->SetPoint-NextPoint; // ƫ��
	pp->SumError += Error; // ����
	dError = pp->LastError - pp->PrevError; // ��ǰ΢��
	pp->PrevError = pp->LastError;
	pp->LastError = Error;
	 
    if(pp->SumError>900)  pp->SumError=900;
    else if(pp->SumError<-900)	  pp->SumError=-900;

	return (pp->Proportion * Error // ������
	+ pp->Integral * pp->SumError // ������
	+ pp->Derivative * dError // ΢����
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
