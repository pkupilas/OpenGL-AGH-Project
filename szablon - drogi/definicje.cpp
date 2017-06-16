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

	/******************************************************/

	float firstBoneX = 0;
	float boneVelocity = 0.1;

	enum BoneDirection { FRONT, BACK};
	BoneDirection boneDir = FRONT;

#undef _DEFINICJE
#endif
