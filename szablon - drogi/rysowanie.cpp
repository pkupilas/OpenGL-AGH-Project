/*

C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
(C) Micha³ Turek.

*/

#ifdef _RYSOWANIE


/******************* SZABLON **************************/




// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpoœrednio w 3ds. 
// Wymagany format pliku: bmp, 24 bity na pixel.

glPushMatrix();
glTranslatef(0, 1, 0);
rysujModel("teren"); // malowanie pod³o¿a
//rysujModel("niebo"); // malowanie nieba
glPopMatrix();


/*------------------------ HOUSES ------------------------*/
glPushMatrix();
	glTranslatef(-50, -5, -50);
	for (int i = 0; i < 8; i++)
	{
		rysujModel("housenew4");
		glTranslatef(0, 0, 20);
		rysujModel("housenew4");
	}
glPopMatrix();
/*------------------------ HOUSES ------------------------*/

/*------------------------ FENCES ------------------------*/
glPushMatrix();
	glTranslatef(-30, -5, -120);
	glRotatef(90, 0, 1, 0);

	for (int i = 0; i < 50; i++)
	{
		rysujModel("fence");
		glTranslatef(-3, 0, 0);
		rysujModel("fence_broken");
		glTranslatef(-3, 0, 0);
	}
glPopMatrix();
/*------------------------ FENCES ------------------------*/

/*------------------------ BARRELS ------------------------*/
glPushMatrix();
	glTranslatef(-40, -5, -55);
	for (int i = 0; i < 9; i++)
	{
		rysujModel("barrel");
		glTranslatef(0, 0, 5);
		rysujModel("barrel");
		glTranslatef(0, 0, 15);
	}
glPopMatrix();
/*------------------------ BARRELS ------------------------*/

/*------------------------ CHAIRS ------------------------*/
glPushMatrix();
	glTranslatef(-40, -5, -51);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("chair");
		glTranslatef(0, 0, 20);
	}
glPopMatrix();
/*------------------------ CHAIRS ------------------------*/

/*------------------------ CAULDRONS ------------------------*/
glPushMatrix();
	glTranslatef(-40, -5, -49);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("cauldron");
		glTranslatef(0, 0, 20);
	}
glPopMatrix();
/*------------------------ CAULDRONS ------------------------*/

/*------------------------ BENCHES ------------------------*/
glPushMatrix();
	glTranslatef(-39, -5, -51);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("bench");
		glTranslatef(0, 0, 20);
	}
glPopMatrix();
/*------------------------ BENCHES ------------------------*/

/*------------------------ CARTS ------------------------*/
glPushMatrix();
	glTranslatef(-50, -3, -60);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 9; i++)
	{
		rysujModel("cart");
		glTranslatef(-20, 0, 0);
	}
glPopMatrix();
/*------------------------ CARTS ------------------------*/

/*------------------------ LATERNS ------------------------*/
glPushMatrix();
glTranslatef(0, -5, -50);
glScalef(2, 3, 2);
glRotatef(180, 0, 1, 0);

rysujModel("latern");
for (int i = 0; i < 10; i++)
{
	rysujModel("latern");
	glTranslatef(0, 0, -10);
}

glPopMatrix();
/*------------------------ LATERNS ------------------------*/

/*------------------------ PIGS ------------------------*/

/*------ farmhouse ----*/
glPushMatrix();
	glTranslatef(20, -5, -25);
	for (int i = 0; i < 4; i++)
	{
		glRotatef(90, 0, 1, 0);
		for (int f = 0; f < 5; f++)
		{
			rysujModel("fence");
			glTranslatef(-3, 0, 0);
			rysujModel("fence_broken");
			glTranslatef(-3, 0, 0);
		}
	}
glPopMatrix();
/*------ farmhouse ----*/

/*------ pumpkins -----*/
glPushMatrix();
	glTranslatef(22, -5, -25);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("pumpkinPitch");
		glTranslatef(3, 0, 0);
	}
	glTranslatef(-3, 0, 3);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("pumpkinPitch");
		glTranslatef(-3, 0, 0);
	}
glPopMatrix();
/*------ pumpkins -----*/

/*------ mushrooms -----*/
glPushMatrix();
	glTranslatef(22, -5, 2);
	glScalef(2, 2, 2);
	for (int i = 0; i < 13; i++)
	{
		rysujModel("mushroom");
		glTranslatef(1, 0, 0);
	}
	glTranslatef(-1, 0, 1);
	for (int i = 0; i < 13; i++)
	{
		rysujModel("mushroom");
		glTranslatef(-1, 0, 0);
	}
glPopMatrix();
/*------ mushrooms -----*/



/*------ pigs ----*/
if (pigDir == FRONT)
{
	if (pigPosition < -20)
	{
		pigDir = BACK;
	}
	else
	{
		pigPosition -= pigVelocity;
	}
}
else
{
	if (pigPosition > 0)
	{
		pigDir = FRONT;
	}
	else
	{
		pigPosition += pigVelocity;
	}
}

glPushMatrix();
	glTranslatef(25, -5, 0);
	glTranslatef(3, 0, pigPosition);
	rysujModel("pig");
glPopMatrix();
/*------ pigs ----*/

/*------------------------ PIGS ------------------------*/



/******************************************************/


#undef _RYSOWANIE
#endif
