#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <cstdio>


#define PI 3.14159265358979323846f

//
// GLOBAL PAGE CONTROL
//
// 0 = Cover (Shoumik)
// 1 = Instructions (Shoumik)
// 2 = Airport (Shoumik)
// 3 = Plane Take Off (Niha)
// 4 = Plane Flying (Annesha)
// 5 = Plane Crash and Merged the project(Soykot)
// 6 = Rescue Operation (Hasib)
int currentPage = 0;

void updateMasterSound();


// 1. SHOUMIK'S VARIABLES (SCENES 0, 1, 2)

GLfloat sh_cloudOffset = 0.0f;
GLfloat sh_cloudSpeed = 1.5f;
GLfloat sh_birdOffset = 0.0f;
GLfloat sh_birdSpeed = 2.5f;
GLfloat sh_planePosX = 0.0f;
GLfloat sh_planeSpeed = 7.0f;
bool    sh_planeMoving = false;
GLfloat sh_bgPlanePosX = -500.0f;
GLfloat sh_bgPlaneSpeed = 1.5f;


// 2. NIHA'S VARIABLES (SCENE 3)

float niha_planeX = 0.0f;
float niha_planeY = 0.0f;
float niha_planeAngle = 0.0f;
float niha_birdMove = 0.0f;
float niha_wingFlap = 0.0f;
float niha_birdSpeed = 1.5f;
float niha_planeSpeedMultiplier = 1.0f;
bool soundMutedNK = false;

// 3. ANNESHA'S VARIABLES (SCENE 4)

float ann_planeX = -600.0f;
float ann_backgroundX = 0.0f;
float ann_speed = 2.0f;
bool ann_isMoving = true;
bool ann_isMuted = false;



// 4. SOYKOT'S VARIABLES (SCENE 5)

GLfloat planeXSoykot = -200.0f;
GLfloat planeYSoykot = 200.0f;
GLfloat planeSpeedXSoykot = 1.8f;
GLfloat planeSpeedYSoykot = 1.2f;
GLfloat birdXSoykot = 0.0f;
GLfloat birdSpeedSoykot = 1.0f;
GLfloat boatXSoykot = 0.0f;
GLfloat boatSpeedSoykot = 0.5f;
bool isCrashedSoykot = false;
bool moveSoykot = false;


// 5. HASIB'S VARIABLES (SCENE 6)

bool hasib_isNight = false;
bool hasib_isMuted = false;
GLfloat hasib_positionW = 0.0f;
GLfloat hasib_speedW = 1.0f;
bool hasib_isMovingCloud = true;
GLfloat hasib_positionC = -300.0f;
GLfloat hasib_speedC = 0.80f;
bool hasib_isMovingBird = true;
GLfloat hasib_positionBI = -450.0f;
GLfloat hasib_speedBI = 3.0f;
bool hasib_isMoving = false;
GLfloat hasib_positionB = -450.0f;
GLfloat hasib_rescueY = 0.0f;
GLfloat hasib_speedB = 2.0f;



//   SHOUMIK'S FUNCTIONS

void sh_drawFilledCircle(float x, float y, float radius) {
    int triangleAmount = 50;
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                   y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void sh_renderBitmapString(float x, float y, void* font, const char* string) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void sh_drawSky() {
    glColor3f(0.40f, 0.72f, 0.95f);
    glBegin(GL_POLYGON);
    glVertex2f(-400, 300); glVertex2f(400, 300);
    glVertex2f(400, 100); glVertex2f(-400, 100);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-400, 100); glVertex2f(400, 100);
    glVertex2f(400, 90); glVertex2f(-400, 90);
    glEnd();
}

void sh_drawSkyline() {
    glColor3f(0.58f, 0.62f, 0.68f);

    glBegin(GL_POLYGON);
        glVertex2f(-370, 90);
        glVertex2f(-348, 90);
        glVertex2f(-348, 175);
        glVertex2f(-370, 175);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-345, 90);
        glVertex2f(-312, 90);
        glVertex2f(-312, 148);
        glVertex2f(-345, 148);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-308, 90);
        glVertex2f(-282, 90);
        glVertex2f(-282, 195);
        glVertex2f(-308, 195);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-278, 90);
        glVertex2f(-245, 90);
        glVertex2f(-245, 128);
        glVertex2f(-278, 128);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-240, 90);
        glVertex2f(-215, 90);
        glVertex2f(-215, 158);
        glVertex2f(-240, 158);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-210, 90);
        glVertex2f(-190, 90);
        glVertex2f(-190, 115);
        glVertex2f(-210, 115);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(195, 90);
        glVertex2f(220, 90);
        glVertex2f(220, 118);
        glVertex2f(195, 118);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(225, 90);
        glVertex2f(255, 90);
        glVertex2f(255, 162);
        glVertex2f(225, 162);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(260, 90);
        glVertex2f(292, 90);
        glVertex2f(292, 188);
        glVertex2f(260, 188);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(298, 90);
        glVertex2f(325, 90);
        glVertex2f(325, 148);
        glVertex2f(298, 148);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(330, 90);
        glVertex2f(358, 90);
        glVertex2f(358, 170);
        glVertex2f(330, 170);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(363, 90);
        glVertex2f(385, 90);
        glVertex2f(385, 130);
        glVertex2f(363, 130);
    glEnd();

    glColor3f(0.50f, 0.54f, 0.60f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-180, 90);
        glVertex2f(-90, 90);
        glVertex2f(-90, 120);
        glVertex2f(-135, 138);
        glVertex2f(-180, 120);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-130, 90);
        glVertex2f(-130, 135);
        glVertex2f(-142, 90);
        glVertex2f(-142, 135);
    glEnd();
}

void sh_drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    sh_drawFilledCircle(x, y, 28);
    sh_drawFilledCircle(x + 30, y + 12, 34);
    sh_drawFilledCircle(x + 62, y + 5, 26);
    sh_drawFilledCircle(x + 18, y - 8, 22);
    sh_drawFilledCircle(x + 48, y - 5, 20);
}

void sh_drawBird(float x, float y) {
    glColor3f(0.08f, 0.08f, 0.08f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - 14, y + 8);
        glVertex2f(x, y);
        glVertex2f(x + 14, y + 8);
    glEnd();
}

void sh_drawGround() {
    glColor3f(0.22f, 0.22f, 0.22f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -300);
        glVertex2f(400, -300);
        glVertex2f(400, -5);
        glVertex2f(-400, -5);
    glEnd();

    glColor3f(0.27f, 0.27f, 0.27f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -200);
        glVertex2f(400, -200);
        glVertex2f(400, -110);
        glVertex2f(-400, -110);
    glEnd();

    glColor3f(0.92f, 0.78f, 0.08f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
        glVertex2f(-400, -130);
        glVertex2f(400, -130);
        glVertex2f(-400, -165);
        glVertex2f(400, -165);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    for (int i = -390; i < 400; i += 45) {
        glBegin(GL_LINES);
            glVertex2f(i, -148);
            glVertex2f(i + 22, -148);
        glEnd();
    }

    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-400, -108);
        glVertex2f(400, -108);
        glVertex2f(-400, -250);
        glVertex2f(400, -250);
    glEnd();
}

void sh_drawTerminal() {
    glColor3f(0.72f, 0.68f, 0.62f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -5);
        glVertex2f(400, -5);
        glVertex2f(400, 85);
        glVertex2f(-400, 85);
    glEnd();

    glColor3f(0.48f, 0.46f, 0.44f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, 78);
        glVertex2f(400, 78);
        glVertex2f(400, 92);
        glVertex2f(-400, 92);
    glEnd();

    glColor3f(0.55f, 0.52f, 0.48f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -5);
        glVertex2f(400, -5);
        glVertex2f(400, 8);
        glVertex2f(-400, 8);
    glEnd();

    glColor3f(0.60f, 0.82f, 0.98f);
    for (int i = -375; i < 390; i += 58) {
        glBegin(GL_POLYGON);
            glVertex2f(i, 15);
            glVertex2f(i + 40, 15);
            glVertex2f(i + 40, 60);
            glVertex2f(i, 60);
        glEnd();
    }

    glColor3f(0.35f, 0.35f, 0.35f);
    glLineWidth(1.0f);
    for (int i = -375; i < 390; i += 58) {
        glBegin(GL_LINES);
            glVertex2f(i + 20, 15);
            glVertex2f(i + 20, 60);
            glVertex2f(i, 37);
            glVertex2f(i + 40, 37);
        glEnd();
    }

    glColor3f(0.28f, 0.24f, 0.20f);
    for (int i = -360; i < 380; i += 115) {
        glBegin(GL_POLYGON);
            glVertex2f(i, -5);
            glVertex2f(i + 28, -5);
            glVertex2f(i + 28, 12);
            glVertex2f(i, 12);
        glEnd();
    }

    glColor3f(0.15f, 0.25f, 0.55f);
    int gateX[] = { -345, -230, -115, 0, 115, 230 };
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
            glVertex2f(gateX[i], 62);
            glVertex2f(gateX[i] + 30, 62);
            glVertex2f(gateX[i] + 30, 73);
            glVertex2f(gateX[i], 73);
        glEnd();
    }

    glColor3f(0.52f, 0.52f, 0.50f);
    glBegin(GL_POLYGON);
        glVertex2f(-295, -5);
        glVertex2f(-272, -5);
        glVertex2f(-268, -62);
        glVertex2f(-291, -62);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-85, -5);
        glVertex2f(-62, -5);
        glVertex2f(-58, -62);
        glVertex2f(-81, -62);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(125, -5);
        glVertex2f(148, -5);
        glVertex2f(152, -62);
        glVertex2f(129, -62);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    int poleX[] = { -370, -200, -30, 140, 310, 390 };
    for (int i = 0; i < 6; i++) {
        glBegin(GL_LINES);
            glVertex2f(poleX[i], -5);
            glVertex2f(poleX[i], 90);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(poleX[i] - 8, 90);
            glVertex2f(poleX[i] + 8, 90);
        glEnd();
    }
}

