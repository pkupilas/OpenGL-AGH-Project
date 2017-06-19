/*

C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
(C) Micha³ Turek.

*/

#ifdef _RYSOWANIE


/******************* SZABLON **************************/




// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpoœrednio w 3ds. 
// Wymagany format pliku: bmp, 24 bity na pixel.

glPushMatrix();
//<<<<<<< HEAD
glTranslatef(0, 1, 0);
rysujModel("teren"); // malowanie pod³o¿a
//rysujModel("niebo"); // malowanie nieba
//=======
//	glTranslatef(0, 1, 0);
//	rysujModel("teren"); // malowanie pod³o¿a
//	rysujModel("niebo"); // malowanie nieba
//>>>>>>> f8d6ca28332421e0793189fb183d240746b15220
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

glPushMatrix();
	glTranslatef(100, -5, -50);
	for (int i = 0; i < 6; i++)
	{
		rysujModel("housenew4");
		glTranslatef(0, 0, 20);
		rysujModel("housenew4");
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(-100, -5, -50);
	for (int i = 0; i < 3; i++)
	{
		rysujModel("housenew4");
		glTranslatef(0, 0, 30);
		rysujModel("housenew4");
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(40, -5, 90);
	for (int i = 0; i < 3; i++)
	{
		rysujModel("housenew4");
		glTranslatef(0, 0, 20);
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
		glTranslatef(0, 0, -9);
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
	if (posPig[0] < -20)
	{
		pigDir = BACK;
	}
	else
	{
		posPig[0] -= pigVelocity;
	}
}
else
{
	if (posPig[0] > 0)
	{
		pigDir = FRONT;
	}
	else
	{
		posPig[0] += pigVelocity;
	}
}

glPushMatrix();
	glTranslatef(25, -5, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(angPig[0]++, 0, 1, 0);
	glTranslatef(2, 0, -2);
	rysujModel("pig");
glPopMatrix();

glPushMatrix();
	glTranslatef(25, -5, 0);
	glTranslatef(3, 0, posPig[0]);
	rysujModel("pig");
glPopMatrix();
/*------ pigs ----*/

/*------------------------ PIGS ------------------------*/

/*------------------------ FENCE2 ------------------------*/
glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	glTranslatef(0, -8, -150);
	for (int i = 0; i < 10; i++)
	{
		rysujModel("fence2");
		glTranslatef(8, 0, 0);
		rysujModel("fence2Curve");
		glTranslatef(8, 0, 0);
		rysujModel("fence2Other");
	}

	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0, 160);

	for (int i = 0; i < 26; i++)
	{
		rysujModel("fence2");
		glTranslatef(8, 0, 0);
		rysujModel("fence2Curve");
		glTranslatef(8, 0, 0);
		rysujModel("fence2Other");
	}
glPopMatrix();
/*------------------------ FENCE2 ------------------------*/

/*------------------------ HORSE ------------------------*/
if (horseDir == FRONT)
{
	if (posHorse[0] < -10)
	{
		horseDir = BACK;
	}
	else
	{
		posHorse[0] -= horseVelocity;
	}
}
else
{
	if (posHorse[0] > 0)
	{
		horseDir = FRONT;
	}
	else
	{
		posHorse[0] += horseVelocity;
	}
}

glPushMatrix();
	glTranslatef(30, -5, -10);
	glRotatef(90, 0, 1, 0);
	glTranslatef(posHorse[0], 0, 3);
	rysujModel("horse");
glPopMatrix();

glPushMatrix();
	glTranslatef(40, -5, -10);
	glRotatef(angHorse[0]++, 0, 1, 0);
	glTranslatef(2, 0, 2);
	rysujModel("horse");
glPopMatrix();
/*------------------------ HORSE ------------------------*/

/*------------------------ BUILD ------------------------*/
glPushMatrix();
	glTranslatef(35, -5, 30);
	rysujModel("build");
	glTranslatef(0, 0, 40);
	rysujModel("build");
glPopMatrix();
/*------------------------ BUILD ------------------------*/

/*------------------------ TABLEBARREL ------------------------*/
glPushMatrix();
	glTranslatef(24, -5, 7);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("tableBarrel");
		glTranslatef(0, 0, 7);
	}
glPopMatrix();
/*------------------------ TABLEBARREL ------------------------*/

/*------------------------ TABLE ------------------------*/
glPushMatrix();
	glTranslatef(15, -5, 40);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("table");
		glTranslatef(0, 0, 7);
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(15, -3.5, 39);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("pot1");
		glTranslatef(0, 0, 7);
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(15, -3.5, 41);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("pot2");
		glTranslatef(0, 0, 7);
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(15, -3.7, 40);
	glRotatef(90, 1, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("sword");
		glTranslatef(0, 7, 0);
	}
glPopMatrix();
/*------------------------ TABLE ------------------------*/

/*------------------------ SHEDS ------------------------*/
glPushMatrix();
	glTranslatef(35, -5, 40);

	for (int i = 0; i < 3; i++)
	{
		rysujModel("shed");
		glTranslatef(0, 0, 9);
		}
glPopMatrix();
/*------------------------ SHEDS ------------------------*/

/*------------------------ MARKETSTANDERS ------------------------*/
glPushMatrix();
	glTranslatef(40, -5, 60);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("mrkStnd");
		glTranslatef(7, 0, 0);
	}
