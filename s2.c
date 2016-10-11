#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// use vertex buffer object(VBO) vertex array object(VAO) to define a triangle
// use shader to draw shape

int main(int argc, char const *argv[]) {
  //glfw initialize
  if(!glfwInit()){
    fprintf(stderr, "Error");
    return 1;
  }

  //set OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  //Suck old function like version <= 3.0,
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  //Create window
  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello", NULL, NULL);
  if(!window){
    fprintf(stderr, "Error\n");
    glfwTerminate();
    return 1;
  }

  //make context for current window
  glfwMakeContextCurrent(window);
  //for mac
  glewExperimental = GL_TRUE;
  //start GLEW extension handler
  glewInit();

  //enable depth-testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  float points[] ={
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };
  
  GLuint vbo = 0;
  // create vbo 1-> number of vbos
  glGenBuffers(1, &vbo);
  // set the vbo as a gl_array_buffer in opengl's state machine
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // copy the points into current vbo
  glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  // create vao 1-> number of vaos
  glGenVertexArrays(1, &vao);
  // set the vao in opengl's state machine
  glBindVertexArray(vao);
  // defile the layout of our first VBO "0"
  glEnableVertexAttribArray(0);
  // regist VBO -> VAO
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  //0-> number of vbo in vao, 3,GL_FLOAT-> the variables are vec3 from every 3 float in VBO, 0-> start position in data, NULL-> interval in data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  //create a shader for vertex
  const char *vertex_shader = 
  "#version 150\n"//set GLSL version to use
  "in vec3 vp;"//3 floats to reserve input data
  "void main(){"//start of GLSL
  " gl_Position = vec4(vp, 1.0);"//output a gl_Position to GL with 4 float
  "}";

  //create a shader for fragment(color)
  const char *fragment_shader =
  "#version 150\n"//set GLSL version to use
  "out vec4 frag_colour;"//4 floats to output color
  "void main(){"//start of GLSL
  " frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
  "}";

  //create a shader for vertex
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  //read vertex shader
  glShaderSource(vs, 1, &vertex_shader, NULL);
  //compile shader
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  //create a program to attach shaders and link them
  GLuint shader_program = glCreateProgram();
  //attach shaders
  glAttachShader(shader_program, fs);
  glAttachShader(shader_program, vs);
  //link shaders
  glLinkProgram(shader_program);

  //loop 
  while(!glfwWindowShouldClose(window)){
    //turn on color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //use program
    glUseProgram(shader_program);
    //use the vao for 'input' to program(vertex_shader) 
    glBindVertexArray(vao);
    //reserve the output and draw the 0~3 points
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //update 
    glfwPollEvents();
    //swap the screen (has 2 buffer)
    glfwSwapBuffers(window);
  }

  //close window
  glfwTerminate();

  return 0;
}
