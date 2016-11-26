/*-------------------------------------------------------------------------
***************************************************************************
* @file classe.cpp
* @author Isaac Jesus da Silva - Centro Universitário da FEI
* @version V0.1.4
* @created 18/11/2014
* @Modified 24/11/2014
* @e-mail isaac25silva@yahoo.com.br
***************************************************************************
Arquivo fonte que contem a implementação da Programação Dinâmica
/------------------------------------------------------------------------*/

#include <iostream>
#include "classe.h"		/* MatrixVector, Matrix3d */
#include <cmath>		/* abs */
#include <vector>		/* vector */
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

////==============================================================================================
////-------------------- Policy Evaluation -------------------------------------------------------
////==============================================================================================
void SGW::policyEvaluation(unsigned int row, unsigned int col)
{
std::cout<<"Policy Evaluation"<<std::endl;

double	erro=0.00001;		//erro desejado
double 	gamma = 1;
double	reward = -1;		//recompensa
int		k=0;
double 	Pi[row][col][4];  	//Politica
double 	Vtemp[row][col];	// state-value temporario
double 	temp;				//variável temporária
double 	delta =0;			// calcula o delta
double V[row][col];			// state-value
double Pr[row][col][row][col][4];	//probabilidade

	// Zera todas as probabilidades-----------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    		for(int y=0; y<row; y++)
				for(int x=0; x<col; x++)
				{
					Pr[i][j][y][x][0]=0;//probabilidade de estar em 'ij' ir para 'yx' com ação 0 =left
					Pr[i][j][y][x][1]=0;//probabilidade de estar em 'ij' ir para 'yx' com ação 1 =right
					Pr[i][j][y][x][2]=0;//probabilidade de estar em 'ij' ir para 'yx' com ação 2 =top
					Pr[i][j][y][x][3]=0;//probabilidade de estar em 'ij' ir para 'yx' com ação 3 =down
				}
	//----------------------------------------------

    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
	    	V[i][j]  = 0;
			//-- valor da politica = 0.25---
			Pi[i][j][0] = 0.25;
			Pi[i][j][1] = 0.25;
			Pi[i][j][2] = 0.25;
			Pi[i][j][3] = 0.25;
			//--------------------------------

			//Gera as probabilidades de ir de um estado a outro -------
			if( (j-1)<0)
   	 			Pr[i][j][i][j][0] = 1; //mantem
			else
   	 			Pr[i][j][i][j-1][0] =  1; //left

			if( (j+1)>=col)
   	 			Pr[i][j][i][j][1] = 1; //mantem
			else
				Pr[i][j][i][j+1][1] =  1; //right

			if( (i-1)<0)
   	 			Pr[i][j][i][j][2] = 1; //mantem
			else
   	 			Pr[i][j][i-1][j][2] = 1; //top

			if( (i+1)>=row)
   	 			Pr[i][j][i][j][3] = 1; //mantem
			else
				Pr[i][j][i+1][j][3] = 1; //down
			//-----------------------------------------------------------
		}