void sh_drawAirplane(float cx, float cy, float s) {
    glColor3f(0.94f, 0.94f, 0.94f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 105 * s, cy + 0 * s);
        glVertex2f(cx - 95 * s, cy - 10 * s);
        glVertex2f(cx + 78 * s, cy - 10 * s);
        glVertex2f(cx + 98 * s, cy + 4 * s);
        glVertex2f(cx + 78 * s, cy + 16 * s);
        glVertex2f(cx - 95 * s, cy + 16 * s);
    glEnd();

    glColor3f(0.80f, 0.80f, 0.82f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 95 * s, cy - 10 * s);
        glVertex2f(cx + 78 * s, cy - 10 * s);
        glVertex2f(cx + 78 * s, cy - 2 * s);
        glVertex2f(cx - 95 * s, cy - 2 * s);
    glEnd();

    glColor3f(0.08f, 0.25f, 0.72f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 95 * s, cy + 5 * s);
        glVertex2f(cx + 80 * s, cy + 5 * s);
        glVertex2f(cx + 80 * s, cy + 10 * s);
        glVertex2f(cx - 95 * s, cy + 10 * s);
    glEnd();

    glColor3f(0.88f, 0.88f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 5 * s, cy - 10 * s);
        glVertex2f(cx + 35 * s, cy - 10 * s);
        glVertex2f(cx + 10 * s, cy - 42 * s);
        glVertex2f(cx - 35 * s, cy - 42 * s);
    glEnd();

    glColor3f(0.75f, 0.75f, 0.78f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 5 * s, cy - 10 * s);
        glVertex2f(cx + 35 * s, cy - 10 * s);
        glVertex2f(cx + 35 * s, cy - 18 * s);
        glVertex2f(cx - 5 * s, cy - 18 * s);
    glEnd();

    glColor3f(0.32f, 0.32f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(cx + 0 * s, cy - 28 * s);
        glVertex2f(cx + 32 * s, cy - 28 * s);
        glVertex2f(cx + 32 * s, cy - 40 * s);
        glVertex2f(cx + 0 * s, cy - 40 * s);
    glEnd();

    glColor3f(0.12f, 0.12f, 0.14f);
    glBegin(GL_POLYGON);
        glVertex2f(cx + 28 * s, cy - 29 * s);
        glVertex2f(cx + 34 * s, cy - 29 * s);
        glVertex2f(cx + 34 * s, cy - 39 * s);
        glVertex2f(cx + 28 * s, cy - 39 * s);
    glEnd();

    glColor3f(0.20f, 0.20f, 0.22f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 2 * s, cy - 29 * s);
        glVertex2f(cx + 2 * s, cy - 29 * s);
        glVertex2f(cx + 2 * s, cy - 39 * s);
        glVertex2f(cx - 2 * s, cy - 39 * s);
    glEnd();

    glColor3f(0.08f, 0.25f, 0.72f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 105 * s, cy + 0 * s);
        glVertex2f(cx - 82 * s, cy + 16 * s);
        glVertex2f(cx - 88 * s, cy + 52 * s);
        glVertex2f(cx - 108 * s, cy + 52 * s);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_drawFilledCircle(cx - 96 * s, cy + 34 * s, 9 * s);

    glColor3f(0.88f, 0.88f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 108 * s, cy + 4 * s);
        glVertex2f(cx - 78 * s, cy + 4 * s);
        glVertex2f(cx - 72 * s, cy - 10 * s);
        glVertex2f(cx - 95 * s, cy - 10 * s);
        glVertex2f(cx - 115 * s, cy - 2 * s);
    glEnd();

    glColor3f(0.55f, 0.80f, 0.98f);
    glBegin(GL_POLYGON);
        glVertex2f(cx + 72 * s, cy + 4 * s);
        glVertex2f(cx + 84 * s, cy + 4 * s);
        glVertex2f(cx + 88 * s, cy + 10 * s);
        glVertex2f(cx + 72 * s, cy + 13 * s);
    glEnd();

    glColor3f(0.50f, 0.78f, 0.95f);
    for (int i = 0; i < 12; i++) {
        glBegin(GL_POLYGON);
            glVertex2f(cx + (60 - i * 14) * s, cy + 13 * s);
            glVertex2f(cx + (65 - i * 14) * s, cy + 13 * s);
            glVertex2f(cx + (65 - i * 14) * s, cy + 16 * s);
            glVertex2f(cx + (60 - i * 14) * s, cy + 16 * s);
        glEnd();
    }

    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(3.0f * s);
    glBegin(GL_LINES);
        glVertex2f(cx - 10 * s, cy - 10 * s);
        glVertex2f(cx - 10 * s, cy - 22 * s);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(cx + 68 * s, cy - 10 * s);
        glVertex2f(cx + 68 * s, cy - 22 * s);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    sh_drawFilledCircle(cx - 10 * s, cy - 22 * s, 6 * s);
    sh_drawFilledCircle(cx + 68 * s, cy - 22 * s, 5 * s);
}

void sh_drawGroundVehicles() {
    glColor3f(0.95f, 0.45f, 0.05f);

    glBegin(GL_TRIANGLES);
        glVertex2f(-340, -5);
        glVertex2f(-334, -5);
        glVertex2f(-337, 6);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-310, -5);
        glVertex2f(-304, -5);
        glVertex2f(-307, 6);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-130, -5);
        glVertex2f(-124, -5);
        glVertex2f(-127, 6);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-100, -5);
        glVertex2f(-94, -5);
        glVertex2f(-97, 6);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-385, -5);
        glVertex2f(-360, -5);
        glVertex2f(-360, 5);
        glVertex2f(-385, 5);
    glEnd();

    glColor3f(0.15f, 0.15f, 0.15f);
    sh_drawFilledCircle(-380, -5, 3);
    sh_drawFilledCircle(-365, -5, 3);
}

void sh_drawBgSky() {
    glColor3f(0.20f, 0.38f, 0.52f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, 300);
        glVertex2f( 400, 300);
        glVertex2f( 400, 90);
        glVertex2f(-400, 90);
    glEnd();

    glColor3f(0.18f, 0.32f, 0.46f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, 90);
        glVertex2f( 400, 90);
        glVertex2f( 400, -10);
        glVertex2f(-400, -10);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, 90);
        glVertex2f( 400, 90);
        glVertex2f( 400, 82);
        glVertex2f(-400, 82);
    glEnd();
}

void sh_drawBgSkyline() {
    glColor3f(0.18f, 0.20f, 0.26f);

    glBegin(GL_POLYGON);
        glVertex2f(-370, 82);
        glVertex2f(-348, 82);
        glVertex2f(-348, 165);
        glVertex2f(-370, 165);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-345, 82);
        glVertex2f(-312, 82);
        glVertex2f(-312, 140);
        glVertex2f(-345, 140);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-308, 82);
        glVertex2f(-282, 82);
        glVertex2f(-282, 185);
        glVertex2f(-308, 185);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-278, 82);
        glVertex2f(-245, 82);
        glVertex2f(-245, 120);
        glVertex2f(-278, 120);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-240, 82);
        glVertex2f(-215, 82);
        glVertex2f(-215, 150);
        glVertex2f(-240, 150);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(225, 82);
        glVertex2f(255, 82);
        glVertex2f(255, 155);
        glVertex2f(225, 155);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(260, 82);
        glVertex2f(292, 82);
        glVertex2f(292, 180);
        glVertex2f(260, 180);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(298, 82);
        glVertex2f(325, 82);
        glVertex2f(325, 140);
        glVertex2f(298, 140);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(330, 82);
        glVertex2f(358, 82);
        glVertex2f(358, 162);
        glVertex2f(330, 162);
    glEnd();
}

void sh_drawBgCloud(float x, float y) {
    glColor3f(0.35f, 0.42f, 0.50f);
    sh_drawFilledCircle(x, y, 28);
    sh_drawFilledCircle(x + 30, y + 12, 34);
    sh_drawFilledCircle(x + 62, y + 5, 26);
    sh_drawFilledCircle(x + 18, y - 8, 22);
    sh_drawFilledCircle(x + 48, y - 5, 20);
}

