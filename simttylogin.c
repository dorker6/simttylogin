#define _XOPEN_SOURCE 500
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>
#include <unistd.h>

#ifndef HOST_NAME_MAX
	#pragma GCC warning "HOST_NAME_MAX is not defined"
	#define HOSTNAMELEN 100
#endif

#ifndef HOSTNAMELEN 
	#define HOSTNAMELEN HOST_NAME_MAX
#endif

static struct pam_conv conv = {
    misc_conv,
    NULL
};

void terminate(pam_handle_t *pamh,int ret);

int main(void){
	char hostname[HOSTNAMELEN];
	int retval;
    pam_handle_t *pamh=NULL;
    char user[32];

	if ( gethostname(hostname, HOSTNAMELEN) != 0 ) {
		perror("gethostname");
		if (hostname == NULL) sprintf(hostname, "unknown"); 
	}
	printf("%s login:", hostname);
	scanf("%s", user);
	
	retval = pam_start("simttylogin", user, &conv, &pamh);
	
    if (retval != PAM_SUCCESS) {
    	perror("pam_start");
    	terminate(pamh, retval);}

	retval = pam_authenticate(pamh, 0);

    if (retval != PAM_SUCCESS){
    perror("pam_authenticate");
    terminate(pamh, retval);
    }

	retval  = pam_acct_mgmt(pamh, 0);

    if (retval != PAM_SUCCESS){ 
    perror("pam_acct_mgmt"); 
    terminate(pamh, retval);
    }      /* permitted access? */

	terminate(pamh, PAM_SUCCESS);
    return EXIT_SUCCESS;       /* indicate success */
} 

void terminate(pam_handle_t *pamh, int retval){
	if (pam_end(pamh,retval) != PAM_SUCCESS) {     /* close Linux-PAM */
        pamh = NULL;
        perror("pam_end");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    }
/* WIP
char *get_os(){
	FILE *fp=fopen("/etc/os-release","r");
	long int size;
	char *data;
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	data=(char *) malloc(size);
}*/
