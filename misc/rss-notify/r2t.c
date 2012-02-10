#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <mrss.h>
#include <iconv.h>
#include <err.h>
#include <assert.h>
#include <locale.h>
#include <langinfo.h>


#define     CONV_ENC_LEN        (64)
#define     CONV_DATE_LEN       (128)
#define     CONV_DATE_GMT       ("GMT")

typedef struct __tag_convert_context_t
{
    iconv_t cd;

    char rss_encoding[CONV_ENC_LEN];
    char sys_encoding[CONV_ENC_LEN];

} convert_context_t;


int convert_init(convert_context_t* cc, char* from, char* to)
{
    assert(NULL != cc);
    assert(NULL != from);
    assert(NULL != to);

    strncpy(cc->rss_encoding, from, CONV_ENC_LEN);
    strncpy(cc->sys_encoding, to,   CONV_ENC_LEN);

    errno = 0;
    cc->cd = iconv_open(cc->sys_encoding, cc->rss_encoding); //to-from parameters logic

    return ((iconv_t)-1 != cc->cd);
}

char* convert(convert_context_t* cc, char* from)
{
    size_t cs = 0;

    size_t from_size = strlen(from);
    char*  from_ptr = from;
    size_t to_size = ((from_size+1)*2);
    char*  to = (char*)malloc(to_size);
    char *to_ptr = to;

    assert(NULL != cc);
    assert(NULL != from_ptr);
    assert(NULL != to_ptr);

    memset(to_ptr, 0, to_size);

    errno = 0;

    if (
            (0 != strncasecmp(cc->rss_encoding, cc->sys_encoding, CONV_ENC_LEN)) &&
            ((iconv_t)-1 != cc->cd)
        )
    {
        cs = iconv(cc->cd, &from_ptr, &from_size, &to_ptr, &to_size);
    }
    else
    {
        cs = strlen(strncpy(to_ptr, from_ptr, to_size));
    }

    return (to);
}

void convert_close(convert_context_t* cc)
{
    assert(NULL != cc);

    memset(cc->rss_encoding,  0, CONV_ENC_LEN);
    memset(cc->sys_encoding, 0, CONV_ENC_LEN);

    iconv_close(cc->cd);
}

char* convert_system_enc()
{
    //DEBUG: static char sys_enc[] = "utf-8";
    char* sys_enc = nl_langinfo(CODESET);

    return (sys_enc);
}
char* convert_pub_date(char* pub_date)
{
    int date_parsed = 0;
    struct tm tm_raw = {0};

    char buf[32] = {0};
    char* dstop = NULL;

    const char *rfc822_format = "%a, %d %b %Y %H:%M:%S %z"; //+0X00 format
    const char *zone_format = "%a, %d %b %Y %H:%M:%S %Z";   //TZ format

    char* new_date_str = malloc(CONV_DATE_LEN);


    assert(NULL != pub_date);
    assert(NULL != new_date_str);
    memset(new_date_str, 0, CONV_DATE_LEN);

    time_t tmp_timet = time(NULL);
    memcpy(&tm_raw, localtime(&tmp_timet), sizeof(struct tm));

    if ( (dstop = strptime(pub_date, rfc822_format, &tm_raw)) )
    {
        date_parsed = NULL != dstop;
    }
    else if ( (dstop = strptime(pub_date, zone_format, &tm_raw)) )
    {
        date_parsed = NULL != dstop;
    }
    else
    {
        date_parsed = 0; //something else?
    }

    if( date_parsed )
    {
        if ( strlen(dstop) )
        {
            if ( 0 == strncasecmp(dstop, CONV_DATE_GMT, strlen(CONV_DATE_GMT)) )
            {
                //apply GMT timediff
                time_t loc_timet = mktime(&tm_raw) - timezone; //in sec
                memcpy(&tm_raw, localtime(&loc_timet), sizeof(struct tm));
            }
            else
            {
                //just indicate TZ
                snprintf(buf, sizeof(buf), "(%s)", dstop);
            }
        }

        strftime(new_date_str, CONV_DATE_LEN, "%d %b %Y %R", &tm_raw);

        if (strlen(buf))
        {
            strncat(new_date_str, buf, sizeof(buf));
        }
    }
    else
    {
        strncpy(new_date_str, pub_date, CONV_DATE_LEN);
    }

    return (new_date_str);
}

