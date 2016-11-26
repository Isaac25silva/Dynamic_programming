/*-------------------------------------------------------------------------
***************************************************************************
* @file classe.h
* @author Isaac Jesus da Silva - FEI
* @version V0.0.1
* @created 18/11/2014
* @Modified 24/11/2014
* @e-mail isaac25silva@yahoo.com.br
***************************************************************************
Arquivo de cabeçalho que contem a classe da Programação Dinâmica
/------------------------------------------------------------------------*/
#ifndef CLASSE_H
#define CLASSE_H
#include <vector>
#include <fstream>

//-------------------------------------------------------------------------
class SGW
{
	public:

    	/*! Construtor. */
    	SGW(){ srand (time(NULL));};
    	/*! Destrutor. */
    	//~SGW();

    /*!Método que executa iterative policy evaluation.
	* @param row - Número de linhas do grid world.
	* @param col - Número de colunas do grid world.
    * @return Não retorna valores. */
	void policyEvaluation(unsigned int row, unsigned int col);

    /*!Método que executa policy iteration.
	* @param row - Número de linhas do grid world.
	* @param col - Número de colunas do grid world.
    * @return Não retorna valores. */
	void policyIteration(unsigned int row, unsigned int col);

    /*!Método que executa value iteration.
	* @param row - Número de linhas do grid world.
	* @param col - Número de colunas do grid world.
    * @return Não retorna valores. */
	void valueIteration(unsigned int row, unsigned int col);

	private:

};
 
/// \example classe.cpp
 
#endif
