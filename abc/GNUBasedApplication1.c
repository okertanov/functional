#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/utsname.h>

void exit_handler(void)
{
    printf("Exiting...\n");
}

int main(int argc, char* argv[], char* env[])
{
    // At exit
    atexit(exit_handler);

    // System name
    const char uname_fmt[] = "%s %s %s %s %s";
    const char uname_unk[] = "unknown";
    struct utsname uts = { {0}, {0}, {0}, {0}, {0}, {0} };
    const size_t buf_sz = 128;
    char buff[buf_sz] = {0};

    int rc = EINVAL;

    if ( (rc = uname(&uts)) == 0 )
        rc = snprintf( buff, buf_sz * sizeof(char), uname_fmt,
                uts.sysname, uts.nodename, uts.release, uts.version, uts.machine );
    else
        rc = snprintf( buff, buf_sz + sizeof(char), uname_fmt,
                uname_unk, uname_unk, uname_unk, uname_unk, uname_unk );

    rc = printf("\nSystem:\n\t%s\n", buff);

    // User
    char* username = cuserid(NULL);

    rc = printf("\nUser:\n\t%s\n", username);

    // Arguments & Environment
    int a = 0, e = 0;

    rc = printf("\nArguments:\n");
    if ( argv )
        while( argv[a] )
            rc = printf("\t%s\n", argv[a++]);

    printf("\nEnvironment:\n");
    if ( env )
        while( env[e] )
            rc = printf("\t%s\n", env[e++]);

    // Network
    struct sockaddr_in saddr = { .sin_family = AF_INET, .sin_port = htons(1234), .sin_addr.s_addr = htonl(INADDR_ANY) };
    int ssock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    const size_t sbuf_sz = 128;
    char sbuff[sbuf_sz] = {0};
    if ( ssock >= 0 )
    {
        int one = 1;

        if ( setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) >= 0 )
        {
            if ( bind(ssock, (struct sockaddr*)&saddr, sizeof(saddr)) == 0 )
            {
                if ( listen(ssock, SOMAXCONN) == 0 )
                {
                    int csock = 0, rd = 0;
                    bool stop_cond = false;
                    struct sockaddr caddr = {0};
                    socklen_t caddrlen = sizeof(caddr);

                    while ( !stop_cond )
                    {
                        printf(">\n");

                        csock = accept(ssock, &caddr, &caddrlen);

                        if ( csock >= 0 )
                        {
                            do
                            {
                                rd = read(csock, sbuff, sbuf_sz);
                                if ( rd > 0 )
                                {
                                    sbuff[rd] = 0;

                                    printf("%s", sbuff);

                                    stop_cond = (strncmp(sbuff, "exit", 4) == 0);

                                    if ( stop_cond )
                                        break;
                                }
                            }
                            while ( rd > 0 );

                            shutdown(csock, SHUT_RDWR), close(csock);
                        }
                        else
                            perror("Error: accept()"), close(ssock), exit(errno);
                    }
                }
                else
                    perror("Error: listen()"), close(ssock), exit(errno);
            }
            else
                perror("Error: bind()"), close(ssock), exit(errno);
        }
        else
            perror("Error: bind()"), close(ssock), exit(errno);
    }
    else
        perror("Error: socket()"), exit(errno);

    shutdown(ssock, SHUT_RDWR), close(ssock);

    return EXIT_SUCCESS;
}