void sh_drawBgBird(float x, float y) {
    glColor3f(0.22f, 0.28f, 0.35f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - 12, y + 7);
        glVertex2f(x, y);
        glVertex2f(x + 12, y + 7);
    glEnd();
}

void sh_drawBgGround() {
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -300);
        glVertex2f( 400, -300);
        glVertex2f( 400, -8);
        glVertex2f(-400, -8);
    glEnd();

    glColor3f(0.13f, 0.13f, 0.13f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -200);
        glVertex2f( 400, -200);
        glVertex2f( 400, -115);
        glVertex2f(-400, -115);
    glEnd();

    glColor3f(0.28f, 0.24f, 0.02f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-400, -132);
        glVertex2f(400, -132);
        glVertex2f(-400, -168);
        glVertex2f(400, -168);
    glEnd();

    glColor3f(0.22f, 0.22f, 0.22f);
    glLineWidth(1.5f);
    for(int i = -390; i < 400; i += 45) {
        glBegin(GL_LINES);
            glVertex2f(i, -150);
            glVertex2f(i + 22, -150);
        glEnd();
    }
}

void sh_drawBgTerminal() {
    glColor3f(0.24f, 0.22f, 0.18f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -8);
        glVertex2f( 400, -8);
        glVertex2f( 400, 80);
        glVertex2f(-400, 80);
    glEnd();

    glColor3f(0.18f, 0.17f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, 74);
        glVertex2f( 400, 74);
        glVertex2f( 400, 86);
        glVertex2f(-400, 86);
    glEnd();

    glColor3f(0.18f, 0.28f, 0.38f);
    for(int i = -375; i < 390; i += 58) {
        glBegin(GL_POLYGON);
            glVertex2f(i, 15);
            glVertex2f(i + 40, 15);
            glVertex2f(i + 40, 58);
            glVertex2f(i, 58);
        glEnd();
    }
}

void sh_drawBgAirplane(float cx, float cy, float s) {
    glColor3f(0.22f, 0.22f, 0.24f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 105 * s, cy + 0 * s);
        glVertex2f(cx - 95 * s, cy - 10 * s);
        glVertex2f(cx + 78 * s, cy - 10 * s);
        glVertex2f(cx + 98 * s, cy + 4 * s);
        glVertex2f(cx + 78 * s, cy + 16 * s);
        glVertex2f(cx - 95 * s, cy + 16 * s);
    glEnd();

    glColor3f(0.19f, 0.19f, 0.21f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 5 * s, cy - 10 * s);
        glVertex2f(cx + 35 * s, cy - 10 * s);
        glVertex2f(cx + 10 * s, cy - 42 * s);
        glVertex2f(cx - 35 * s, cy - 42 * s);
    glEnd();

    glColor3f(0.20f, 0.20f, 0.22f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 105 * s, cy + 0 * s);
        glVertex2f(cx - 82 * s, cy + 16 * s);
        glVertex2f(cx - 88 * s, cy + 52 * s);
        glVertex2f(cx - 108 * s, cy + 52 * s);
    glEnd();
}
void sh_displayCoverPage() {
    glClearColor(0.06f, 0.08f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sh_drawBgSky();
    sh_drawBgSkyline();

    glPushMatrix();
        glTranslatef(sh_cloudOffset, 0.0f, 0.0f);
        sh_drawBgCloud(-320, 235);
        sh_drawBgCloud(-130, 260);
        sh_drawBgCloud(60, 245);
        sh_drawBgCloud(230, 255);
        sh_drawBgCloud(330, 220);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(sh_birdOffset, 0.0f, 0.0f);
        sh_drawBgBird(-250, 205);
        sh_drawBgBird(-228, 215);
        sh_drawBgBird(-208, 203);
        sh_drawBgBird(30, 230);
        sh_drawBgBird(55, 240);
        sh_drawBgBird(280, 215);
        sh_drawBgBird(305, 224);
    glPopMatrix();

    sh_drawBgGround();
    sh_drawBgTerminal();

    sh_drawBgAirplane(-280, -68, 0.48f);
    sh_drawBgAirplane(-70, -68, 0.48f);
    sh_drawBgAirplane(140, -68, 0.48f);
    sh_drawBgAirplane(sh_bgPlanePosX, -175, 0.82f);

    glColor4f(0.04f, 0.06f, 0.12f, 0.88f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glVertex2f(-380, -280);
        glVertex2f(380, -280);
        glVertex2f(380, 285);
        glVertex2f(-380, 285);
    glEnd();

    glDisable(GL_BLEND);

    glColor3f(0.85f, 0.68f, 0.08f);
    glLineWidth(2.5f);

    glBegin(GL_LINES);
        glVertex2f(-360, 275);
        glVertex2f(360, 275);

        glVertex2f(-360, -270);
        glVertex2f(360, -270);

        glVertex2f(-360, 275);
        glVertex2f(-360, -270);

        glVertex2f(360, 275);
        glVertex2f(360, -270);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    sh_renderBitmapString(-285, 248, GLUT_BITMAP_HELVETICA_18, "                                                                   American International University-Bangladesh (AIUB)");

    glColor3f(0.82f, 0.82f, 0.85f);
    sh_renderBitmapString(-158, 222, GLUT_BITMAP_HELVETICA_12, "                                                      Faculty of Science & Technology");

    glColor3f(0.85f, 0.68f, 0.08f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        glVertex2f(-340, 208);
        glVertex2f(340, 208);
    glEnd();

    glColor3f(0.78f, 0.82f, 0.92f);
    sh_renderBitmapString(-340, 190, GLUT_BITMAP_HELVETICA_12, "Course: Computer Graphics          Section: I          Semester: Spring 25-26");

    glColor3f(0.45f, 0.50f, 0.60f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, 178);
        glVertex2f(340, 178);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-50, 158, GLUT_BITMAP_HELVETICA_12, "               PROJECT TITLE:");

    glColor3f(0.95f, 0.95f, 1.0f);
    sh_renderBitmapString(-262, 135, GLUT_BITMAP_HELVETICA_18, "                                                                    Flight to Rescue: An Aviation Emergency");
    sh_renderBitmapString(-210, 110, GLUT_BITMAP_HELVETICA_18, "                                                          Scenario & Rescue Mission");

    glColor3f(0.45f, 0.50f, 0.60f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, 92);
        glVertex2f(340, 92);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, 72, GLUT_BITMAP_HELVETICA_12, "Submitted To:");

    glColor3f(0.90f, 0.90f, 0.95f);
    sh_renderBitmapString(-340, 50, GLUT_BITMAP_HELVETICA_18, "MAHFUJUR RAHMAN");

    glColor3f(0.45f, 0.50f, 0.60f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, 32);
        glVertex2f(340, 32);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, 14, GLUT_BITMAP_HELVETICA_12, "Submitted By (Group Members):");

    glColor3f(0.88f, 0.90f, 0.95f);
    sh_renderBitmapString(-340, -12, GLUT_BITMAP_HELVETICA_12, "1. SHAHADAT HOSSAIN");

    glColor3f(0.65f, 0.72f, 0.85f);
    sh_renderBitmapString(-340, -28, GLUT_BITMAP_HELVETICA_12, "   ID: 23-51341-1");

    glColor3f(0.88f, 0.90f, 0.95f);
    sh_renderBitmapString(-340, -52, GLUT_BITMAP_HELVETICA_12, "2. NIHA KARMOKAR");

    glColor3f(0.65f, 0.72f, 0.85f);
    sh_renderBitmapString(-340, -68, GLUT_BITMAP_HELVETICA_12, "   ID: 24-56028-1");

    glColor3f(0.88f, 0.90f, 0.95f);
    sh_renderBitmapString(-340, -92, GLUT_BITMAP_HELVETICA_12, "3. ZAHIN TAHIAT ANNESHA");

    glColor3f(0.65f, 0.72f, 0.85f);
    sh_renderBitmapString(-340, -108, GLUT_BITMAP_HELVETICA_12, "   ID: 23-50414-1");

    glColor3f(0.88f, 0.90f, 0.95f);
    sh_renderBitmapString(20, -12, GLUT_BITMAP_HELVETICA_12, "4. MIR MOAHTASIM BILLAH SOYKOT");

    glColor3f(0.65f, 0.72f, 0.85f);
    sh_renderBitmapString(20, -28, GLUT_BITMAP_HELVETICA_12, "   ID: 23-50414-1"); // ID modified based on prompt structure if needed, kept as provided

    glColor3f(0.88f, 0.90f, 0.95f);
    sh_renderBitmapString(20, -52, GLUT_BITMAP_HELVETICA_12, "5. HAMIDUL ISLAM");

    glColor3f(0.65f, 0.72f, 0.85f);
    sh_renderBitmapString(20, -68, GLUT_BITMAP_HELVETICA_12, "   ID: 23-50447-1");

    glColor3f(0.45f, 0.50f, 0.60f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, -128);
        glVertex2f(340, -128);
    glEnd();

    glColor3f(0.50f, 0.56f, 0.68f);
    sh_renderBitmapString(-175, -210, GLUT_BITMAP_HELVETICA_12, "                                                        Press  [ RIGHT ARROW ]  to view Instructions");

    glColor3f(0.85f, 0.68f, 0.08f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-340, -210);
        glVertex2f(-200, -210);
        glVertex2f(200, -210);
        glVertex2f(340, -210);
    glEnd();

    glColor3f(0.38f, 0.42f, 0.52f);
    sh_renderBitmapString(-135, -252, GLUT_BITMAP_HELVETICA_12, "                                   AIUB  |  Spring 2025-2026  |  Computer Graphics");

    glutSwapBuffers();
}