void replace(char *in, char *what, char by_what)
{
    int what_len = strlen(what);

    /* replace &lt; etc. */
    for(;;)
    {
        char *str = strstr(in, what);
        if (!str)
            break;

        memcpy(str + 1, str + what_len, strlen(str + what_len) + 1);
        *str = by_what;
    }
}

char *remove_html_tags(char *in)
{
    char *copy = strdup(in);

    /* strip <...> */
    for(;;)
    {
        char *lt = strchr(copy, '<'), *gt;
        if (!lt)
            break;

        gt = strchr(lt, '>');
        if (!gt)
            break;

        memcpy(lt, gt + 1, strlen(gt + 1) + 1);
    }

    replace(copy, "&lt;", '<');
    replace(copy, "&gt;", '>');
    replace(copy, "&amp;", '&');

    return copy;
}

/* 0: is a new record, -1: not a new record */
int is_new_record(mrss_item_t *check_list, mrss_item_t *cur_item)
{
    while(check_list)
    {
        if (check_list -> pubDate != NULL && cur_item -> pubDate != NULL)
        {
            if (strcmp(check_list -> pubDate, cur_item -> pubDate) == 0)
                return -1;
        }
        else
        {
            int navail = 0, nequal = 0;

            if (check_list -> title != NULL && cur_item -> title != NULL)
            {
                navail++;

                if (strcmp(check_list -> title, cur_item -> title) == 0)
                    nequal++;
            }
            if (check_list -> link  != NULL && cur_item -> link  != NULL)
            {
                navail++;

                if (strcmp(check_list -> link, cur_item -> link ) == 0)
                    nequal++;
            }
            if (check_list -> description != NULL && cur_item -> description != NULL)
            {
                navail++;

                if (strcmp(check_list -> description, cur_item -> description) == 0)
                    nequal++;
            }

            if (navail == nequal && navail > 0)
            {
                return -1;
            }
        }

        check_list = check_list -> next;
    }

    return 0;
}

void version(void)
{
    printf("rsstail v" VERSION ", (C) 2005-2007 by folkert@vanheusden.com\n\n");
}

void usage(void)
{
    version();

    printf("-t  show timestamp\n");
    printf("-l  show link\n");
    printf("-d  show description\n");
    printf("-p  show publication date\n");
    printf("-a  show author\n");
    printf("-c  show comments\n");
    printf("-N      do not show headings\n");
    printf("-b x    limit description/comments to x bytes\n");
    printf("-z      continue even if there are XML parser errors in the RSS feed\n");
    printf("-Z x    add heading 'x'\n");
    printf("-n x    initially show x items\n");
    printf("-H  strip HTML tags\n");
/*  printf("-o x    only show items newer then x[s/M/h/d/m/y]\n");  */
    printf("-u url  URL of RSS feed to tail\n");
    printf("-i x    check interval in seconds (default is 15min)\n");
    printf("-x x    proxy server to use (host[:port])\n");
    printf("-y x    proxy authorization (user:password)\n");
    printf("-P  do not exit when an error occurs\n");
    printf("-1  one shot\n");
    printf("-m  notify friendly\n");
    printf("-v  be verbose (add more to be more verbose)\n");
    printf("-V  show version and exit\n");
    printf("-h  this help\n");
}

