#include <GL/glut.h>
#include <cmath>
#include <SOIL/SOIL.h>
#include <stdio.h>


// Definição das variáveis de ângulo para cada planeta
GLfloat angle_mercurio_orbita = 0.0f;
GLfloat angle_venus_orbita = 0.0f;
GLfloat angle_terra_orbita = 0.0f;
GLfloat angle_marte_orbita = 0.0f;
GLfloat angle_lua_orbita = 0.0f;
GLfloat angle_jupiter_orbita = 0.0f;
GLfloat angle_saturno_orbita = 0.0f;
GLfloat angle_urano_orbita = 0.0f;
GLfloat angle_netuno_orbita = 0.0f;

GLfloat angle_mercurio_rotacao = 0.0f;
GLfloat angle_venus_rotacao = 0.0f;
GLfloat angle_terra_rotacao = 0.0f;
GLfloat angle_marte_rotacao = 0.0f;
GLfloat angle_lua_rotacao = 0.0f;
GLfloat angle_jupiter_rotacao = 0.0f;
GLfloat angle_saturno_rotacao = 0.0f;
GLfloat angle_urano_rotacao = 0.0f;
GLfloat angle_netuno_rotacao = 0.0f;
GLfloat angle_sol_rotacao = 0.0f;

// Definição das velocidades de translação para cada planeta
GLfloat veloc_mercurio_orbita = 1.0f;
GLfloat veloc_venus_orbita = 0.6f;
GLfloat veloc_terra_orbita = 0.4f;
GLfloat veloc_marte_orbita = 0.3f;
GLfloat veloc_lua_orbita = 1.0f;
GLfloat veloc_jupiter_orbita = 0.2f;
GLfloat veloc_saturno_orbita = 0.1f;
GLfloat veloc_urano_orbita = 0.08f;
GLfloat veloc_netuno_orbita = 0.06f;

GLfloat veloc_mercurio_rotacao = 1.0f;
GLfloat veloc_venus_rotacao = 1.0f;
GLfloat veloc_terra_rotacao = 1.0f;
GLfloat veloc_marte_rotacao = 1.0f;
GLfloat veloc_lua_rotacao = 1.0f;
GLfloat veloc_jupiter_rotacao = 1.0f;
GLfloat veloc_saturno_rotacao = 1.0f;
GLfloat veloc_urano_rotacao = 1.0f;
GLfloat veloc_netuno_rotacao = 1.0f;
GLfloat veloc_sol_rotacao = 1.0f;

// carregar textura
GLuint loadTexture(const char* filename) {
    return SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

// aplicar textura na esfera
void applyTexture(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Apply texture with lighting
}

// desenhar esfera texturizada
void drawTexturedSphere(float raio, GLuint textureID) {
    applyTexture(textureID);

    const float angle = 90.0f;
    const float radians = angle * (M_PI / 180.0f); // Converte graus para radianos

    // Matriz de rotação manual
    GLfloat rotationMatrix[16] = {
        1.0f, 0.0f,           0.0f,          0.0f,
        0.0f, cos(radians),   -sin(radians), 0.0f,
        0.0f, sin(radians),   cos(radians),  0.0f,
        0.0f, 0.0f,           0.0f,          1.0f
    };

    glPushMatrix(); // Salva a matriz de transformação atual
    glMultMatrixf(rotationMatrix); // Aplica a rotação manual

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE); // Habilita coordenadas de textura
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, raio, 36, 18);
    gluDeleteQuadric(quad);

    glPopMatrix(); // Restaura a matriz de transformação anterior
    glDisable(GL_TEXTURE_2D);
}

// definição das texturas
GLuint textura_sol, textura_mercurio, textura_venus, textura_terra, textura_lua,
         textura_marte, textura_jupiter, textura_saturno, textura_urano, textura_netuno;


// Função de inicialização
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0); // Define cor de fundo preta
    glShadeModel(GL_SMOOTH);

    // carregando texturas
    textura_marte = loadTexture("imagens/t_marte.jpg"); 
    textura_lua = loadTexture("imagens/t_lua.jpg"); 
    textura_terra = loadTexture("imagens/t_terra.jpg");
    textura_venus = loadTexture("imagens/t_venus.jpg");
    textura_mercurio = loadTexture("imagens/t_mercurio.jpg");
    textura_sol = loadTexture("imagens/t_sol.jpg");
    textura_jupiter = loadTexture("imagens/t_jupiter.jpg");
    textura_saturno = loadTexture("imagens/t_saturno.jpg");
    textura_urano = loadTexture("imagens/t_urano.jpg");
    textura_netuno = loadTexture("imagens/t_netuno.jpg");

    // Configuração de iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

}