void sh_displayInstructionPage() {
    glClearColor(0.06f, 0.08f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sh_drawBgSky();
    sh_drawBgSkyline();

    glPushMatrix();
        glTranslatef(sh_cloudOffset, 0.0f, 0.0f);
        sh_drawBgCloud(-320, 235);
        sh_drawBgCloud(-130, 260);
        sh_drawBgCloud(60, 245);
        sh_drawBgCloud(230, 255);
        sh_drawBgCloud(330, 220);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(sh_birdOffset, 0.0f, 0.0f);
        sh_drawBgBird(-250, 205);
        sh_drawBgBird(-228, 215);
        sh_drawBgBird(-208, 203);
        sh_drawBgBird(30, 230);
        sh_drawBgBird(55, 240);
        sh_drawBgBird(280, 215);
    glPopMatrix();

    sh_drawBgGround();
    sh_drawBgTerminal();

    sh_drawBgAirplane(-280, -68, 0.48f);
    sh_drawBgAirplane(-70, -68, 0.48f);
    sh_drawBgAirplane(140, -68, 0.48f);
    sh_drawBgAirplane(sh_bgPlanePosX, -175, 0.82f);

    glColor4f(0.04f, 0.06f, 0.12f, 0.90f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glVertex2f(-380, -280);
        glVertex2f(380, -280);
        glVertex2f(380, 285);
        glVertex2f(-380, 285);
    glEnd();

    glDisable(GL_BLEND);

    glColor3f(0.85f, 0.68f, 0.08f);
    glLineWidth(2.5f);

    glBegin(GL_LINES);
        glVertex2f(-360, 275);
        glVertex2f(360, 275);

        glVertex2f(-360, -270);
        glVertex2f(360, -270);

        glVertex2f(-360, 275);
        glVertex2f(-360, -270);

        glVertex2f(360, 275);
        glVertex2f(360, -270);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    sh_renderBitmapString(-105, 250, GLUT_BITMAP_HELVETICA_18, "                     PROJECT INSTRUCTIONS");

    glColor3f(0.85f, 0.68f, 0.08f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, 235);
        glVertex2f(340, 235);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, 212, GLUT_BITMAP_HELVETICA_12, "Scene 1: Airport Scene                               Done By: SHAHADAT HOSSAIN");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, 192, GLUT_BITMAP_HELVETICA_12, "  Keyboard Keys:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, 174, GLUT_BITMAP_HELVETICA_12, "    Right Arrow : Move To The Next Display (Scene)");
    sh_renderBitmapString(-340, 157, GLUT_BITMAP_HELVETICA_12, "    s           : Play sound");
    sh_renderBitmapString(-340, 140, GLUT_BITMAP_HELVETICA_12, "    m           : Mute sound");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, 122, GLUT_BITMAP_HELVETICA_12, "  Mouse Key:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, 105, GLUT_BITMAP_HELVETICA_12, "    Right Mouse Click : Foreground Plane Takeoff");

    glColor3f(0.28f, 0.32f, 0.42f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-340, 92);
        glVertex2f(340, 92);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, 74, GLUT_BITMAP_HELVETICA_12, "Scene 2: Scene of Plane Take Off                  Done By: NIHA KARMOKAR");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, 55, GLUT_BITMAP_HELVETICA_12, "  Keyboard Keys:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, 38, GLUT_BITMAP_HELVETICA_12, "    w : Plane Up        s : Plane Down");
    sh_renderBitmapString(-340, 21, GLUT_BITMAP_HELVETICA_12, "    f : Speed Increase  d : Speed Decrease");
    sh_renderBitmapString(-340, 4, GLUT_BITMAP_HELVETICA_12, "    m : Mute sound      u : Unmute sound");

    glColor3f(0.28f, 0.32f, 0.42f);
    glBegin(GL_LINES);
        glVertex2f(-340, -8);
        glVertex2f(340, -8);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, -26, GLUT_BITMAP_HELVETICA_12, "Scene 3: Plane Flying                             Done By: ZAHIN TAHIAT");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, -43, GLUT_BITMAP_HELVETICA_12, "  Keyboard Keys:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, -60, GLUT_BITMAP_HELVETICA_12, "    p : Pause/Resume");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, -77, GLUT_BITMAP_HELVETICA_12, "  Mouse Key:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, -94, GLUT_BITMAP_HELVETICA_12, "    Left Mouse Click : Pause");

    glColor3f(0.28f, 0.32f, 0.42f);
    glBegin(GL_LINES);
        glVertex2f(-340, -108);
        glVertex2f(340, -108);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, -126, GLUT_BITMAP_HELVETICA_12, "Scene 4: Plane Landing/Crash                      Done By: SOYKOT");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, -143, GLUT_BITMAP_HELVETICA_12, "  Keyboard Keys:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, -160, GLUT_BITMAP_HELVETICA_12, "    s : Start    m : Mute sound    u : Unmute sound");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, -177, GLUT_BITMAP_HELVETICA_12, "  Mouse Key:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, -194, GLUT_BITMAP_HELVETICA_12, "    Left Mouse Click : Pause");

    glColor3f(0.28f, 0.32f, 0.42f);
    glBegin(GL_LINES);
        glVertex2f(-340, -208);
        glVertex2f(340, -208);
    glEnd();

    glColor3f(0.85f, 0.68f, 0.08f);
    sh_renderBitmapString(-340, -226, GLUT_BITMAP_HELVETICA_12, "Scene 5: Rescue Operation                         Done By: HAMIDUL ISLAM");

    glColor3f(0.68f, 0.75f, 0.90f);
    sh_renderBitmapString(-340, -243, GLUT_BITMAP_HELVETICA_12, "  Keyboard & Mouse:");

    glColor3f(0.80f, 0.82f, 0.88f);
    sh_renderBitmapString(-340, -258, GLUT_BITMAP_HELVETICA_12, "   n : Day/Night    KeyBoard Up/Down Arrow :Boat Move/Stop     Mouse Right Click :Boat Reverse   m :Mute sound    u :Unmute sound");

    glColor3f(0.50f, 0.56f, 0.68f);
    sh_renderBitmapString(-335, -282, GLUT_BITMAP_HELVETICA_12, "[ LEFT ARROW ] Back to Cover                [ RIGHT ARROW ] Airport Scene");

    glutSwapBuffers();
}

void sh_displayAirportScene() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sh_drawSky();
    sh_drawSkyline();

    glPushMatrix();
        glTranslatef(sh_cloudOffset, 0.0f, 0.0f);
        sh_drawCloud(-320, 240);
        sh_drawCloud(-130, 265);
        sh_drawCloud(60, 248);
        sh_drawCloud(230, 258);
        sh_drawCloud(330, 225);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(sh_birdOffset, 0.0f, 0.0f);
        sh_drawBird(-250, 210);
        sh_drawBird(-228, 220);
        sh_drawBird(-208, 208);
        sh_drawBird(30, 235);
        sh_drawBird(55, 245);
        sh_drawBird(78, 232);
        sh_drawBird(100, 240);
        sh_drawBird(280, 218);
        sh_drawBird(305, 228);
    glPopMatrix();

    sh_drawGround();
    sh_drawTerminal();
    sh_drawGroundVehicles();

    sh_drawAirplane(-280, -68, 0.48f);
    sh_drawAirplane(-70, -68, 0.48f);
    sh_drawAirplane(140, -68, 0.48f);

    sh_drawAirplane(sh_planePosX, -175, 0.82f);

    glutSwapBuffers();
}

// NIHA'S FUNCTIONS

void niha_circle(float x, float y, float r) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 360; i++) {
            float a = i * 3.1416f / 180.0f;
            glVertex2f(x + cos(a) * r, y + sin(a) * r);
        }
    glEnd();
}

void niha_drawBird(float x, float y, float size) {
    float flap = sin(niha_wingFlap) * size * 0.4f;
    glColor3f(0.02f, 0.02f, 0.02f);
    glLineWidth(3);

    glBegin(GL_LINE_STRIP);
        glVertex2f(x - size, y);
        glVertex2f(x - size * 0.5f, y + size * 0.6f + flap);
        glVertex2f(x, y + size * 0.25f);
        glVertex2f(x + size * 0.5f, y + size * 0.6f + flap);
        glVertex2f(x + size, y);
    glEnd();
}

