/*  
 *                   COPYRIGHT (c) 1988-1994 BY                             *
 *        PARADIGM ASSOCIATES INCORPORATED, CAMBRIDGE, MASSACHUSETTS.       *
 *        See the source file SLIB.C for more information.                  *

 * Reorganization of files (Mar 1999) by Alan W Black <awb@cstr.ed.ac.uk>

 * Client/server functions

*/
#include <cstdio>
#include "EST_io_aux.h"
#include "siod.h"
#include "siodp.h"

using namespace std;

int siod_server_socket = -1;

LISP siod_send_lisp_to_client(LISP x)
{
    int r;
    LISP rx = x;
    
    // Send x to the client
    if (siod_server_socket == -1)
    {
	err("siod: not in server mode",x);
    }

    EST_String tmpfile = make_tmp_filename();
    FILE *fd;
    EST_String m = siod_sprint(x);

    if ((fd=fopen(tmpfile,"wb")) == NULL)
    {
	cerr << "siod: can't open temporary file \"" << 
	    tmpfile << "\" for client lisp return" << endl;
    }
    else
    {
	fwrite((const char *)m,sizeof(char),m.length(),fd);
	fwrite("\n",1,1,fd);
	fclose(fd);
#ifdef _WIN32
        (void) r;
	send(siod_server_socket,"LP\n",3,0);
#else
	r = write(siod_server_socket,"LP\n",3);
        if (r != 3)
            rx = NIL;
#endif
	socket_send_file(siod_server_socket,tmpfile);
	unlink(tmpfile);
    }

    return rx;
}

int sock_acknowledge_error()
{
    // Called to let client know if server gets an error
    // Thanks to mcb for pointing out this omission
    int r = 0;
    
    if (siod_server_socket != -1)
#ifdef _WIN32
	send(siod_server_socket,"ER\n",3,0);
#else
        r = write(siod_server_socket,"ER\n",3);
#endif
        return r;

}
    
static int acknowledge_sock_print(LISP x)
{   // simple return "OK" -- used in server socket mode
    int r;

    siod_send_lisp_to_client(x);
#ifdef _WIN32
    r = send(siod_server_socket,"OK\n",3,0);
#else
    r = write(siod_server_socket,"OK\n",3);
#endif
    if (r == 3)
        return 0;
    else
        return -1;
}

static int ignore_puts(char *x)
{   
    (void)x;
    return 0;
}

long repl_from_socket(int fd)
{
    /* Read from given fd as stdin */
    struct repl_hooks hd;

#ifdef _WIN32
    if (!SetStdHandle(STD_INPUT_HANDLE,(HANDLE)fd))
    {
	GetLastError();
	cerr << "repl_from_socket: couldn't set stdin to socket\n";
    }
#else
    dup2(fd,0);                     // make socket into stdin
    // dup2(fd,1);                     // make socket into stdout
#endif
    hd.repl_puts = ignore_puts;
    hd.repl_print = acknowledge_sock_print;
    hd.repl_eval = NULL;
#ifdef _WIN32
    hd.repl_read = lreadwinsock;
#else
    hd.repl_read = NULL;
#endif
    siod_interactive = false;
    siod_server_socket = fd;

    return repl_driver(1,0,&hd);
}

void init_subrs_srv(void)
{
 init_subr_1("send_client",siod_send_lisp_to_client,
 "(send_client EXPR)\n\
 Send EXPR to client.  In server mode this will send a printed form of\n\
 ESPR to the client.  It is the client's job to expect it.");
}