glPopMatrix();
/*------------------------ MARKETSTANDERS ------------------------*/

/*------------------------ FRUITBOXES ------------------------*/
glPushMatrix();
	glTranslatef(32, -5, 60);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("fruitBox");
		glTranslatef(1, 0, 0);
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(32, -5, 51);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("fruitBoxv2");
		glTranslatef(1, 0, 0);
	}
glPopMatrix();

glPushMatrix();
	glTranslatef(32, -5, 43);
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("fruitBoxv3");
		glTranslatef(1, 0, 0);
	}
glPopMatrix();
/*------------------------ FRUITBOXES ------------------------*/

/*------------------------ GRAINSACKS ------------------------*/
glPushMatrix();
	glTranslatef(32, -4.5, 44);

	glTranslatef(0, 0, 0.5);
	rysujModel("grain");

	glTranslatef(0, 0, 1.5);
	rysujModel("grain2");

	glTranslatef(-1, 0, -1);
	rysujModel("grain3");

	glTranslatef(1, 0, 7.5);

	glTranslatef(0, 0, 0.5);
	rysujModel("grain2");

	glTranslatef(0, 0, 1.5);
	rysujModel("grain3");

	glTranslatef(-1, 0, -1);
	rysujModel("grain");
glPopMatrix();
/*------------------------ GRAINSACKS ------------------------*/

/*------------------------ FISHES ------------------------*/
glPushMatrix();
	glTranslatef(32, -4.7, 43);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("fish");
		glTranslatef(0, 1, 0);
		rysujModel("fish");
		glTranslatef(0, 1, 0);
		glTranslatef(0, -5.5, 0);
	}
glPopMatrix();
/*------------------------ FISHES ------------------------*/

/*------------------------ CORN ------------------------*/
glPushMatrix();
	glTranslatef(32, -4, 51);
	glRotatef(180, 0, 1, 0);
	glRotatef(-30, 0, 0, 1);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("corn");
		glTranslatef(0, 0, 0.3);
		rysujModel("corn");
		glTranslatef(0, 0, 0.6);
	}
glPopMatrix();
/*------------------------ CORN ------------------------*/

/*------------------------ BREAD ------------------------*/
glPushMatrix();
	glTranslatef(32, -4.5, 60.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(-30, 0, 0, 1);
	for (int i = 0; i < 5; i++)
	{
		rysujModel("bread");
		glTranslatef(0, 0, 0.3);
		rysujModel("bread");
		glTranslatef(0, 0, 0.7);
	}
glPopMatrix();
/*------------------------ BREAD ------------------------*/

/*------------------------ DIRTPILES ------------------------*/
glPushMatrix();
	glTranslatef(60, -5, -50);

	for (int j = 0; j < 13; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			rysujModel("dirtpile1");
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-10, 0, 10);
	}
glPopMatrix();
/*------------------------ DIRTPILES ------------------------*/

/*------------------------ FISHRACKS ------------------------*/
glPushMatrix();
	glTranslatef(60, -5, -50);

	for (int j = 0; j < 13; j++){
		for (int i = 0; i < 4; i++)
		{
			rysujModel("fishRack");
			glTranslatef(3, 0, 0);
		}
		glTranslatef(-12, 0, 10);
	}
glPopMatrix();
/*------------------------ FISHRACKS ------------------------*/

/*------------------------ TENTS ------------------------*/
glPushMatrix();
	glTranslatef(40, -5, -50);
	glScalef(2, 2, 2);
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 4; i++)
	{
		rysujModel("tent");
		glTranslatef(5, 0, 0);
	}
glPopMatrix();
/*------------------------ TENTS ------------------------*/






/******************************************************/


#undef _RYSOWANIE
#endif