void niha_drawBirdGroup(float x, float y) {
    niha_drawBird(x, y, 10);
    niha_drawBird(x + 25, y + 10, 8);
    niha_drawBird(x + 50, y - 5, 9);
    niha_drawBird(x + 75, y + 8, 7);
    niha_drawBird(x + 100, y - 2, 8);
}

void niha_drawSkyBackground() {
    glBegin(GL_POLYGON);
        glColor3f(0.78f, 0.88f, 1.0f);
        glVertex2f(-400, 300);
        glVertex2f(400, 300);
        glColor3f(0.48f, 0.68f, 0.92f);
        glVertex2f(400, -65);
        glVertex2f(-400, -65);
    glEnd();
}

void niha_drawSky() {
    glColor3f(1.0f, 0.75f, 0.30f);
    niha_circle(300, 200, 40);

    glColor3f(0.72f, 0.75f, 0.84f);
    niha_circle(300, 150, 28);
    niha_circle(340, 165, 38);
    niha_circle(380, 150, 28);

    glColor3f(0.55f, 0.58f, 0.70f);
    niha_circle(-35, 210, 35);
    niha_circle(20, 235, 50);
    niha_circle(80, 210, 35);

    glColor3f(0.86f, 0.87f, 0.92f);
    niha_circle(-50, 170, 22);
    niha_circle(-15, 185, 30);
    niha_circle(25, 170, 22);

    glColor3f(0.86f, 0.87f, 0.92f);
    niha_circle(-315, 185, 28);
    niha_circle(-265, 205, 40);
    niha_circle(-215, 185, 28);

    glColor3f(0.80f, 0.82f, 0.88f);
    niha_circle(-255, 115, 22);
    niha_circle(-220, 130, 30);
    niha_circle(-185, 115, 22);

    glColor3f(0.68f, 0.71f, 0.80f);
    niha_circle(190, 180, 25);
    niha_circle(235, 195, 35);
    niha_circle(280, 180, 25);

    niha_drawBird(-200 - niha_birdMove, 200, 10);
    niha_drawBird(-150 - niha_birdMove, 220, 8);
    niha_drawBird(-100 - niha_birdMove, 190, 12);
    niha_drawBird(50 - niha_birdMove, 210, 10);
    niha_drawBird(120 - niha_birdMove, 230, 9);

    niha_drawBirdGroup(240 - niha_birdMove, 140);
    niha_drawBirdGroup(-350 - niha_birdMove, 60);
}

void niha_drawTerminal() {
    glColor3f(0.7f, 0.7f, 0.75f);
    glBegin(GL_POLYGON);
        glVertex2f(120, -65);
        glVertex2f(380, -65);
        glVertex2f(380, 20);
        glVertex2f(120, 20);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(110, 20);
        glVertex2f(390, 20);
        glVertex2f(370, 40);
        glVertex2f(130, 40);
    glEnd();

    glColor3f(0.2f, 0.6f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(140, -10);
        glVertex2f(360, -10);
        glVertex2f(360, 10);
        glVertex2f(140, 10);
    glEnd();

    glColor3f(0.1f, 0.5f, 0.9f);
    for (int x = 140; x <= 340; x += 30) {
        for (int y = -50; y <= 0; y += 20) {
            glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + 18, y);
                glVertex2f(x + 18, y + 12);
                glVertex2f(x, y + 12);
            glEnd();
        }
    }
}

void niha_drawTower() {
    glColor3f(0.6f, 0.6f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(-330, -65);
        glVertex2f(-300, -65);
        glVertex2f(-300, 80);
        glVertex2f(-330, 80);
    glEnd();

    glColor3f(0.55f, 0.55f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-345, 80);
        glVertex2f(-285, 80);
        glVertex2f(-285, 100);
        glVertex2f(-345, 100);
    glEnd();

    glColor3f(0.2f, 0.7f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-340, 85);
        glVertex2f(-290, 85);
        glVertex2f(-290, 100);
        glVertex2f(-340, 100);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(-315, 100);
        glVertex2f(-315, 120);
    glEnd();
}

void niha_drawRunway() {
    glColor3f(0.0f, 0.12f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -65);
        glVertex2f(400, -65);
        glVertex2f(400, -95);
        glVertex2f(-400, -95);
    glEnd();

    glColor3f(0.23f, 0.45f, 0.23f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -95);
        glVertex2f(400, -95);
        glVertex2f(400, -300);
        glVertex2f(-400, -300);
    glEnd();

    glColor3f(0.16f, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(-400, -200);
        glVertex2f(-390, -400);
        glVertex2f(400, -105);
        glVertex2f(390, -90);
    glEnd();

    glColor3f(0.95f, 0.95f, 0.90f);
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex2f(-400, -205);
        glVertex2f(400, -90);
        glVertex2f(-120, -300);
        glVertex2f(400, -105);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-310, -255);
        glVertex2f(-222, -234);
        glVertex2f(-207, -252);
        glVertex2f(-295, -274);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-105, -205);
        glVertex2f(-35, -188);
        glVertex2f(-23, -202);
        glVertex2f(-93, -220);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(98, -160);
        glVertex2f(154, -146);
        glVertex2f(164, -157);
        glVertex2f(108, -171);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(289, -122);
        glVertex2f(322, -114);
        glVertex2f(327, -120);
        glVertex2f(294, -129);
    glEnd();
}

void niha_drawPlane() {
    glPushMatrix();
        glTranslatef(niha_planeX, niha_planeY, 0.0f);
        glRotatef(niha_planeAngle, 0, 0, 1);

        glColor3f(0.65f, 0.62f, 0.55f);
        glBegin(GL_POLYGON);
            glVertex2f(-25, -10);
            glVertex2f(-185, -55);
            glVertex2f(-170, -75);
            glVertex2f(25, -18);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-25, 10);
            glVertex2f(-185, 55);
            glVertex2f(-170, 75);
            glVertex2f(25, 18);
        glEnd();

        glColor3f(0.96f, 0.94f, 0.88f);
        glBegin(GL_POLYGON);
            glVertex2f(-125, -18);
            glVertex2f(80, -18);
            glVertex2f(135, 0);
            glVertex2f(80, 18);
            glVertex2f(-125, 18);
        glEnd();

        glColor3f(1.0f, 0.98f, 0.94f);
        glBegin(GL_TRIANGLES);
            glVertex2f(80, -18);
            glVertex2f(155, 0);
            glVertex2f(80, 18);
        glEnd();

        glColor3f(0.78f, 0.75f, 0.68f);
        glBegin(GL_POLYGON);
            glVertex2f(-10, -8);
            glVertex2f(-95, -95);
            glVertex2f(-65, -105);
            glVertex2f(40, -14);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-10, 8);
            glVertex2f(-95, 95);
            glVertex2f(-65, 105);
            glVertex2f(40, 14);
        glEnd();

        glColor3f(0.80f, 0.78f, 0.72f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-120, 15);
            glVertex2f(-170, 70);
            glVertex2f(-80, 18);
        glEnd();

        glColor3f(0.85f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-115, 18);
            glVertex2f(-150, 78);
            glVertex2f(-75, 18);
        glEnd();

        glColor3f(0.03f, 0.08f, 0.16f);
        for (int x = -75; x <= 55; x += 18) {
            niha_circle(x, 7, 4);
        }

        glBegin(GL_POLYGON);
            glVertex2f(82, 6);
            glVertex2f(112, 8);
            glVertex2f(128, 0);
            glVertex2f(92, 0);
        glEnd();

        glColor3f(0.12f, 0.12f, 0.12f);
        niha_circle(-45, -45, 17);
        niha_circle(-45, 45, 17);

        glColor3f(0.65f, 0.65f, 0.62f);
        niha_circle(-45, -45, 10);
        niha_circle(-45, 45, 10);

        glColor3f(0.03f, 0.03f, 0.03f);
        niha_circle(35, -35, 7);
        niha_circle(50, -35, 7);
        niha_circle(-35, -35, 7);

        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(42, -18);
            glVertex2f(42, -32);
            glVertex2f(-35, -18);
            glVertex2f(-35, -32);
        glEnd();
    glPopMatrix();
}

void niha_display() {
    glClearColor(0.70f, 0.82f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    niha_drawSkyBackground();
    niha_drawSky();
    niha_drawRunway();
    niha_drawTerminal();
    niha_drawTower();
    niha_drawPlane();

    glutSwapBuffers();
}


// ANNESHA'S FUNCTIONS

void ann_drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(segments);
            glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
        }
    glEnd();
}

void ann_drawSingleCloud(float x, float y, float scale) {
    glColor3f(1.0f, 1.0f, 1.0f);
    ann_drawCircle(x, y, 30 * scale, 20);
    ann_drawCircle(x - 25 * scale, y - 5 * scale, 20 * scale, 20);
    ann_drawCircle(x + 25 * scale, y - 5 * scale, 20 * scale, 20);
    ann_drawCircle(x - 40 * scale, y - 15 * scale, 15 * scale, 20);
    ann_drawCircle(x + 40 * scale, y - 15 * scale, 15 * scale, 20);
    ann_drawCircle(x, y - 15 * scale, 25 * scale, 20);
}

