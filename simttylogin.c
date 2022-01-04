#define _XOPEN_SOURCE 500
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>
#include <unistd.h>

/*#define COLOR */ 

#ifdef COLOR
	#define GREEN "\x1b[32m"
	#define RED "\x1b[31m"
	#define CRESET "\x1b[0m"
#endif

#ifndef HOST_NAME_MAX
	#pragma GCC warning "HOST_NAME_MAX is not defined"
	#define HOSTNAMELEN 100
#else
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
	scanf("%32s", user);
	
	retval = pam_start("simttylogin", user, &conv, &pamh);
	
    	if (retval != PAM_SUCCESS) {
    		perror("pam_start");
    		terminate(pamh, retval);
    	}
	

	retval = pam_authenticate(pamh, 0);

    	if (retval != PAM_SUCCESS){
    		/*perror("pam_authenticate");*/
#ifdef COLOR
		printf("%s\nLogin incorrect\n\n%s", RED, CRESET);    
#else
		printf("\nLogin incorrect\n\n");
#endif
    		terminate(pamh, retval);
    	}

	retval  = pam_acct_mgmt(pamh, 0);

    	if (retval != PAM_SUCCESS){ 
    		perror("pam_acct_mgmt"); 
    		terminate(pamh, retval);
    	}  
#ifdef COLOR  
	printf("%s\nLogged in sucesfully welcome\n\n%s", GREEN, CRESET);
#else
	printf("\nLogged in sucesfully welcome\n\n");
#endif
	terminate(pamh, PAM_SUCCESS);
    	return EXIT_SUCCESS;
} 

void terminate(pam_handle_t *pamh, int retval){
	if (pam_end(pamh,retval) != PAM_SUCCESS) {
        	pamh = NULL;
        	perror("pam_end");
        	exit(EXIT_FAILURE);
    }
    	exit(EXIT_SUCCESS);
    }
/* WIP TODO:implement this
char *get_os(){
	FILE *fp=fopen("/etc/os-release","r");
	long int size;
	char *data;
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	data=(char *) malloc(size);
}*/
