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

	enum Direction { FRONT, BACK };

	// PIGS -----------------------------
	Direction pigDir = FRONT;
	float pigVelocity = 0.1;
	float pigAngle = 0.1;
	bool pigTurn = false;
	float turnBackAngle = 0.0f;
	float turnBackAngleHorse = 90.0f;
	float angPig[] = { 0 };
	float posPig[] = { 1.0 };
	// PIGS -----------------------------

	// HORSES ---------------------------
	Direction horseDir = FRONT;
	float horseVelocity = 0.2;
	float angHorse[] = { 0, 0 };
	float posHorse[] = { 1.0, 1.0 };
	// HORSES ---------------------------

	/******************************************************/
#undef _DEFINICJE
#endif