void ann_drawClouds() {
    glPushMatrix();
        glTranslatef(ann_backgroundX * 0.4f, 0, 0);
        ann_drawSingleCloud(-300, 200, 1.2f);
        ann_drawSingleCloud(-100, 250, 0.8f);
        ann_drawSingleCloud(150, 180, 1.0f);
        ann_drawSingleCloud(350, 230, 0.7f);
        ann_drawSingleCloud(-200, -150, 0.9f);
        ann_drawSingleCloud(50, -180, 1.1f);
        ann_drawSingleCloud(280, -200, 0.8f);
    glPopMatrix();
}

void ann_drawBird(float x, float y) {
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(x - 15, y + 5);
        glVertex2f(x, y);
        glVertex2f(x + 15, y + 5);
    glEnd();
}

void ann_drawBirds() {
    glPushMatrix();
        glTranslatef(ann_backgroundX * 0.8f, 0, 0);
        ann_drawBird(-300, 100);
        ann_drawBird(-260, 130);
        ann_drawBird(-220, 90);
        ann_drawBird(150, 50);
        ann_drawBird(190, 20);
    glPopMatrix();
}

void ann_drawPlane() {
    glPushMatrix();
        glTranslatef(ann_planeX, 0, 0);

        // Wing/Tail elements
        glColor3f(0.6f, 0.6f, 0.6f);
        glBegin(GL_QUADS);
            glVertex2f(-40, 20);
            glVertex2f(20, 20);
            glVertex2f(70, 90);
            glVertex2f(50, 90);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex2f(70, 90);
            glVertex2f(55, 90);
            glVertex2f(75, 110);
        glEnd();

        // Vertical Stabilizer
        glBegin(GL_POLYGON);
            glColor3f(0.9f, 0.9f, 0.9f);
            glVertex2f(-220, 20);
            glVertex2f(-240, 110);
            glVertex2f(-180, 110);
            glVertex2f(-140, 20);
        glEnd();

        glColor3f(0.8f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(-190, 20);
            glVertex2f(-195, 110);
            glVertex2f(-180, 110);
            glVertex2f(-160, 20);
        glEnd();

        // Fuselage
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex2f(-220, 20);
            glVertex2f(200, 20);
            glVertex2f(200, -30);
            glVertex2f(-220, -30);
        glEnd();

        // Nose cone
        glBegin(GL_POLYGON);
            for (int i = 0; i <= 10; i++) {
                float theta = -1.57f + (3.14f * i / 10.0f);
                glVertex2f(200 + 40 * cos(theta), -5 + 25 * sin(theta));
            }
        glEnd();

        // Stripes
        glColor3f(0.1f, 0.3f, 0.6f);
        glBegin(GL_QUADS);
            glVertex2f(-220, 5);
            glVertex2f(205, 5);
            glVertex2f(205, -5);
            glVertex2f(-220, -5);
        glEnd();

        glColor3f(0.8f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(-220, -5);
            glVertex2f(210, -5);
            glVertex2f(210, -15);
            glVertex2f(-220, -15);
        glEnd();

        // Windows
        glColor3f(0.1f, 0.1f, 0.1f);
        for(int i=0; i<6; i++) {
            ann_drawCircle(-150 + i * 40, 10, 3, 10);
        }

        // Lower Wing
        glColor3f(0.85f, 0.85f, 0.85f);
        glBegin(GL_QUADS);
            glVertex2f(-80, -10);
            glVertex2f(30, -10);
            glVertex2f(-20, -70);
            glVertex2f(-120, -70);
        glEnd();
    glPopMatrix();
}

void ann_display() {
    glClearColor(0.44f, 0.69f, 0.89f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ann_drawClouds();
    ann_drawBirds();
    ann_drawPlane();

    glutSwapBuffers();
}


//  SOYKOT'S FUNCTIONS


void drawCircleSoykot(float cx, float cy, float r, int segments) {
    glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
            glVertex2f(r * cosf(theta) + cx, r * sinf(theta) + cy);
        }
    glEnd();
}

void drawSunSoykot(float x, float y, float r) {
    glColor3f(1.0f, 0.6f, 0.0f);
    drawCircleSoykot(x, y, r, 40);

    int numRays = 18;
    float inner = r + 2;
    float outer = r + 12;

    glBegin(GL_LINES);
        for (int i = 0; i < numRays; i++) {
            float angle = 2.0f * PI * i / numRays;
            glVertex2f(x + cosf(angle) * inner, y + sinf(angle) * inner);
            glVertex2f(x + cosf(angle) * outer, y + sinf(angle) * outer);
        }
    glEnd();
}

void drawPlaneSoykot(float x, float y, float scale) {
    // Fuselage
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 35 * scale, y + 2 * scale);
        glVertex2f(x + 20 * scale, y + 2 * scale);
        glVertex2f(x + 35 * scale, y + 5 * scale);
        glVertex2f(x + 20 * scale, y + 10 * scale);
        glVertex2f(x - 30 * scale, y + 10 * scale);
    glEnd();

    // Wing
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(x - 5 * scale, y + 4 * scale);
        glVertex2f(x + 10 * scale, y + 4 * scale);
        glVertex2f(x - 5 * scale, y - 15 * scale);
        glVertex2f(x - 15 * scale, y - 15 * scale);
    glEnd();

    // Tail
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 30 * scale, y + 10 * scale);
        glVertex2f(x - 15 * scale, y + 10 * scale);
        glVertex2f(x - 28 * scale, y + 22 * scale);
        glVertex2f(x - 35 * scale, y + 22 * scale);
    glEnd();

    // Cockpit
    glColor3f(0.2f, 0.4f, 0.8f);
    drawCircleSoykot(x + 18 * scale, y + 7 * scale, 3 * scale, 15);
}

void drawBirdSoykot(float x, float y) {
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(x - 8, y + 4);
        glVertex2f(x - 4, y + 1);
        glVertex2f(x, y + 3);
        glVertex2f(x + 4, y + 1);
        glVertex2f(x + 8, y + 4);
    glEnd();
    glLineWidth(1.0f);
}

void drawBoatSoykot(float x, float y, float scale) {
    // Hull
    glColor3f(0.35f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 25 * scale, y);
        glVertex2f(x + 25 * scale, y);
        glVertex2f(x + 18 * scale, y - 10 * scale);
        glVertex2f(x - 18 * scale, y - 10 * scale);
    glEnd();

    // Mast
    glColor3f(0.2f, 0.1f, 0.0f);
    glRectf(x - 1, y, x + 1, y + 15 * scale);

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 1, y + 15 * scale);
        glVertex2f(x + 1, y + 3 * scale);
        glVertex2f(x + 12 * scale, y + 3 * scale);
    glEnd();
}

void displaySoykot() {
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float waterLine = -50;

    // Sky Background
    glBegin(GL_QUADS);
        glColor3f(0.1f, 0.5f, 0.9f);
        glVertex2f(-400, 300);
        glVertex2f(400, 300);
        glColor3f(1.0f, 0.7f, 0.4f);
        glVertex2f(400, 0);
        glVertex2f(-400, 0);
    glEnd();

    drawSunSoykot(250, 5, 25);

    // Horizon Water
    glColor3f(0.2f, 0.6f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-400, waterLine);
        glVertex2f(400, waterLine);
        glVertex2f(400, 0);
        glVertex2f(-400, 0);
    glEnd();

    drawPlaneSoykot(planeXSoykot, planeYSoykot, 2.5f);

    // Foreground Water
    glColor3f(0.1f, 0.5f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-400, -300);
        glVertex2f(400, -300);
        glVertex2f(400, waterLine);
        glVertex2f(-400, waterLine);
    glEnd();

    // Boats
    glPushMatrix();
        glTranslatef(boatXSoykot, 0.0f, 0.0f);
        drawBoatSoykot(-380, -120, 1.1f);
        drawBoatSoykot(-150, -140, 1.3f);
        drawBoatSoykot(80, -115, 1.2f);
        drawBoatSoykot(280, -150, 1.0f);
        drawBoatSoykot(500, -125, 1.4f);
    glPopMatrix();

    // Birds
    glPushMatrix();
        glTranslatef(birdXSoykot, 0.0f, 0.0f);
        drawBirdSoykot(-410, 210);
        drawBirdSoykot(-450, 220);
        drawBirdSoykot(-500, 195);
        drawBirdSoykot(-550, 250);
        drawBirdSoykot(-600, 230);
        drawBirdSoykot(-650, 270);
        drawBirdSoykot(-700, 240);
        drawBirdSoykot(-750, 280);
    glPopMatrix();

    glutSwapBuffers();
}



// HASIB'S FUNCTIONS

void hasib_drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments);
        glVertex2f(r * cosf(theta) + cx, r * sinf(theta) + cy);
    }
    glEnd();
}

