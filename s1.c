#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Create basic window

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

  //close window
  glfwTerminate();

  return 0;
}