do
{
	k++;
	//Faz o somatório com todas as políticas e todos as probabilidades-------------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			Vtemp[i][j] = 0;
			// faz o somatorio com todas as probabilidades da ação left----------
    		for(int y=0; y<row; y++) 
				for(int x=0; x<col; x++)
				{
					if( (j-1)<0)
   	 					Vtemp[i][j] += Pi[i][j][0]*Pr[i][j][y][x][0]*(reward + gamma*V[i][j]); //mantem
					else
   	 					Vtemp[i][j] += Pi[i][j][0]*Pr[i][j][y][x][0]*(reward + gamma*V[i][j-1]); //left
				}
			//-------------------------------------------------------------------

			// faz o somatorio com todas as probabilidades da ação right---------
    		for(int y=0; y<row; y++)
				for(int x=0; x<col; x++)
				{
					if( (j+1)>=col)
   	 					Vtemp[i][j] += Pi[i][j][1]*Pr[i][j][y][x][1]*(reward + gamma*V[i][j]); //mantem
					else
						Vtemp[i][j] += Pi[i][j][1]*Pr[i][j][y][x][1]*(reward + gamma*V[i][j+1]);//right
				}
			//-------------------------------------------------------------------

			// faz o somatorio com todas as probabilidades da ação top-----------
    		for(int y=0; y<row; y++)
				for(int x=0; x<col; x++)
				{
					if( (i-1)<0)
   	 					Vtemp[i][j] += Pi[i][j][2]*Pr[i][j][y][x][2]*(reward + gamma*V[i][j]); //mantem
					else
   	 					Vtemp[i][j] += Pi[i][j][2]*Pr[i][j][y][x][2]*(reward + gamma*V[i-1][j]); //top
				}
			//-------------------------------------------------------------------

			// faz o somatorio com todas as probabilidades da ação down----------
    		for(int y=0; y<row; y++)
				for(int x=0; x<col; x++)
				{
					if( (i+1)>=row)
   	 					Vtemp[i][j] += Pi[i][j][3]*Pr[i][j][y][x][3]*(reward + gamma*V[i][j]); //mantem
					else
						Vtemp[i][j] += Pi[i][j][3]*Pr[i][j][y][x][3]*(reward + gamma*V[i+1][j]); //down
				}
			//-------------------------------------------------------------------
   		}
	//-------------------------------------------------------------------------------------------------

	//Atualiza o valor de V(s) e calcula o delta -----------------
	delta=0;
	double tempDelta=0; //delta temporário
	//Calcula o delta máximo e passa o state-value temporario para V----
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			temp=V[i][j];
			V[i][j] = Vtemp[i][j];

			if((i==0 && j==0) || (i==(row-1) && j==(col-1)))
				V[i][j] = 0;

			// pega o max(delta)------------
			tempDelta = std::abs(temp - V[i][j]);
			if(tempDelta>delta)
				delta = tempDelta;
			//------------------------------
		}
	//-------------------------------------------------------------------
	//imprime os valores V(s)--------------
	if(k<4 || k==10 || delta < erro)
	{
	std::cout<<"K = "<<k<<std::endl;
	    for(int i=0; i<row; i++)
		{
			for(int j=0; j<col; j++)
   				 printf("%1.2f\t",V[i][j]);
			std::cout<<std::endl;
		}
	std::cout<<std::endl;
	}
	//-------------------------------------
}while(delta > erro);

}
////==============================================================================================
////-------------------- Policy Iteration --------------------------------------------------------
////==============================================================================================
void SGW::policyIteration(unsigned int row, unsigned int col)
{
std::cout<<"Policy Iteration"<<std::endl;

double			erro=0.01;		//erro desejado
double 			gamma = 0.999;
double			reward = -1;	//recompensa
int 			k=0;
double Pr=1;
double Vtemp[row][col];
double temp;
double delta =0;
double 	V[row][col];			//state-value
double 	Vmax[row][col];			//state-value máximo
bool	policyInstable;			//variável que armazena se a política anterior é igual a atual
bool	tempPolitica[row][col][4]; //armazena a politica anterior
bool	Politica[row][col][4]; 	// Politica[row][col][0] = LEFT
								// Politica[row][col][1] = RIGHT
								// Politica[row][col][2] = UP
								// Politica[row][col][3] = DOWN

	//Inicializa a política com possibilidades aleatória------------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][0] = 0; //se zero não vai ter left na politica
			else
				Politica[i][j][0] = 1; //se 1 significa que vai ter left na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][1] = 0; //se zero não vai ter right na politica
			else
				Politica[i][j][1] = 1; //se 1 significa que vai ter right na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][2] = 0; //se zero não vai ter top na politica
			else
				Politica[i][j][2] = 1; //se 1 significa que vai ter top na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][3] = 0; //se zero não vai ter down na politica
			else
				Politica[i][j][3] = 1; //se 1 significa que vai ter down na politica
		}
	//----------------------------------------------------------------------------

	//Imprime a politica--------------------------------------------------------
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			if(Politica[i][j][0] == 1)
				std::cout<<"<";
			if(Politica[i][j][1] == 1)
				std::cout<<">";	
			if(Politica[i][j][2] == 1)
				std::cout<<"^";	
			if(Politica[i][j][3] == 1)
				std::cout<<"v";			
			std::cout<<"\t\t";
		}
		std::cout<<std::endl;
   	}
	std::cout<<std::endl;
	//--------------------------------------------------------------------------
	//getchar();
