/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#ifdef _DEFINICJE


	/******************* SZABLON **************************/



	// DEFINICJE ZMIENNYCH	

	GLfloat	 spotDirectionLight1[4];

	float car1X = 0;
	float car1XSpeed = 0;

	float car1Z = 0;
	float car1ZSpeed = 0.3;
	float tankerSpeed = 0.3;
	float tankerPos = 0;

	float samZ = 0;
	bool kierunek = true;
	float predkosc = 0.35;

	// PIGS -----------------------------
	float pigVelocity = 0.1;
	float pigAngle = 0.1;
	bool pigTurn = false;
	float pigPosition = 1.0;
	enum PigDirection { FRONT, BACK };
	PigDirection pigDir = FRONT;
	// PIGS -----------------------------




	/******************************************************/
#undef _DEFINICJE
#endif