void hasib_drawSun(float x, float y, float r) {
    glColor3f(1.0f, 0.85f, 0.0f);
    hasib_drawCircle(x, y, r, 40);

    int numRays = 24;
    float rayInner = r + 8.0f;
    float rayOuter = r + 25.0f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numRays; i++) {
        float angle = 2.0f * PI * float(i) / float(numRays);
        float tipX = x + cosf(angle) * rayOuter;
        float tipY = y + sinf(angle) * rayOuter;

        float baseX1 = x + cosf(angle - 0.05f) * rayInner;
        float baseY1 = y + sinf(angle - 0.05f) * rayInner;
        float baseX2 = x + cosf(angle + 0.05f) * rayInner;
        float baseY2 = y + sinf(angle + 0.05f) * rayInner;

        glVertex2f(baseX1, baseY1);
        glVertex2f(baseX2, baseY2);
        glVertex2f(tipX, tipY);
    }
    glEnd();
}

void hasib_drawWaves(float yLevel) {
    glColor3f(0.0f, 0.40f, 0.65f);
    glPushMatrix();
        glTranslatef(hasib_positionW, 0.0f, 0.0f);
        for (float x = -500; x < 400; x += 60) {
            glBegin(GL_LINE_STRIP);
                glVertex2f(x, yLevel);
                glVertex2f(x + 15, yLevel + 5);
                glVertex2f(x + 30, yLevel);
            glEnd();
        }
    glPopMatrix();
}

void hasib_drawCloud(float x, float y, float sizeScale) {
    if (hasib_isNight) glColor3f(0.15f, 0.15f, 0.25f);
    else glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
        glTranslatef(hasib_positionC, 5.0f, 0.0f);
        float r = 20.0f * sizeScale;
        hasib_drawCircle(x, y, r, 20);
        hasib_drawCircle(x + (r * 0.8f), y + (r * 0.2f), r * 0.8f, 20);
        hasib_drawCircle(x - (r * 0.8f), y + (r * 0.1f), r * 0.7f, 20);
        hasib_drawCircle(x + (r * 0.4f), y + (r * 0.6f), r * 0.7f, 20);
        hasib_drawCircle(x - (r * 0.3f), y + (r * 0.5f), r * 0.75f, 20);
    glPopMatrix();
}

void hasib_drawBird(float x, float y) {
    glLineWidth(2.0f);
    if (hasib_isNight) glColor3f(0.0f, 0.0f, 0.0f);
    else glColor3f(0.1f, 0.1f, 0.1f);

    glBegin(GL_LINE_STRIP);
        glVertex2f(x - 8, y + 4);
        glVertex2f(x, y);
        glVertex2f(x + 8, y + 4);
    glEnd();
}

void hasib_drawBoat(float x, float y, float scale, float yOffset) {
    glPushMatrix();
        glTranslatef(hasib_positionB, yOffset, 0.0f);

        // Hull
        glColor3f(0.4f, 0.4f, 0.4f);
        glBegin(GL_QUADS);
            glVertex2f(x - (45 * scale), y);
            glVertex2f(x + (45 * scale), y);
            glVertex2f(x + (30 * scale), y - (15 * scale));
            glVertex2f(x - (30 * scale), y - (15 * scale));
        glEnd();

        // Sail
        glColor3f(0.95f, 0.95f, 0.95f);
        glBegin(GL_TRIANGLES);
            glVertex2f(x + (5 * scale), y + (22 * scale));
            glVertex2f(x - (15 * scale), y);
            glVertex2f(x + (30 * scale), y);
        glEnd();
    glPopMatrix();
}