do
{
	do
	{
		k++;
    	for(int i=0; i<row; i++)
			for(int j=0; j<col; j++)
    		{
				if(Politica[i][j][0] == 1)
				{
					if( (j-1)<0)
   	 					Vtemp[i][j] =  Pr*(reward + gamma*V[i][j]); //mantem
					else
   	 					Vtemp[i][j] =  Pr*(reward + gamma*V[i][j-1]); //left
				}

				if(Politica[i][j][1] == 1)
				{
					if( (j+1)>=col)
   	 					Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
					else
						Vtemp[i][j] = Pr*(reward + gamma*V[i][j+1]); //right
				}

				if(Politica[i][j][2] == 1)
				{			
					if( (i-1)<0)
   	 					Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
					else
   	 					Vtemp[i][j] = Pr*(reward + gamma*V[i-1][j]); //top
				}

				if(Politica[i][j][3] == 1)
				{	
					if( (i+1)>=row)
   	 					Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
					else
						Vtemp[i][j] = Pr*(reward + gamma*V[i+1][j]); //down
				}
   			}

		//Atualiza o valor de V(s) e calcula o delta -----------------
		delta=0;
		double tempDelta=0;
    	for(int i=0; i<row; i++)
			for(int j=0; j<col; j++)
    		{
				temp=V[i][j];
				V[i][j] = Vtemp[i][j];

				if((i==0 && j==0) || (i==(row-1) && j==(col-1)))
					V[i][j] = 0;

				// pega o max(delta)------------
				tempDelta = abs(temp - V[i][j]);
				if(tempDelta>delta)
					delta = tempDelta;
				//------------------------------
			}
		//------------------------------------------------------------

		//imprime os valores V(s) se delta for menor que erro --------------
		if(delta < erro)
		{
			std::cout<<"K = "<<k<<std::endl;
	   		for(int i=0; i<row; i++)
			{
				for(int j=0; j<col; j++)
   					 printf("%4.2f\t",V[i][j]);
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		}
		//------------------------------------------------------------------
	}while(delta > erro);

	//---------------------------------------------------------------------------------
	//--------------  Inicializa o calculo da politica---------------------------------
	//- Calcula o Vmax ---------------------------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			if( (j-1)<0)
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j-1]); //left

			Vmax[i][j] = Vtemp[i][j];

			if( (j+1)>=col)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i][j+1]); //right

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			if( (i-1)<0)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i-1][j]); //top

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			if( (i+1)>=row)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i+1][j]); //down

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			Vtemp[i][j] = Vmax[i][j]; // Atualiza Vtemp com o Valor máximo de V(s)
   		}
	//----------------------------------------------------------------------

	//Calcula a melhor política---------------------------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			// Armazena temporariamente a politica----
			tempPolitica[i][j][0] = Politica[i][j][0];
			tempPolitica[i][j][1] = Politica[i][j][1];
			tempPolitica[i][j][2] = Politica[i][j][2];
			tempPolitica[i][j][3] = Politica[i][j][3];
			//----------------------------------------

			if( (j-1)<0)
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j-1]); //left

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][0] = 0;
			else
				Politica[i][j][0] = 1;				

			if( (j+1)>=col)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i][j+1]); //right

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][1] = 0;
			else
				Politica[i][j][1] = 1;

			if( (i-1)<0)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i-1][j]); //top

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][2] = 0;
			else
				Politica[i][j][2] = 1;

			if( (i+1)>=row)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i+1][j]); //down

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][3] = 0;
			else
				Politica[i][j][3] = 1;
   		}
	//-------------------------------------------------------------------------------

	//Imprime a politica e verifica se a politica anterior é diferente da atual------
	policyInstable = 0;
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			//Imprime a melhor politica---------
			if(Politica[i][j][0] == 1)
				std::cout<<"<";
			if(Politica[i][j][1] == 1)
				std::cout<<">";	
			if(Politica[i][j][2] == 1)
				std::cout<<"^";	
			if(Politica[i][j][3] == 1)
				std::cout<<"v";			
			std::cout<<"\t\t";
			//-----------------------------------

			//verifica se a politica anterior é diferente da atual---
			if(Politica[i][j][0] != tempPolitica[i][j][0])
				policyInstable = 1;
			if(Politica[i][j][1] != tempPolitica[i][j][1])
				policyInstable = 1;
			if(Politica[i][j][2] != tempPolitica[i][j][2])
				policyInstable = 1;
			if(Politica[i][j][3] != tempPolitica[i][j][3])
				policyInstable = 1;
			//-------------------------------------------------------
		}
		std::cout<<std::endl;
   	}
	std::cout<<std::endl;
	//------------------------------------------------------------------------------------
	//getchar();
}while(policyInstable);

}
////==============================================================================================
////-------------------- Value Iteration ---------------------------------------------------------
////==============================================================================================
void SGW::valueIteration(unsigned int row, unsigned int col)
{
std::cout<<"Value Iteration"<<std::endl;

double			erro=0.000001; //erro desejado
double 			gamma = 1;
double			reward = -1;
int 			k=0;
double Pr=1;
double Vtemp[row][col];
double temp;
double delta =0;
double 	V[row][col];			//state-value
double 	Vmax[row][col];			//state-value máximo
bool	Politica[row][col][4]; 	// Politica[row][col][0] = LEFT
								// Politica[row][col][1] = RIGHT
								// Politica[row][col][2] = UP
								// Politica[row][col][3] = DOWN

	//Inicializa a política com possibilidades aleatória e V(s)=0--------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
		{
			V[i][j]  = 0; 	//inicializa V(s)=0
			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][0] = 0; //se zero não vai ter left na politica
			else
				Politica[i][j][0] = 1; //se 1 significa que vai ter left na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][1] = 0; //se zero não vai ter right na politica
			else
				Politica[i][j][1] = 1; //se 1 significa que vai ter right na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][2] = 0; //se zero não vai ter top na politica
			else
				Politica[i][j][2] = 1; //se 1 significa que vai ter top na politica

			if(((rand()/(double)RAND_MAX)) > 0.5)
				Politica[i][j][3] = 0; //se zero não vai ter down na politica
			else
				Politica[i][j][3] = 1; //se 1 significa que vai ter down na politica
		}
	//----------------------------------------------------------------------------