int main(int argc, char *argv[])
{
    char **url = NULL;
    int n_url = 0, cur_url = 0;
    int check_interval = 15 * 60;
    mrss_t **data_prev = NULL;
    mrss_t **data_cur = NULL;
    int data_size;
    char *proxy = NULL, *proxy_auth = NULL;
    int sw;
    int verbose = 0;
    int notify_friendly = 0;
    char show_timestamp = 0, show_link = 0, show_description = 0, show_pubdate = 0, show_author = 0, show_comments = 0;
    char strip_html = 0, no_error_exit = 0;
    char one_shot = 0;
    char no_heading = 0;
    int bytes_limit = 0;
    time_t last_changed = (time_t)0;
    char continue_on_error = 0/*, dummy*/;
    int show_n = -1;
    /*long int max_age = -1;*/
    char *heading = NULL;
    mrss_options_t mot;

    convert_context_t conv_context;
    convert_context_t* cc = &conv_context;
    char *conv_title = 0;
    char *rss_title = 0;
    char *conv_rss_title = 0;
    char *conv_author = 0;
    char *conv_description = 0;
    char *conv_comments = 0;

    tzset();
    setlocale(LC_ALL, "");

    memset(&mot, 0x00, sizeof(mot));

    while((sw = getopt(argc, argv, "Z:1b:PHztldpacmu:Ni:n:x:y:vVh")) != -1)
    {
        switch(sw)
        {
            case 'Z':
                heading = optarg;
                break;

            case 'N':
                no_heading = 1;
                break;

            case 'm':
                notify_friendly = 1;
                break;

            case '1':
                one_shot = 1;
                break;

            case 'b':
                bytes_limit = atoi(optarg);
                if (bytes_limit <= 0)
                {
                    fprintf(stderr, "-b requires a number > 0\n");
                    return 1;
                }
                break;

            case 'P':
                no_error_exit = 1;
                break;

            case 'H':
                strip_html = 1;
                break;

            case 'n':
                show_n = atoi(optarg);
                if (show_n < 0)
                {
                    fprintf(stderr, "-n requires an positive value\n");
                    return 1;
                }
                else if (show_n > 50)
                    fprintf(stderr, "Initially showing more then 50 items, must be one hell of an rss feed!\n");
                break;

#if 0
            case 'o':
                dummy = optarg[strlen(optarg) - 1];
                max_age = atoi(optarg);
                if (max_age < 0)
                {
                    printf("-o requires an positive value\n");
                    return 1;
                }
                if (dummy == 's')
                    max_age *= 1;
                else if (dummy == 'M')
                    max_age *= 60;
                else if (dummy == 'h')
                    max_age *= 3600;
                else if (dummy == 'd')
                    max_age *= 86400;
                else if (dummy == 'm')
                    max_age *= 86400 * 31;
                else if (dummy == 'y')
                    max_age *= 86400 * 365.25;
                else if (isalpha(dummy))
                {
                    printf("'%c' is a not recognized multiplier\n", dummy);
                    return 1;
                }
                break;
#endif

            case 'z':
                continue_on_error = 1;
                break;

            case 't':
                show_timestamp = 1;
                break;

            case 'l':
                show_link = 1;
                break;

            case 'd':
                show_description = 1;
                break;

            case 'p':
                show_pubdate = 1;
                break;

            case 'a':
                show_author = 1;
                break;

            case 'c':
                show_comments = 1;
                break;

            case 'u':
                url = (char **)realloc(url, sizeof(char *) * (n_url + 1));
                if (!url)
                {
                    fprintf(stderr, "Cannot allocate memory\n");
                    return 2;
                }
                url[n_url++] = optarg;
                break;

            case 'i':
                check_interval = atoi(optarg);
                break;

            case 'x':
                proxy = optarg;
                break;

            case 'y':
                proxy_auth = optarg;
                break;

            case 'v':
                verbose++;
                break;

            case 'V':
                version();
                return 1;

            case 'h':
            default:
                usage();
                return 1;
        }
    }

    mot.timeout = check_interval;
        mot.proxy = proxy;
    mot.proxy_authentication = proxy_auth;
    mot.user_agent = "rsstail " VERSION ", (C) 2006-2007 by folkert@vanheusden.com";

    if (n_url == 0)
    {
        fprintf(stderr, "Please give the URL of the RSS feed to check with the '-u' parameter.\n");
        return 1;
    }

    data_size = sizeof(mrss_t *) * n_url;
    data_prev = (mrss_t **)malloc(data_size);
    data_cur  = (mrss_t **)malloc(data_size);
    if (!data_prev || !data_cur)
    {
        fprintf(stderr, "Cannot allocate memory\n");
        return 2;
    }

    memset(data_prev, 0x00, data_size);
    memset(data_cur , 0x00, data_size);

    if (verbose)
    {
        int loop;
        fprintf(stderr, "Monitoring RSS feeds:\n");
        for(loop=0; loop<n_url; loop++)
            fprintf(stderr, "\t%s\n", url[loop]);
        fprintf(stderr, "Check interval: %d\n", check_interval);
    }

    for(;;)
    {
        mrss_error_t err_read;
        mrss_item_t *item_cur = NULL;
        time_t cur_last_changed;
        int n_shown = 0;

        if (verbose)
            fprintf(stderr, "Retrieving RSS feed '%s'...\n", url[cur_url]);

        if ((err_read = mrss_get_last_modified(url[cur_url], &cur_last_changed)) != MRSS_OK)
        {
            if (err_read == MRSS_ERR_POSIX)
            {
                if (errno == EINPROGRESS)
                {
                    fprintf(stderr, "Time-out while connecting to RSS feed, continuing\n");
                    goto goto_next_url;
                }
            }

            fprintf(stderr, "Error reading RSS feed: %s\n", mrss_strerror(err_read));

            if (no_error_exit)
                goto goto_next_url;
            else
                return 2;
        }

        if (cur_last_changed == last_changed && cur_last_changed != 0)
        {
            if (verbose)
                fprintf(stderr, "Feed did not change since last check.\n");
            goto goto_next_url;
        }
        last_changed = cur_last_changed;

        if ((err_read = mrss_parse_url_with_options(url[cur_url], &data_cur[cur_url], &mot)) != MRSS_OK)
        {
            if (err_read == MRSS_ERR_POSIX)
            {
                if (errno == EINPROGRESS)
                {
                    fprintf(stderr, "Time-out while connecting to RSS feed, continuing\n");
                    goto goto_next_url;
                }
            }
            else if (err_read == MRSS_ERR_PARSER && continue_on_error)
            {
                fprintf(stderr, "Error reading RSS feed: %s\n", mrss_strerror(err_read));
                goto goto_next_url;
            }

            fprintf(stderr, "Error reading RSS feed: %s\n", mrss_strerror(err_read));
            if (no_error_exit)
                goto goto_next_url;
            else
                return 2;
        }

        item_cur = data_cur[cur_url] -> item;
        rss_title = data_cur[cur_url] -> title;

        if( !convert_init(cc, data_cur[cur_url]->encoding, convert_system_enc()) )
        {
            fprintf(stderr, "\nERROR: iconv initialization error.\n" );
        }

        while(item_cur)
        {
            if ((data_prev[cur_url] && is_new_record(data_prev[cur_url] -> item, item_cur) != -1) ||
                (!data_prev[cur_url]))
            {
#if 0
                if (/* pubdate */ < max_age && max_age != -1)
                    continue;
#endif

                if ((!data_prev[cur_url]) && n_shown >= show_n && show_n != -1)
                {
                    item_cur = item_cur -> next;
                    continue;
                }
                n_shown++;

                if ((show_link + show_description + show_pubdate + show_author + show_comments ) > 1 && !notify_friendly )
                    printf("\n");

                if (show_timestamp)
                {
                    time_t now = time(NULL);
                    struct tm *now_tm = localtime(&now);

                    printf("%04d/%02d/%02d %02d:%02d:%02d  ",
                            now_tm -> tm_year + 1900,
                            now_tm -> tm_mon + 1,
                            now_tm -> tm_mday,
                            now_tm -> tm_hour,
                            now_tm -> tm_min,
                            now_tm -> tm_sec);
                }

                if (show_pubdate && item_cur -> pubDate != NULL)
                {
                    if ( notify_friendly )
                    {
                        char* new_date_str = convert_pub_date(item_cur->pubDate);
                        printf("%s%s ", no_heading?" ":"Pub.date: ", new_date_str);
                        free(new_date_str);
                    }
                    else
                    {
                        printf("%s%s\n", no_heading?" ":"Pub.date: ", item_cur -> pubDate);
                    }
                }

                if (heading)
                {
                    printf(" %s", heading);
                }

                if ( notify_friendly )
                {
                    if ( rss_title )
                    {
                        conv_rss_title = convert(cc, rss_title);
                        printf("%s*%s* ", no_heading?" ":"RSS Title: ", conv_rss_title);
                        free(conv_rss_title);
                    }
                }

                if (item_cur -> title != NULL)
                {
                    conv_title = convert(cc, item_cur->title);
                    printf("%s%s%s", no_heading?" ":"Title: ", conv_title, (notify_friendly?" ":"\n"));
                    free(conv_title);
                }

                if (show_link && item_cur -> link != NULL)
                {
                    if ( notify_friendly )
                    {
                        printf("%s<a href=\"%s\">Link</a>\n", no_heading?" ":"Link: ", item_cur -> link );
                    }
                    else
                    {
                        printf("%s%s\n", no_heading?" ":"Link: ", item_cur -> link );
                    }
                }
                else
                {
                    if ( notify_friendly )
                    {
                        printf("\n"); //crlf without Link html tag
                    }
                }

                if (show_description && item_cur -> description != NULL)
                {
                    if (strip_html)
                    {
                        char *stripped = remove_html_tags(item_cur -> description);

                        if (bytes_limit != 0 && bytes_limit < strlen(stripped))
                            stripped[bytes_limit] = 0x00;

                        conv_description = convert(cc, stripped);
                        printf("%s%s\n", no_heading?" ":"Description: ", conv_description);
                        free(conv_description);

                        free(stripped);
                    }
                    else
                    {
                        if (bytes_limit != 0 && bytes_limit < strlen(item_cur -> description))
                            (item_cur -> description)[bytes_limit] = 0x00;

                        conv_description = convert(cc, item_cur->description);
                        printf("%s%s\n", no_heading?" ":"Description: ", conv_description);
                        free(conv_description);
                    }
                }

                if (show_author && item_cur -> author != NULL)
                {
                    conv_author = convert(cc, item_cur->author);
                    printf("%s%s\n", no_heading?" ":"Author: ", conv_author);
                    free(conv_author);
                }

                if (show_comments && item_cur -> comments != NULL)
                {
                    if (bytes_limit != 0 && bytes_limit < strlen(item_cur -> comments))
                        (item_cur -> comments)[bytes_limit] = 0x00;

                    conv_comments = convert(cc, item_cur->comments);
                    printf("%s%s\n", no_heading?" ":"Comments: ", conv_comments);
                    free(conv_comments);
                }
            }

            item_cur = item_cur -> next;
        }

        convert_close(cc);

        if (data_prev[cur_url])
        {
            mrss_error_t err_free = mrss_free(data_prev[cur_url]);

            if (err_free != MRSS_OK)
            {
                fprintf(stderr, "Error freeing up memory: %s\n", mrss_strerror(err_read));
                if (no_error_exit)
                    goto goto_next_url;
                else
                    return 2;
            }
        }

        data_prev[cur_url] = data_cur[cur_url];
        data_cur[cur_url] = NULL;

goto_next_url:
        cur_url++;
        if (cur_url == n_url)
            cur_url = 0;

        fflush(stdout);

        if (one_shot)
            break;

        if (verbose > 2)
            fprintf(stderr, "Sleeping...\n");
        sleep(check_interval / n_url);
    }

    return 0;
}