// Função para desenhar a circunferência com rotação em torno do eixo X
void desenharCircunferencia(float raio, float fatorDeAchatamento, float anguloDeRotacao) {
    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(anguloDeRotacao, 1.0f, 0.0f, 0.0f); // Aplica a rotação de 90 graus no sentido anti-horário em torno do eixo X
    glBegin(GL_LINE_LOOP); // Começa a desenhar um loop de linhas
    for(int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180; // Converte o ângulo para radianos
        float x = raio * cos(theta); // Calcula a coordenada x
        float y = raio * fatorDeAchatamento * sin(theta); // Calcula a coordenada y com fator de achatamento
        glVertex2f(x, y); // Adiciona o ponto ao loop
    }
    glEnd(); // Termina o loop de linhas
    glPopMatrix(); // Restaura a matriz de transformação anterior
}

// função de renderização
void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // configura a câmera para visualizar a cena de um pouco mais de cima
    gluLookAt(0, 10, 25, // posição da câmera
              0, 0, 0,  // ponto para o qual a câmera está olhando
              0, 1, 0); // vetor "up" (para cima)


    // ====================================== SOL ======================================

    // características da esfera do sol
    GLfloat sol_ambiente[] = { 1, 1, 1, 1 }; // cor
    glLightfv(GL_LIGHT0, GL_AMBIENT, sol_ambiente);

    // desenha o sol
    glPushMatrix();
    glRotatef(angle_sol_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)
    drawTexturedSphere(1.5, textura_sol); 
    glPopMatrix();
    glPushMatrix();


    // ====================================== LUZ ======================================

    // Define a luz no centro do Sol
    GLfloat posicao_luz[] = { 0, 0, 0, 1 }; // Posição da luz (no centro do Sol)
    GLfloat luz_ambiente[] = { 0.25, 0.25, 0.25, 1 }; // Luz ambiente
    GLfloat luz_difusa[] = { 1, 1, 1, 1 }; // Luz difusa
    GLfloat luz_especular[] = { 1, 1, 1, 1 }; // Luz especular

    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ====================================== MERCÚRIO ======================================

    // Aplica transformações para Mercúrio
    glRotatef(angle_mercurio_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(4.0, 0.0, 0.0); // Translada para a posição da órbita
    // Rotaciona em torno de seu próprio eixo
    glRotatef(angle_mercurio_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.3, textura_mercurio); 

    // Restaura o estado da matriz de Mercúrio
    glPopMatrix();
    // Salva o estado da matriz antes de desenhar Vênus
    glPushMatrix();


    // ====================================== VÊNUS ======================================

    // Aplica transformações para Vênus
    glRotatef(angle_venus_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(6.0, 0.0, 0.0); // Translada para a posição da órbita
    // Rotaciona em torno de seu próprio eixo
    glRotatef(angle_venus_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    // Define e desenha Vênus
    drawTexturedSphere(0.5, textura_venus); 

    // Restaura o estado da matriz de Vênus
    glPopMatrix();
    // Salva o estado da matriz antes de desenhar a Terra
    glPushMatrix();


    // ====================================== TERRA ======================================

    // Aplica transformações para a Terra
    glRotatef(angle_terra_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(8.0, 0.0, 0.0); // Translada para a posição da órbita
    // Rotaciona a Terra em torno de seu próprio eixo
    glRotatef(angle_terra_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.6, textura_terra); 

    // Salva o estado da matriz novamente para a Lua
    glPushMatrix();


    // ====================================== LUA ======================================

    // Aplica transformações para a Lua
    glRotatef(angle_lua_orbita, 0, 1.0, 0.0); // Rotaciona ao redor do eixo Y
    glTranslatef(1.5, 0, 0); // Translada para a posição da órbita da Lua
    // Rotaciona em torno de seu próprio eixo
    glRotatef(angle_lua_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    // Define e desenha a Lua
    drawTexturedSphere(0.2, textura_lua); 

    // Restaura o estado da matriz da Lua
    glPopMatrix();
    // Restaura o estado da matriz da Terra
    glPopMatrix();

    // Salva o estado da matriz antes de desenhar Marte
    glPushMatrix();


    // ====================================== MARTE ======================================

    // transformações para Marte
    glRotatef(angle_marte_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(10.0, 0.0, 0.0); // Translada para a posição da órbita
    // Rotaciona em torno de seu próprio eixo
    glRotatef(angle_marte_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    // Define e desenha Marte
    drawTexturedSphere(0.4, textura_marte); 

    // restaura o estado da matriz de Marte
    glPopMatrix();
    // restaura o estado da matriz inicial
    glPopMatrix();


    // ====================================== JÚPITER ======================================

    glPushMatrix();
    glRotatef(angle_jupiter_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(12.0, 0.0, 0.0); // Translada para a posição da órbita
    glRotatef(angle_jupiter_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.8, textura_jupiter); 

    glPopMatrix();


    // ====================================== SATURNO ======================================

    glPushMatrix();
    glRotatef(angle_saturno_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(15.0, 0.0, 0.0); // Translada para a posição da órbita
    glRotatef(angle_saturno_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.7, textura_saturno);

    // Anéis de Saturno
    desenharCircunferencia(0.9, 1.5, 45);

    glPopMatrix();

    // ====================================== URANO ======================================

    glPushMatrix();
    glRotatef(angle_urano_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(18.0, 0.0, 0.0); // Translada para a posição da órbita
    glRotatef(angle_urano_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.6, textura_urano);
    desenharCircunferencia(0.75, 1.5, 45);

    glPopMatrix();

    // ====================================== NETUNO ======================================

    glPushMatrix();
    glRotatef(angle_netuno_orbita, 0, 1, 0); // Rotaciona ao redor do eixo Y
    glTranslatef(21.0, 0.0, 0.0); // Translada para a posição da órbita
    glRotatef(angle_netuno_rotacao, 0, 1, 0); // Rotaciona ao redor do eixo Y (rotação própria)

    drawTexturedSphere(0.5, textura_netuno);

    glPopMatrix();

    glutSwapBuffers();
}

// função de atualização do ângulo de rotação
void update(int value) {

    // terra
    angle_terra_orbita += veloc_terra_orbita;
    if (angle_terra_orbita > 360) {
        angle_terra_orbita -= 360;
    }

    angle_terra_rotacao += veloc_terra_rotacao;
    if (angle_terra_rotacao > 360) {
        angle_terra_rotacao -= 360;
    }

    // mercurio
    angle_mercurio_orbita += veloc_mercurio_orbita;
    if (angle_mercurio_orbita > 360) {
        angle_mercurio_orbita -= 360;
    }

    angle_mercurio_rotacao += veloc_mercurio_rotacao;
    if (angle_mercurio_rotacao > 360) {
        angle_mercurio_rotacao -= 360;
    }

    // venus
    angle_venus_orbita += veloc_venus_orbita;
    if (angle_venus_orbita > 360) {
        angle_venus_orbita -= 360;
    }

    angle_venus_rotacao += veloc_venus_rotacao;
    if (angle_venus_rotacao > 360) {
        angle_venus_rotacao -= 360;
    }

    // marte
    angle_marte_orbita += veloc_marte_orbita;
    if (angle_marte_orbita > 360) {
        angle_marte_orbita -= 360;
    }

    angle_marte_rotacao += veloc_marte_rotacao;
    if (angle_marte_rotacao > 360) {
        angle_marte_rotacao -= 360;
    }

    // lua
    angle_lua_orbita += veloc_lua_orbita;
    if (angle_lua_orbita > 360) {
        angle_lua_orbita -= 360;
    }

    angle_lua_rotacao += veloc_lua_rotacao;
    if (angle_lua_rotacao > 360) {
        angle_lua_rotacao -= 360;
    }

    // jupiter
    angle_jupiter_orbita += veloc_jupiter_orbita;
    if (angle_jupiter_orbita > 360) {
        angle_jupiter_orbita -= 360;
    }

    angle_jupiter_rotacao += veloc_jupiter_rotacao;
    if (angle_jupiter_rotacao > 360) {
        angle_jupiter_rotacao -= 360;
    }

    // saturno
    angle_saturno_orbita += veloc_saturno_orbita;
    if (angle_saturno_orbita > 360) {
        angle_saturno_orbita -= 360;
    }

    angle_saturno_rotacao += veloc_saturno_rotacao;
    if (angle_saturno_rotacao > 360) {
        angle_saturno_rotacao -= 360;
    }

    // urano
    angle_urano_orbita += veloc_urano_orbita;
    if (angle_urano_orbita > 360) {
        angle_urano_orbita -= 360;
    }

    angle_urano_rotacao += veloc_urano_rotacao;
    if (angle_urano_rotacao > 360) {
        angle_urano_rotacao -= 360;
    }

    // netuno
    angle_netuno_orbita += veloc_netuno_orbita;
    if (angle_netuno_orbita > 360) {
        angle_netuno_orbita -= 360;
    }

    angle_netuno_rotacao += veloc_netuno_rotacao;
    if (angle_netuno_rotacao > 360) {
        angle_netuno_rotacao -= 360;
    }

    // sol
    angle_sol_rotacao += veloc_sol_rotacao;
    if (angle_sol_rotacao > 360) {
        angle_sol_rotacao -= 360;
    }

    // Redesenha a cena
    glutPostRedisplay();

    // Chama a função de atualização novamente após 16 ms (aproximadamente 60 FPS)
    glutTimerFunc(16, update, 0);
}

// função de redimensionamento
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// função de teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // tecla ESC
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema solar em OpenGL");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0); // Configura a função de atualização
    glutMainLoop();
    return 0;
}