do
{
	k++;
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			if( (j-1)<0)
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j-1]); //left

			Vmax[i][j] = Vtemp[i][j];

			if( (j+1)>=col)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i][j+1]); //right

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			if( (i-1)<0)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i-1][j]); //top

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			if( (i+1)>=row)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i+1][j]); //down

			if(Vmax[i][j] < Vtemp[i][j])
				Vmax[i][j] = Vtemp[i][j];

			Vtemp[i][j] = Vmax[i][j]; // Atualiza Vtemp com o Valor máximo de V(s)
   		}

	//Atualiza o valor de V(s) e calcula o delta -----------------
	delta=0;
	double tempDelta=0;
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			temp=V[i][j];
			V[i][j] = Vtemp[i][j];

			if((i==0 && j==0) || (i==(row-1) && j==(col-1)))
				V[i][j] = 0;

			// pega o max(delta)------------
			tempDelta = abs(temp - V[i][j]);
			if(tempDelta>delta)
				delta = tempDelta;
			//------------------------------
		}
	//------------------------------------------------------------

	//imprime os valores V(s)--------------
	if(k<5 || k==10 || delta < erro)
	{
	std::cout<<"K = "<<k<<std::endl;
	    for(int i=0; i<row; i++)
		{
			for(int j=0; j<col; j++)
   				 printf("%1.2f\t",V[i][j]);
			std::cout<<std::endl;
		}
	std::cout<<std::endl;
	}
	//-------------------------------------
}while(delta > erro);

	//Calcula a melhor política---------------------------------------------
    for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
    	{
			if( (j-1)<0)
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] =  Pr*(reward + gamma*V[i][j-1]); //left

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][0] = 0;
			else
				Politica[i][j][0] = 1;				

			if( (j+1)>=col)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i][j+1]); //right

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][1] = 0;
			else
				Politica[i][j][1] = 1;

			if( (i-1)<0)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i-1][j]); //top

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][2] = 0;
			else
				Politica[i][j][2] = 1;

			if( (i+1)>=row)
   	 			Vtemp[i][j] = Pr*(reward + gamma*V[i][j]); //mantem
			else
				Vtemp[i][j] = Pr*(reward + gamma*V[i+1][j]); //down

			if(Vmax[i][j] > Vtemp[i][j])
				Politica[i][j][3] = 0;
			else
				Politica[i][j][3] = 1;
   		}
	//-------------------------------------------------------------------------------

	//Imprime a melhor politica---------------------------------------------
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			if(Politica[i][j][0] == 1)
				std::cout<<"<";
			if(Politica[i][j][1] == 1)
				std::cout<<">";	
			if(Politica[i][j][2] == 1)
				std::cout<<"^";	
			if(Politica[i][j][3] == 1)
				std::cout<<"v";			
			std::cout<<"\t\t";
		}
	std::cout<<std::endl;
   	}
	//----------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------
