// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

/* function declaration */
void calc (lua_State* L, const char **args);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){
  lua_State* L = luaL_newstate();
  // char* argvs = argv;
  luaL_openlibs(L);

  // carrega o arquivo e executa suas as ações
  luaL_dofile(L, "calc.lua");
  
  // printf("%d \n", strlen(*argv));
  calc(L, argv);

  lua_close(L);
  return 0;
}

/* call a function `calculo' defined in Lua */
void calc (lua_State* L, const char **args) {

  /* push functions and arguments */
  lua_getglobal(L, args[1]);  /* function to be called */

  for (int i = 3; i < atoi(args[2]) + 3; i++){
    // printf("%d \n", atoi(args[i]));
    lua_pushnumber(L, atoi(args[i]));   /* push 1st argument */
  }
  
  int results = (atoi(args[2]) > 1) ? 2 : 1;


  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, atoi(args[2]), results, 0) != 0)
    error(L, "error running function `calculo': %s \n",
              lua_tostring(L, -1));

  /* retrieve result */
  if (!lua_isnumber(L, -1))
    error(L, "function `calculo' must return a number \n");

  // printf("%s \n", lua_tostring(L, -1));
  
  for (int i = 0; i < results; i++){
    printf("Result %d: %.2f \n",i+1, lua_tonumber(L, -1));
    lua_pop(L, 1);  /* pop returned value */
  }
  
}


// https://www.lua.org/pil/24.1.html#first-ex
void error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(L);
  exit(EXIT_FAILURE);
}