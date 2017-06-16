/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#ifdef _INTERAKCJA


	/******************* SZABLON **************************/

	// DEFINICJE FUNKCJI OBS£UGUJ¥CYCH ZDARZENIA MYSZY I KLAWIATURY	

void PrzyciskMyszyWcisniety (int button, int state, int x, int y)
{
	SzablonPrzyciskMyszyWcisniety (button, state, x, y); // wywolanie standardowej obslugi zdarzen szablonu 


	//*************************************************************
	// tu mo¿na umieœciæ kod obs³uguj¹cy wciœniêcie przycisku myszy









}

void RuchKursoraMyszy (int x, int y)
{
	SzablonRuchKursoraMyszy (x, y); // wywolanie standardowej obslugi zdarzen szablonu 

	//****************************************************
	//tu mo¿na umieœciæ kod obs³uguj¹cy ruch kursora myszy









}

void KlawiszKlawiaturyWcisniety (GLubyte key, int x, int y)
{
	SzablonKlawiszKlawiaturyWcisniety (key, x, y);	// wywolanie standardowej obslugi zdarzen szablonu 
	
	//*******************************************************************************
	// tu mo¿na umieœciæ kod obs³uguj¹cy wciœniêcie klawisza klawiatury, przyk³adowo:
	
	switch (key) 
	{
		case 'k':    /* 'k' to koniec programu */
			exit(1);
			break;
	
	}










}
void KlawiszSpecjalnyWcisniety (GLint key, int x, int y)
{

	//*******************************************************************************
	// tu mo¾na umie˜ci† kod obsˆuguj¥cy wci˜ni©cie specjalnego klawisza klawiatury, przykˆadowo:
	
	switch (key)	// GLUT_KEY_F1 .. GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

	{
		case GLUT_KEY_LEFT:

			break;
		case GLUT_KEY_RIGHT:

			break;
		case GLUT_KEY_UP:

			break;
		case GLUT_KEY_DOWN:

			break;

	}
}

	/******************************************************/

#undef _INTERAKCJA
#endif
