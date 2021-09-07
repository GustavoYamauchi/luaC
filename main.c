// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

/* function declaration */
double calc (lua_State* L, const char **args);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){
  lua_State* L = luaL_newstate();
  // char* argvs = argv;
  luaL_openlibs(L);

  // carrega o arquivo e executa suas as ações
  luaL_dofile(L, "calc.lua");
  
  // printf("%d \n", strlen(*argv));
  double valor = calc(L, argv);

  printf("Valor de resultado %.2f \n", valor);

  lua_close(L);
  return 0;
}

/* call a function `calculo' defined in Lua */
double calc (lua_State* L, const char **args) {
  double z;


  /* push functions and arguments */
  lua_getglobal(L, args[1]);  /* function to be called */

  for (int i = 3; i < atoi(args[2]) + 3; i++){
    lua_pushnumber(L, atoi(args[i]));   /* push 1st argument */
  }
  

  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, atoi(args[2]), (1 || 2), 0) != 0)
    error(L, "error running function `calculo': %s",
              lua_tostring(L, -1));

  /* retrieve result */
  if (!lua_isnumber(L, -1))
    error(L, "function `calculo' must return a number");
  z = lua_tostring(L, -1);
  lua_pop(L, 1);  /* pop returned value */

  return z;
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