void hasib_display() {
    if (hasib_isNight) glClearColor(0.15f, 0.2f, 0.4f, 1.0f);
    else glClearColor(0.7f, 0.85f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (hasib_isNight) {
        glColor3f(0.9f, 0.9f, 0.95f);
        hasib_drawCircle(300, 220, 25, 40);
    } else {
        hasib_drawSun(300, 220, 30);
    }

    glBegin(GL_TRIANGLES);
        if (hasib_isNight) glColor3f(0.05f, 0.15f, 0.05f);
        else glColor3f(0.13f, 0.45f, 0.13f);
        glVertex2f(-400, 0); glVertex2f(-180, 180); glVertex2f(50, 0);
        if (hasib_isNight) glColor3f(0.1f, 0.2f, 0.1f);
        else glColor3f(0.2f, 0.6f, 0.2f);
        glVertex2f(-20, 0); glVertex2f(200, 150); glVertex2f(420, 0);
    glEnd();

    float waterLine = -55.0f;
    if (hasib_isNight) glColor3f(0.0f, 0.12f, 0.25f);
    else glColor3f(0.0f, 0.49f, 0.73f);
    glBegin(GL_QUADS);
        glVertex2f(-400, waterLine); glVertex2f(400, waterLine);
        glVertex2f(400, 0); glVertex2f(-400, 0);
    glEnd();

    hasib_drawWaves(-20.0f);

    glPushMatrix();
        glTranslatef(10.0f, -40.0f, 0.0f);
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
        if (hasib_isNight) glColor3f(0.2f, 0.2f, 0.25f);
        else glColor3f(0.6f, 0.6f, 0.6f);

        glBegin(GL_POLYGON);
        glVertex2f(-30, 15);
        glVertex2f(20, 10);
        glVertex2f(0, 50);
        glVertex2f(-40, 45);
        glEnd();

        if (hasib_isNight)
            glColor3f(0.3f, 0.3f, 0.35f);
        else glColor3f(0.85f, 0.85f, 0.85f);

        glBegin(GL_POLYGON);
            glVertex2f(-110, -5); glVertex2f(-90, 18); glVertex2f(60, 20); glVertex2f(90, 8);
            glVertex2f(90, -10); glVertex2f(60, -20); glVertex2f(-80, -20); glVertex2f(-105, -12);
        glEnd();

        if (hasib_isNight)
            glColor3f(0.0f, 0.0f, 0.1f);
        else glColor3f(0.1f, 0.2f, 0.3f);

        glBegin(GL_POLYGON);
        glVertex2f(-106, 0);
        glVertex2f(-92, 16);
        glVertex2f(-78, 16);
        glVertex2f(-88, 0);
        glEnd();

        if (hasib_isNight)
            glColor3f(0.4f, 0.4f, 0.2f);
        else glColor3f(0.1f, 0.2f, 0.3f);
        glBegin(GL_QUADS);

            for(int i = -60; i <= 40; i += 14) {
                glVertex2f(i, 10);
                glVertex2f(i + 6, 10);
                glVertex2f(i + 6, 4);
                glVertex2f(i, 4);
            }
        glEnd();
        if (hasib_isNight)
            glColor3f(0.4f, 0.4f, 0.45f);
        else glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(45, 20);
        glVertex2f(70, 18);
        glVertex2f(95, 80);
        glVertex2f(65, 80);
        glEnd();

        if (hasib_isNight && (int)hasib_positionW % 20 < 10) {
            glColor3f(1.0f, 0.0f, 0.0f);
            hasib_drawCircle(80, 80, 4, 10);
        }
        if (hasib_isNight)
            glColor3f(0.25f, 0.25f, 0.3f);
        else glColor3f(0.75f, 0.75f, 0.75f);
        glBegin(GL_POLYGON);
        glVertex2f(-40, -10);
        glVertex2f(10, -15);
        glVertex2f(-15, -55);
        glVertex2f(-50, -50);
        glEnd();
    glPopMatrix();

    if (hasib_isNight)
        glColor3f(0.0f, 0.12f, 0.25f);
    else glColor3f(0.0f, 0.49f, 0.73f);
    glBegin(GL_QUADS);
        glVertex2f(-400, -300);
        glVertex2f(400, -300);
        glVertex2f(400, waterLine);
        glVertex2f(-400, waterLine);
    glEnd();

    hasib_drawWaves(-100.0f);
    hasib_drawWaves(-200.0f);

    if (!hasib_isNight) {
        hasib_drawCloud(-260, 220, 1.2f);
        hasib_drawCloud(40, 240, 1.5f);
        hasib_drawCloud(280, 200, 1.1f);
        glPushMatrix();
            glTranslatef(hasib_positionBI, 0.50f, 0.0f);
            hasib_drawBird(-50, 270); hasib_drawBird(0, 250); hasib_drawBird(250, 275);
            hasib_drawBird(-80, 240); hasib_drawBird(100, 280); hasib_drawBird(150, 265);
            hasib_drawBird(200, 245);
        glPopMatrix();
    }

    hasib_drawBoat(-260, -160, 1.3f, 0.0f);
    hasib_drawBoat(-100, -110, 1.1f, hasib_rescueY);
    hasib_drawBoat(180, -200, 1.2f, 0.0f);
    hasib_drawBoat(300, -100, 1.4f, 0.0f);

    glutSwapBuffers();
}


// MASTER DISPLAY

void display() {
    if (currentPage == 0)      sh_displayCoverPage();
    else if (currentPage == 1) sh_displayInstructionPage();
    else if (currentPage == 2) sh_displayAirportScene();
    else if (currentPage == 3) niha_display();
    else if (currentPage == 4) ann_display();
    else if (currentPage == 5) displaySoykot();
    else if (currentPage == 6) hasib_display();
}

//  MASTER ANIMATION
void update(int value) {
    // SHAHIN'S SCENES (0, 1, 2)
    if (currentPage >= 0 && currentPage <= 2) {
        sh_cloudOffset += sh_cloudSpeed;
        if (sh_cloudOffset > 500.0f) sh_cloudOffset = -400.0f;

        sh_birdOffset += sh_birdSpeed;
        if (sh_birdOffset > 500.0f) sh_birdOffset = -400.0f;

        if (sh_planeMoving) {
            sh_planePosX += sh_planeSpeed;
            if (sh_planePosX > 500.0f) sh_planePosX = -400.0f;
        }

        sh_bgPlanePosX += sh_bgPlaneSpeed;
        if (sh_bgPlanePosX > 550.0f) sh_bgPlanePosX = -550.0f;
    }

    // NIHA'S SCENE (3)
    else if (currentPage == 3) {
        niha_planeX += 2.2f * niha_planeSpeedMultiplier;
        if (niha_planeX > 200) niha_planeY += 0.8f * niha_planeSpeedMultiplier;
        if (niha_planeAngle < 15.0f) niha_planeAngle += 0.15f;

        niha_birdMove += niha_birdSpeed;
        if (niha_birdMove > 500) niha_birdMove = -400;

        niha_wingFlap += 0.25f;
        niha_birdSpeed = 1.2f + fabs(sin(niha_wingFlap)) * 0.8f;
    }

    // ANNESHA'S SCENE (4)
    else if (currentPage == 4) {
        if (ann_isMoving) {
            ann_planeX += ann_speed;
            if (ann_planeX > 600) ann_planeX = -600;

            ann_backgroundX -= ann_speed * 0.2f;
            if (ann_backgroundX < -1000) ann_backgroundX = 1000;
        }
    }

    // SOYKOT'S SCENE (5)
    else if (currentPage == 5) {
        if (moveSoykot) {
            if (!isCrashedSoykot) {
                planeXSoykot += planeSpeedXSoykot;
                planeYSoykot -= planeSpeedYSoykot;

                if (planeYSoykot <= -50.0f) {
                    planeSpeedYSoykot = 0.3f;
                    planeSpeedXSoykot = 0.3f;
                }
                if (planeYSoykot <= -58.0f) {
                    planeYSoykot = -58.0f;
                    planeSpeedXSoykot = 0.0f;
                    planeSpeedYSoykot = 0.0f;
                    isCrashedSoykot = true;
                    PlaySound(NULL, 0, 0);
                }
            }
            birdXSoykot += birdSpeedSoykot;
            if (birdXSoykot > 1150.0f) birdXSoykot = 0.0f;

            boatXSoykot += boatSpeedSoykot;
            if (boatXSoykot > 850.0f) boatXSoykot = -410.0f;
        }
    }

    // HASIB'S SCENE (6)
    else if (currentPage == 6) {
        hasib_positionW += hasib_speedW;
        if (hasib_positionW > 100.0f) hasib_positionW = 0.0f;

        if (hasib_isMovingCloud && !hasib_isNight) {
            hasib_positionC += 0.5f;
            if (hasib_positionC > 400.0f) hasib_positionC = -400.0f;
        }

        if (hasib_isMovingBird && !hasib_isNight) {
            hasib_positionBI += 3.0f;
            if (hasib_positionBI > 450.0f) hasib_positionBI = -450.0f;
        }

        if (hasib_isMoving) {
            hasib_positionB += hasib_speedB;
            if (hasib_positionB > 450.0f) hasib_positionB = -450.0f;

            if (hasib_positionB > -200.0f && hasib_positionB < 200.0f)
                hasib_rescueY = 60.0f - (fabs(hasib_positionB) * 0.3f);
            else
                hasib_rescueY = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0); // Unified 50 FPS loop
}


//  MASTER SOUND

void updateMasterSound() {
    PlaySound(NULL, 0, 0); // Stop old sound
    if (currentPage <= 2) {
        PlaySound("planesoundeffect.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    } else if (currentPage == 3 && !soundMutedNK) {
        PlaySound("airport_sound.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    } else if (currentPage == 4 && !ann_isMuted) {
        PlaySound("plane1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    } else if (currentPage == 5) {
        // Soykot's sound triggers on 's'
    } else if (currentPage == 6 && !hasib_isMuted) {
        PlaySound("Rescue.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    }
}



void handleKeypress(unsigned char key, int x, int y) {
    // Navigation: Enter to advance, Backspace to go back
    if (key == 13) {
        if (currentPage < 6) { currentPage++; updateMasterSound(); }
    }
    else if (key == 8) {
        if (currentPage > 0) { currentPage--; updateMasterSound(); }
    }

    // Scene Specific Keyboard Controls
    if (currentPage <= 2) {
        if (key == 's' || key == 'u') PlaySound("planesoundeffect.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        if (key == 'm') PlaySound(NULL, 0, 0);
    }
    else if (currentPage == 3) {
        if (key == 'w' || key == 'W') niha_planeY += 5.0f;
        if (key == 's' || key == 'S') niha_planeY -= 5.0f;
        if (key == 'f' || key == 'F') niha_planeSpeedMultiplier += 0.1f;
        if (key == 'd' || key == 'D') {
            niha_planeSpeedMultiplier -= 0.1f;
            if (niha_planeSpeedMultiplier < 0.1f) niha_planeSpeedMultiplier = 0.1f;
        }
        if (key == 'm' || key == 'M') { soundMutedNK = true; updateMasterSound(); }
        if (key == 'u' || key == 'U') { soundMutedNK = false; updateMasterSound(); }
    }
    else if (currentPage == 4) {
        if (key == 'p' || key == 'P') ann_isMoving = !ann_isMoving;
        if (key == 'm' || key == 'M') { ann_isMuted = true; updateMasterSound(); }
        if (key == 'u' || key == 'U') { ann_isMuted = false; updateMasterSound(); }
    }
    else if (currentPage == 5) {
        if (key == 's' || key == 'u') {
            moveSoykot = true;
            PlaySound("airplane-fly-by-02.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        }
        if (key == 'm') PlaySound(NULL, 0, 0);
    }
    else if (currentPage == 6) {
        if (key == 'n' || key == 'N') hasib_isNight = !hasib_isNight;
        if (key == 'm' || key == 'M') { hasib_isMuted = true; updateMasterSound(); }
        if (key == 'u' || key == 'U') { hasib_isMuted = false; updateMasterSound(); }
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    // Navigation: Right Arrow to advance, Left Arrow to go back
    if (key == GLUT_KEY_RIGHT) {
        if (currentPage < 6) { currentPage++; updateMasterSound(); }
    }
    else if (key == GLUT_KEY_LEFT) {
        if (currentPage > 0) { currentPage--; updateMasterSound(); }
    }

    // Scene Specific Special Key Controls
    if (currentPage == 3) {
        if (key == GLUT_KEY_UP) niha_planeY += 3.0f;
        if (key == GLUT_KEY_DOWN) niha_planeY -= 3.0f;
    }
    else if (currentPage == 4) {
        if (key == GLUT_KEY_UP) ann_speed += 0.5f;
        if (key == GLUT_KEY_DOWN) { ann_speed -= 0.5f; if (ann_speed < 0) ann_speed = 0; }
    }
    else if (currentPage == 5) {
        if (key == GLUT_KEY_UP) {
            planeSpeedXSoykot += 0.2f; planeSpeedYSoykot += 0.2f;
            birdSpeedSoykot += 0.2f; boatSpeedSoykot += 0.2f;
        }
        if (key == GLUT_KEY_DOWN && birdSpeedSoykot > 1.0f) {
            planeSpeedXSoykot -= 0.2f; planeSpeedYSoykot -= 0.2f;
            birdSpeedSoykot -= 0.2f; boatSpeedSoykot -= 0.2f;
        }
    }
    else if (currentPage == 6) {
        if (key == GLUT_KEY_UP) hasib_isMoving = true;
        if (key == GLUT_KEY_DOWN) hasib_isMoving = false;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (currentPage <= 2) {
            if (button == GLUT_RIGHT_BUTTON) sh_planeMoving = true;
        }
        else if (currentPage == 3) {
            if (button == GLUT_LEFT_BUTTON) niha_planeY += 5.0f;
            if (button == GLUT_RIGHT_BUTTON) niha_planeY -= 5.0f;
        }
        else if (currentPage == 4) {
            if (button == GLUT_LEFT_BUTTON) ann_isMoving = !ann_isMoving;
        }
        else if (currentPage == 5) {
            if (button == GLUT_LEFT_BUTTON) moveSoykot = false;
        }
        else if (currentPage == 6) {
            if (button == GLUT_RIGHT_BUTTON) hasib_speedB = -hasib_speedB;
        }
    }
    glutPostRedisplay();
}


//   MAIN SETUP

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Aviation Emergency & Rescue Operation - Group 5");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(20, update, 0); // Unified timer loop
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

    updateMasterSound(); // Start with initial scene sound

    glutMainLoop();
    return 0;
}
