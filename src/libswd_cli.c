/*
 * Serial Wire Debug Open Library.
 * Command Line Interface Body File.
 *
 * Copyright (C) 2010-2013, Tomasz Boleslaw CEDRO (http://www.tomek.cedro.info)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the Tomasz Boleslaw CEDRO nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.*
 *
 * Written by Tomasz Boleslaw CEDRO <cederom@tlen.pl>, 2010-2013;
 *
 */

/** \file libswd_cli.c */

#include <libswd.h>
#include <string.h>
#include <errno.h>

/*******************************************************************************
 * \defgroup libswd_cli Command Line Interface functions.
 * @{
 ******************************************************************************/

int libswd_cli_print_usage(libswd_ctx_t *libswdctx){
 if (libswdctx==NULL) return LIBSWD_ERROR_NULLPOINTER;
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I: Available LibSWD CLI commands:\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I:  [h]elp / [?]\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I:  [d]etect\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I:  [l]oglevel newloglevel\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I:  [r]ead [d]ap/[a]p/[m]emap address count\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I:  [w]rite [d]ap/[a]p/[m]emap address data[0] .. data[n]\n");
 libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "\n");
 return LIBSWD_OK;
}

/** Command Line Interface parse and execution engine.
 * \param *libswdctx libswd context
 * \param *cmd command string pointer
 * \return LIBSWD_ERROR_OK on success or negative value error code otherwise.
 */
int libswd_cli(libswd_ctx_t *libswdctx, char *command){
 if (libswdctx==NULL) return LIBSWD_ERROR_NULLCONTEXT;
 if (command==NULL) return LIBSWD_ERROR_NULLPOINTER;

 int retval;
 char *cmd;
 cmd=strtok(command," ");
 while (cmd!=NULL){
  if ( strncmp(cmd,"?",1)==0 || \
       strncmp(cmd,"help",4)==0 || \
       strncmp(cmd,"h",1)==0) {
   return libswd_cli_print_usage(libswdctx); 

  } else if ( strncmp(cmd,"l",1)==0 || strncmp(cmd,"loglevel",8)==0 ){
   int loglevel_new=LIBSWD_LOGLEVEL_DEFAULT;
   cmd=strtok(NULL," ");
   if (cmd==NULL) {
    libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I: Current loglevel is: %d (%s)\n", \
    (int)libswdctx->config.loglevel, \
    libswd_log_level_string(libswdctx->config.loglevel));
   } else {
    errno=LIBSWD_OK;
    loglevel_new=atol(cmd);
    if (errno==LIBSWD_OK){
     retval=libswd_log_level_set(libswdctx, (libswd_loglevel_t)loglevel_new);
     if (retval<0) {
      libswd_log(libswdctx, LIBSWD_LOGLEVEL_ERROR, \
                 "LIBSWD_E: libswd_cli(@libswdctx=%p, loglevel=%d/%s): %s\n", \
                 (void*)libswdctx, loglevel_new, \
                 libswd_log_level_string((libswd_loglevel_t)loglevel_new), \
                 libswd_error_string(retval) );
     }
     cmd=strtok(NULL,command);
    } else if (errno!=LIBSWD_OK){
     libswd_log(libswdctx, LIBSWD_LOGLEVEL_INFO, "LIBSWD_I: Current loglevel is: %d (%s)\n", \
      (int)libswdctx->config.loglevel, \
      libswd_log_level_string(libswdctx->config.loglevel));
    }
   }
   libswd_log(libswdctx, LIBSWD_LOGLEVEL_NORMAL, "LOGLEVEL=%d\n", (int)libswdctx->config.loglevel);
   continue;

  } else if ( strncmp(cmd,"r",1)==0 || strncmp(cmd,"read",4)==0 ){
   printf("LIBSWD READ\n");

  } else {
   libswd_log(libswdctx, LIBSWD_LOGLEVEL_ERROR, "LIBSWD_E: libswd_cli(@libswdctx=%p, @command=%p): %s\n", (void*)libswdctx, (void*)command, libswd_error_string(LIBSWD_ERROR_CLISYNTAX));
   libswd_cli_print_usage(libswdctx);
   return LIBSWD_ERROR_CLISYNTAX; 
  } 
  cmd=strtok(NULL," ");
 }
 return LIBSWD_OK;
};


/** @} */